// Osman Servin
// Write the compiler used: Visual GCC
// Compile command line: gcc -g -Wall hw05q1.c -o output
// Executable command: ./output



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_STUDENTS 20
#define MAX_NAME_LENGTH 30
#define MAX_HOME_COUNTRY_NAME_LENGTH 30

typedef enum { Physics = 0, Mathematics, CS } departmentType;  // enum type

struct studentRecord // struct for students details
{
    char studentName[MAX_NAME_LENGTH];
    departmentType department;
    unsigned int idNumber;
    char homeCountry[MAX_HOME_COUNTRY_NAME_LENGTH];
};

struct studentRecord list[MAX_STUDENTS];  // declare the list of students
int count = 0;  // the number of students currently stored in the list (initialized to 0)


void flushStdIn();
void executeAction(char);
void save(char* fileName);

int add(char* studentName_input, unsigned int idNumber_input, 
	char* department_input, char* homeCountry_input);  // DONE
void sort();  // DONE
int delete(unsigned int idNumber_input);  // DONE
void load(char* fileName);  // DONE 
void display(); 



int main()
{
    char* fileName = "Student_List.txt";
    load(fileName);  // load list of students from file (if it exists). Initially there will be no file.
    char choice = 'i';  // initialized to a dummy value
    do
    {
        printf("\nEnter your selection:\n");
        printf("\t a: add a new student\n");
        printf("\t d: display student list\n");
        printf("\t r: remove an student from list\n");
        printf("\t s: sort student list by ID in descending order\n");
        printf("\t q: quit\n");
        choice = getchar();
        flushStdIn();
        executeAction(choice);
    } while (choice != 'q');

    save(fileName);  // save list of students to file (overwrites file, if it exists)
    return 0;
}


// flush out leftover '\n' characters
void flushStdIn()
{
    char c;
    do c = getchar();
    while (c != '\n' && c != EOF);
}

// ask for details from user for the given selection and perform that action
void executeAction(char c)
{
    char studentName_input[MAX_NAME_LENGTH], homeCountry_input[MAX_NAME_LENGTH];
    unsigned int idNumber_input, add_result = 0;
    char department_input[20];
    switch (c)
    {
        case 'a':
            // input student record from user
            printf("\nEnter student name: ");
            fgets(studentName_input, sizeof(studentName_input), stdin);
            studentName_input[strlen(studentName_input) - 1] = '\0';  // discard the trailing '\n' char
            
            printf("Enter whether student is in 'Physics' or 'Mathematics' or 'CS': ");
            fgets(department_input, sizeof(department_input), stdin);
            department_input[strlen(department_input) - 1] = '\0';  // discard the trailing '\n' char
            
            printf("Enter Home Country: ");
            fgets(homeCountry_input, sizeof(homeCountry_input), stdin);
            homeCountry_input[strlen(homeCountry_input) - 1] = '\0';  // discard the trailing '\n' char
            
            printf("Please enter student ID number: ");
            scanf("%d", &idNumber_input);
            flushStdIn();

            // add the student to the list
            add_result = add(studentName_input, idNumber_input, department_input, homeCountry_input);
            if (add_result == 0)
                printf("\nStudent is already on the list! \n\n");
            else if (add_result == 1)
                printf("\nStudent successfully added to the list! \n\n");
            else
                printf("\nUnable to add. Student list is full! \n\n");

            break;

        case 'r':
            printf("Please enter ID number of student to be deleted: ");
            scanf("%d", &idNumber_input);
            flushStdIn();
            int delete_result = delete(idNumber_input);
            if (delete_result == 0)
                printf("\nStudent not found in the list! \n\n");
            else
                printf("\nStudent deleted successfully! \n\n");
            break;

        case 'd': display();	break;

        case 's': sort();		break;

        case 'q': break;
        default: printf("%c is invalid input!\n", c);
    }
}




