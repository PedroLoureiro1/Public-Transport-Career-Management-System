#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include "constants.h"

typedef struct Stop{
    char *name;
    double latitude;
    double longitude;
    struct Stop *next;
    struct Stop *previous;
    struct Bus *firstBus;
}Stop;

typedef struct Connection{
    char *name;
    char *startingStop;
    char *finalStop;
    double cost;
    double duration;
    struct Connection* next;
    struct Connection* previous;
}Connection;

typedef struct Bus{
    char *name;
    char *startingStop;
    char *finalStop;
    struct Connection *first_connection;
    struct Connection *last_connection;
    struct Bus *next;
}Bus;

typedef struct DataBase{
    Stop *stops;
    Bus *buses;
}DataBase;
 
typedef struct BusNames{
    char* name;
    struct BusNames *next;
} BusNames;

 
#endif  