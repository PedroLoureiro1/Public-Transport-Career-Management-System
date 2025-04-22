#include "constants.h"
#include "prototypes.h"
#include "structures.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* 
Pedro Loureiro
ist 1107059
*/

enum State {
    INSIDE,
    QUOTES
};

int skipSpaces(char arguments[], int i) {
    while (arguments[i] == ' ') {
        i++;
    }
    return i;
}

int readWord(char arguments[], char word[]) {

    enum State st;
    static int argumentIndex = 0;
    int wordIndex = 0;

    word[0] = '\0';

    argumentIndex = skipSpaces(arguments, argumentIndex);

    if (arguments[argumentIndex] == '\"') {
        st = QUOTES;
        argumentIndex++;
    } else {
        st = INSIDE;
    }

    while (1) {
        if ((arguments[argumentIndex] == '\n')||(arguments[argumentIndex] == '\0')){
            word[wordIndex] = '\0';
            argumentIndex = 0;
            return FALSE;
        }

        if (st == INSIDE) { 
            if (arguments[argumentIndex] == ' ') {
                word[wordIndex] = '\0';
                return TRUE;
            }
        } 
        
        else {
            if (arguments[argumentIndex] == '\"') {
                word[wordIndex] = '\0';
                argumentIndex++;

                if (arguments[argumentIndex] == '\n') {
                    argumentIndex = 0;
                    return FALSE;
                }

                return TRUE;
            }
        }

        word[wordIndex++] = arguments[argumentIndex++];
    }
}

int totalStops(Bus *bus){
    int total = 0;
    Connection *aux;

    if (bus == NULL)
        return 0;

    if (bus->first_connection == NULL)
        return 0;

    for(aux = bus->first_connection; aux != NULL ; aux = aux->next){
        total++;
    }

    return total + 1;
}

Bus* isBus(DataBase *db, char *name){
    Bus *aux;

    for (aux = db->buses; aux != NULL; aux = aux->next){
        if (strcmp(name, aux->name) == 0)
            return aux;
    }
    return NULL;
}

double totalDuration(Bus *bus){

    double total = 0;
    Connection *aux;

    if (bus == NULL)
        return 0;

    if (bus->first_connection == NULL)
        return 0;

    for(aux = bus->first_connection; aux != NULL ; aux = aux->next){

        total+= aux->duration;
    }

    return total;
}

double totalCost(Bus *bus){
    double total = 0;
    Connection *aux;

    if (bus == NULL)
        return 0;

    if (bus->first_connection == NULL)
        return 0;

    for(aux = bus->first_connection; aux != NULL ; aux = aux->next){
        total+= aux->cost;
    }

    return total;
}

int isAbbreviation(char arg2[]){

    int i, len=strlen(arg2);
    if (len < 3 || len > 7)
        return FALSE;
    for (i = 0; i < len ; i++){
        if (INVERSE[i] != arg2[i])
            return FALSE;
    }
    return TRUE;  
}

void printstops(char *name, DataBase *db){
    Bus* bus = isBus(db, name);
    Connection* aux;
    int contador = 0;

    if ((totalStops(bus)) == 0){
        return;
    }

    if ((totalStops(bus)) == 2){
        printf("%s, %s\n", bus->first_connection->startingStop, bus->first_connection->finalStop);
        return;
    }

    for(aux = bus->first_connection; aux != bus->last_connection; aux = aux->next){
        if (contador == 0){
            printf("%s, %s, ", bus->first_connection->startingStop, bus->first_connection->finalStop);
            contador++;
        }
        else{
            printf("%s, ",aux->finalStop);
        }
    }
    printf("%s\n", bus->finalStop);
}

void printstopsInverse(char *name, DataBase *db){
    Bus* bus = isBus(db, name);
    Connection* aux;
    int contador = 0;
    
    if ((totalStops(bus)) == 0){
        return;
    }

    if ((totalStops(bus)) == 2){
        printf("%s, %s\n", bus->first_connection->finalStop, bus->first_connection->startingStop);
        return;
    }

    for(aux = bus->last_connection; aux != bus->first_connection; aux = aux->previous){
        if (contador == 0){
            printf("%s, %s, ", bus->last_connection->finalStop, bus->last_connection->startingStop);
            contador++;
        }
        else{
            printf("%s, ",aux->startingStop);
        }
    }
    printf("%s\n", bus->startingStop);
}

