#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//function prototypes
void mainMenu();
void createFile();
void deleteFile();
void moveFile();
void renameFile();
void copyFile();
void appendText(char file[]);
void insertText(char file[]);
void removeText(char file[]);
void displayText(char file[]);
void textOps();

//function used to create a file,
void createFile()   {
    // Initialize necessary vars
    int choice;
    char createdFile[50];
    FILE *newFile;
    char c;

    printf("You have chosen to create a file specified by you, the user. If you'd like to learn more about this function please press 0, else press 1 to continue: ");
    scanf("%d", &choice); //read user input
    if(choice == 0) { //that is, the user would like to learn more about the functions operations
        printf("This function begins by asking you for the name and extension of the file you'd like to create and then creates it.");
        printf(" If this is not the function you meant to select, kindly press 0 to return to the main menu, else press 1 to continue: ");
        scanf("%d", &choice); //read user input
        while(choice > 1 || choice < 0) {
        if(choice == 0) //that is, the user doesn not want to create a file and wants to return to the menu
            mainMenu();
        }
    }
    printf("Please the name and extension (.txt, .bat, etc) you'd like to create: ");
    scanf("%s", createdFile); //read user input

	newFile = fopen(createdFile, "ab+"); //create new file

	if (newFile) { //that is, if the file has been successfully created
        printf("File '%s' successfully created.\n", createdFile);
	}
	else { //file unable to be created
        printf("Error: File '%s' was not created.", createdFile);
        printf("\nAccess to this file may be restricted.\n");
    }
    fclose(newFile); //close file

    getchar(); //eat up new line
    printf("Would you like to execute more operations? (y/n): ");
    scanf("%c", &c); //get user input
    while(c != 'y' && c != 'n') { //while invalid input
        printf("Invalid input. Please enter y or n.");
        scanf("%c", &c);
    }
    if(c == 'y') //bring user back to main menu to execute more operations
        mainMenu();
    else
        return;
}

//function used to delete an already existing file
void deleteFile()   {
    // Initialize necessary vars
    FILE* fPtr;
    int choice;
    char targetFile[32];
    int delSuccess;
    char c;

    printf("You have chosen to delete a file that will soon be specified by you, the user. If you'd like to learn more about this function please press 0, else press 1 to continue: ");
    scanf("%d", &choice); //read user input
    if(choice == 0) { //that is, user would like to learn more about the functions operations
        printf("This function begins by asking you to specify the file you'd like to delete. After recieving your input, it will proceed to delete it.");
        printf(" If this is not the function you meant to select, kindly press 0 to return to the main menu, else press 1 to continue: ");
        scanf("%d", &choice);//read user input
        if(choice == 0) //direct user back to main menu
            mainMenu();
    }
        printf("\nPlease enter the name and extension of the file you'd like to delete: ");
            scanf("%s", targetFile); //read the name of the file the user would like to delete

    if(!(fPtr = fopen(targetFile, "r"))) { //file does not exist or user does not have permission to open it
        printf("Error. %s does not exist.\n", targetFile);
        return;
        }
    fclose(fPtr);

    delSuccess = remove(targetFile); //attempt to remove file. remove() will return 0 if successful

    if(delSuccess == 0) { //file successfully deleted
        printf("The file specified '%s' was succesfully deleted.", targetFile);
    }
    else { //file has not been deleted
        printf("Error. %s was not deleted. Access may be restricted\n", targetFile);
    }

    getchar(); //eat up new line
    printf("\nWould you like to execute more operations? (y/n): ");
    scanf("%c", &c); //get user input
    while(c != 'y' && c != 'n') { //while invalid input
        printf("Invalid input. Please enter y or n.");
        scanf("%c", &c);
    }
    if(c == 'y') //bring user back to main menu to execute more operations
        mainMenu();
    else
        return;
}

