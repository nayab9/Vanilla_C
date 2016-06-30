#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include <string.h>

/* Inserts item at the end of the Linked List */
Node* insertAtEnd(Node *head, char* name, int line_seen, int vowel_count) {
    // bool to see if item already exists
    int exists = 0;
    
    // Create the new node to be inserted
    Node *newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->name = malloc(strlen(name));
    newNode->count = 1;
    strcpy(newNode->name, name);
    newNode->vowel_count = vowel_count;
    newNode->first_seen = -1;
    newNode->last_seen = -1;
    
    // No elements, create head
    if (head == NULL) {
        newNode->first_seen = line_seen;
        newNode->last_seen = line_seen;
        head = newNode;
    } else {
        // Append to list
        Node *temp = head;
        Node *prev = NULL;
        while (temp != NULL) {
            // Check if string exists
            if (strcmp(temp->name, name) == 0) {
                // Increment its counter
                temp->count++;
                exists = 1;
                temp->last_seen = line_seen;
                break;
            } else {
                // No match found, continue loop
                prev = temp;
                temp = temp->next;
            }
        }
        if (exists == 0) {
            prev->next = newNode;
            newNode->first_seen = line_seen;
            newNode->last_seen = line_seen;
        }
    }

    return head;
}

void findMostVowels(Node *head) {
    Node *mostVowels = head;
    Node *temp = head;
    while (temp != NULL) {
        if (temp->vowel_count > mostVowels->vowel_count) {
            mostVowels = temp;
        } else if (temp->vowel_count == mostVowels->vowel_count) {
            if ((int)strlen(temp->name) > (int)strlen(mostVowels->name)) {
                mostVowels = temp;
            } else if ((int)strlen(temp->name) == (int)strlen(mostVowels->name)) {
                if (temp->last_seen > mostVowels->last_seen) {
                    mostVowels = temp;
                }
            }
        }
        temp = temp->next;
    }
    
    printf("Name with the most vowels: %s\n", mostVowels->name);
    printf("Number of times above name seen: %d\n",mostVowels->count);
    printf("Above word first seen: %d\n", mostVowels->first_seen);
    printf("Above word last seen: %d\n", mostVowels->last_seen);
}

// Utility function to print the entire list
void printList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("Name: %s, Count: %d\n",temp->name, temp->count);
        temp = temp->next;
    }
    
    printf("---\n");
}

// Returns the size of the list
void printSize(Node *head) {
    int size_counter = 0;
    Node* temp = head;
    while (temp != NULL) {
        size_counter++;
        temp = temp->next;
    }
    printf("Number of unique names: %d\n", size_counter);
}

// Free the memory of the list
void freeList(Node *head) {
    Node* temp = head;
    
    while (head != NULL) {
        head = head->next;
        // Free the name string
        free(temp->name);
        // Free the Node
        free(temp);
        temp = head;
    }
}
