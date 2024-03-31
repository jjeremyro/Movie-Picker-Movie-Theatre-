//
// Created by Jeremy Ro on 2023-11-24.
//
// movie.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movieTheaterDB_movie.h"

// This function creates a new movie and inserts it into the linked list
void insertMovie(Movie **head) {
    int code;
    char *name = NULL, *genre = NULL;
    size_t size = 0;
    float rating;

    printf("Enter movie code: ");
    scanf("%d", &code);
    while (getchar() != '\n');  // Clear the input buffer

    // Check for duplicate or invalid code
    for (Movie *current = *head; current != NULL; current = current->next) {
        if (current->code == code || code < 0) {
            printf("Invalid or duplicate movie code.\n");
            return;
        }
    }

    // Dynamically allocate and read movie name
    printf("Enter movie name: ");
    getline(&name, &size, stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline character

    // Dynamically allocate and read movie genre
    size = 0; // Reset bufsize for genre input
    printf("Enter movie genre: ");
    getline(&genre, &size, stdin);
    genre[strcspn(genre, "\n")] = 0; // Remove newline character

    // Read movie rating
    printf("Enter movie rating: ");
    int readItems = scanf("%f", &rating);
    while (getchar() != '\n');  // Clear the input buffer
    if (readItems != 1 || !isValidRating(rating)) {
        printf("Invalid rating. Please enter a value between 0.0 and 10.0.\n");
        free(name); free(genre); // Free allocated memory
        return;
    }

    // creates new movie and assigns values
    Movie *newMovie = (Movie *)malloc(sizeof(Movie));
    if (!newMovie) {
        printf("Failed to allocate memory.\n");
        free(name); free(genre); // frees allocated memory
        return;
    }
    newMovie->code = code;
    newMovie->name = name;
    newMovie->genre = genre;
    newMovie->rating = rating;
    newMovie->next = *head;
    *head = newMovie;

    printf("Movie added successfully.\n");
}

// This function searches for a movie and displays the name, genre, and rating
void searchMovie(Movie *head) {
    int code;
    printf("Enter movie code: ");
    scanf("%d", &code);

    for (Movie *current = head; current != NULL; current = current->next) {
        if (current->code == code) {
            printf("Movie Code: %d\nMovie Name: %s\nMovie Genre: %s\nMovie Rating: %.1f\n", current->code, current->name, current->genre, current->rating);
            return;
        }
    }
    printf("Movie not found.\n");
}

// This function updates a movie
void updateMovie(Movie *head) {
    int code;
    printf("Enter movie code: ");
    scanf("%d", &code);

    for (Movie *current = head; current != NULL; current = current->next) { // iterates over linked list
        if (current->code == code) { // if the current movie's code matches the input code
            printf("Enter updated movie name: ");
            scanf(" %99[^\n]", current->name); // reads updated name and assigns it into the current movie name

            printf("Enter updated movie genre: ");
            scanf(" %24[^\n]", current->genre);

            printf("Enter updated movie rating: ");
            scanf("%f", &current->rating); // Read the updated rating into the current movie's rating field
            if (!isValidRating(current->rating)) { // if new rating is not within the valid range prints error message if rating is invalid
                printf("Invalid rating, enter a value between 0.0 and 10.0\n");
                return;
            }

            printf("Movie updated successfully\n");
            return; // exits the function after updating the movie
        }
    }
    printf("Movie not found\n"); // prints message if no valid movie code was found
}

// This function prints all movie information
void printMovies(Movie *head) {
    printf("Movie Code  Movie Name                  Movie Genre              Movie Rating\n");
    for (Movie *current = head; current != NULL; current = current->next) {
        printf("%-12d%-28s%-25s%.1f\n", current->code, current->name, current->genre, current->rating);
    }
}

// This function deletes a movie
void eraseMovie(Movie **head) {
    int code;
    printf("Enter movie code: ");  // Prompt for the movie code
    scanf("%d", &code);

    Movie *current = *head, *prev = NULL;  // initialization of pointers for traversal

    while (current != NULL && current->code != code) { // Loops indefinitely until it finds movie with input code
        prev = current;  // Keeps track of previous movie
        current = current->next;  // Moves to next movie
    }

    if (current == NULL) { // if the movie is not found in the list prints error message
        printf("Movie not found.\n");
        return;
    }

    if (prev == NULL) { // if movie to be deleted is first in  list updates the head of the list
        *head = current->next;
    } else {
        prev->next = current->next;  // this line bypasses the movie to be deleted
    }

    free(current);  // frees memory allocated for the movie
    printf("Movie deleted successfully.\n");
}

int isValidRating(float rating) {
    return (rating >= 0.0 && rating <= 10.0) ? 1 : 0; // returns 1 if rating is valid and 0 if not valid
}

// dumpMovies: Saving all our movies to a file
void dumpMovies(const Movie *head, const char *filename) {
    FILE *file = fopen(filename, "wb"); // opens file, or creates it if it doesn't exist
    if (!file) {
        perror("Error opening file");
        return;
    }

    const Movie *current = head; // start at the beginning of our movie list
    while (current != NULL) { // Keep going as long as there are movies in list.
        fwrite(current, sizeof(Movie), 1, file); // write current movie to the file
        current = current->next; // Move on to next movie.
    }

    fclose(file); //closes file
}

// restoreMovies
void restoreMovies(Movie **head, const char *filename) {
    FILE *file = fopen(filename, "rb"); // opens the file to read movies
    if (!file) {
        perror("Error opening file");
        return;
    }

    Movie buffer; // temporary spot to keep each movie we read
    while (fread(&buffer, sizeof(Movie), 1, file) == 1) { // read movies until there are no more
        Movie *newMovie = malloc(sizeof(Movie)); // creating memory location for a new movie
        *newMovie = buffer; // copies movie into new memory location
        newMovie->next = *head; // puts new movie at the beginning of the list
        *head = newMovie; // Updates the head to be new movie
    }

    fclose(file); // closes file
}