//function to move a preexisting file to a new location
void moveFile() {

    FILE *fPtr, *destPtr;
    int choice;
    char ch, fileName[30], dirName[100], c;

    printf("You have chosen to move a file to a new location. If you'd like to learn more about this function please press 0, else press 1 to continue: ");
    scanf("%d", &choice); //read user input
    if(choice == 0) { //user would like to learn more
        printf("This function begins by asking you the name and extension of the file you'd like to move. After recieving your input, it will then ask you to input the name of the file where you'd like to move the data. It will then proceed to do so.");
        printf(" If this is not the function you meant to select, kindly press 0 to return to the main menu, else press 1 to continue: ");
        scanf("%d", &choice); //read user input
        if(choice == 0) //direct user back to main menu
            mainMenu();
    }
    printf("Please enter the name of the file you'd like to move: ");
    scanf("%s",fileName); //read user input containing the file they'd like to move

    fPtr = fopen(fileName, "r"); //open file

    while(fPtr == NULL) { //while the file either does not exist or cannot be opened
        printf("Error. File either does not exist or you do not have persmission to open it. Please enter a filename that exists or type quit to exit: ");
        scanf("%s",fileName); //get user input
        if(strcmp(fileName, "quit") == 0) //exit program
            return;
        fPtr = fopen(fileName, "r"); //try to open file for reading purposes

    }

    printf("Enter the location where you'd like to move the file: ");
    scanf("%s",dirName); //read user input detailing where they'd like to move the file

    destPtr = fopen(dirName, "wb"); // Open file to write content of source

    while(destPtr == NULL) { //the file either does not exist or cannot be opened
        printf("Error accessing location. Check it's existence and your permissions and try again, or type quit to exit: ");
        scanf("%s",dirName); //get user input
        if(strcmp(dirName, "quit") == 0) { //exit program
            fclose(fPtr);
            return;
        }
        destPtr = fopen(dirName, "wb"); //attempt to open file
    }

    while (( ch = fgetc(fPtr) ) != EOF) { // Write content of source to new file char by char till the end of file.
        fputc(ch, destPtr);
    }

    printf("File successfully moved.\n");

    fclose(fPtr);
    fclose(destPtr);

    remove(fileName); // Remove source file

    getchar(); //eat up new line
    printf("Would you like to execute more operations? (y/n): ");
    scanf("%c", &c); //get user input
    while(c != 'y' && c != 'n') { //while invalid input
        printf("Invalid input. Please enter y or n.");
        scanf("%c", &c);
    }
    if(c == 'y') //bring user back to main menu to execute more operations
        mainMenu();
    else
        return;
}

//function to rename an already existent file
void renameFile() {

    FILE* fPtr;
    int choice;
    char oldFileName[50], newFileName[50], c;

    printf("You have chosen to rename a preexisting file. If you would like to learn more about this function please press 0, else press 1 to continue: ");
    scanf("%d", &choice); //read user input
    if(choice == 0) { //tell the user more about the functions operations
        printf("This function will first ask you to enter the name of an already existent file. If the file exists it will ask you to input what you'd like ot rename it to. If it doesn't exist however, ");
        printf("it will prompt you to enter the name of a file that does.\n");
        printf("If you don't wish to rename a file please press 0 to return to the main menu, else press 1 to continue: ");
        scanf("%d", &choice); //read user input
        if(choice == 0) //redirect user to main menu
            mainMenu();
    }
    printf("Please enter name of the file that will be renamed: ");
    scanf("%s", oldFileName); //read name of file that the user would like renamed

    fPtr = fopen(oldFileName, "r"); //attempt to open the file

    while(!fPtr) //while file doesn't exist
          {
              printf("File does not exist. Please enter one that does: ");
              scanf("%s", oldFileName); //read user input
              fPtr = fopen(oldFileName, "r"); //attempt to open the file
          }
    fclose(fPtr); //close file

    printf("Please enter what you'd like to rename the file to: ");
    scanf("%s", newFileName); //read what the user would like the file to renamed to
    fPtr = fopen(newFileName, "r"); //check to see if a file already exists under that name

        while (fPtr) //while a file already exists under the given name
        {
            printf("File name already exists. Please enter something that doesn't: ");
            scanf("%s", newFileName); //read user input
            fPtr = fopen(newFileName, "r"); //check to see if a file already exists under the desired name
        }
    rename(oldFileName, newFileName); //rename the old filename to the new filename
    printf("File %s has successfully been renamed to %s\n", oldFileName, newFileName); //notify user that the operation has completed successfully

    getchar(); //eat up new line
    printf("Would you like to execute more operations? (y/n): ");
    scanf("%c", &c); //get user input
    while(c != 'y' && c != 'n') { //while invalid input
        printf("Invalid input. Please enter y or n.");
        scanf("%c", &c);
    }
    if(c == 'y') //bring user back to main menu to execute more operations
        mainMenu();
    else
        return;

}

