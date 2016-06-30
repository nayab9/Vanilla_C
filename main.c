/* This application will use a Linked List to input data from stdin,
   and parses each line for 1 or more names.
   Each name must be camelcase formatted to be valid.
   
   The application will print the following:
   Total number of lines read in,
   Total number of names (can be multiple names per line), and
   Total number of unique names.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

int isVowel(char character) {
    int isVowel = 0;
    
    if (character >= 'A' && character <= 'Z') {
        // convert to lower case for the vowel check
        character = character + 'a' - 'A';
    }
      
    if (character == 'a' || character == 'e' || character == 'i' 
                         || character == 'o' || character == 'u') {
        isVowel = 1;
    }
 
    return isVowel;
}

int main() {
    
    // This will be the head of the linked list
    Node *head = NULL;
    
    // This pointer points to the lines read from stdin
    char *line = NULL;
    
    // These variables keep track of stats for output at the end
    int lineCounter = 0;
    int nameCounter = 0;
    int vowelCounter = 0;
    size_t size = 0;
    
    // flag used for finding a validname
    int validName = 1;
    
    // this string pointer will point to each word in a delimited line
    char *string;
    // these are the delimiters allowed for seperating names per line
    char delimit[]=" ,\t\r\n";
    
    int i;

    // Loop stdin until EOF
    while (getline(&line, &size, stdin) != -1) {
        lineCounter++;
        string = strtok(line, delimit);

        while (string != NULL) {
            vowelCounter = 0;
            validName = 1;
            // A valid name must be larger than 1 char
            if ((int)strlen(string) > 1) {
                // Camel case checker
                if (string[0] >= 'A' && string[0] <= 'Z') {
                    if (isVowel(string[0]) == 1) {
                        vowelCounter++;
                    }
                    for (i = 1; i < (int)strlen(string) - 1; i++) {
                        if (string[i] >= 'a' && string[i] <= 'z') {
                            // Check lower case letters to see if they are vowels
                            if (isVowel(string[0]) == 1) {
                                vowelCounter++;
                            }
                        } else {
                            validName = 0;
                            break;
                        }
                    }
                } else {
                    validName = 0;
                }    
            } else {
                validName = 0;
            }
            
            // if the name is deemed valid, increment counter and insert
            if (validName == 1) {
                nameCounter++;
                head = insertAtEnd(head, string, lineCounter, vowelCounter); 
            }
            // continue parsing the line for additional delimited names
            string = strtok(NULL, delimit);
        }
    }
    
    // Print out the final output requested
    printf("Number of input lines: %d\n", lineCounter);
    printf("Number of input names: %d\n", nameCounter);
    printSize(head);
    findMostVowels(head);
    
    // Free memory
    if (line != NULL) {
        free(line);   
    }
    
    if (head != NULL) {
        freeList(head);
    }
    
    return 0;
}