// This function is used to add a student into the list. You can simply add the new student to the end of list (array of structs).
// Do not allow the student to be added to the list if it already exists in the list. You can do that by checking student names OR IDs already in the list.
int add(char* studentName_input, unsigned int idNumber_input, char* department_input, char* homeCountry_input)
{
	// Write the code below.
	int i; 

	// IF THE LIST ISNT FULL THEN GO INTO IF STATEMENT
	if(count < MAX_STUDENTS && count >= 0)
	{
		// SERACH TO SEE IF THE STUDENT IS ALREADY IN THE LIST
		for(i = 0; i < count; i++)
		{
			// CHECKS IF THE NAME OR ID NUMBER MATCHES EXISTING NAME/ID
			if(strcmp(list[i].studentName, studentName_input) == 0 || list[i].idNumber == idNumber_input)
			{
				return 0; // IF THE STUDENT WAS FOUND THEN RETRUN 0 AND LEAVE FUNCTION
			}
		}

		strcpy(list[count].studentName, studentName_input); // ADDS THE STUDENT NAME TO THE STRUCT
		
		// CHECKS THE USER INPUT AND DECIDES WHAT THE DEPARTMENT IS
		if(strcmp("Physics", department_input) == 0)
		{
			list[count].department = Physics; // STUDENT DEPARTMENT IS PHYSICS
		}
		else if(strcmp("Mathematics", department_input) == 0)
		{
			list[count].department = Mathematics; // STUDENT DEPARTMENT IS MATH
		}
		else
		{
			list[count].department = CS; // STUDENT DEPARTMENT IS CS
		}

		list[count].idNumber = idNumber_input; // ADDS THE ID NUMBER TO THE STRUCT
		strcpy(list[count].homeCountry, homeCountry_input); // ADDS THE HOME COUNTRY TO THE STRUCT

		count++; // INCREMENT THE COUNT TO KEEP TRACK OF NUMBER OF STUDENTS IN LIST
		return 1; // STUDENT WAS SUCCESSFULLY ADDED TO THE LIST
	}
	// IF THE LIST IS FULL
	else
	{
		return 2; // LIST IS FULL AND CANNOT ADD ANOTTHER STUDENT
	}
}



// This function displays the student list with the details (struct elements) of each student.
void display()
{
    char* departmentString = "Physics";  // dummy init

    for (int i = 0; i < count; i++)  // iterate through the list
    {
        printf("\nStudent name: %s", list[i].studentName);  // display student's name

        if (list[i].department == Physics)  // find what to display for department
            departmentString = "Physics";
        else if (list[i].department == Mathematics)
            departmentString = "Mathematics";
        else
            departmentString = "CS";
        printf("\nDepartment: %s", departmentString);  // display department
        printf("\nID Number: %d", list[i].idNumber);  // display student's ID
        printf("\nHome Country: %s", list[i].homeCountry);  // display student's room number
        printf("\n");
    }
}



// This function is used to sort the list(array of structs) numerically by student's ID in descending order.
void sort()
{
	struct studentRecord studentTemp;  // needed for swapping structs. Not absolutely necessary to use.

	// Write the code below.
	int i, j;
	
	// ITERATES THROUGH EACH STUDENT
	for(i = 0; i < count; i++)
	{
		// WILL CHECK THAT THE IDS ARE IN DESCENDING ORDER AND SWAP THEM IF THEY ARE NOT
		for(j = i + 1; j < count; j++)
		{
			// IF THE ID AT THE INDEX i IS LESS THAN THE ID OF THE NEXT INDEX THEN SWAP THE STUDENT INFORMATION
			if(list[i].idNumber < list[j].idNumber)
			{
				// COPIES THE STUDENT INFORMATION TO studentTemp 
				strcpy(studentTemp.studentName, list[i].studentName);
				studentTemp.department = list[i].department;
				studentTemp.idNumber = list[i].idNumber;
				strcpy(studentTemp.homeCountry, list[i].homeCountry);

				// SWAPS THE STUDENT WITH HIGHER ID NUMBER TO INDEX i
				strcpy(list[i].studentName, list[j].studentName);
				list[i].department = list[j].department;
				list[i].idNumber = list[j].idNumber;
				strcpy(list[i].homeCountry, list[j].homeCountry);

				// COPIES THE STUDENT INFORMATION WITH SMALLER ID NUMBER BACK INTO THE STRUCT
				strcpy(list[j].studentName, studentTemp.studentName);
				list[j].department = studentTemp.department;
				list[j].idNumber = studentTemp.idNumber;
				strcpy(list[j].homeCountry, studentTemp.homeCountry);
			}
		}
	}	

	// display message for user to check the result of sorting.
	printf("\nStudent list sorted! Use display option 'd' to view sorted list.\n");
}



