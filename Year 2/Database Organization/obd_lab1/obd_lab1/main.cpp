#include "Lecturer.h"
#include "ScientificPublication.h"
#include "GarbageCollector.h"
#include "CommonFileFunc.h"

#include <stdio.h>
#include <fstream>
#include <iostream>




bool menu(char* GARBAGE_COLLECTOR_FILE, char* LECTURER_FILE, char* LECTURER_INDEX_FILE, char* SCIENTIFIC_PUBLICATIONS_FILE, lecturer::LecturerIndexTable& index_table)
{
    int option;

    std::cout << "Choose the option:\n"; 
    std::cout << "1 - Add lecturer (insert-m)\n"; 
    std::cout << "2 - Update lecturer (update-m)\n"; 
    std::cout << "3 - Delete lecturer (del-m)\n"; 
    std::cout << "4 - Find lecturer by ID (get-m)\n";
    std::cout << "5 - Print information about all the lecturers\n"; 
    std::cout << "6 - Add scientific publication (insert-s)\n"; 
    std::cout << "7 - Update scientific publication (update-s)\n"; 
    std::cout << "8 - Delete scientific publication (del-s)\n"; 
    std::cout << "9 - Find scientific publication by ID and lecturer ID (get-s)\n"; 
    std::cout << "10 - Print information about all the scientific publications\n"; 
    std::cout << "11 - Print information about all the scientific publications by the same lecturer\n"; 
    std::cout << "12 - Clear data from all files\n"; 
    std::cout << "13 - Clear data from publication files\n";

    std::cin >> option;

    //insert-m
    if (option == 1)
    {
        int id, age;
        char name[20], surname[20], academic_degree[20];
        std::cout << "Enter the id, name, surname, academic_degree and age of the lecturer\n";
        std::cin >> id >> name >> surname >> academic_degree >> age;
        lecturer::insertLecturer(id, name, surname, academic_degree, age,
            LECTURER_FILE, GARBAGE_COLLECTOR_FILE, index_table);
        writeToFileStructure<lecturer::LecturerIndexTable>(index_table, LECTURER_INDEX_FILE, 0);
        return true;
    }

    //update-m
    else if (option == 2)
    {
        int id, age;
        char academic_degree[20];
        std::cout << "Enter the id, age and academic_degree of the lecturer\n";
        std::cin >> id >> age >> academic_degree;
        lecturer::updateLecturer(id, academic_degree, age, LECTURER_FILE, index_table);
        return true;
    }

    //del-m
    else if (option == 3)
    {
        int id;
        std::cout << "Enter the id of the lecturer\n";
        std::cin >> id;
        lecturer::deleteLecturerById(id, LECTURER_FILE, SCIENTIFIC_PUBLICATIONS_FILE, GARBAGE_COLLECTOR_FILE, index_table);
        return true;
    }

    //get-m
    else if (option == 4)
    {
        int id;
        std::cout << "Please, enter the lecturer's ID:\n";
        std::cin >> id;
        lecturer::printLecturerById(id, LECTURER_FILE, index_table);
        return true;
    }

    //Print all lecturers
    else if (option == 5)
    {
        lecturer::printAllLecturers(LECTURER_FILE);
        return true;
    }

    //insert-s
    else if (option == 6)
    {
        int id, lecturer_id, publication_year;
        char name[20], field[20];
        std::cout << "Enter the id, lecturer_id, name, field and year of publication\n";
        std::cin >> id >> lecturer_id >> name >> field >> publication_year;
        scpu::insertPublication(id, lecturer_id, name, field, publication_year,
            SCIENTIFIC_PUBLICATIONS_FILE, LECTURER_FILE, GARBAGE_COLLECTOR_FILE, index_table);
        return true;
    }

    //update-s
    else if (option == 7)
    {
        int id;
        char name[20];
        std::cout << "Enter the id and new name for the publication\n";
        std::cin >> id >> name;
        scpu::updatePublicationById(id, name, SCIENTIFIC_PUBLICATIONS_FILE, index_table);
        return true;
    }

    //del-s
    else if (option == 8)
    {
        int id, lecturer_id;
        std::cout << "Enter the id of the publication and lecturer\n";
        std::cin >> id >> lecturer_id;
        scpu::delPublicationById(id, lecturer_id, SCIENTIFIC_PUBLICATIONS_FILE, LECTURER_FILE, GARBAGE_COLLECTOR_FILE, index_table);
        return true;
    }

    else if (option == 9)
    {
        int lecturer_id, publication_id;
        std::cout << "Please, enter the lecturer's ID and the publication id:\n";
        std::cin >> lecturer_id >> publication_id;
        scpu::printPublicationByIdAndLectureId(publication_id, lecturer_id, 
            SCIENTIFIC_PUBLICATIONS_FILE, LECTURER_FILE, index_table);
        return true;
    }

    else if (option == 10)
    {
        scpu::printAllPublications(SCIENTIFIC_PUBLICATIONS_FILE);
        return true;
    }

    else if (option == 11)
    {
        int lecturer_id;
        std::cout << "Please, enter the lecturer's ID:\n";
        std::cin >> lecturer_id;
        scpu::printPublicationByTheSameLecturer(lecturer_id, SCIENTIFIC_PUBLICATIONS_FILE, LECTURER_FILE, index_table);
        return true;
    }

    else if (option == 12)
    {
        std::ofstream lect;
        lect.open(LECTURER_FILE, std::ofstream::out | std::ofstream::trunc);
        lect.close();

        std::ofstream lect_idx;
        lect_idx.open(LECTURER_INDEX_FILE, std::ofstream::out | std::ofstream::trunc);
        lect_idx.close();

        std::ofstream publ;
        publ.open(SCIENTIFIC_PUBLICATIONS_FILE, std::ofstream::out | std::ofstream::trunc);
        publ.close();

        std::ofstream garb;
        garb.open(GARBAGE_COLLECTOR_FILE, std::ofstream::out | std::ofstream::trunc);
        garb.close();

        lecturer::LecturerIndexTable temp;
        index_table = temp;

        return true;
    }

    else if (option == 13)
    {
    std::ofstream publ;
    publ.open(SCIENTIFIC_PUBLICATIONS_FILE, std::ofstream::out | std::ofstream::trunc);
    publ.close();

    std::ofstream garb;
    garb.open(GARBAGE_COLLECTOR_FILE, std::ofstream::out | std::ofstream::trunc);
    garb.close();

    lecturer::LecturerIndexTable temp;
    index_table = temp;

    return true;
    }

    else return false;
}


int main()
{
    char GARBAGE_COLLECTOR_FILE[30] = "garbage_collector.dat";
    char LECTURER_FILE[30] = "lecturer.dat";
    char LECTURER_INDEX_FILE[30] = "lecturer.index";
    char SCIENTIFIC_PUBLICATIONS_FILE[30] = "scentific_publications.dat";

    garbage::garbageCollectorInitilialization(GARBAGE_COLLECTOR_FILE);

    lecturer::LecturerIndexTable index_table = readFromFileStructure<lecturer::LecturerIndexTable>(LECTURER_INDEX_FILE, -1);

    while (menu(GARBAGE_COLLECTOR_FILE, LECTURER_FILE, LECTURER_INDEX_FILE, SCIENTIFIC_PUBLICATIONS_FILE, index_table))
    {
        continue;
    }
    return 0;
}