#pragma once

#include "Lecturer.h"

#include <string>

namespace scpu
{
    struct Publication
    {
        int id;
        int lecturer_id;
        char name[20];
        char field[20];
        int publication_year;
        int next_book_by_the_lecturer;
        int prev_book_by_the_lecturer;
        bool deleted_flag;

        Publication();
        Publication(int id, int lecturer_id, char* name, char* field, int publication_year);
        void print();
    };

    //get-s
    scpu::Publication getPublicationByIdAndLecturerId(int id, int lecturer_id, char* PUBLICATIONS_FILE_NAME, 
        char* LECTURER_FILE_NAME, lecturer::LecturerIndexTable idx_table);
    //insert-m
    void insertPublication(int id, int lecturer_id, char* name, char* field, int publication_year,
        char* FILE_NAME, char* LECTURE_FILE_NAME, char* GARBAGE_FILE_NAME, lecturer::LecturerIndexTable& idx_table);
    //update-s
    void updatePublicationById(int id, char* name, char* FILE_NAME, lecturer::LecturerIndexTable& idx_table);
    //del-s
    void delPublicationById(int id, int lecturer_id, char* FILE_NAME, char* LECTURER_FILE_NAME, char* GARBAGE_FILE, lecturer::LecturerIndexTable& idx_table);

    void printPublicationByIdAndLectureId(int id, int lecturer_id, char* PUBLICATION_FILE_NAME,
        char* LECTURER_FILE_NAME, lecturer::LecturerIndexTable idx_table);
    void printPublicationByTheSameLecturer(int lecturer_id, char* PUBLICATIONS_FILE_NAME,
        char* LECTURER_FILE_NAME, lecturer::LecturerIndexTable idx_table);
    void printAllPublications(char* PUBLICATIONS_FILE_NAME);

}