//function to copy the contents of a file into an already existent or entirely new file
void copyFile()
{
    int choice;
    FILE *oldFile, *newFile;
    char ch, oldFileName[25], newFileName[25], c;

    printf("You have chosen to copy the contents of an existing file into an either already existent or an entirely new file. If you'd like to learn more about this function please press 0, else press 1 to continue: ");
    scanf("%d", &choice); //read user input
    if(choice == 0) { //tell the user more about the function
        printf("This file first will prompt you to input the name of the file you'd like to copy the contents of, then, upon checking for its existence, it will ask you to enter the name of the new file that you'd like copy the contents into. If the file doesn't already exist, the program will ask if you'd like to create it. It will then copy the contents of the old file into the new one and notify you upon completion.");
        printf(" If this is not the function you'd like to execute, please press 0 to return to the main menu, else press 1 to continue: ");
        scanf("%d", &choice); //read user input
        if(choice == 0) //redirect user to main menu
            mainMenu();
    }
    printf("Please enter the name of the file you'd like to copy: ");
    scanf("%s",oldFileName); //read the name of the file the user would like to copy the contents of

    oldFile = fopen(oldFileName, "r"); //attempt to open it
    while (!oldFile) { //while the file cannot be opened
        printf("File does not exist. Please enter the name of a file that exists: ");
        scanf("%s",oldFileName); //read user input
        oldFile = fopen(oldFileName, "r"); //attempt to open file
    }
    if( oldFile == NULL ) { //if file cannot be read from
        printf("Error. You do not have permission to read from this file.");
        return;
    }

    printf("Enter the name of the file you'd like to copy the data to: ");
    scanf("%s",newFileName); //get name of file the user would like to copy the data to

    newFile = fopen(newFileName, "r"); //attempt to open the file

    while(!newFile) { //while the file cannot be opened
        printf("File does not exist. Press 1 if you'd like to create it or 0 to return to the main menu: ");
        scanf("%d", &choice);//get user input
        if(choice == 0) //return user to main menu
            mainMenu();

        newFile = fopen(newFileName, "w"); //create file
        }

    fclose(newFile); //close file

    newFile = fopen(newFileName, "wb"); //open file for writing purposes

    if( newFile == NULL ) { //file cannot be written to
      fclose(oldFile);
      printf("Error. You do not have permission to write to %s", newFileName);
      return;
    }

    while ((ch = fgetc(oldFile)) != EOF) { // copy source to new file char by char till the end of file.
        fputc(ch, newFile);
    }

    printf("File successfully copied.\n");

    fclose(oldFile); //close file
    fclose(newFile); //close file

    getchar(); //eat up new line
    printf("Would you like to execute more operations? (y/n): ");
    scanf("%c", &c); //get user input
    while(c != 'y' && c != 'n') { //while invalid input
        printf("Invalid input. Please enter y or n.");
        scanf("%c", &c);
    }
    if(c == 'y') //bring user back to main menu to execute more operations
        mainMenu();
    else
        return;
}

//function to append text onto an already existent or entirely new file
void appendText(char file[]) {

    FILE* fPtr = fopen(file, "a"); //open file for appending
    char text[100], c;
    int choice;

    printf("You have chosen to append text to the end the specified text file. To learn more about this function please press 0, else press 1 to continue: ");
    scanf("%d", &choice); //get user input
    if(choice == 0) { //tell the user more about the function
        printf("This function asks you, the user, to enter the text you'd like to append to the end of the file and then does it.");
        printf("If this is not the function you meant to select, kindly press 0 to return to the main menu, else press 1 to continue: ");
        scanf("%d", &choice); //read user input
        if(choice == 0) //redirect user back to main menu
            mainMenu();
    }
    if(fPtr == NULL) { //if file cannot be opened
        printf("Error opening file. Please check the spelling/existence of the file and try again.");
    }
    else { //file successfully opened
        printf("File successfully opened. Please enter the text you'd like to append to the file: \n");

        getchar(); //eat new line thus allowing to read user input
        gets(text); //read the text that the user would like to append to the end of the file

        fprintf(fPtr, "%s", text); //print the text to the file
    }

    fclose(fPtr); //close file

    printf("Would you like to execute more operations? (y/n): ");
    scanf("%c", &c); //get user input
    while(c != 'y' && c != 'n') { //while invalid input
        printf("Invalid input. Please enter y or n.");
        scanf("%c", &c);
    }
    if(c == 'y') //bring user back to main menu to execute more operations
        mainMenu();
    else
        return;
}

