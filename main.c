#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*---------------------------------------------------------------------------------------------------------------------------------------------------------
Fall Semester 2024
Project 3: Bit Big Bug Tug-Word Ladder Builder
Course: CS 211 Programming Practicum
Section: 4pm Lecture Wed & Fri, 12pm Lab Tue
System: Zybooks Advanced IDE and Replitt
Author: Priyanjali Rudra

Description:
The Purpose of this game is to create a word ladder, the word ladder starts and ends with player given words 
And the goal of the game is to reach the final word from the starting word by only changing one letter at a time but still having a valid english word.
The game continues until the player reaches the final word or reaches the maximum height of the ladder also specified by the player.
------------------------------------------- -----------------------------------------------------------------------------------------------------------*/

/*
Task 1: StrCmpCnt() returns the number of differences two words have between eachother. 
Difference in length also counts as a difference.
StrCmpCnt takes in as parameters, word1 and word2, which are of type char pointers. 
Each index contains one letter and can be reached by incrementing its respective word's char pointer.
StrCmpCnt() is utilized again in checkForValidWord( ) to ensure that every word in the ladder has only a 1 letter difference.
*/
int strCmpCnt(char* word1, char* word2) {

    int differences = 0; //keeps count of number of difference
    while (*word1 != '\0' || *word2 != '\0') { //keeps incrementing word pointers until BOTH word pointers have reache \0 (Null Character)

        if (*word1 != *word2) { 
            differences++; //Increments differences variable once a difference is found

        }
        if(*word1 != '\0'){ //Ensures that word1 pointer incrementats only if \0 is not met, else only word2 pointer is incremented
            word1++; //moves on to next character of word1

        }
        if(*word2 != '\0'){ //Ensures that word2 pointer incrementats only if \0 is not met, else only word1 pointer is incremented
            word2++; //moves on to next character of word1

        }

    }
    
    return differences; //returns number of difference between word1 and word2

}

/*
Task 2: StrCmpInd() returns the index where the difference has been found between two words. 
Since both words are the same length and the game requires only a one letter difference between the two words, as checked by strCmpCnt(), 
the function returns index as soon as it finds a difference to avoid looping the entire word pointers, unless both words are the same.
StrCmpInd() takes in as parameters, word1 and word2, which are of type char pointers. 
Each index contains one letter and can be reached by incrementing its respective word's char pointer.
StrCmpInd() is utilized again in displayCompleteLadder( ) to accurately create the completed word ladder display,
the word ladder is a stack of valid words with a ^ character placed under the index of where the difference can be found for each word.
*/
int strCmpInd(char* word1, char* word2) {

    int index = 0; //stores index of where difference is found between the two words
    while (*word1 != '\0' || *word2 != '\0') {

        if(*word1 != *word2) { //keeps incrementing word pointers until BOTH word pointers have reache \0 (Null Character)
            return index; //immediately returns index the moment a difference is found, without looping through the entirety of both words
        }

        if(*word1 != '\0'){ //Ensures that word1 pointer incrementats only if \0 is not met, else only word2 pointer is incremented
            word1++; //moves on to next character of word1
        }

        if(*word2 != '\0'){ //Ensures that word2 pointer incrementats only if \0 is not met, else only word1 pointer is incremented
            word2++; //moves on to next character of word2
        }

        index++; //if char at index is not different, moves on to the next index

    }
    return -1; //if no difference is found function returns -1

}

/*
Task 3: appendWord() adds the words read from dictionary.txt that fit the word length requirement into a words pointer array. 
Also adds during gameplay the words that meet the checkForValidWord( ) requirements into the ladder pointer array introduced later.
appendWord() takes in parameters, pWords pointer array (array of char pointers), pNumWords (int pointer), pMaxWords (int pointer) and newWord (char pointer).
The pWords is the array that newWord is being appended into until pMaxWords is met. If pNumWords = pMaxWords, 
the pWords arry size is doubled to accomodate for new words.
*/
void appendWord(char*** pWords, int* pNumWords, int* pMaxWords, char* newWord) {
    if(*pNumWords == *pMaxWords) { //Checks if max number of words appended is met

        *pMaxWords = *pMaxWords * 2; //Since pNumWords = pMaxWords, pMaxWords is doubled to accomodate for new words.
        //create a new temporary pointer array and allocate enough space to accomodate pMaxWords double words
        char** newArray = (char**)malloc(*pMaxWords * sizeof(char*)); 

        //iterates through original pWords array, and assignes index by index the data within pWords array into newArray
        for(int i = 0; i < *pNumWords; i++){ 
            newArray[i] = (*pWords)[i];

        }

        free(*pWords); //deletes all info held with *pWords 
        *pWords = newArray; //assigns information withing newArray + augmented space into pWords
        
    }

    //if pNumWords is not equal to pMaxWords
    char* newArrayWord = (char*)malloc(strlen(newWord) + 1); //space is allocated to accomodate the new word
    strcpy(newArrayWord, newWord); //newWord is copied into newArrayWord

    (*pWords)[*pNumWords] = newArrayWord; //Last index of pWords is assigned with newArrayWord
    (*pNumWords)++; //pNumWords is incremented, since number of words has increased

}

