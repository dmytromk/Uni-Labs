#pragma once

#include "GarbageCollector.h"

#include<string>

namespace lecturer
{
    struct LecturerIndex
    {
        int id;
        int position;
        bool deleted_flag;
        LecturerIndex();
        LecturerIndex(int id);
    };
    struct LecturerIndexTable
    {
        LecturerIndex idx_cells[20];
        int cur_pos;
        LecturerIndexTable();
        void sortById();
        void shiftUp(int pos);
        bool add(int id);
        int findFirstDeletedLectureIdx();
        LecturerIndex getPositionOfLecturerById(int id);
        int getIndexPositionOfLecturerById(int id);
    };
    struct Lecturer
    {
        int id;
        char name[20];
        char surname[20];
        char academic_degree[20];
        int age;
        int first_record_book;
        int scientific_publications_amount;
        bool deleted_flag;

        Lecturer();
        Lecturer(int id, char* name, char* surname, char* academic_degree, int age);
        void del();
        void print();
    };

    void merge(LecturerIndex array[], int left, int mid, int right);
    void mergeSort(LecturerIndex array[], int begin, int end);

    //get-m
    Lecturer getLecturerById(int id, char* FILE_NAME, LecturerIndexTable idx_table);
    //insert-m
    void insertLecturer(int id, char* name, char* surname, char* academic_degree, int age,
        char* FILE_NAME, char* GARBAGE_FILE_NAME, LecturerIndexTable& idx_table);
    //update-m
    void updateLecturer(int id, char* academic_degree, int age,
        char* FILE_NAME, LecturerIndexTable& idx_table);
    //del-m
    void deleteLecturerById(int id, char* FILE_NAME, char* PUBLICATIONS_FILE_NAME, char* GARBAGE_FILE_NAME, LecturerIndexTable& idx_table);

    void printLecturerById(int ID, char* FILE_NAME, LecturerIndexTable idx_table);
    void printAllLecturers(char* FILE_NAME);
}