Bus* createBus(char *name){
    Bus* newBus = (Bus*) malloc(sizeof(Bus));
    newBus->name = (char*) malloc(sizeof(char)*(strlen(name)+1));
    strcpy(newBus->name, name);
    newBus->last_connection = NULL;
    newBus->first_connection = NULL;
    newBus->next = NULL;
    newBus->startingStop = NULL;
    newBus->finalStop = NULL;
    return newBus;
}

/*Working on this*/
void busCommand(DataBase *db, char arguments[]) {
    char arg1[MAX_INPUT], arg2[30];
    int moreArguments, numArguments = 0;
    Bus *aux;

    moreArguments = readWord(arguments, arg1);
    if (strlen(arg1) != 0){
        numArguments++;
        if(moreArguments){
            readWord(arguments, arg2);
            numArguments++;
        }
    }
    if (numArguments == 0){
        for (aux = db->buses; aux != NULL; aux = aux->next){
            if ((aux->startingStop) == NULL){
                printf("%s %d %.2f %.2f\n", aux->name, 
                totalStops(aux),totalCost(aux),
                totalDuration(aux));
            }
            else{
                printf("%s %s %s %d %.2f %.2f\n", aux->name,
                aux->startingStop, aux->finalStop, 
                totalStops(aux), totalCost(aux),
                totalDuration(aux));
            }
        }
    }
    
    if (numArguments == 1){
        if (isBus(db, arg1)){
            printstops(arg1, db);
        }
        else{
            if (db->buses == NULL){
                db->buses = createBus(arg1);
            }
            
            else{
                for (aux = db->buses; aux->next != NULL; aux = aux->next){
                    ;
                }
                aux->next = createBus(arg1);
            }
        }
    }

    if (numArguments == 2){
        if (isAbbreviation(arg2)){
            printstopsInverse(arg1, db); 
        }
        else{
            printf("incorrect sort option.\n");
            return;
        }
    }
}

/*trabalhar nisto*/
BusNames *createName(char *name){
    BusNames *newName = (BusNames*) malloc(sizeof(BusNames));
    newName->name = (char*) malloc(sizeof(char)*(strlen(name)+1));
    strcpy(newName->name, name);
    newName->next = NULL;
    return newName;
}

int totalBuses(char *name, DataBase *db){

    Connection *auxCon;
    Bus *auxBus;
    int total = 0;
    BusNames *names = NULL;
    BusNames *auxName;

    for (auxBus = db->buses; auxBus != NULL; auxBus = auxBus->next)
    {     
        for (auxCon = auxBus->first_connection; auxCon != NULL; auxCon = auxCon->next)
        {         
            if ((strcmp(auxCon->startingStop, name)==0) || (strcmp(auxCon->finalStop, name)==0))
            {
                if (names == NULL)
                    names = createName(name);
                else{
                    for (auxName = names; auxName->next != NULL; auxName = auxName->next){
                        ;
                    }
                    auxName->next = createName(name);
                }
                total++;
                break;
            }          
        }       
    }
    
    return total;
}

Stop* isStop(DataBase *db, char *name){
    Stop *aux;
    for (aux = db->stops; aux != NULL; aux = aux->next){
        if (strcmp(name, aux->name) == 0)
            return aux;
    }
    return NULL;
}


Stop* createStop(DataBase *db, char *name, char *latitude, char *longitude){
    if (isStop(db, name) != NULL){
        printf("%s: stop already exists.\n", name);
        return NULL;
    }

    else{
        Stop* newStop = (Stop*) malloc(sizeof(Stop));
        newStop->name = (char*) malloc(sizeof(char)*(strlen(name)+1));
        strcpy(newStop->name, name);
        newStop->latitude = strtod(latitude, NULL);
        newStop->longitude = strtod(longitude, NULL);
        newStop->next = NULL;
        return newStop;
    }
}

