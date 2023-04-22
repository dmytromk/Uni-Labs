#include "ScientificPublication.h"

#include "Lecturer.h"
#include "CommonFileFunc.h"
#include "GarbageCollector.h"

#include <fstream>
#include <string>
#include <iostream>

scpu::Publication::Publication()
{
	this->id = -1;
	this->lecturer_id = -1;
	strcpy_s(this->name, " ");
	strcpy_s(this->field, " ");
	this->publication_year = -1;
	this->next_book_by_the_lecturer = -1;
	this->prev_book_by_the_lecturer = -1;
	this->deleted_flag = false;
}
scpu::Publication::Publication(int id, int lecturer_id, char* name, char* field, int publication_year)
{
	this->id = id;
    this->lecturer_id = lecturer_id;
	strcpy_s(this->name, name);
	strcpy_s(this->field, field);
    this->publication_year = publication_year;
    this->next_book_by_the_lecturer = -1;
	this->prev_book_by_the_lecturer = -1;
    this->deleted_flag = false;
}
void scpu::Publication::print()
{
    std::cout << this->name << " | ";
	std::cout << this->id << " | ";
	std::cout << this->lecturer_id << " | ";
	std::cout << this->field << " | ";
	std::cout << this->publication_year << "\n";
}

//get-s
scpu::Publication scpu::getPublicationByIdAndLecturerId(int id, int lecturer_id, 
	char* PUBLICATIONS_FILE_NAME, char* LECTURER_FILE_NAME, lecturer::LecturerIndexTable idx_table)
{
	{
		lecturer::Lecturer lecturer = lecturer::getLecturerById(lecturer_id, LECTURER_FILE_NAME, idx_table);
		scpu::Publication buffer;
		if (lecturer.id == -1)
			return buffer;
		int pos = lecturer.first_record_book;
		int amount = lecturer.scientific_publications_amount;
		std::ifstream file(PUBLICATIONS_FILE_NAME, std::ifstream::in | std::ifstream::binary);
		file.seekg(sizeof(buffer) * pos, std::ifstream::beg);
		for (int i = 0; i <= amount; i++)
		{
			file.read((char*)&buffer, sizeof(buffer));
			if (buffer.deleted_flag == true)
			{
				i--;
				continue;
			}
			if (buffer.id == id)
				return buffer;
			file.seekg(sizeof(buffer) * buffer.next_book_by_the_lecturer, std::ifstream::beg);

		}
		file.close();
		scpu::Publication temp;
		return temp;
	}
}
//insert-s
void scpu::insertPublication(int id, int lecturer_id, char* name, char* field, int publication_year,
	char* FILE_NAME, char* LECTURE_FILE_NAME, char* GARBAGE_FILE_NAME, lecturer::LecturerIndexTable& idx_table)
{
	int garb = garbage::getGarbageCollectorLastRecord(GARBAGE_FILE_NAME, 1);
	lecturer::LecturerIndex idx = idx_table.getPositionOfLecturerById(lecturer_id);
	lecturer::Lecturer lect = readFromFileStructure<lecturer::Lecturer>(LECTURE_FILE_NAME, idx.position);
	if (lect.id == -1)
	{
		std::cout << "There is no lecturer with such an ID\n\n";
		return;
	}
	scpu::Publication publ(id, lecturer_id, name, field, publication_year);
	scpu::Publication buffer;
	std::fstream file(FILE_NAME, std::fstream::in | std::fstream::out | std::fstream::binary);
	file.seekg(0, file.end);
	int length = garb;

	if (garb == -1)
	{
		length = file.tellg();
		length = length / sizeof(publ);
	}

	int cur_pos = lect.first_record_book;
	if (cur_pos == -1)
	{
		lect.first_record_book = length;
		lect.scientific_publications_amount++;
		file.write((char*)&publ, sizeof(publ));
		file.close();
		writeToFileStructure<lecturer::Lecturer>(lect, LECTURE_FILE_NAME, idx.position);
		return;
	}

	for (int i = 0; i < lect.scientific_publications_amount; i++)
	{
		file.clear();
		file.seekg(sizeof(buffer) * cur_pos, std::ifstream::beg);
		file.read((char*)&buffer, sizeof(buffer));
		if (buffer.deleted_flag == true)
		{
			i--;
			continue;
		}
		cur_pos = buffer.next_book_by_the_lecturer;
	}
	buffer.next_book_by_the_lecturer = length;

	int temp = static_cast<int>(sizeof(buffer));
	file.seekg(-temp, std::ifstream::cur);

	int temp_pos = file.tellg()/ sizeof(publ);
	publ.prev_book_by_the_lecturer = temp_pos;

	file.write((char*)&buffer, sizeof(buffer));
	file.seekg(0, file.end);
	file.write((char*)&publ, sizeof(publ));
	file.close();
	lect.scientific_publications_amount++;
	writeToFileStructure<lecturer::Lecturer>(lect, LECTURE_FILE_NAME, idx.position);
	return;
}
//update-s
void scpu::updatePublicationById(int id, char* name, char* FILE_NAME, lecturer::LecturerIndexTable& idx_table)
{
	std::fstream file(FILE_NAME, std::fstream::in | std::fstream::out | std::fstream::binary);
	scpu::Publication buffer;
	if (file.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "There are no books.\n\n";
		return;
	}
	while (!file.eof())
	{
		file.read((char*)&buffer, sizeof(buffer));
		if (!file.good())
			break;
		if (buffer.id == id)
		{
			if (buffer.deleted_flag == true)
			{
				std::cout << "This books is deleted.";
				return;
			}
			strcpy_s(buffer.name, name);
			int temp = static_cast<int>(sizeof(buffer));
			file.seekg(-temp, std::ifstream::cur);
			file.write((char*)&buffer, sizeof(buffer));
			file.close();
			return;
		}
		continue;
	}
	file.close();
	std::cout << "Book with such an ID doesn't exist.\n\n";
	return;
}
//del-s
void scpu::delPublicationById(int id, int lecturer_id, char* FILE_NAME, char* LECTURER_FILE_NAME, char* GARBAGE_FILE, lecturer::LecturerIndexTable& idx_table)
{
	int lect_pos = idx_table.getPositionOfLecturerById(lecturer_id).position;
	lecturer::Lecturer lect = lecturer::getLecturerById(lecturer_id, LECTURER_FILE_NAME, idx_table);
	if (lect.deleted_flag == true || lect.first_record_book == -1)
	{
		std::cout << "There is no such a publication.\n\n";
		return;
	}

	std::fstream file(FILE_NAME, std::fstream::in | std::fstream::out | std::fstream::binary);
	scpu::Publication buffer;
	int cur_pos = lect.first_record_book;
	for (int i = 0; i < lect.scientific_publications_amount; i++)
	{
		file.clear();
		file.seekg(sizeof(buffer) * cur_pos, std::ifstream::beg);
		file.read((char*)&buffer, sizeof(buffer));
		if (buffer.id == id)
		{
			if (buffer.deleted_flag == true)
			{
				std::cout << "This publication is already deleted.\n\n";
				return;
			}
			buffer.deleted_flag = true;
			if (cur_pos == lect.first_record_book)
				lect.first_record_book = buffer.next_book_by_the_lecturer;
			file.close();

			if (buffer.prev_book_by_the_lecturer != -1)
			{
				scpu::Publication temp1 = readFromFileStructure<scpu::Publication>(FILE_NAME, buffer.prev_book_by_the_lecturer);
				temp1.next_book_by_the_lecturer = buffer.next_book_by_the_lecturer;
				writeToFileStructure<scpu::Publication>(temp1, FILE_NAME, buffer.prev_book_by_the_lecturer);
			}

			//rewrite the next
			if (buffer.next_book_by_the_lecturer != -1)
			{
				scpu::Publication temp2 = readFromFileStructure<scpu::Publication>(FILE_NAME, buffer.next_book_by_the_lecturer);
				temp2.prev_book_by_the_lecturer = buffer.prev_book_by_the_lecturer;
				writeToFileStructure<scpu::Publication>(temp2, FILE_NAME, buffer.next_book_by_the_lecturer);
			}

			lect.scientific_publications_amount--;
			buffer.deleted_flag = true;
			garbage::GarbageCollector garb = readFromFileStructure<garbage::GarbageCollector>(GARBAGE_FILE, 1);
			garb.add(cur_pos);
			writeToFileStructure<lecturer::Lecturer>(lect, LECTURER_FILE_NAME, lect_pos);
			writeToFileStructure<garbage::GarbageCollector>(garb, GARBAGE_FILE, 1);
			writeToFileStructure<scpu::Publication>(buffer, FILE_NAME, cur_pos);
			return;
		}
		if (buffer.deleted_flag == true)
			i--;
		cur_pos = buffer.next_book_by_the_lecturer;
	}
	std::cout << "There is no such a book\n\n";
	return;
}

