/*
* FILE									    : studentManagementFunctions.h
* PROJECT									: SENG1005 MAJOR ASSIGNMENT 2
* PROGRAMMER								: NICHOLAS REILLY
* FIRST VERSION								: 2024-12-03
* DESCRIPTION								: The file that will hold the protypes for structs, functions and calls for C libraries used.
* REFERENCING FOR MY EXTERNAL KNOWLEDGE     : Deitel, P., & Deitel, H. (2016). How to Program in C and C++ (8th ed.). Deitel & Associates Inc. && code from NReilly's Focus Assignment 6.
*/

#pragma once
//Defining the standard libraries we are importing for this project to work.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


//Defining the max amount of students to be read and the maximum length of a name to prevent buffer overflow.
#define MAX_STUDENTS 30
#define MAX_NAME_LENGTH 50
#define MAX_NUMBER_GRADES 5

//Struct Student.
typedef struct  {
    char name[MAX_NAME_LENGTH];
    int id;
    float grades[MAX_NUMBER_GRADES];
    float average;
}Student;

//Function prototypes.
errno_t openFile(FILE** file, const char* filename, const char* mode);
errno_t closeFile(FILE* file);
void writeStudentsToFile(Student students[], int studentCount);
void displayMenu();
void addStudent(Student students[], int* studentCount);
void displayStudents(Student students[], int studentCount);
int searchStudent(Student students[], int studentCount, const char searchName);
void modifyStudent(Student students[],int studentCount);
int readStudentsFromFile(Student students[], int* studentCount);
void averageCalc(Student* newStudent);
void modifyGradeAverage(Student students[], int index);
void modeSelect();