void stopCommand(DataBase *db, char arguments[]){
    char arg1[MAX_INPUT+1], arg2[30], arg3[30];
    int moreArguments, numArguments = 0;
    Stop *aux, *currentStop;

    moreArguments = readWord(arguments, arg1);

    if (strlen(arg1) != 0){
        numArguments++;
        if(moreArguments){
            readWord(arguments, arg2);
            readWord(arguments, arg3);
            numArguments+=2;
        }
    }

    if (numArguments == 0)
        for (aux = db->stops; aux != NULL; aux = aux->next){
            printf("%s: %16.12f %16.12f %d\n", aux->name, 
            aux->latitude, aux->longitude, totalBuses(aux->name, db));
        }

    if (numArguments == 1){

            if ((currentStop = isStop(db, arg1)) != NULL)
                printf("%16.12f %16.12f\n", currentStop->latitude, 
                currentStop->longitude);
            else{
                printf("%s: no such stop.\n", arg1);
                return;
            }
    }

    if (numArguments == 3){
            if (db->stops == NULL){
                db->stops = createStop(db, arg1, arg2, arg3);
            }
            
            else{
                for (aux = db->stops; aux->next != NULL; aux = aux->next){
                    ;
                }
                aux->next = createStop(db, arg1, arg2, arg3);
            }
    }   
}

Connection* createConnection(char *arg1,char *arg2,char *arg3,char *arg4,char *arg5){

        Connection *currentCon = (Connection*) malloc(sizeof(Connection));
        currentCon->name = (char*) malloc(sizeof(char)*(strlen(arg1)+1));
        strcpy(currentCon->name,arg1);
        currentCon->startingStop = (char*) malloc(sizeof(char)*(strlen(arg2)+1));
        strcpy(currentCon->startingStop,arg2);
        currentCon->finalStop = (char*) malloc(sizeof(char)*(strlen(arg3)+1));
        strcpy(currentCon->finalStop,arg3);
        currentCon->cost = strtod(arg4, NULL);
        currentCon->duration = strtod(arg5, NULL);
        currentCon->next = NULL;
        currentCon->previous = NULL;
        return currentCon;
}

void connectionsCommand(DataBase *db, char arguments[]){
    Bus *currentBus;
    Connection *currentCon;
    char arg1[MAX_INPUT+1], arg2[MAX_INPUT+1], arg3[MAX_INPUT+1],
    arg4[LEN_COST_DURATION], arg5[LEN_COST_DURATION];
    readWord(arguments, arg1);
    readWord(arguments, arg2);
    readWord(arguments, arg3);
    readWord(arguments, arg4);
    readWord(arguments, arg5);
    if ((isBus(db, arg1)) == NULL){
        printf("%s: no such line.\n", arg1);
        return;
    }
    if ((isStop(db, arg2)) == NULL){
        printf("%s: no such stop.\n", arg2);
        return;
    }
    if ((isStop(db, arg3)) == NULL){
        printf("%s: no such stop.\n", arg3);
        return;
    }
    if (strtod(arg4,NULL) < 0 || (strtod(arg5,NULL) < 0)){
        printf("negative cost or duration.\n");
        return;
    }

    currentBus = isBus(db, arg1);

    /* adding the first stop of the bus*/
    if (currentBus->startingStop == NULL){
        currentCon = createConnection(arg1, arg2, arg3, arg4, arg5);
        currentCon->next = NULL;
        currentCon->previous = NULL;
        currentBus->first_connection = currentCon;
        currentBus->last_connection = currentCon;
        currentBus->startingStop = (char*) malloc(sizeof(char)*(strlen(arg2)+1));
        strcpy(currentBus->startingStop,arg2);
        currentBus->finalStop = (char*) malloc(sizeof(char)*(strlen(arg3)+1));
        strcpy(currentBus->finalStop,arg3);
    }
    else{
        /* adding the connection at the end of the bus*/
        if (strcmp(currentBus->finalStop,arg2) == 0){
            currentCon = createConnection(arg1, arg2, arg3, arg4, arg5);
            free(currentBus->finalStop);
            currentBus->finalStop = (char*) malloc (sizeof(char)*(strlen(arg3)+1));
            strcpy(currentBus->finalStop, arg3);
            currentCon->previous = currentBus->last_connection;
            currentBus->last_connection->next = currentCon; 
            currentBus->last_connection = currentCon;


        }
        /* adding the connection to the beginning of the bys*/
        else if (strcmp(currentBus->startingStop, arg3) == 0){
            currentCon = createConnection(arg1, arg2, arg3, arg4, arg5);
            free(currentBus->startingStop);
            currentBus->startingStop = (char*) malloc(sizeof(char)*(strlen(arg2)+1));
            strcpy(currentBus->startingStop, arg2);
            currentCon->next = currentBus->first_connection;
            currentBus->first_connection->previous = currentCon; 
            currentBus->first_connection = currentCon;
        }
        else{
            printf("link cannot be associated with bus line.\n");
            return;
        }
    }
}

