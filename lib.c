#include "interface.h"

/*
 * Function: createTestData
 * ------------------------
 *  brief: create some test .txt data and write to each file some text
 *
 *  1 parameter: int,   number of files to create
 *
 *  return: void
 */
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
/*
 * Function: checkDir
 * ------------------
 *  brief: checks if the folder with the program contains the pathA(./A) folder and the pathB(./B) folder
 *
 *  return: int,    1 - if there is no pathA(./A) folder
 *                  2 - if there is no pathB(./B) folder
 *                  3 - if there is no pathA(./A) and pathB(./B) folder
 */
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

/*
 * Function: makeDir
 * -----------------
 *  brief: create some folder
 *
 *  1 parameter: char,  name of folder
 *
 *  return: void
 */
void makeDir(char* nameOfDirectory)
{
    //create the Directory. There some mode, I think we do not need it => int mkdir(const char *path, mode_t mode);
    mkdir(nameOfDirectory);
}

/*
 * Function: copyDataToList
 * ------------------------
 *  brief: delete all data from the path
 *
 *  1 parameter: char,  path from where to delete data
 *
 *  return: void
 */
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

/*
 * Function: gotoXY
 * ----------------
 *  brief: set our cursor at the Console to the (x,y) position
 *
 *  1 parameter: int,  column number
 *  1 parameter: int,  line number
 *
 *  return: void
 */
void gotoXY (int x, int y)
{
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    //Handle Console Buffer
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(handle, coordinate);
}

/*
 * Function: createFrame
 * ----------------
 *  brief: create user interface in the console
 *
 *  return: void
 */
void createFrame (void)
{
    int i,j;

    for (i=0; i < FRAMEWIDTH; i++)
    {
        gotoXY(i,0);
        printf("=");

        gotoXY(24,1);
        printf("Control:");
        gotoXY(1,2);
        printf("If you have new Files in ./A and you want to add the to the list type 1");
        gotoXY(1,3);
        printf("If you want to copy test data from ./A to B type 2");
        gotoXY(1,4);
        printf("If you want to delete test data from ./A type 3");
        gotoXY(1,5);
        printf("If you want to show the List type 4");
        gotoXY(1,6);
        printf("If you want to complete the work - click Esc");

        gotoXY(SATUSAREA_X+5,1);
        printf("Threads overview:");

        if (!(i > SATUSAREA_X))
        {
            gotoXY(i,7);
            printf("-");
        }


    }

    for(j=0; j <= FRAMEHEIGHT; j++)
    {
        gotoXY(0,j);
        printf("|");
        if(j!=0)
        {
            gotoXY(SATUSAREA_X,j);
            printf("|");
        }
        gotoXY(FRAMEWIDTH,j);
        printf("|");
    }
}

/*
 * Function: CursorOnOff
 * ---------------------
 *  brief: turn Cursor On or Off in the Console
 *
 *  1 parameter: int,   if 1 - ON
 *                      if 0 - OFF
 *
 *  return: void
 */
void CursorOnOff(int x)  //  cursor 1/0 = ON/OFF
{
    if ( x == 0 || x == 1 )
    {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 10;  //  size of cursor
        info.bVisible = x;
        SetConsoleCursorInfo(consoleHandle, &info);
    }
}

/*
 * Function: clearStatusArea
 * -------------------------
 *  brief: Clear the Status Area at the Console
 *
 *  return: void
 */
void clearStatusArea(void)
{
    int i,j;
    int frameheightLocal;

    if (gNumberOfNodes>20)
    {
        frameheightLocal = gNumberOfNodes;
    }
    else
    {
        frameheightLocal = FRAMEHEIGHT;
    }

    for(i=1; i < SATUSAREA_X; i++)
    {
        for(j=SATUSAREA_Y; j < frameheightLocal; j++)
        {
            gotoXY(i,j);
            printf(" ");
        }
    }

}


/*
 * Function: createLog
 * -------------------------
 *  brief: Create .txt file for log of every thread
 *
 *  1 parameter: DataList*, Node of DataList
 *
 *  return: void
 */
void createLog(DataList* current)
{
    pthread_mutex_lock(&gLock);

    char tmp[80];
    char text[120];
    FILE* fptr;


    // put our string with the Path and the Data Name into the tmp
    snprintf(tmp, 80, "./logThreadNumber%d.txt", current ->threadNr);
    // open/write the data to the A-directory
    fptr  = fopen (tmp, "ab");
    //write something to the File
    snprintf(text, 120, "\nName of the file: %s\n Number of Thread: %d\n Number of Mutex: %d\n==========================\n",
             current ->name,current ->threadNr, current ->mutex);
    fputs(text,fptr);
    // close the file
    fclose (fptr);

    pthread_mutex_unlock(&gLock);

}

/*
 * Function: createLog
 * -------------------------
 *  brief: delete .txt file for log of every thread
 *
 *  1 parameter: DataList*, Node of DataList
 *
 *  return: void
 */
void deleteLog(int ThreadNumber)
{
    pthread_mutex_lock(&gLock);

    char tmp[80];

    snprintf(tmp, 80, "./logThreadNumber%d.txt", ThreadNumber);
    remove(tmp);

    pthread_mutex_unlock(&gLock);

}