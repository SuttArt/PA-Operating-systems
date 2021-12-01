#include "interface.h"

void* ThrdFunc (void* arg)
{
    int* Numb = (int*) arg; // Casting. It was : int* Numb = arg;
    printf("\nThread has the number %2d",*Numb); // Before Casting in was printf("\nThread has the number %2d",Numb);
    return 0;
}

int mainq(void)
{
    pthread_t ID;
    pthread_create(&ID, NULL, &ThrdFunc, &ID); //(&ID - For Operation System, NULL, &ThrdFunc - Funktion übergabe, &ID - Argument from ThrdFunc(void* arg))
    printf("From main(): %d", ID);
    pthread_join(ID,NULL); // Thread abwarten
    //sleep(3);
    return 0;
}