void quicksort(char **arr, int left, int right) {
    int i = left;
    int j = right;
    char *tmp;
    char *pivot = (char*) malloc(sizeof(char)*(strlen(arr[(left + right) / 2])+1));
    strcpy(pivot, arr[(left + right) / 2]);

    while (i <= j) {
        while (strcmp(arr[i], pivot) < 0) {
            i++;
        }
        while (strcmp(arr[j], pivot) > 0) {
            j--;
        }
        if (i <= j) {
            tmp = (char*) malloc(sizeof(char)*(strlen(arr[i])+1));
            strcpy(tmp, arr[i]);
            strcpy(arr[i], arr[j]);
            strcpy(arr[j], tmp);
            i++;
            j--;
        }
    }

    if (left < j) {
        quicksort(arr, left, j);
    }
    if (i < right) {
        quicksort(arr, i, right);
    }
}


BusNames *numBusesWithNames(char *name, DataBase *db, int *numBuses){
    Connection *auxCon;
    Bus *auxBus;
    BusNames *auxName;
    BusNames *names = NULL;
    int *count = (int*) malloc(sizeof(int));
    *count = 0;

    for (auxBus = db->buses; auxBus != NULL; auxBus = auxBus->next)
    {     
        for (auxCon = auxBus->first_connection; auxCon != NULL; auxCon = auxCon->next)
        {         
            if ((strcmp(auxCon->startingStop, name)==0) 
            || (strcmp(auxCon->finalStop, name)==0))
            {
                if (names == NULL)
                    names = createName(auxBus->name);
                else{
                    for (auxName = names; auxName->next != NULL; auxName = auxName->next){
                        ;
                    }
                    auxName->next = createName(auxBus->name);
                }
                (*count)++;
                break;
            }          
        }       
    }
    *numBuses = *count;
    return names;
}

void intersectionCommand(DataBase *db){
    
    Stop *aux;
    BusNames *linkedNames = NULL;
    BusNames *auxNames;
    int numBuses = 0;
    int i=0;
    char **names = NULL;
    for (aux = db->stops; aux!=NULL; aux=aux->next){
        linkedNames = numBusesWithNames(aux->name, db, &numBuses);
        if (numBuses > 1){
            printf("%s %d:", aux->name, numBuses);
            names = (char**) malloc(numBuses*sizeof(char*));
            for (auxNames = linkedNames; auxNames != NULL; auxNames = auxNames->next)
            {
                names[i] = (char*) malloc(sizeof(char)*(strlen(auxNames->name)+1));
                strcpy(names[i], auxNames->name);
                i++;
            }
            
            quicksort(names, 0, numBuses-1);
            for (i=0; i<numBuses; i++){
                printf(" %s", names[i]);
            }
            printf("\n");
            for (i = 0; i < numBuses; i++){
                free(names[i]);
            }
            free(names);
            i = 0;
            numBuses = 0;
        }
    }
}

void clearDataBus(Bus *bus){
        Connection* auxCon;
        free(bus->name);
        if (bus->startingStop != NULL){
            free(bus->startingStop);
        }
        if(bus->finalStop != NULL){
            free(bus->finalStop);
        }

        /* falta dar free no bus->next */

        for(auxCon = bus->first_connection; auxCon != bus->last_connection; auxCon = auxCon->next){
            if (auxCon != NULL){
                free(auxCon->name);
            }
        }
        if (bus->last_connection != NULL){
            free(bus->last_connection->name);
        }
}

void busRemoval(DataBase *db, char busname[]){
    char bus[MAX_INPUT];
    Bus *supposedToDelete;
    Bus *currentBus = db->buses, *previousBus = NULL;

    readWord(busname, bus);

    if ((supposedToDelete = isBus(db, bus)) == NULL){
        printf("%s: no such line.\n", bus);
        return;
    }
        
    while((currentBus != supposedToDelete) && (currentBus!=NULL)){
        previousBus = currentBus;
        currentBus = currentBus->next;
    }

    if(currentBus == NULL){
        printf("%s: no such line.\n", bus);
        return;
    }

    if(previousBus == NULL){
        db->buses = currentBus->next;
    }  
    else{
        previousBus->next = currentBus->next;
    }

    clearDataBus(currentBus);
}

