//
// Created by Jeremy Ro on 2023-11-24.
//

#include <stdio.h> // includes I/O library
#include "movieTheaterDB_movie.h" // includes all movie functions and structures
#include "movieTheaterDB_actor.h" // includes all actor functions and structures

int main() {
    Movie *movies = NULL; // Starts with no movies
    Actor *actors = NULL; // Starts with no actors
    char op;

    printf("*********************\n");
    printf("2211 Movie Cinema 2.0\n");
    printf("*********************\n");

    while (1) { // Keeps the program running indefinitely unless user inputs 'q' (quit)
        printf("\nEnter operation code (h for help, m for movies, a for actors, q to quit): "); // Prompts user for an operation
        scanf(" %c", &op); // Read's user's input

        switch (op) {
            case 'h': // If user asks for help, display what all inputs mean
                printf("Commands:\n h: Help\n m: Manage movies\n a: Manage actors\n q: Quit\n");
                break;

            case 'm': { // Movie operations
                char movieOp;
                printf("Movie operations (i: Insert, s: Search, u: Update, p: Print, e: Erase, r: Recover, d: dump, b: Back): ");
                scanf(" %c", &movieOp); // Reads input

                switch (movieOp) {
                    case 'i': // Inserts a new movie
                        insertMovie(&movies); // Calls insert movie function
                        break;
                    case 's': // Searches for a movie
                        searchMovie(movies); // Calls search movie function
                        break;
                    case 'u': // Updates a movie
                        updateMovie(movies); // Calls update movie function
                        break;
                    case 'p': // Prints all movies
                        printMovies(movies); // Calls print movies function
                        break;
                    case 'e': // Erases a movie
                        eraseMovie(&movies); // Calls erase movie function
                        break;
                    case 'b': // Go back to main menu
                        break; // exits switch-case
                    case 'd': { // Dump movies
                        char filename[256];
                        printf("Enter filename to dump movies: ");
                        scanf("%s", filename);
                        dumpMovies(movies, filename);
                        break;
                    }
                    case 'r': { // Restore movies
                        char filename[256];
                        printf("Enter filename to restore movies: ");
                        scanf("%s", filename);
                        restoreMovies(&movies, filename);
                        break;
                    }
                    default: // In case of an invalid movie operation code
                        printf("Invalid movie operation code.\n");
                }
                break; // Exit movie operations
            }

            case 'a': { // Actor operations
                char actorOp;
                printf("Actor operations (i: Insert, s: Search, u: Update, p: Print, e: Erase, r: recover, d: dump, b: Back): "); // prompts user for input
                scanf(" %c", &actorOp); // Reads user input

                switch (actorOp) {
                    case 'i': // Inserts a new actor
                        insertActor(&actors); // Calls insert actor function
                        break;
                    case 's': // Searches for an actor
                        searchActor(actors); // Calls search actor function
                        break;
                    case 'u': // Updates an actor
                        updateActor(actors); // Calls update actor function
                        break;
                    case 'p': // Prints all actors
                        printActors(actors); // Calls print actors function
                        break;
                    case 'e': // Erases actor
                        eraseActor(&actors); // Calls erase actor function
                        break;
                    case 'b': // Goes back to main menu
                        break; // Exits switch-case
                    default: // prints message if none of the cases above apply
                        printf("Invalid actor operation code.\n");
                    case 'd': { // Dump actors
                        char filename[256];
                        printf("Enter filename to dump actors: ");
                        scanf("%s", filename);
                        dumpActors(actors, filename);
                        break;
                    }
                    case 'r': { // Restore actors
                        char filename[256];
                        printf("Enter filename to restore actors: ");
                        scanf("%s", filename);
                        restoreActors(&actors, filename);
                        break;
                    }
                }
                break; // Exit
            }

            case 'q': // If user chooses to quit
                // Free all dynamic memory before exiting (to be implemented)
                // freeMovies(&movies);
                // freeActors(&actors);
                printf("Exiting program.\n");
                return 0; // Exits the program

            default:
                printf("Invalid, please enter a valid input.\n");
        }
    }
}
