#include "interface.h"

/*
 * Function: makeList
 * ------------------
 *  brief: create a List of DataList structure.
 *
 *  1 parameter: char,  name of file
 *
 *  return: void
 */
void makeList(char* nameOfFile)
{
    //current/working Node of the List
    DataList* current = NULL;
    int gDataListsize = sizeof (DataList);

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
        if(!checkDuplicates(nameOfFile))
        {
            gLastData -> next = current;
            gNumberOfNodes++;
        }
    }
    gLastData = current;
}

/*
 * Function: iterateList
 * ---------------------
 *  brief: iterate through whole DataList structure and print some data of each Node
 *
 *  return: void
 */
void iterateList(void)
{
    //current/working Node of the List
    DataList* current = gFirstData;
    int i = SATUSAREA_Y;

    if (current == NULL)
    {
        gotoXY(1,SATUSAREA_Y);
        printf("Seems your List is Empty...");
    }
    while (current != NULL)
    {
        gotoXY(1,i);
        printf("name of file: %s", current->name);
        current = current->next;
        i++;
    }
}

/*
 * Function: iterateListAndCopy
 * ----------------------------
 *  brief: iterate through whole DataList structure and Copy all Data from start path (pathA(./A) or pathB(./B))
 *         to the end path (depends of start path)
 *
 *  1 parameter: char,  start path, if pathA(./A) then copy to pathB(./B) and vice versa
 *
 *  return: void
 */
void iterateListAndCopy(char* path)
{
    //current/working Node of the List
    DataList* current = gFirstData;
    // full name of source name
    char name_in[80];
    //full name of target file
    char name_out[80];
    FILE* fptrIn;
    FILE* fptrOut;
    int ch;

    while (current != NULL)
    {
        snprintf(name_in, 80, "%s/%s",path, current -> name);
        if(pathA)
        {
            snprintf(name_out, 80, "%s/%s",pathB, current -> name);
        }
        else
        {
            snprintf(name_out, 80, "%s/%s",pathA, current -> name);
        }



        fptrIn = fopen(name_in,"rb"); //r - Read b - Binary
        fptrOut = fopen(name_out,"wb");// w - write

        while ((ch=fgetc(fptrIn)) != EOF) //EOF - End Of File
        {
            fputc(ch,fptrOut);
        }

        fclose(fptrIn);
        fclose(fptrOut);

        current = current->next;
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
 * Function: copyDataToList
 * ------------------------
 *  brief: copy all data from the path to the DataList structure
 *
 *  1 parameter: char,  path from where to get the data
 *
 *  return: void
 */
void copyDataToList(char* pathFrom)
{
    DIR* dir;
    char tmp [80];
    struct dirent* d_pntr;

    dir = opendir(pathFrom);
    if(dir != NULL)
    {
        while ((d_pntr = readdir(dir)) != NULL)
        {
            strcpy(tmp,d_pntr -> d_name);
            if (strcmp(tmp, ".") == 1 && strcmp(tmp,"..") == 1) //(tmp[0] != '.' || (tmp[0] != '.' && tmp[1] != '.'))
            {
                makeList(tmp);
            }
        }
    }
}

int checkDuplicates(char* nameOfFile)
{
    DataList* current = gFirstData;
    int found;

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