/*
Task 5: linSearchForWord() checks whether a user input word is a valid English word and is of correct length. 
linSearchForWord() does so by iterating through words pointer array, which contains all valid words of specified length by parsing through dictionary.txt.
linSearchForWord() takes in parameters, words pointer array, numWords (int), and findWord (char pointer).
The words pointer array as mentioned before contains all valid words of specified length, 
numWords is the number of words in the words pointer array and findWord is the user inputted word being check of its validity.
linSearchforWord is used in checkForValidWord() to ensure words inserted by user are valid
*/
int linSearchForWord(char** words, int numWords, char* findWord) { 

    for (int i = 0; i < numWords; i++) { //iterates through words pointer array

        if (strcmp( words[i], findWord) == 0) { //if user given findWord wound in words
            return i; //immediately return index where findWord was found, instead of looping through the enitrety of words

        }

    }
  
    return -99; //if findWord is not found, word is not valid and -99 is returned
}


/*
Task 6: checkForValidWord( ) checks whether a user input word is valid by checking multiple requirements utilizing many previously written functions.
The Requirements being checked are:
-Whether the user inputted DONE, therefore stopping the game.
-Whether the user inputted a word of correct specified length, therefore prompting code to ask user to input a different word.
-Whether the user inputted word is an English word in the dictionary.txt file provided
-Whether the user inputter word is only a one letter difference from the previous word in the ladder pointer array.

checkForValidWord() takes in the paramenters, words pointer array, numWords (int), wordLen (int), ladder pointer array, ladderHeight (int), and aword (char pointer)
words pointer array contains all valid words of specified length by parsing through dictionary.txt, numWords is the number of words in words pointer array,
wordLen is the specified length each word should be in the ladder array, ladder pointer array is where the valid words are being appended into, ladderHeight is the 
max height this game will run for, and aWord is the user Inputted word being checked of its validity.
*/
bool checkForValidWord(char** words, int numWords, int wordLen, char** ladder, int ladderHeight, char* aWord) {

    if (strcmp("DONE", aWord) == 0) { //Checks whether User Inputted DONE
        printf("Stopping with an incomplete word ladder...\n");
        return true; //Returns true to stop game play by exiting while loop in main
    } 

    else if (strlen(aWord) != wordLen) { //Checks whether User Inputted incorrect word length
        printf("Entered word does NOT have the correct length. Try again...\n");
        return false; //Returns false to prompt user for a different word
    }

    else if (linSearchForWord(words, numWords, aWord) == -99) { //Checks whether User Inputted valid english word
        printf("Entered word NOT in dictionary. Try again...\n");
        return false; //Returns false to prompt user for a different word
    }

    else if (strCmpCnt(ladder[ladderHeight - 1], aWord) != 1) { //Checks whether User Inputted word only one letter difference from the previous word
        printf("Entered word is NOT a one-character change from the previous word. Try again...\n");
        return false; //Returns false to prompt user for a different word
    }

    else {
        printf("Entered word is valid and will be added to the word ladder.\n");
        return true; //exits while loop in main, word is valid and appended
    }     

}

