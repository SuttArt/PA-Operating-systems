#include "interface.h"

/*
 * Function: Add2List
 * ------------------
 *  brief: create a List of DataList structure.
 *
 *  1 parameter: char,  name of file
 *
 *  return: void
 */
void Add2List(char* nameOfFile)
{
    //current/working Node of the List
    DataList* current = NULL;
    int gDataListsize = sizeof (DataList);
    int found = 0;

    current = (DataList*) malloc(gDataListsize); //Storage reservation

    strcpy(current -> name, nameOfFile);
    current -> mutex = 0;
    current -> threadNr = 0;
    current -> next = NULL;

    if (gFirstData == NULL) //list is empty
    {
        gFirstData = current;
        gLastData = gFirstData;
        gNumberOfNodes++;
    }
    else
    {

        if(checkDuplicates(nameOfFile) == 0)
        {
            gLastData -> next = current;
            gNumberOfNodes++;
            gLastData = current;
        }
    }


}

/*
 * Function: ShowList
 * ------------------
 *  brief: iterate through whole DataList structure and print some data of each Node
 *
 *  return: void
 */
void ShowList(void)
{
    //current/working Node of the List
    DataList* current = gFirstData;
    int i = SATUSAREA_Y;

    if (current == NULL)
    {
        gotoXY(1,SATUSAREA_Y);
        printf("Seems your List is Empty...");
        gotoXY(1,SATUSAREA_Y+2);
        printf("Just type 1 and try show the list again.");
    }
    while (current != NULL)
    {
        gotoXY(1,i);
        printf("name of file: %s, id of Thread: %d, id of Mutex: %d", current->name, current ->threadNr, current ->mutex);
        current = current->next;
        i++;
    }
}

/*
 * Function: deleteList
 * --------------------
 *  brief: delete whole DataList structure
 *
 *  return: void
 */
void deleteList(void)
{
    //current/working Node of the List
    DataList* current = gFirstData;
    //temporary Node of the List
    DataList* x = NULL;
    int i = SATUSAREA_Y;

    while (current != NULL)
    {
        gotoXY(1,i);
        printf("Delete: %s", current->name);
        x = current->next;
        free(current);
        current = x;
        i++;
    }
    gFirstData = NULL;
    gLastData = gFirstData;
}

/*
 * Function: GenList
 * -----------------
 *  brief: copy all data from the pathA(./A) to the DataList structure
 *
 *  return: void
 */
void GenList(void)
{
    DIR* dir;
    char tmp [80];
    struct dirent* d_pntr;

    dir = opendir(pathA);
    if(dir != NULL)
    {
        while ((d_pntr = readdir(dir)) != NULL)
        {
            strcpy(tmp,d_pntr -> d_name);
            if (strcmp(tmp, ".") == 1 && strcmp(tmp,"..") == 1) //(tmp[0] != '.' || (tmp[0] != '.' && tmp[1] != '.'))
            {
                Add2List(tmp);
            }
        }
    }
    closedir(dir);
}


/*
 * Function: Cpy
 * -------------
 *  brief: iterate through whole DataList structure and Copy all Data from start path (pathA(./A) to pathB(./B))
 *
 *  1 parameter: char,  name of the file to copy
 *
 *  return: void
 */
void Cpy(char* nameOfFile)
{
    pthread_mutex_lock(&gLock);
    // full name of source name
    char name_in[80];
    //full name of target file
    char name_out[80];
    FILE* fptrIn;
    FILE* fptrOut;
    int ch;

    snprintf(name_in, 80, "%s/%s",pathA, nameOfFile);
    snprintf(name_out, 80, "%s/%s",pathB, nameOfFile);

    fptrIn = fopen(name_in,"rb"); //r - Read b - Binary
    fptrOut = fopen(name_out,"wb");// w - write

    while ((ch=fgetc(fptrIn)) != EOF) //EOF - End Of File
    {
        fputc(ch,fptrOut);
    }

    fclose(fptrIn);
    fclose(fptrOut);
    pthread_mutex_unlock(&gLock);
}


/*
 * Function: checkDuplicates
 * -------------------------
 *  brief: iterate through whole DataList structure and say if there some duplicate of file is
 *
 *  1 parameter: char,  name of the file to check
 *
 *  return: int,    1 or 0, found or not found
 */
int checkDuplicates(char* nameOfFile)
{
    DataList* current = gFirstData;
    int found = 0;

    while (current != NULL)
    {
        do
        {
            if(strcmp(current -> name, nameOfFile) == 0)
            {
                found = 1;
            }
            current = current -> next;
        } while ((!found) && (current != NULL));

        return found;
    }

}