void stopRemoval(DataBase *db, char stopname[]){
    char stop[MAX_INPUT];
    Stop *supposedToDelete, *currentStop = db->stops, *previousStop = NULL;
    Bus *auxBus;
    Connection *currentCon, *tempCon;

    readWord(stopname, stop);

    if ((supposedToDelete = isStop(db, stop)) == NULL){
        printf("%s: no such stop.\n", stop);
        return;
    }

    while(currentStop != supposedToDelete){
        previousStop = currentStop;
        currentStop = currentStop->next;
    }

    if(previousStop == NULL){
        db->stops = currentStop->next;
    } 
    else{
        previousStop->next = currentStop->next;
    }

    for(auxBus = db->buses; auxBus != NULL; auxBus = auxBus->next){
        currentCon = auxBus->first_connection;
        while(currentCon != NULL){

            /* supposed to delete is the first bus stop of the bus */
            if ((strcmp(currentCon->startingStop,supposedToDelete->name) == 0)
             && (currentCon == auxBus->first_connection)){
                auxBus->first_connection = currentCon->next;
                if (auxBus->first_connection == NULL){
                    auxBus->startingStop = NULL;
                    auxBus->finalStop = NULL;
                    auxBus->first_connection = NULL;
                    auxBus->last_connection = NULL;
                }
                else{
                    auxBus->first_connection->previous = NULL;
                    auxBus->startingStop = auxBus->first_connection->startingStop;
                }
            }
            else if (strcmp(currentCon->finalStop,supposedToDelete->name) == 0){
                /* supposed to delete is the last bus stop of the bus*/
                if(currentCon->next == NULL){
                    auxBus->last_connection = currentCon->previous;
                    if (auxBus->last_connection == NULL){
                        auxBus->startingStop = NULL;
                        auxBus->finalStop = NULL;
                        auxBus->first_connection = NULL;
                        auxBus->last_connection = NULL;
                    }
                    else{
                        auxBus->last_connection->next = NULL;
                        auxBus->finalStop = auxBus->last_connection->finalStop;
                    }
                }

                /* supposed to delete is somewhere in the middle of the bus*/
                else{
                    tempCon = currentCon->next;
                    currentCon->cost += tempCon->cost;
                    currentCon->duration += tempCon->duration;
                    currentCon->next = tempCon->next;
                    currentCon->finalStop = tempCon->finalStop;
                    if (currentCon->next == NULL)
                        auxBus->last_connection = currentCon;
                    else
                        currentCon->next->previous = currentCon;
                    continue;    
                }
            }
            currentCon = currentCon->next;
        }
    }
}


void clearData(DataBase *db){
    Bus *auxBus;
    Stop *auxStop;
    Connection *auxCon;

    for(auxStop = db->stops; auxStop!=NULL;auxStop = auxStop->next){
        free(auxStop->name);
    }

    for(auxBus = db->buses; auxBus != NULL; auxBus = auxBus->next){
        for(auxCon = auxBus->first_connection; auxCon != NULL; auxCon = auxCon->next){
            free(auxCon->name);
            free(auxCon->startingStop);
            free(auxCon->finalStop);
        }
        free(auxBus->name);
    }

    db->buses = NULL;
    db->stops = NULL;

}
int main(){
    
    char c, arguments[MAX_INPUT];
    DataBase db;
    db.buses = NULL;
    db.stops = NULL;

    while (((c=getchar()) != EOF) && (c != '\0')) {

        if (fgets(arguments, MAX_INPUT, stdin) != NULL){

        switch(c){
            case 'q':
                clearData(&db);
                return 0;
        
            case 'c':
                busCommand(&db, arguments);
                break;

            case 'p':
                stopCommand(&db, arguments);
                break;

            case 'l':
                connectionsCommand(&db, arguments);
                break;

            case 'i':
                intersectionCommand(&db);
                break;
                
            case 'r':
                busRemoval(&db, arguments);
                break;

            case 'e':
                stopRemoval(&db, arguments);
                break;

            case 'a':
                clearData(&db);
                break;
            }
        }
    }
    return 0;
}
