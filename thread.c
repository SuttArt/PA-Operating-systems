#include "interface.h"

void* ThrdFunc (void* arg)
{
    int* ID = (int*) arg;
    //current/working Node of the List
    DataList* current = gFirstData;
    int i;

    while (current != NULL)
    {
        if(pthread_mutex_trylock(&gLockThrdFunc) == 0)
        {

            if(current -> threadNr == 0)
            {
                current -> threadNr = *ID;
                current -> mutex = &gLockThrdFunc;
                Cpy(current ->name);
                createLog(current);

            }
            pthread_mutex_unlock(&gLockThrdFunc);
        }
        sleep(THDELAY);

        current = current->next;

    }
}

/*
 * Ich habe dazu ein Paar fragen, wie man das mit mehrere Mutexes machen kann
 * Weil 1 Mutex für DIESE Aufgabe ist nicht effizient! Z.b. mit 1 Mutex wird es durchschnittlich in 21.4 sec ausgeführt,
 * mit 20 Mutexes(entsprechend Anzahl der Knoten in die Liste) wäre es ungefähr 6.1 sec!
 */


/*void* ThrdFunc (void* arg)
{
    int* ID = (int*) arg;
    //current/working Node of the List
    DataList* current = gFirstData;
    int i;

    for(i=0; i < gNumberOfNodes; i++)
    {
        if(pthread_mutex_trylock(&mutex[i]) == 0)
        {

            if(current -> threadNr == 0)
            {
                current -> threadNr = *ID;
                current -> mutex = &mutex[i];
                Cpy(current ->name);
                createLog(current);

                sleep(THDELAY);
            }
            pthread_mutex_unlock(&mutex[i]);
        }

        if(current -> next != NULL)
        {
            current = current->next;
        }
    }
}*/

/*
void InitThread (void)
{
    pthread_t ID[TCOUNT];
    int i;

    for(i=0; i <= TCOUNT; i++)
    {
        deleteLog(i);
    }

    for(i=0; i<gNumberOfNodes; i++){
        pthread_mutex_init(&mutex[i], NULL);
    }

    for(i=0; i < TCOUNT; i++)
    {
        pthread_create(&ID[i], NULL, &ThrdFunc, &ID[i]);
    }

    for(i=0; i < TCOUNT; i++)
    {
        pthread_join(ID[i], NULL);
    }
};
*/