void scpu::printPublicationByIdAndLectureId(int id, int lecturer_id, char* PUBLICATION_FILE_NAME, 
	char* LECTURER_FILE_NAME, lecturer::LecturerIndexTable idx_table)
{
	scpu::Publication publication = getPublicationByIdAndLecturerId(id, lecturer_id, PUBLICATION_FILE_NAME, LECTURER_FILE_NAME, idx_table);
	if (publication.id != -1)
	{
		std::cout << "NAME | ";
		std::cout << "ID | ";
		std::cout << "LECTURER_ID | ";
		std::cout << "FIELD | ";
		std::cout << "PUBLICATION_YEAR\n";
		publication.print();
	}
	else std::cout << "Incorrect input!\n\n";
}
void scpu::printPublicationByTheSameLecturer(int lecturer_id, char* PUBLICATION_FILE_NAME,
	char* LECTURER_FILE_NAME, lecturer::LecturerIndexTable idx_table)
{
	lecturer::Lecturer lecturer = lecturer::getLecturerById(lecturer_id, LECTURER_FILE_NAME, idx_table);
	scpu::Publication buffer;
	if (lecturer.id == -1)
		std::cout << "There is no lecturer with such an id.\n\n";
	int pos = lecturer.first_record_book;
	int amount = lecturer.scientific_publications_amount;
	std::ifstream file(PUBLICATION_FILE_NAME, std::ifstream::in | std::ifstream::binary);
	file.seekg(sizeof(buffer) * pos, std::ifstream::beg);
	std::cout << "NAME | ";
	std::cout << "ID | ";
	std::cout << "LECTURER_ID | ";
	std::cout << "FIELD | ";
	std::cout << "PUBLICATION_YEAR\n";
	for (int i = 1; i <= amount; i++)
	{
		file.read((char*)&buffer, sizeof(buffer));
		if (buffer.deleted_flag == true)
		{
			i--;
			continue;
		}
		buffer.print();
		file.seekg(sizeof(buffer) * buffer.next_book_by_the_lecturer, std::ifstream::beg);
	}
	file.close();
}
void scpu::printAllPublications(char* PUBLICATION_FILE_NAME)
{
	std::ifstream file(PUBLICATION_FILE_NAME, std::ifstream::in | std::ifstream::binary);
	Publication buffer;
	if (file.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "There are no publications.\n\n";
		return;
	}
	std::cout << "NAME | ";
	std::cout << "ID | ";
	std::cout << "LECTURER_ID | ";
	std::cout << "FIELD | ";
	std::cout << "PUBLICATION_YEAR\n";
	while (!file.eof())
	{
		file.read((char*)&buffer, sizeof(buffer));
		if (!file.good())
			break;
		if (buffer.deleted_flag != false)
			continue;
		if(buffer.id != -1) buffer.print();
	}
	file.close();
}


