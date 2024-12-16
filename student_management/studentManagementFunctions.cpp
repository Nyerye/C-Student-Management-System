/*
* FILE									    : studentManagementFunctions.cpp
* PROJECT									: SENG1005 MAJOR ASSIGNMENT 2
* PROGRAMMER								: NICHOLAS REILLY
* FIRST VERSION								: 2024-12-03
* DESCRIPTION								: The file that will hold the code for all of the functions used in the program.
* REFERENCING FOR MY EXTERNAL KNOWLEDGE     : Deitel, P., & Deitel, H. (2016). How to Program in C and C++ (8th ed.). Deitel & Associates Inc. && code from NReilly's Focus Assignment 6.
*/

//Calling the custom header file we made with libraries.
#include "studentManagementFunctions.h"

//
// FUNCTION :    openFile
// DESCRIPTION : This function finds the assigned file it needs to open and opens it. 
// PARAMETERS :  The file pointer to the address of the file pointer, the name of the file (const char array pointer), and the mode it will be opening it in (const char pointer).
// RETURNS :     EXIT_SUCCESS / EXIT_FAILURE depending on whether the process was successful. 
//
errno_t openFile(FILE** file, const char* filename, const char* mode) {
	errno_t err = fopen_s(file, filename, mode);
	if (err != 0 || *file == NULL) {
		perror("Error opening file");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


//
// FUNCTION :    closeFile
// DESCRIPTION : This function closed the already opened file. 
// PARAMETERS :  file, the reference file that the file pointer is pointing to. 
// RETURNS :     EXIT_SUCCESS / EXIT_FAILURE depending on whether the process was successful. 
//
errno_t closeFile(FILE* file) {
	if (fclose(file) != 0) {
		perror("Error closing file.");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


//
// FUNCTION	:		writeStudentsToFile
// DESCRIPTION  :   This function writes either the average score or sorted results (by grades or IDs) to a specified file.
// PARAMETERS :		Student students[], the struct array for the Student data type, and int studentCount, the total number of students actively in the array.				
// RETURNS :		nothing. 
//
void writeStudentsToFile(Student students[], int studentCount) {
	
	//Set the file pointer to be output.txt and open the file for writing.
	FILE* outputFile = NULL;
	openFile(&outputFile, "output.txt","w");
	if (outputFile == NULL) {
		printf("Error: Could not open file for writing.\n");
		return;
	}

	//Use a for loop to traverse the array index by index. Manually write the lines out for each piece of data to the file.
	for (int i = 0; i < studentCount; i++) {
		fprintf(outputFile, "Full Name: %s\n", students[i].name);
		fprintf(outputFile, "Student Number: %d\n", students[i].id);

		fprintf(outputFile, "Grades: ");
		for (int j = 0; j < 5; j++) {
			fprintf(outputFile, "%.2f ", students[i].grades[j]);
		}
		fprintf(outputFile, "\n");

		fprintf(outputFile, "Average Grade: %.2f\n", students[i].average);
		fprintf(outputFile, "----------------------\n");
	}

	//Securely close the file.
	fclose(outputFile); 
	printf("Student information written to output.txt successfully.\n");
}


//
// FUNCTION :    displayMenu
// DESCRIPTION : This function will display all options available to user to select.
// PARAMETERS :  nothing.
// RETURNS :     nothing. 
//
void displayMenu() {
	printf("Please enter the corresponding number to its respected function\n1. Add a student.\n2. Search for student by name.\n3. Modify students grades.\n4. Display all students.\n5. Write data to file.\n6. Read data from file.\n7. Exit.\n");
}


//
// FUNCTION :    addStudent
// DESCRIPTION : This function will add a student into the Student struct arrray with all parameters that make up a Student.
// PARAMETERS :  Student students[], the struct array for the Student data type, and int studentCount, the total number of students actively in the array.	
// RETURNS :     nothing. 
//
void addStudent(Student students[], int* studentCount) {

	//Check if MAX_STUDENTS condition is already met. If so, do not allow anymore. 
	if (*studentCount >= MAX_STUDENTS) {
		printf("Cannot add more students. Maximum capacity reached.\n");
		return;
	}

	//Get the data for the new student to be added into the array.
	int count;
	int whichGradeIAmOn = 1;
	float sum = 0;
	Student newStudent;

	//Code that will get and append the students name.
	printf("Enter the full name of the student that you are adding:\n");
	getchar();
	fgets(newStudent.name, sizeof(newStudent.name), stdin);
	newStudent.name[strcspn(newStudent.name, "\n")] = 0;

	//Code that appends the ID number to the student.
	printf("Enter their corresponding student identification number:\n");
	scanf_s("%d", &newStudent.id);

	//Code that will gather the students grade.
	averageCalc(&newStudent);

	//Append the student to the array.
	students[*studentCount] = newStudent;
	(*studentCount)++;
	printf("Student added successfully!\n");

}


//
// FUNCTION :    displayStudents
// DESCRIPTION : This function will traverse the Student struct array and print the results for each student found.
// PARAMETERS :  Student students[], the struct array for the Student data type, and int studentCount, the total number of students actively in the array.	
// RETURNS :     nothing. 
//
void displayStudents(Student students[], int studentCount) {
	printf("Student List:\n");
	printf("-------------------------------------------------\n");
	for (int i = 0; i < studentCount; i++) {
		printf("Name: %s, ID: %d, Average: %.2f\n",
			students[i].name,
			students[i].id,
			students[i].average);
	}
	printf("-------------------------------------------------\n");
}


//
// FUNCTION :    searchStudent
// DESCRIPTION : This function will search the fullName of a student and compare it to the Student.fullname data value for a match
// PARAMETERS :  students(the Student struct array), studentCount (number of students the system has identified) and the fullName const char array containing the full name the user entered.
// RETURNS :     i, which is the index value where the name the user is looking for matched that Student.fullname's value. -1 if it did not find a result. 
//
int searchStudent(Student students[], int studentCount, const char* fullName) {
	for (int i = 0; i < studentCount; i++) {
		if (strcmp(students[i].name, fullName) == 0) {
			return i;
		}
	}
	return -1;
}


//
// FUNCTION :    modifyStudent
// DESCRIPTION : This function will modiy the marks of a student based on the retuned index value from the searchStudent function. 
// PARAMETERS :  Student students[], the struct array for the Student data type, and int studentCount, the total number of students actively in the array.	
// RETURNS :     nothing.  
//
void modifyStudent(Student students[], int studentCount) {
	char searchName[MAX_NAME_LENGTH];
	float sum = 0;

	//Clear the input buffer explicitly using the end of file flag.
	while (getchar() != '\n' && !feof(stdin));

	//Code to ask user for the name of the student they want to modify. 
	printf("Enter the full name of the student to modify: ");
	fgets(searchName, MAX_NAME_LENGTH, stdin);
	searchName[strcspn(searchName, "\n")] = '\0';


	//Call the searchStudent function to confirm there is a match.
	int index = searchStudent(students, studentCount, searchName);
	if (index == -1) {
		printf("Student with full name '%s' not found.\n", searchName);
	}

	//Modify the students grade information based on the returned index value. 
	modifyGradeAverage(students, index);
	printf("Grades updated successfully. New average: %.2f\n", students[index].average);
}


//
// FUNCTION :    readStudentsFromFile
// DESCRIPTION : This function will modiy the marks of a student based on the retuned index value from the searchStudent function. 
// PARAMETERS :  students(the Student struct array), studentCount (number of students the system has identified).
// RETURNS :     nothing.  
//
int readStudentsFromFile(Student students[], int* studentCount) {

	//Declaring the local variables used for the opening of the input.txt file.
	FILE* inputFile = NULL;
	int count = 0;

	//Open the file. Evaluate if there is an error opening it or not. 
	openFile(&inputFile, "input.txt", "r");
	if (inputFile == NULL) {
		perror("Error opening file");
		return -1;
	}
	else {
		printf("File open and read successfully.\n");
	}

	//Check for pre exisitng students and confirm that they are less than the ceiling value and confirm end of file is not met to get current index starting point for import.
	while (*studentCount + count < MAX_STUDENTS && !feof(inputFile)) {
		int currentIndex = *studentCount + count;

		//Reading the students full name from the input file. 
		if (fgets(students[currentIndex].name, MAX_NAME_LENGTH, inputFile) == NULL) {
			break;
		}
		students[currentIndex].name[strcspn(students[currentIndex].name, "\n")] = '\0'; // Remove newline

		//Reading the students student number from the input file. 
		if (fscanf_s(inputFile, "%d\n", &students[currentIndex].id) != 1) {
			break;
		}

		//Reading each of the students individual grades from the input file.
		for (int i = 0; i < 5; i++) {
			if (fscanf_s(inputFile, "%f", &students[currentIndex].grades[i]) != 1) {
				break;
			}
		}

		//Reading their current average value from the input file. 
		if (fscanf_s(inputFile, "%f\n", &students[currentIndex].average) != 1) {
			break;
		}
		count++;
	}

	//Securely close the file after data processing. 
	fclose(inputFile);

	//Update the value at the address of studentCount so the local variable acts as a global and is updating across the program. 
	*studentCount += count;
	return 0;
}


//
// FUNCTION :    averageCalc
// DESCRIPTION : This function will take in all the grade values and apply it to the student. Then, will calculate average from sum and append it to student. 
// PARAMETERS :  Student* newStudent, a pointer referencing the newStudent datatype to modify from addStudent.
// RETURNS :     nothing. 
//
void averageCalc(Student* newStudent) {

	//Declaring local variables. 
	int whichGradeIAmOn = 1;
	float sum = 0;
	int count;

	//For loop that will cycle through the grades as many times as the grade's ceiling (currently 5). It will append each grade to the grades array.
	for (count = 0; count < MAX_NUMBER_GRADES; count++) {
		printf("Enter the mark for Grade %d.\n", whichGradeIAmOn);
		scanf_s("%f", &newStudent->grades[count]);
		sum += newStudent->grades[count];
		whichGradeIAmOn++;
	}

	//Code that will calculate the average.
	newStudent->average = sum / MAX_NUMBER_GRADES;
}	


//
// FUNCTION :    modifyGradeAverage
// DESCRIPTION : This function will take in all the grade values and apply it to the student. Then, will calculate average from sum and append it to student. It does
//				 this accurately because it has the index number of the student to target before hand. Thus, a different average function was needed. 
// PARAMETERS :  Student students[], athe entire array as reference. int index to know which student we are modifiying. 
// RETURNS :     nothing. 
//
void modifyGradeAverage(Student students[], int index) {
	float sum = 0;
	//Modify the students grade information absed on the returned index value. 
	for (int count = 0; count < MAX_NUMBER_GRADES; count++) {
		printf("Enter the mark for Grade %d: ", count + 1);
		while (scanf_s("%f", &students[index].grades[count]) != 1) {
			printf("Invalid input. Please enter a valid number: ");
			while (getchar() != '\n');
		}
		sum += students[index].grades[count];
	}

	//Recalculate the average after grades have been modified. 
	students[index].average = sum / MAX_NUMBER_GRADES;
}


//
// FUNCTION :    modeSelect
// DESCRIPTION : This function will process all options that are available to the user and call on the corresponding functions depending on the option selected. 
// PARAMETERS :  nothing.
// RETURNS :     nothing. 
//
void modeSelect() {

	//Defining constant variables used throughout the program as this function will call other functions.
	Student students[MAX_STUDENTS];
	int studentCount = 0;
	double averageScore = 0;
	int choice = 0;
	FILE* inputFile = NULL;
	char searchName[MAX_NAME_LENGTH];
	int index = 0;

	//Program will exit once you enter 7.
	while (choice != 7) {
		displayMenu();
		printf("Enter your choice: ");

		//Logic that will scan my choice and determine it is valid. If not, asks for new input. If it is, clears buffer to prevent infinite loop.
		if (scanf_s("%d", &choice) != 1) {
			printf("Invalid input. Please enter a valid number.\n");
			while (getchar() != '\n');
			continue;
		}

		//Option 1: Add a student to the struct array.
		if (choice == 1) {
			addStudent(students,&studentCount);

		}

		//Option 2: Search for a student by name.
		else if (choice == 2) {

			//Check to confirm that user has actually initiated a reading option before calculating average. Throw error if not.
			if (studentCount == 0) {
				printf("No student data available. Please read data first (option 1).\n");
			}
			else {
				getchar();
				printf("Enter the full name to search for: ");
				fgets(searchName, MAX_NAME_LENGTH, stdin);
				searchName[strcspn(searchName, "\n")] = '\0';
				index = searchStudent(students, studentCount, searchName);
				if (index != -1) {
					printf("Student found. Name: %s, Student ID: %d, Average: %.2f\n", students[index].name, students[index].id, students[index].average);
				}
				else {
					printf("Student with full name '%s' not found.\n", searchName);
				}
			}
		}


		//Option 3: Modify a students grades that is located in the Student struct array.
		else if (choice == 3) {

			//Check to confirm that user has actually initiated a reading option before calculating average. Throw error if not.
			if (studentCount == 0) {
				printf("No student data available. Please read data first (option 1).\n");
			}
			else {
				modifyStudent(students, studentCount);
			}
		}

		//Option 4: Display all the students in the Student struct array.
		else if (choice == 4) {

			//Check to confirm that user has actually initiated a reading option before calculating average. Throw error if not.
			if (studentCount == 0) {
				printf("No student data available. Please read data first (option 1).\n");
			}
			else {
				displayStudents(students, studentCount);
			}
		}


		//Option 5: Write the Student struct array to a text file.
		else if (choice == 5) {

			//Confirm there is valid data in the Student struct array. If not, throw an error
			if (studentCount == 0) {
				printf("No data available. Please either add data manually (Option 1) or import data from file (Option 5).\n");
			}
			else {
				writeStudentsToFile(students, studentCount);
			}
		}


		//Option 6: Open file and read data.
		else if (choice == 6) {
			readStudentsFromFile(students,&studentCount);
		}

		//Option 7: Terminate the program.
		else if (choice == 7) {
			printf("Exiting program.\n");
		}

		//Filter invalid choices.
		else {
			printf("Invalid choice. Please try again.\n");
		}
	}
}


