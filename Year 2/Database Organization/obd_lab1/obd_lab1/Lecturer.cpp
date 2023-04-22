#include "Lecturer.h"
#include "GarbageCollector.h"
#include "CommonFileFunc.h"
#include "ScientificPublication.h"

#include <fstream>
#include <string>
#include <iostream>

const int INDEX_TABLE_CAPACITY = 20;

void lecturer::merge(lecturer::LecturerIndex array[], int left, int mid, int right)
{
	int left_array_length = mid - left + 1;
	int right_array_length = right - mid;

	// Create temp arrays
	auto* left_array = new LecturerIndex[left_array_length],
		* right_array = new LecturerIndex[right_array_length];

	for (int i = 0; i < left_array_length; i++)
		left_array[i] = array[left + i];
	for (int j = 0; j < right_array_length; j++)
		right_array[j] = array[mid + 1 + j];

	int index_left_array = 0,
		index_right_array = 0,
		index_merged_array = left;

	while (index_left_array < left_array_length && index_right_array < right_array_length)
	{
		if (left_array[index_left_array].id < right_array[index_right_array].id)
		{
			array[index_merged_array] = left_array[index_left_array];
			index_left_array++;
			index_merged_array++;
		}
		else
		{
			array[index_merged_array] = right_array[index_right_array];
			index_right_array++;
			index_merged_array++;
		}
	}

	while (index_left_array < left_array_length)
	{
		array[index_merged_array] = left_array[index_left_array];
		index_left_array++;
		index_merged_array++;
	}

	while (index_right_array < right_array_length)
	{
		array[index_merged_array] = right_array[index_right_array];
		index_right_array++;
		index_merged_array++;
	}

	delete[] left_array;
	delete[] right_array;
}
void lecturer::mergeSort(lecturer::LecturerIndex array[], int begin, int end)
{
	if (begin >= end)
		return;

	int mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

lecturer::LecturerIndex::LecturerIndex()
{
	this->id = -1;
	this->position = 0;
	this->deleted_flag = false;
}
lecturer::LecturerIndex::LecturerIndex(int id)
{
	this->id = id;
	this->position = -1;
	this->deleted_flag = false;
}
lecturer::LecturerIndexTable::LecturerIndexTable()
{
	for (int i = 0; i <= INDEX_TABLE_CAPACITY; i++)
	{
		this->idx_cells[i];
	}
	this->cur_pos = -1;
}
lecturer::Lecturer::Lecturer()
{
	this->id = -1;
	this->first_record_book = -1;
	this->scientific_publications_amount = 0;
	this->age = -1;
	this->deleted_flag = false;
}
lecturer::Lecturer::Lecturer(int id, char* name, char* surname, char* academic_degree, int age)
{
	this->id = id;
	strcpy_s(this->name, name);
	strcpy_s(this->surname, surname);
	strcpy_s(this->academic_degree, academic_degree);
	this->first_record_book = -1;
	this->scientific_publications_amount = 0;
	this->age = age;
	this->deleted_flag = false;
}



lecturer::LecturerIndex lecturer::LecturerIndexTable::getPositionOfLecturerById(int id)
{
	for (int i = 0; i <= this->cur_pos; i++)
	{
		if (this->idx_cells[i].id == id && this->idx_cells[i].deleted_flag != true) return this->idx_cells[i];
	}
	return LecturerIndex(-1);
}
int lecturer::LecturerIndexTable::getIndexPositionOfLecturerById(int id)
{
	for (int i = 0; i <= this->cur_pos; i++)
	{
		if (this->idx_cells[i].id == id) return i;
	}
	return -1;
}
void lecturer::LecturerIndexTable::sortById()
{
	mergeSort(this->idx_cells, 0, this->cur_pos);
}
void lecturer::LecturerIndexTable::shiftUp(int pos)
{
	lecturer::LecturerIndex temp = this->idx_cells[pos];
	for (int i = pos; i < this->cur_pos; i++)
		this->idx_cells[i] = this->idx_cells[i + 1];
	this->idx_cells[this->cur_pos] = temp;
	this->idx_cells[this->cur_pos].deleted_flag = true;
}
bool lecturer::LecturerIndexTable::add(int id)
{
	if (this->cur_pos == 19)
		return false;
	this->cur_pos++;
	this->idx_cells[this->cur_pos] = LecturerIndex(id);
	this->idx_cells[this->cur_pos].position = this->cur_pos;
	this->sortById();
	return true;
}
int lecturer::LecturerIndexTable::findFirstDeletedLectureIdx()
{
	for (int i = 0; i <= this->cur_pos; i++)
		if (this->idx_cells[i].deleted_flag == true) return i;
}

void lecturer::Lecturer::del()
{
	this->deleted_flag = true;
}
void lecturer::Lecturer::print()
{
	std::cout << this->name << " | ";
	std::cout << this->surname << " | ";
	std::cout << this->id << " | ";
	std::cout << this->academic_degree << " | ";
	std::cout << this->scientific_publications_amount << " | ";
	std::cout << this->age << "\n";
}

//get-m
lecturer::Lecturer lecturer::getLecturerById(int id, char* FILE_NAME, LecturerIndexTable idx_table)
{
	int pos = idx_table.getPositionOfLecturerById(id).position;
	Lecturer buffer;
	if (pos == -1)
		return buffer;
	return readFromFileStructure<Lecturer>(FILE_NAME, pos);
}
//insert-m
void lecturer::insertLecturer(int id, char* name, char* surname, char* academic_degree, int age,
	char* FILE_NAME, char* GARBAGE_FILE_NAME, LecturerIndexTable& idx_table)
{
	lecturer::Lecturer lect(id, name, surname, academic_degree, age);
	int garbage_idx_pos = garbage::getGarbageCollectorLastRecord(GARBAGE_FILE_NAME, 0);
	if (garbage_idx_pos != -1)
	{
		int pos = idx_table.idx_cells[garbage_idx_pos].position;
		lecturer::LecturerIndex temp(id);
		temp.position = pos;
		idx_table.idx_cells[garbage_idx_pos] = temp;
		writeToFileStructure<lecturer::Lecturer>(lect, FILE_NAME, pos);
		return;
	}
	if(!idx_table.add(id))
	{
		std::cout << "Index table overflow!";
		return;
	}
	writeToFileStructure<lecturer::Lecturer>(lect, FILE_NAME, -1);

}
//update-m
void lecturer::updateLecturer(int id, char* academic_degree, int age,
	char* FILE_NAME, LecturerIndexTable& idx_table)
{
	LecturerIndex idx = idx_table.getPositionOfLecturerById(id);
	Lecturer lect = readFromFileStructure<lecturer::Lecturer>(FILE_NAME, idx.position);
	if (lect.id == -1)
	{
		std::cout << "There is no lecturer with such an ID.\n\n";
		return;
	}
	strcpy_s(lect.academic_degree, academic_degree);
	lect.age = age;
	writeToFileStructure<lecturer::Lecturer>(lect, FILE_NAME, idx.position);
	return;
}
//del-m
void lecturer::deleteLecturerById(int id, char* FILE_NAME, char* PUBLICATIONS_FILE_NAME, char* GARBAGE_FILE_NAME, LecturerIndexTable& idx_table)
{
	lecturer::Lecturer lect = lecturer::getLecturerById(id, FILE_NAME, idx_table);
	if (lect.deleted_flag == true || lect.first_record_book == -1)
	{
		std::cout << "There is no such a lecturer.\n\n";
		return;
	}
	int idx_pos = idx_table.getIndexPositionOfLecturerById(id);
	int pos = idx_table.getPositionOfLecturerById(id).position;
	idx_table.idx_cells[idx_pos].deleted_flag = true;
	lect.deleted_flag = true;
	idx_table.shiftUp(idx_pos);
	writeToFileStructure<lecturer::Lecturer>(lect, FILE_NAME, pos);
	garbage::GarbageCollector garb_col = readFromFileStructure<garbage::GarbageCollector>(GARBAGE_FILE_NAME, 0);
	garb_col.add(idx_pos);
	writeToFileStructure<garbage::GarbageCollector>(garb_col, GARBAGE_FILE_NAME, 0);


	int cur_pos = lect.first_record_book;
	scpu::Publication buffer;
	std::fstream file(PUBLICATIONS_FILE_NAME, std::fstream::in | std::fstream::out | std::fstream::binary);
	garbage::GarbageCollector garb_publ = readFromFileStructure<garbage::GarbageCollector>(GARBAGE_FILE_NAME, 1);
	for (int i = 0; i < lect.scientific_publications_amount; i++)
	{
		file.clear();
		file.seekg(sizeof(buffer) * cur_pos, std::ifstream::beg);
		file.read((char*)&buffer, sizeof(buffer));
		if (buffer.deleted_flag == false)
		{
			garb_publ.add(cur_pos);
			buffer.deleted_flag = true;
			writeToFileStructure<scpu::Publication>(buffer, PUBLICATIONS_FILE_NAME, cur_pos);
		}
		else if (buffer.deleted_flag == true)
			i--;
		cur_pos = buffer.next_book_by_the_lecturer;
	}
	file.close();
	writeToFileStructure<garbage::GarbageCollector>(garb_publ, GARBAGE_FILE_NAME, 1);
	return;
}

void lecturer::printLecturerById(int id, char* FILE_NAME, LecturerIndexTable idx_table)
{
	lecturer::Lecturer lect = lecturer::getLecturerById(id, FILE_NAME, idx_table);
	if (lect.id != -1)
	{
		std::cout << "NAME | ";
		std::cout << "SURNAME | ";
		std::cout << "ID | ";
		std::cout << "ACADEMIC DEGREE | ";
		std::cout << "SCIENTIFIC PUBLICATIONS AMOUNT | ";
		std::cout << "AGE\n";
		lect.print();
	}
	else std::cout << "There is no lecturer with such an ID.\n\n";
	return;
}
void lecturer::printAllLecturers(char* FILE_NAME)
{
	std::ifstream index_file(FILE_NAME, std::ifstream::in | std::ifstream::binary);
	Lecturer buffer;
	if (index_file.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "There are no lecturers.\n\n";
		return;
	}
	std::cout << "NAME | ";
	std::cout << "SURNAME | ";
	std::cout << "ID | ";
	std::cout << "ACADEMIC DEGREE | ";
	std::cout << "SCIENTIFIC PUBLICATIONS AMOUNT | ";
	std::cout << "AGE\n";
	while (!index_file.eof())
	{
		index_file.read((char*)&buffer, sizeof(buffer));
		if (!index_file.good()) 
			break;
		if (buffer.deleted_flag != false)
			continue;
		buffer.print();
	}
	index_file.close();
}


