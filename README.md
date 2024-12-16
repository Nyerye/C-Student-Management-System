# Student Management System

## Description

This is a C++ based program for managing student data. The program allows users to add student information, modify grades, search for students by name, display student records, and save the data to a file. It also includes functionality for reading student data from a file and performing average grade calculations.

The main features include:
- **Add a student**: Collect student data (name, ID, grades) and store it.
- **Search for a student by name**: Locate a student in the list by their full name.
- **Modify student grades**: Update the grades of an existing student.
- **Display all students**: Print a list of all students with their details.
- **Write student data to a file**: Save the student records to an output file.
- **Read student data from a file**: Import student records from an input file.
- **Exit**: Terminate the program.

## Table of Contents

1. [Features](#features)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Functionality Overview](#functionality-overview)
5. [File Structure](#file-structure)
6. [Contributing](#contributing)
7. [License](#license)

## Features

- **Student Management**: Organize student data including personal information and academic records.
- **File I/O Operations**: Support for saving and loading data from text files.
- **Grade Calculations**: Calculate and update student grade averages.
- **User-Friendly Interface**: Menu-driven interface for easy navigation and operation.

## Installation

To run the program locally, follow these steps:

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/your-username/student-management-system.git

2. Navigate to the directory
   ```bash
    cd student-management-system
3. Compile the code. 
   ```bash
    g++ -o studentManagement studentManagementFunctions.cpp
4. Run the program. 
   ```bash
    ./studentManagement

##Functionality Overview
###Adding a Student
The program prompts the user to enter the student's name, ID, and grades. Once entered, the student data is stored in a list.

###Searching for a Student
Users can search for a student by their full name. The program will return the student's details if found.

###Modifying Student Grades
Users can modify the grades of an existing student by searching for their name and entering new grade information.

###Displaying All Students
All student records will be displayed in a tabular format, including their names, IDs, and grades.

###Writing Data to a File
Student records can be saved to a file. This will allow you to persist the data across program runs.

###Reading Data from a File
Student data can be loaded from a pre-existing file into the program for editing or viewing.

