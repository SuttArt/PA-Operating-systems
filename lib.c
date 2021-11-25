#include "interface.h"

void createTestData (int number)
{
    int i;
    char tmp[80];
    char text[80];
    FILE* fptr;

    for (i = 0; i < number; i++)
    {
        // put our string with the Path and the Data Name into the tmp
        snprintf(tmp, 80, "./A/data%d.txt", i);
        // open/write the data to the A-directory
        fptr  = fopen (tmp, "wb");
        //write something to the File
        snprintf(text, 80, "This is file data%d.txt", i);
        fputs(text,fptr);
        // close the file
        fclose (fptr);

    }

}

int checkDir(void)
{
    //struct from <sys/stat.h>, we need it for stat()
    struct stat buf;
    int i = 0;
    //check if ./A Directory exists
    if(stat(pathA, &buf) != 0)
    {
        i = 1;
    }
    if(stat(pathB, &buf) != 0)
    {
        i = 2;
    }
    if(stat(pathA, &buf) != 0 && stat(pathB, &buf) != 0)
    {
        i = 3;
    }

    return i;
}

void makeDir(char* nameOfDirectory)
{
    //create the Directory. There some mode, I think we do not need it => int mkdir(const char *path, mode_t mode);
    mkdir(nameOfDirectory);
}

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
    }
    else
    {
        gLastData -> next = current;
    }
    gLastData = current;
}

void iterateList(void)
{
    //current/working Node of the List
    DataList* current = gFirstData;

    while (current != NULL)
    {
        printf("\n== my address: %p == name of file: %s == address of next: %p",current ,current->name, current->next);
        current = current->next;

    }
}

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

void deleteList(void)
{
    //current/working Node of the List
    DataList* current = gFirstData;
    //temporary Node of the List
    DataList* x = NULL;

    while (current != NULL)
    {
        printf("\nDelete: %s", current->name);
        x = current->next;
        free(current);
        current = x;
    }
}

void copyData(char* pathFrom)
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
            iterateListAndCopy(pathFrom);
        }
    }
}

void deleteOldData(char* path)
{
    //current/working Node of the List
    DataList* current = gFirstData;
    char tmp [80];

    while (current != NULL)
    {
        snprintf(tmp, 80, "%s/%s",path, current -> name);
        remove(tmp);
        current = current->next;
    }
}