/*
Task 7: isLadderComplete() Ends Game by checking if ladder is complete. Game is won by reaching the final word given by the user, 
if the last word appended in the ladder is equal to the final word, that means the game has been won and ends.
isLadderComplete() return true if Ladder is complete and false otherwise.
isLadderComplete() takes in parameters, pointer array ladderWords, height (int) and char pointer finalWord.
pointer array LadderWords hold all the words the user inputed that were also valid in order, height is the length of the LadderWords pointer array and 
finalWord is the winning word of the game that need to be reached.
*/
bool isLadderComplete(char** ladderWords, int height, char* finalWord) {
    
    if (strcmp(ladderWords[height - 1], finalWord) == 0){ //if the last word stored in ladderWords is equal to the final Word given by the user
        return true; //Game is won

    }
    
    return false; //Game keeps going unless maxHeight(ho many iterations game is played) is reached
}

/*
Task 9: displayIncompleteLadder() Displays Ladder while the game is being played.
the words are stacked in order of insertion by the user, which means the first word is at the bottom of the stack
while the most recent word is at the top.
displayIncompleteLadder( ) takes in parameters pointer array ladderWords and height (int).
ladderWords contains all the user-inputted words that pass the game requirements and height is the length of the LadderWords pointer array.
*/
void displayIncompleteLadder(char** ladderWords, int height) {
    int elipses = 0;
    while(elipses < 3){ //Aesthetic choice that addes elipses ... for three rows at the top of the word stack to indicate the game is still going
        printf("  ...\n");
        elipses++;
    }
    
    for (int i = height-1; i >= 0; i--) { //iterates through ladderWords backwords so the oldest word is at the bottom of the stack and newest at the top.
        printf("  %s\n", ladderWords[i]);
    }
    

}

/*
Task 10: displayCompleteLadder() Displays the completed ladder after the game has been won.
Similar to displayIncompleteLadder words are stacked in order of insertion by user, but also seperated by a line that indicates the letter 
that has changed using a ^ character, Since each word should only have a single letter difference than the word before and after itself.
displayCompleteLadder( ) takes in parameters pointer array ladderWords and height (int).
ladderWords contains all the user-inputted words that pass the game requirements and height is the length of the LadderWords pointer array.
Ex. Output
"  code"
"    ^ "
"  cove"
"   ^  "
"  cave"
"  ^   "
"  gave"
"    ^ "
"  gate"
"  ^   "
"  date"
"     ^"
"  data
*/
void displayCompleteLadder(char** ladderWords, int height) {

    for (int iteration = height-1; iteration >= 0; iteration--) { //iterates through ladderWords and prints each word
        printf("  %s\n", ladderWords[iteration]);
        
        if(iteration > 0){ //while first word has not been met 

            //Use strCmpInd() to find the index of the changed letter, compare word at each index of the ladder with the word in the index before it 
            int index = strCmpInd(ladderWords[iteration], ladderWords[iteration-1]); 
            //char array (string) that will hold only blank spaces ' ' except '^' at the index where a difference has been found.
            char display[strlen(ladderWords[iteration])+1];
            //set the last index of the display char arry with a null character \0
            display[strlen(ladderWords[iteration])] = '\0';
                
            for (int j = 0; j < strlen(ladderWords[iteration]); j++){ // iterates through each word within LadderWords

                if (j == index){
                    display[j] = '^'; //stores char ^ if index where a difference has beeen found is met in display char array

                }
                else{
                    display[j] = ' '; //otherwise stores a ' '

                }

            }
            printf("  %s\n", display); //prints string with ^ at difference
        }

    }

}

