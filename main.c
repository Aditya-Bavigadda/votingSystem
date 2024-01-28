#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void login();
void createAccount();
void beCandidate(char userName[255], char password[255]);
void vote();
void withdrawVote();
void removeCandidate(char userName[255], char password[255]);
void recreateCandidatelist(int i, char candidates[255][255]);
void viewVotes();
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
        printf("You have not voted for anybody, would you like to vote, enter V for vote or enter C if you would like to be a candidate or enter P if you would like to view the votes: ");
        scanf("%c", userInput);
        if(strncmp(userInput, "V", 1) == 0 || strncmp(userInput, "v", 1) == 0){
            vote(userName, password);
        }
        else if(strncmp(userInput, "C", 1) == 0 || strncmp(userInput, "c", 1) == 0){
            beCandidate(userName, password);
        }
        else if(strncmp(userInput, "P", 1) == 0 || strncmp(userInput, "p", 1) == 0){
            viewVotes();
        }
        else{
            printf("I, as your voting system do not have time for wrong inputs");
            exit(0);
        }
    }
    else if (strcmp(readFromFile1, "candidate") == 0) {
        printf("If you would like to withdraw your candidateship, enter Y or if you would like to view the current standings, enter P: ");
        scanf("%c", userInput);
        if(strncmp(userInput, "Y", 1) == 0 || strncmp(userInput, "y", 1) == 0){
            removeCandidate(userName, password);
        }
        else if(strncmp(userInput, "P", 1) == 0 || strncmp(userInput, "p", 1) == 0){
            viewVotes();
        }
        else{
            printf("Why are you here then?");
            exit(0);
        }
    }
    else {
        
        printf("If you would like to withdraw your vote, enter Y or if you would like to view the current standings, enter P: ");
        scanf("%c", userInput);
        if(strncmp(userInput, "Y", 1) == 0 || strncmp(userInput, "y", 1) == 0){
            withdrawVote();
        }
        else if(strncmp(userInput, "P", 1) == 0 || strncmp(userInput, "p", 1) == 0){
            viewVotes();
        }
        else{
            printf("Why are you here then?");
            exit(0);
        }
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
void beCandidate(char userName[255], char password[255]){
    printf("becoming canddiate\n");
    FILE *pCand = fopen("candidate.txt", "a+"); //appends to the file if it exists or creates it if it doesnt
    fprintf(pCand, "%s\n", userName); //adds username to list of candidates
    fclose(pCand);
    char fileName[255];
    strcpy(fileName, userName);
    strcat(fileName, ".txt"); //creates userName.txt
    FILE *pUser = fopen(fileName, "w"); //rerwites file
    fprintf(pUser, "%s\ncandidate", password);
    fclose(pUser);
    FILE *pVo = fopen("vote.txt", "a+");
    fprintf(pVo, "0\n"); //they have 0 votes
    fclose(pVo);
    printf("\nYou have succesfully become a candidate!\n");
    exit(0);
}
void vote(char userName[255], char password[255]){
    printf(".......VOTING SYSTEM LOADING.......\n");
    printf("The current candidates are, with the amount of votes of: ");
    FILE *pCandi = fopen("candidate.txt", "r"); //opens candidate file to read
    FILE *pVote = fopen("vote.txt", "a+"); //creates votes file if it doesnt exist
    int candidateNumber = 0;
    char temp[255];
    char throwaway;
    char candidateNames[255][255]; //double array to store candidate names
    int votes[255]; //array to store vote numbers
    while(fgets(temp, 255, pCandi)){
        candidateNumber++;
    }
    rewind(pCandi);
    for(int i = 0; i < candidateNumber; i++){
        fgets(candidateNames[i], 255, pCandi);
        candidateNames[i][strlen(candidateNames[i])-1] = '\0'; //removes whitespace at end of name
        fgets(temp, 255, pVote);
        votes[i] = atoi(temp); //converts the string to an integer
        if(i == candidateNumber - 1){
            printf("%s, %d\n", candidateNames[i], votes[i]);
        }
        else{
            printf("%s, %d || ", candidateNames[i], votes[i]); //prints out candidate names and their votes
        }
    }
    scanf("%c", &throwaway); //input buffer
    int candidNumber = 0;
    bool candidateExists = false;
    while (candidateExists == false){
        printf("Please enter the name of the candidate you would like to vote for: ");
        fgets(temp, 255, stdin);
        temp[strlen(temp)-1] = '\0'; //removes whitespace
        for(int j = 0; j < candidateNumber; j++){
            if(strncmp(temp, candidateNames[j], strlen(candidateNames[j])) == 0){
                candidateExists = true;
                candidNumber = j;
            }
        }
        if(candidateExists == false){
            printf("The candidate you voted for does not exist, try again!\n");
        }
    }
    printf("VOTING FOR %s\n", candidateNames[candidNumber]);
    rewind(pVote);
    int voteStorage[255]; //to store votes
    for(int i = 0; i < candidateNumber; i++){
        fgets(temp, 255, pVote);
        if (i != candidNumber){ //not candidate vote
            voteStorage[i] = atoi(temp); //converts to int
        }
        else{
            voteStorage[i] = atoi(temp) + 1;
        }
    }
    fclose(pVote);
    FILE *pVoteFileAgain = fopen("vote.txt", "w"); //reopens file with the purpose of rewriting everything
    for(int i = 0; i < candidateNumber; i++){
        fprintf(pVoteFileAgain, "%d\n", voteStorage[i]);
    }
    fclose(pVoteFileAgain);
    fclose(pCandi);
     //need to add name of person voted onto user file so if they want to withdraw vote, it is easy to 
    char fileName[255];
    strcpy(fileName, userName);
    strcat(fileName, ".txt"); //creates userName.txt
    FILE *pUseragain = fopen(fileName, "w"); //rerwites file
    fprintf(pUseragain, "%s\n%s", password, candidateNames[candidateNumber - 2]);
    fclose(pUseragain);
    //create a vote file, which matches to the order of names and add it to an array
    //e.g. user file: user1, user2    vote file: 1, 2
    //add votes to each user file
    //run through file of candidates and read amount of votes that each candidate has
}
void withdrawVote(){
    printf("Redacting vote\n");
}

void removeCandidate(char userName[255], char password[255]){
    printf("REMOVING CANDIDATE\n");
    char fileName[255];
    strcpy(fileName, userName);
    strcat(fileName, ".txt"); //creates userName.txt
    FILE *pUser = fopen(fileName, "w"); //rerwites file
    fprintf(pUser, "%s\nno", password);
    fclose(pUser);
    char candidates[255][255]; //an array to store candidate names
    FILE *pCandid = fopen("candidate.txt", "a+");
    char candidateName[255];
    int i = 0; 
    while (fgets(candidateName, 255, pCandid)){
        if(strncmp(candidateName, userName, strlen(userName)) != 0){ //if name on file is not user name
            for(int k = 0; k < strlen(candidateName); k++){
                strcpy(candidates[i], candidateName); //copy name on file to array
            }
            i++; //i is the amount of names
        }
    }
    fclose(pCandid);
    candidates[i+1][0] = '\0'; //null termiantor
    recreateCandidatelist(i, candidates);
}

void recreateCandidatelist(int i, char candidates[255][255]){
    FILE *pCandida = fopen("candidate.txt", "w"); //overwrites the old candidate file
    // if (pCandida == NULL){ //wtf if i do this then segmentatoin error????
    //      printf("Error!\n");
    //      exit(0);
    // }
    int j = 0;
       //while(isspace(candidates[j]) != 0){ //if it is not blank
        while(strcmp(candidates[j], " ") != 0 && candidates[j][0] != '\0'){ //detects blankspace which solved a bunch of issues
        fprintf(pCandida, "%s", candidates[j]);
        printf("%s", candidates[j]);
        j++;
       }
    fclose(pCandida);
    printf("\nYou have succesfully removed yourself from candidateship!\n");
    exit(0);
}
void viewVotes(){
     printf("The current candidates are, with the amount of votes of: ");
    FILE *pCanddi = fopen("candidate.txt", "r"); //opens candidate file to read
    FILE *pVotte = fopen("vote.txt", "a+"); //creates votes file if it doesnt exist
    int candidateNumber = 0;
    char temp[255];
    char throwaway;
    char candidateNames[255][255]; //double array to store candidate names
    int votes[255]; //array to store vote numbers
    while(fgets(temp, 255, pCanddi)){
        candidateNumber++;
    }
    rewind(pCanddi);
    for(int i = 0; i < candidateNumber; i++){
        fgets(candidateNames[i], 255, pCanddi);
        candidateNames[i][strlen(candidateNames[i])-1] = '\0'; //removes whitespace at end of name
        fgets(temp, 255, pVotte);
        votes[i] = atoi(temp); //converts the string to an integer
        if(i == candidateNumber - 1){
            printf("%s, %d\n", candidateNames[i], votes[i]);
        }
        else{
            printf("%s, %d || ", candidateNames[i], votes[i]); //prints out candidate names and their votes
        }
    }
    fclose(pCanddi);
    fclose(pVotte);
}