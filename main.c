#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void login();
void createAccount();
void beCandidate();
void vote();

int main(){
    int input;
    char throwaway;
    while (true){
        printf("If you would like to login to your account, press 1, if you would like to create an account, press 2\n");
        scanf("%d", &input);
        if(input == 1){
            printf("LOGGING INTO ACCOUNT\n");
            login();
        }
        else if (input == 2){
            printf("CREATING ACCOUNT\n");
            createAccount();
        }
        else{
            printf("Not a valid input\n");
        }
    }
}
void login(){
    char buffer[255]; //used as a dummy variable for names
    char userName[255];
    char password[255];
    char readFromFile[255];
    char readFromFile1[255];
    char userInput[255];
    scanf("%c", buffer); //clears input buffer 
    printf("What is your username: ");
    fgets(userName, 255, stdin);
    userName[strlen(userName) - 1] = '\0'; //reads name and removes whitespace at end of it
    for(int i = 0; i < strlen(userName); i++){ //makes everything lowercase
        userName[i] = tolower(userName[i]);
    }
    strcpy(buffer, userName);
    strcat(buffer, ".txt");
    FILE *pUser1 = fopen(buffer, "r"); //opens 2nd file to read it, and creates it if it doesn't exist
    if(pUser1 == NULL){
        printf("That aint registered on the system doofus\n");
        exit(0);
    }
    printf("What is your password: ");
    fgets(password, 255, stdin);
    password[strlen(password) - 1] = '\0';
    fgets(readFromFile, 255, pUser1);
    fgets(readFromFile1, 255, pUser1); //reads next line
    if(strncmp(readFromFile, password, strlen(password)) == 0 && readFromFile[strlen(password)] == '\n'){ //checks the amount of characters in the string password and only compares those characters  
        printf("You have succesfully logged in!\n");
    }   
    else{
        printf("Haxor!\n");
        exit(0); //breaks function
    }
    if(strcmp(readFromFile1, "no") == 0){
        printf("You have not voted for anybody, would you like to vote, enter V for vote or enter C if you would like to be a candidate: ");
        scanf("%c", userInput);
        if(strncmp(userInput, "V", 1) == 0 || strncmp(userInput, "v", 1) == 0){
            vote();
        }
        else if(strncmp(userInput, "C", 1) == 0 || strncmp(userInput, "c", 1) == 0){
            beCandidate();
        }
        else{
            printf("\nI, as your voting system do not have time for wrong inputs");
            exit(0);
        }
    }
    else{
        printf("There is nothing on your file!");
    }
    fclose(pUser1);
}

void createAccount(){
     while (true){
        char userName[255];
        char buffer[255]; //used as a dummy variable for names
        bool uniqueUsername = true; //used to check if username is unique
        char password[255];
        scanf("%c", buffer); //clears input buffer   
        printf("What would you like your username to be(lowercase): ");
        fgets(userName, 255, stdin);
        userName[strlen(userName) - 1] = '\0'; //reads name and removes whitespace at end of it
        for(int i = 0; i < strlen(userName); i++){ //makes everything lowercase
            userName[i] = tolower(userName[i]);
        }
        FILE *pF = fopen("usernames.txt", "a+"); //opens 2nd file to read it, and creates it if it doesn't exist
        
        //int length = sizeof(userName)/sizeof(userName[0]);
        while(fgets(buffer, 255, pF)){ //reads file adn checks if the username is on it
            //if(strncmp(buffer, userName, strlen(userName)) == 0){  DIDN'T WORK
            if(strncmp(buffer, userName, strlen(userName)) == 0 && buffer[strlen(userName)] == '\n'){ //checks the amount of characters in the string userName and only compares those characters 
                uniqueUsername = false;
                break;
            }
        }
        if(uniqueUsername == true){
            printf("What is your password: ");
            fgets(password, 255, stdin);
            password[strlen(password)-1] = '\0'; //removes whitespace at end of password cause fgets is just like that
            printf("Your username is %s and your password is %s", userName, password);
            fprintf(pF, "%s\n", userName); //adds username to the list of usernames. 
            //I do know that it would be more efficient to ignore the file with the list of usernames and instead list through the existing profile files of a user but I spent a lot of time figuring out how to check things in a file so I'm gonna keep it in
            char buf[255]; 
            strcpy(buf, userName);
            strcat(buf, ".txt"); //creates a variable which matches the file name
            FILE *pUser = fopen(buf, "w"); //opens a file with the username of the individual
            fprintf(pUser, "%s\nno", password); //creates a user file
            printf("\nYour username has succesfully been registered into the system!\n\n");
            fclose(pF);
            fclose(pUser);
            break;
        }
        else{
            printf("This username is already taken, try again\n");
        }
        fclose(pF);
    }
}
void beCandidate(){
    printf("becoming canddiate\n");
}
void vote(){
    printf("voting\n");
}