//function to insert text at a location in the file specified by the user
void insertText(char file[]) {
    FILE* fPtr = fopen(file, "r+"); //open the file for reading and writing

    int choice;
    char text[50];
    char temp[50];
    char c;
    memset(text, 0, sizeof(text)); //initialize array to 0's
    memset(temp, 0, sizeof(temp)); //initialize array to 0's
    int i = 0;
    int pos;
    printf("You have chosen to insert text enter by you, the user, into a specified location of the chosen file. If this you'd like to learn more about this function press 0, otherwise press 1 to continue: ");
    scanf("%d", &choice); //read user input
    if(choice == 0) { //tell user more about the function
        printf("This function begins by asking you the location in the file you'd like to begin writing. After that it will ask you what text you'd like to include at that position.");
        printf("If this is not the function you meant to select, kindly press 0 to return to the main menu, else press 1 to continue: ");
        scanf("%d", &choice); //read user input
        if(choice == 0) //bring user back to main menu
            mainMenu();
    }
    while(fscanf(fPtr, "%c", &temp[i]) != EOF) { //load temp array with contents of the file
        i++;
    }

    printf("\n");

    printf("Please specify the character index where you'd like to start writing: ");
    scanf("%d", &pos); //read user input

    printf("Please enter the string you'd like to insert at position %d: ", pos);
    getchar(); //eat new line thus allowing the user to input data
    gets(text); //read the text the user would like to insert at the previously specified position
    i=0;
    int j = 0;
    fseek(fPtr, 0, SEEK_SET); //set pointer at the beginning of the file
    while(temp[i] != 0) { //read until end of text found in temp array

        if(ftell(fPtr) == pos) { //if pointer is at the position where the user would like to add his text

                fprintf(fPtr, "%c", temp[i]); //print last remaining character before location
            while(text[j] != 0) { //while there is more text to add from the text the user would like to add at the position specified
                fprintf(fPtr, "%c", text[j]); //print text to file
                j++; //move ahead in array
            }
        }
        else { //pointer is not at specified position
            fprintf(fPtr, "%c", temp[i]);//continue printing text already found within the file
        }
        i++;
    }

    fseek(fPtr, 0, SEEK_SET); //set pointer to beginning of file
    printf("Contents of file after insertion: ");
    c = fgetc(fPtr); //print first char
    while(c != EOF) { //while more text in file
        printf("%c", c);
        c = fgetc(fPtr);
    }
    fclose(fPtr); //close file

    printf("\nWould you like to execute more operations? (y/n): ");
    scanf("%c", &c); //get user input
    while(c != 'y' && c != 'n') { //while invalid input
        printf("Invalid input. Please enter y or n.");
        scanf("%c", &c);
    }
    if(c == 'y') //bring user back to main menu to execute more operations
        mainMenu();
    else
        return;
}

//function to remove all text from file
void removeText(char file[]) {
    int choice;
    char c;

    printf("You have chosen to remove all text from the specified text file. If you'd like to learn more about this function please press 0. If you'd like to continue then simply press 1.");
    scanf("%d", &choice); //read user input
    if(choice == 0) { //tell user more about function
        printf("This function works by first opening the file for writing purposes and then simply prints empty quotations to the file thus overwriting the previous content with nothing. If you do not want to delete all the text in the specified file then kindly press 0 to return to the main menu, else press 1 to continue: ");
        getchar();
        scanf("%c", &choice);
        if(choice == 0) //bring user back to main menu
            mainMenu();
    }
    FILE* fPtr = fopen(file, "w"); //open file for writing purposes

    if(!fPtr) { //if file cannot be opened
        printf("Error opening file. Either the file does not exist or you do not have permission to modify it.");
        return;
    }
    //else, if file can be opened
    fprintf(fPtr, ""); //print blank to it thus emptying file
    printf("Contents of file successfully deleted.\n");
    fclose(fPtr); //close file

    getchar(); //eat up new line
    printf("Would you like to execute more operations? (y/n): ");
    scanf("%c", &c); //get user input
    while(c != 'y' && c != 'n') { //while invalid input
        printf("Invalid input. Please enter y or n.");
        scanf("%c", &c);
    }
    if(c == 'y') //bring user back to main menu to execute more operations
        mainMenu();
    else
        return;
}

