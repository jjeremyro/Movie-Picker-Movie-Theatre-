//
// Created by Jeremy Ro on 2023-11-24.
//
// movieTheaterDB_actor.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movieTheaterDB_actor.h"

// This function inserts a new actor
void insertActor(Actor **head) {
    int code;
    int age;
    char *name = NULL;
    char *imdbProfile = NULL;
    size_t size = 0;

    printf("Enter actor code: "); scanf("%d", &code); // reads actor code
    while (getchar() != '\n'); // clears input buffer

    // Checks for duplicate actor codes
    for (Actor *current = *head; current != NULL; current = current->next) {
        if (current->code == code) { printf("Duplicate actor code.\n"); return; } // if duplicate found then print error message
    }

    printf("Enter actor name: ");
    getline(&name, &size, stdin); // Reads name and dynamically allocates memory so that we can take in any length string
    name[strcspn(name, "\n")] = 0; // Removes newline character

    printf("Enter actor age: ");
    scanf("%d", &age); // takes age input and assigns it to age variable
    while (getchar() != '\n'); // clears input buffer after reading age

    if (age < 0 || age > 120) { // if the age is outside the valid range, then print error message
        printf("Invalid age. Age must be between 0 and 120.\n");
        free(name); // frees allocated name memory
        return; // Exits program
    }

    printf("Enter IMDB profile URL: ");
    size = 0;
    getline(&imdbProfile, &size, stdin); // read IMDb URLL dynamically
    imdbProfile[strcspn(imdbProfile, "\n")] = 0; // removes newline character

    Actor *newActor = (Actor *)malloc(sizeof(Actor)); // allocates memory for actor
    if (!newActor) { printf("Failed to allocate memory.\n"); free(name); free(imdbProfile); return; } // memory allocation check

    newActor->code = code; newActor->name = name; // assigns code and name
    newActor->age = age; newActor->imdbProfile = imdbProfile; // assigns age and IMDb URL
    newActor->next = *head; *head = newActor; // inserts at head
    printf("Actor added successfully.\n");
}

// This function searches for an actor by code
void searchActor(Actor *head) {
    int code; printf("Enter actor code: "); scanf("%d", &code); // prompts and reads actor code


    for (Actor *current = head; current != NULL; current = current->next) { // loops indefinetly through actors until it finds matching code
        if (current->code == code) {
            printf("Actor Code: %d\nActor Name: %s\nAge: %d\nIMDB Profile: %s\n", current->code, current->name, current->age, current->imdbProfile);
            return; // exit function
        }
    }
    printf("Actor not found.\n");
}

// This function updates an existing actor's details
void updateActor(Actor *head) {
    int code; printf("Enter actor code: ");
    scanf("%d", &code); // prompts and reads actor code

    for (Actor *current = head; current != NULL; current = current->next) { // loops indefinitely through actors until it finds the matching code
        if (current->code == code) {
            printf("Enter new actor name: ");
            scanf(" %[^\n]", current->name);
            printf("Enter new actor age: ");
            scanf("%d", &current->age); // updates age
            if (current->age < 0 || current->age > 120) { // if the inputted age is not between 0 and 120, then error message
                printf("Invalid age. Age must be between 0 and 120.\n");
                return;
            } // checks for valid age input
            printf("Enter new IMDB profile URL: ");
            scanf(" %[^\n]", current->imdbProfile); // updates IMDB URL
            printf("Actor updated successfully.\n");
            return;
        }
    }
    printf("Actor not found.\n");
}

// This function prints all actors
void printActors(Actor *head) {
    printf("Actor Code    Actor Name        Age    IMDB Profile\n");
    for (Actor *current = head; current != NULL; current = current->next) {  // loops through actors & prints info
        printf("%-14d%-18s%-7d%s\n", current->code, current->name, current->age, current->imdbProfile);
    }
}

// This function erases an actor from the list
void eraseActor(Actor **head) {
    int code; printf("Enter actor code: "); scanf("%d", &code); // prompts and reads actor code (assigns actor code to var code for future use)

    Actor *current = *head, *prev = NULL;
    while (current != NULL && current->code != code) { prev = current; current = current->next; } // loop indefinetly through actors to find and keep track of the previous actor

    if (current == NULL) { printf("Actor not found.\n"); return; } // exits program if an actor is not found

    if (prev == NULL) { *head = current->next; } // removes actor from head
    else { prev->next = current->next; } // removes actor from middle

    free(current); // frees memory of the erased actor
    printf("Actor deleted successfully.\n");
}

// dumpActors -> saves list of actors to a file
void dumpActors(const Actor *head, const char *filename) {
    FILE *file = fopen(filename, "wb"); // open file to write
    if (!file) {
        perror("Error opening file");
        return;
    }

    for (const Actor *current = head; current != NULL; current = current->next) {
        fwrite(&(current->code), sizeof(current->code), 1, file); // writes the actor code and age
        fwrite(&(current->age), sizeof(current->age), 1, file);

        size_t nameLen = strlen(current->name) + 1;  // includes null terminator
        fwrite(&nameLen, sizeof(nameLen), 1, file); // Writing the length of name
        fwrite(current->name, nameLen, 1, file); // actual name

        size_t profileLen = strlen(current->imdbProfile) + 1; // Same process for the IMDb profile.
        fwrite(&profileLen, sizeof(profileLen), 1, file); // Length
        fwrite(current->imdbProfile, profileLen, 1, file); // URL
    }

    fclose(file); //closes file
}

// restoreActors
void restoreActors(Actor **head, const char *filename) {
    FILE *file = fopen(filename, "rb"); // opens file for reading
    if (!file) {
        perror("Error opening file");
        return;
    }

    Actor buffer; // Temporary storage for each actor
    while (fread(&(buffer.code), sizeof(buffer.code), 1, file) == 1) { // Loops until EOF.
        fread(&(buffer.age), sizeof(buffer.age), 1, file); // Reads age

        size_t nameLen;
        fread(&nameLen, sizeof(nameLen), 1, file);
        buffer.name = malloc(nameLen); // Allocates memory for the name
        fread(buffer.name, nameLen, 1, file); // read name

        size_t profileLen; // Same process for IMDb URL
        fread(&profileLen, sizeof(profileLen), 1, file);
        buffer.imdbProfile = malloc(profileLen);
        fread(buffer.imdbProfile, profileLen, 1, file);

        Actor *newActor = malloc(sizeof(Actor)); // Creates new actor node.
        *newActor = buffer; // Copy data
        newActor->next = *head; // Adds it to the front of list
        *head = newActor; // Updates head pointer
    }

    fclose(file); // Closes file
}
