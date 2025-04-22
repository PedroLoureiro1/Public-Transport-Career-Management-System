#ifndef __PROTOTYPES_H__
#define __PROTOTYPES_H__

#include "constants.h"
#include "structures.h"

/*skips the spaces on the input*/
int skipSpaces(char arguments[], int i);

/*reads a word from the input having in mind the states presented previously
and tells me if I have more arguments to read*/
int readWord(char arguments[], char word[]);

/*gets how many stops the bus given has*/
int totalStops(Bus *bus);

/*verifies if the given bus name already exists*/
Bus* isBus(DataBase *db, char *name);

/*adds the durations of the connections of a given bus*/
double totalDuration(Bus *bus);

/*adds the costs of the connections of a given bus*/
double totalCost(Bus *bus);

/*checks if the second argument is an abbreviantion for inverse*/
int isAbbreviation(char arg2[]);

/*prints all the stops that a bus has according to the connections*/
void printstops(char *name, DataBase *db);

/*prints all the stops starting from the latter to the first of a given bus*/
void printstopsInverse(char *name, DataBase *db);

/*It creates a Bus*/
Bus* createBus(char *name);

/*handle "c" command*/
void busCommand(DataBase *db, char arguments[]);

/*It creates a name referred to a bus*/
BusNames *createName(char *name);

/*counts how many buses pass on the stop given*/
int totalBuses(char *name, DataBase *db);

/*verifies if the name given matches a stop already created*/
Stop* isStop(DataBase *db, char *name);

/*it creates a stop*/
Stop* createStop(DataBase *db, char *name, char *latitude, char *longitude);

/*handles "p" command*/
void stopCommand(DataBase *db, char arguments[]);

/*it creates a new Connection*/
Connection* createConnection(char *arg1,char *arg2,char *arg3,char *arg4,char *arg5);

/* handle "l" command */
void connectionsCommand(DataBase *db, char arguments[]);

/*quicksort implementation*/
void quicksort(char **arr, int left, int right);

/*It gets the number of buses that pass on a certain stops and their names*/
BusNames *numBusesWithNames(char *name, DataBase *db, int *numBuses);

/*handle "i" command*/
void intersectionCommand(DataBase *db);

/*handle "r" command*/
/*remove buses and connections related to this bus*/
void busRemoval(DataBase *db, char busname[]);

/*handle "e" command*/
/*remove the stop, shorten the the buslines if needed or removing the stop from their lines. Adjust cost and duration.*/
void stopRemoval(DataBase *db, char stopname[]);

/*clear all the data given by the user.*/
void clearData(DataBase *db);
  
#endif  