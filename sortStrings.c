//
//  Programmer: Noran Diaconu
//  Userid: diaconuna
//  Purpose: The program takes as input a list of strings and orders them in correct alphabetical order.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//A list node contains an array of 30 characters to hold one word
//and a pointer to the next list node
struct listNode
{
    char word[30];
    struct listNode * next;
};

//This defines a type called listNodeType that is a struct listNode
typedef struct listNode listNodeType;

void printMessageAndExit(char * message);
//Add the two prototypes for the functions you'll write here

void printWords(listNodeType * first);

listNodeType * insertWords(listNodeType * first, char * newWord);

int main(int argc, char ** argv)
{
   char buffer[30];
   FILE * fp;
   listNodeType * list = NULL; 

   //If there isn't at least two command line arguments, print
   //usage information and exit
   if (argc < 2) printMessageAndExit(NULL);

   fp = fopen(argv[1], "r");
   //If the file can't be opened, print an error message and exit
   if (fp == NULL) printMessageAndExit("File not found"); 

   int count;
   while (fgets(buffer, 30, fp))
   {
      //This read one line of input from the file (up to 30 characters in
      //length). The file contains one word per line thus buffer contains
      //one word.  The word in the buffer is followed by newline ('\n') and
      //the NULL character.  ('\0').


      //Use the strlen function to find the position of the newline
      //and over write it with a NULL character
      count = strlen(buffer);
      buffer[count] = '\0';

      //Next, call a function to insert the word in the linked list (in order)
      list = insertWords(list, buffer);
   }

   //call a function to print out the words in the linked list
   printWords(list);
}

/* 
 * printMessageAndExit:  takes as input a C-string, prints the C-string,
 *                       prints usage information, and causes the program
 *                       to exit
 * parameters:
 *     message - C-string to be printed or NULL
 *
 * returns: none
 */
void printMessageAndExit(char * message)
{
   if (message) printf("%s\n", message);
   printf("Usage: sortStrings <filename>\n");
   exit(0);
}

/*
 * printWords:  prints out the list of words
 *
 * parameters:
 *      first - the list of word nodes
 *
 * returns: none
 */
void printWords(listNodeType * first)
{    
    while (first != NULL)
    {
        printf("%s", first -> word);
        first = first -> next;
    }
}

/*
 * insertWords: inserts the words into a list and orders them
 *
 * parameters:
 *      first - the list of word nodes
 *      newWord - the new word to add to the list
 *
 * returns : listNodeType
 */
listNodeType * insertWords(listNodeType * first, char * newWord)
{
    listNodeType * pointer = (listNodeType *) malloc(sizeof(listNodeType));
    strcpy(pointer -> word, newWord);
    listNodeType * previous = NULL;
    listNodeType * current = first;
    if (first == NULL || strcmp(first -> word, newWord) > 0)
    {
        pointer -> next = first;
        first = pointer;
        return first;
    }
    while (current != NULL && strcmp(current -> word, newWord) <= 0)
    {
        previous = current;
        current = current -> next;
    }
    if (current == NULL)
    {
        previous -> next = pointer;
        pointer -> next = NULL;
    }
    else
    {
        pointer -> next = current;
        previous -> next = pointer;
    }
    return first;
}