// This function saves the array of structures to file. It is already implemented.
void save(char* fileName)
{
    FILE* file;
    int i, departmentValue = 0;
    file = fopen(fileName, "wb");  // open file for writing

    fwrite(&count, sizeof(count), 1, file);  // First, store the number of students in the list

    // Parse the list and write student record to file
    for (i = 0; i < count; i++)
    {
        fwrite(list[i].studentName, sizeof(list[i].studentName), 1, file);
	fwrite(&list[i].idNumber, sizeof(list[i].idNumber), 1, file);

        // convert enum to a number for storing
        if (list[i].department == Physics)
        {
	    	departmentValue = 0;  // 0 for Physics
        }
	else if (list[i].department == Mathematics)
        {
	    	departmentValue = 1; // 1 for Mathematics
        }
	else
        {
	   	departmentValue = 2; // 2 for CS
	}

	fwrite(&departmentValue, sizeof(departmentValue), 1, file); 
        fwrite(&list[i].homeCountry, sizeof(list[i].homeCountry), 1, file);
    }

    fclose(file);  // close the file after writing
}



// This function is used to delete an student by ID.
int delete(unsigned int idNumber_input)
{
	// struct studentRecord studentTemp;  // needed for swapping structs. Not absolutely necessary to use.
	// Write the code below
	int i, indexOfId;
	
	// IF THE FILE/LIST HAS STUDENTS THEN LOOK THROUGH THEM TO FIND THE ID 
	if (count > 0)
	{
		// SEARCHES FOR THE ID NUMBER
		for(i = 0; i < count; i++)
		{
			// IF THE ID NUMBER IS FOUND 
			if(list[i].idNumber == idNumber_input)
			{
				indexOfId = i; // idIndex IS SET TO THE i VALUE
				break; // EXIT LOOP IF ID WAS FOUND
			}
			// IF ALL ID NUMBERS HAVE BEEN CHECKED & LAST ID NUMBER != ID INPUT THEN RETURN 0;
			else if(count - 1  == i && list[i].idNumber != idNumber_input)
			{
				return 0; // ID NUMBER NOT FOUND IN LIST AND LEAVE FUNCTION
			}	
		}
	
		// IF THE ID NUMBER WAS FOUND THEN ENTER IF STATEMENT
		if(indexOfId >= 0)
		{
			// REMOVE THE STUDENT BY SHIFTING STUDENTS STARTING AT THE INDEX THE STUDENT WAS FOUND
			for(i = indexOfId; i < count - 1; i++)
			{
				strcpy(list[i].studentName, list[i + 1].studentName); // MOVES STUDENT'S NAME OVER ONE INDEX
				list[i].department = list[i + 1].department; // MOVES STUDENTS DEPARTMENT ONE INDEX
				list[i].idNumber = list[i + 1].idNumber; // MOVES THE STUDENT ID TO NEXT INDEX
				strcpy(list[i].homeCountry, list[i + 1].homeCountry); // MOVES STUDENT COUNTRY TO NEXT INDEX
			}
			count--; // DECREMENTS THE COUNT TO KEEP TRACK OF NUMBER OF STUDENTS IN LIST
			return 1; // STUDENT WAS DELETED AND LIST WAS UPDATED 
		}
	}
	// IF THE FILE IS EMPTY RETURN 0
	else
	{
		return 0; // ID/STUDENT WAS NOT FOUND IN THE LIST
	}
}




// This function reads the student list from the saved file and builds the array of structures 'list'.:
void load(char* fileName)
{
	// Write the code below.
	FILE* file; // MAKE FILE
	int i, departmentValue = 0;
	file = fopen(fileName, "rb"); // OPEN FILE FOR READING IT 

	if(file == NULL)
	{
		printf("%s not found.\n", fileName); // IF THE FILE IS NOT FOUND PRINT THIS TO USER
		return; // GETS OUT OF THE FUNCTION load
	}

	fread(&count, sizeof(count), 1, file); // FIRST READ THE NUMBER OF STUDENTS IN THE LIST

	for(i = 0; i < count; i++)
	{
		fread(list[i].studentName, sizeof(list[i].studentName), 1, file);
		fread(&list[i].idNumber, sizeof(list[i].idNumber), 1, file);
	
		// CONVERT THE ENUM TO NUMBER FOR STORING 
		if(list[i].department == Physics)
		{
			departmentValue = 0; // 0 FOR PHYSICS
		}
		else if(list[i].department == Mathematics)
		{
			departmentValue = 1; // 1 FOR MATH 
		}
		else
		{
			departmentValue = 2; // 2 FOR CS 
		}		
		fread(&departmentValue, sizeof(departmentValue), 1, file);
		fread(list[i].homeCountry, sizeof(list[i].homeCountry), 1, file);
	}	   	
	
	fclose(file); // CLOSE THE FILE AFTER READING IT	
} // TEST









