//
// Created by Jeremy Ro on 2023-11-24.
//
// movieTheaterDB_movie.h
//

#ifndef INC_251319988_ASSIGNMENT5_MOVIETHEATERDB_MOVIE_H
#define INC_251319988_ASSIGNMENT5_MOVIETHEATERDB_MOVIE_H

// Movie structure definition
typedef struct Movie {
    int code;
    char *name; // pointer to char var name
    char *genre; // pointer to genre var
    float rating;
    struct Movie *next;
} Movie;

void insertMovie(Movie **head);
void searchMovie(Movie *head);
void updateMovie(Movie *head);
void printMovies(Movie *head);
void eraseMovie(Movie **head);
int isValidRating(float rating);
void dumpMovies(const Movie *head, const char *filename);
void restoreMovies(Movie **head, const char *filename);

#endif //INC_251319988_ASSIGNMENT5_MOVIETHEATERDB_MOVIE_H