//function to display the contents of a file, giving the user the option to stop at each new line encountered
void displayText(char file[]) {
    int choice;
    char text[1000];
    char c;
    int i = 0;

    printf("You have chosen to display the text of the selected file. To learn more about this function press 0, or, if you'd like to continue, please press 1: ");
    scanf("%d", &choice); //read user input

    if(choice == 0) { //tell user more about function
        printf("This function first opens the file for reading purposes then reads up until a new line is encountered. At this point you have the option to either continue or stop reading from the file by typing y or n, respectively. If this is not the option you meant to select, press 0 to go back to the main menu or press 1 if you'd like to proceed.");
        scanf("%d", &choice); //read user input
        if(choice == 0) //bring user back to main menu
            mainMenu();
    }

    FILE* fPtr = fopen(file, "r"); //open file for reading

    if(!fPtr) { //if file cannot be opened
        printf("Error. File either doesn't exist or you do not have permission to read from it");
    }

    while(fscanf(fPtr, "%c", &text[i]) != EOF) { //while there is more text to read
            if(text[i] == '\n') { //if new line is encountered
                printf("\nNew line encountered. Continue? (y/n)");
                getchar(); //eat new line to input can be entered
                scanf("%c", &c); //read user input

                if(c == 'n') //if user wants to stop reading
                    exit(0); //exit
            }
        printf("%c", text[i]); //else, continue
        i++;
    }
    printf("\n");
    getchar();
    printf("Would you like to execute more operations? (y/n): ");
    scanf("%c", &c); //get user input
    while(c != 'y' && c != 'n') { //while invalid input
        printf("Invalid input. Please enter y or n.");
        scanf("%c", &c);
    }
    if(c == 'y') //bring user back to main menu to execute more operations
        mainMenu();
    else
        return;
}
//function to display the menu detailing the operations that can be performed on the text file entered by the user
void textOps() {

    char fileName[25];
    int choice;
    int goBack = 0;
    FILE* fPtr;

    printf("Please enter the name of the file you'd like to edit, or type help to gain info on how this function is used: ");
    scanf("%s", fileName); //read file user would like to modify

    if(strcmp(fileName, "help") == 0) { //tell user more about function
        printf("This function serves as a menu that allows the user(you) to choose between various operations to be done on a text file.If this is not the option you meant to select, please press 0 to return back to the main menu. Alternatively, if you'd like to proceed please press 1.\n");
        scanf("%d", &choice); //read user input
        if(choice == goBack) //return user to main menu
            mainMenu();
        else { //user wants to continue
            printf("Please enter the name of the file you'd like to edit: ");
            scanf("%s", fileName); //read file name entered by user
        }
    }
    fPtr = fopen(fileName, "r");
    while(!fPtr) {
        printf("File does not exist. Please enter the name of one that does: ");
        scanf("%s", fileName);
        fPtr = fopen(fileName, "r");
    }
    //display menu
    printf("Please choose one of the following operations you'd like to do to %s: \n", fileName);
    printf("1) Append text to the end of the file\n");
    printf("2) Insert text in a specific position of the file\n");
    printf("3) Remove all text in the file\n");
    printf("4) Show the content of the file\n");

    scanf("%d", &choice); //read user input

    while(choice > 4 || choice < 1) {
        printf("Invalid input. Please enter a number between 1 and 4: ");
        scanf("%d", &choice); //read user input
    }
    switch(choice) {
        case 1:
            appendText(fileName);
            break;
        case 2:
            insertText(fileName);
            break;
        case 3:
            removeText(fileName);
            break;
        case 4:
            displayText(fileName);
            break;
    }
}

//main menu, provides the user with a menu with which to execute various
//file operations by entering the corresponding number
void mainMenu() {
    int choice;

    printf("Please select one of the following options:\n");
    printf("1) Create a new file\n");
    printf("2) Delete a file\n");
    printf("3) Rename a file already created\n");
    printf("4) Copy a file\n");
    printf("5) Move a files contents from one location to another\n");
    printf("6) Various text file operations\n");

    scanf("%d", &choice); //read user input

    while(choice > 6 || choice < 1) {
        printf("Invalid input. Please enter a number between 1 and 6: ");
        scanf("%d", &choice);
    }
    switch(choice) {
        case 1:
            createFile(); //create a file
            break;
        case 2:
            deleteFile(); //delete a file
            break;
        case 3:
            renameFile(); //rename a file
            break;
        case 4:
            copyFile(); //copy a file
            break;
        case 5:
            moveFile(); //move a file
            break;
        case 6:
            textOps(); //brings user to a menu of various text operations
            break;
    }
}

//main function
int main()
{
    printf("Welcome to our portable file manipulator.\n\n");
    mainMenu(); //display main menu
    return 0;
}