//MAIN Starts here
int main(int argc, char* argv[]) {

    printf("\nProcessing command-line arguments...\n");

    int wordLen = 0; //word length initially set as 0
    int maxLadder = 1; //Ladder Height initially set as 1
    char dict[100] = "notAfile";   //Dictionary file, initially set as an invalid file name   
    char startWord[30] = "notAword"; //Starting word, initially set as an invalid start word   
    char finalWord[30] = "notValid"; //Final word, initially set as an invalid final word

    //-----------------------------------------------------------------------------------------------------------------------------------------------------
    /*
    Task 12: This section of the code allows command-line arguments, which allows the user to change setting of the game such as word length, Ladder height, 
    dictionary file, start word and final word. The code reads the argv arguments, and makes changes if it meets the following:

    [-n] = sets word length for word ladder;
    if [wordLen] is not a valid input (cannot be less than 2 or greater than 20), or missing from command-line arguments,
    then let user set it using interactive user input.

    [-m] = sets maximum word ladder height;
    [maxLadder] must be at least 2;
    if [maxLadder] is invalid or missing from command-line arguments, then let user set it using interactive user input.

    [-d] = sets dictionary file; 
    if [dictFile] is invalid (file not found) or missing from command-line arguments, 
    then let user set it using interactive user input

    [-s] = sets the starting word; 
    if [startWord] is invalid (not in dictionary or incorrect length) or missing from command-line arguments, 
    then let user set it using interactive user input

    [-f finalWord] = sets the final word; 
    if [finalWord] is invalid (not in dictionary or incorrect length) or missing from command-line arguments, 
    then let user set it using interactive user input
    */

    for(int i = 0; i < argc; i++) {
        if(strcmp(argv[i],"-n") == 0) { //searches for -n in argv
            sscanf(argv[i + 1], "%d", &wordLen); //sets word length for word ladder
        }
        else if(strcmp(argv[i],"-m") == 0) { //searches for -m in argv
            sscanf(argv[i+1], "%d",&maxLadder); //sets maximum word ladder height
        }
        else if(strcmp(argv[i],"-d") == 0) { //searches for -d in argv
            strcpy(dict, argv[i + 1]); //sets dictionary file
        }
        else if(strcmp(argv[i], "-s") == 0) { //searches for -s in argv
            strcpy(startWord, argv[i+1]); //sets the starting word
        }
        else if(strcmp(argv[i], "-f") == 0) { //searches for -f in argv
            strcpy(finalWord, argv[i+1]); //sets the final word
        }
    }
    //-----------------------------------------------------------------------------------------------------------------------------------------------------

    printf("Interactively (re)setting invalid parameters:\n");

    // set word length using interactive user-input if necessary
    int numInputs = 1;
    while (numInputs > 0 && (wordLen < 2 || wordLen > 20)) {
        printf("Invalid word length = %d\n", wordLen);
        printf("Enter a valid word length (must be 2-20): ");
        numInputs = scanf("%d",&wordLen);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }


    // set max ladder height using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && maxLadder < 2) {
        printf("Invalid max ladder height = %d\n", maxLadder);
        printf("Enter a valid max ladder height (must be >1): ");
        numInputs = scanf("%d",&maxLadder);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }

    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    FILE* fileTry = fopen(dict,"r");
    numInputs = 1;
    while (numInputs > 0 && fileTry == NULL) {
        printf("Dictionary file %s not found...\n", dict);
        printf("Enter filename for dictionary: \n");
        numInputs = scanf("%s", dict);

        fileTry = fopen(dict,"r");
    }
    fclose(fileTry);
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }

    // build the [words] array, a heap-allocated array of C-strings
    // where the words are a read-in from the dictionary file
    // and only those words of the desired length [wordLen] 

    int numWords = 0; // initially, no words in the array
    int maxWords = 4; // initially, capacity = 4
    char** words = (char**)malloc(maxWords*sizeof(char*));

    //-----------------------------------------------------------------------------------------------------------------------------------------------------
    /*
    Task 4: The goal of task 4 is to fill words pointer array with valid words of the correct length by reading in the dictionary.txt file.
    Storage has already been allocated to words pointer array before beginning task 4.
    */
    FILE *file_ptr; // create file_ptr to open dictionary file
    file_ptr = fopen(dict, "r"); //open user-input dictionary in read-mode, stored in variable dict

    if (NULL == file_ptr) { //if file_ptr is empty/Null there is no file to open.

        printf("file can't be opened \n");
        return -1;
    }


    char* buffer[200]; //create char pointer array to store each word from the dictionary
    while(fscanf(file_ptr, "%s", buffer) == 1){ //scan/read each word of dictionary and store word into buffer

        int length = strlen(buffer); //store length of word into int length
        if(length == wordLen){ //if word is of correct length

            appendWord(&words, &numWords, &maxWords, buffer);  //add word to words pointer array that stores all valid words of the correct size
        }

    } 

    fclose(file_ptr); //close dictionary file
    //-----------------------------------------------------------------------------------------------------------------------------------------------------

    printf("The dictionary contains %d words of length %d.\n",numWords,wordLen);
    printf("Max size of the dynamic words array is %d.\n",maxWords); 
    printf("\n");

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("Dictionary %s contains insufficient %d-letter words...\n",dict,wordLen);
        printf("Terminating program...\n");
        return -1;
    }

    // resetting start word using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && linSearchForWord(words,numWords,startWord) < 0) {
        printf("Start word %s is not valid...\n", startWord);
        printf("Enter a valid start word: ");
        numInputs = scanf("%s", startWord);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }

    // resetting final word using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && linSearchForWord(words,numWords,finalWord) < 0 ) {
        printf("Final word %s is not valid...\n", finalWord);
        printf("Enter a valid final word: ");
        numInputs = scanf("%s", finalWord);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }


    printf("\nWelcome to the CS 211 Word Ladder Builder!\n");
    printf("\n"); 

    printf("Your goal is to make a word ladder between two ");
    printf("%d-letter words: \n  %s -> %s\n\n",wordLen, startWord,finalWord);  

    // Allocating the word ladder for the maximum allowed height
    char** ladder = (char**)malloc(maxLadder*sizeof(char*));
  
    int ladderHeight = 0; // initially, the ladder is empty

    // add the start word to the ladder, i.e. the "bottom rung"
    appendWord(&ladder,&ladderHeight,&maxLadder,startWord);

    char aWord[30] = "XYZ";
    printf("\n");

    // Let the user build a word ladder interactively & iteratively.
    // First, check that ladder is not too long AND not complete.

    //-----------------------------------------------------------------------------------------------------------------------------------------------------
    /*
    Task 8: The goal of this task was to modify the while loop condition so that the game continues running until the following events takes place:
    -The ladder has reached maximum allowed height
    -The user is attempting to stop the game by entering "DONE"
    -The Ladder is complete, which means the last word added to the ladder is equal to the final word.
    Task 8 uses isLadderComplete function to check for the final event
    */

    while ((ladderHeight != maxLadder) && (!isLadderComplete(ladder,ladderHeight,finalWord)) && (strcmp(aWord,"DONE") != 0)) {   // modify this line 

        printf("The goal is to reach the final word: %s\n",finalWord);
        printf("The ladder is currently: \n");
        displayIncompleteLadder(ladder,ladderHeight);
        printf("Current ladder height: %d\n",ladderHeight);
        printf("Maximum ladder height: %d\n",maxLadder);
        printf("Enter the next word (or DONE to stop): ");
        scanf("%s",aWord);
        printf("\n");

        // Make sure the entered word is valid for the next ladder rung;
        // if not, repeatedly allow user to enter another word until one is valid
        while (!checkForValidWord(words, numWords, wordLen, ladder, ladderHeight, aWord)) {

            printf("Enter another word (or DONE to stop): ");
            scanf("%s",aWord);
            printf("\n");

        }

        // add the entered word to the ladder (unless it is "DONE")
        if (strcmp(aWord,"DONE") != 0) {

            appendWord(&ladder,&ladderHeight,&maxLadder,aWord);

        }
        printf("\n");

    }
    //-----------------------------------------------------------------------------------------------------------------------------------------------------

    // Check if the built word ladder is complete and 
    // display the word ladder appropriately. 
    if (isLadderComplete(ladder, ladderHeight, finalWord)) {
        printf("Word Ladder complete!\n");
        displayCompleteLadder(ladder,ladderHeight);
        printf("Word Ladder height = %d. \n", ladderHeight);
        printf("Can you find a shorter Word Ladder next time??? \n");
    } else {
        if (ladderHeight == maxLadder) printf("The Word Ladder reached the maximum height.\n");
        printf("The final Word Ladder is incomplete:\n");
        displayIncompleteLadder(ladder,ladderHeight);
        printf("Word Ladder height = %d. \n", ladderHeight);
        printf("Can you complete the Word Ladder next time??? \n");
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------
    /*
    Task 11: The Goal of Task 11 is to free all heap allocated memory to avoid memory leaks. 
    The only two heap allocated memory objects that are still yet to be free is the  char** words pointer array and the char** ladder pointer array.
    Therefore, both words and ladder would need to be freed along with each individual index of both pointer arrays.
    */
    for (int i = 0; i < numWords; i++) { //iterate through words pointer array
        free(words[i]); //individually free each index
    }
    free(words); //free words completely

    for (int i = 0; i < ladderHeight; i++) { //iterate through ladder pointer array
        free(ladder[i]); //individually free each index
    }
    free(ladder); //free words completely
    //-----------------------------------------------------------------------------------------------------------------------------------------------------
    
    return 0;
}
