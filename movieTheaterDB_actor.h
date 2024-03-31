//
// Created by Jeremy Ro on 2023-11-24.
//
// movieTheaterDB_actor.h

#ifndef INC_251319988_ASSIGNMENT5_MOVIETHEATERDB_ACTOR_H
#define INC_251319988_ASSIGNMENT5_MOVIETHEATERDB_ACTOR_H

typedef struct Actor {
    int code;
    char *name;
    int age;
    char *imdbProfile;
    struct Actor *next;
    char *filename;
} Actor;

// Function prototypes
void insertActor(Actor **head);
void searchActor(Actor *head);
void updateActor(Actor *head);
void printActors(Actor *head);
void eraseActor(Actor **head);
void dumpActors(const Actor *head, const char *filename);
void restoreActors(Actor **head, const char *filename);

#endif //INC_251319988_ASSIGNMENT5_MOVIETHEATERDB_ACTOR_H
