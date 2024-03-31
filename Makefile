all: program # This is the default target - make with no arguments will run instructions for all the files

# This part defines how to build the program executable
program: movieTheaterDB.o movieTheaterDB_actor.o movieTheaterDB_movie.o
	gcc -o program movieTheaterDB.o movieTheaterDB_actor.o movieTheaterDB_movie.o

# compilation of movieTheaterDB.c source file into its corresponding object file
movieTheaterDB.o: movieTheaterDB.c
	gcc -c movieTheaterDB.c

# same as above - compilation of source file into object file
movieTheaterDB_actor.o: movieTheaterDB_actor.c
	gcc -c movieTheaterDB_actor.c

# compilation of movieTheaterDB_movie.c file into its corresponding object file
movieTheaterDB_movie.o: movieTheaterDB_movie.c
	gcc -c movieTheaterDB_movie.c

# removes all generated object files and the final executable - ensure a new rebuild can be done
clean:
	rm -f *.o program
