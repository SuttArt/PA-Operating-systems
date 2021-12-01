#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>
#include <windows.h>



//Precompiler-Variablen
#define K_ESC 27
#define FRAMEWIDTH 100
#define FRAMEHEIGHT 28
#define SATUSAREA_X 59
#define SATUSAREA_Y 8
#define pathA "./A"
#define pathB "./B"

//Datatypes
typedef struct DataList
{
    char name[80];
    int mutex;
    int threadNr;
    struct DataList* next; //address of the next node
}
DataList; //this is ONE node in the List

//Protorypen
void init(void);
void finish(void);
int getch(void);
void createTestData (int number);
int checkDir(void);
void makeDir(char* nameOfDirectory);
void makeList(char* nameOfFile);
void iterateList(void);
void iterateListAndCopy(char* path);
void deleteList(void);
void copyDataToList(char* path);
void deleteOldData(char* path);
void gotoXY (int x, int y);
void createFrame (void);
void CursorOnOff(int x);
void clearStatusArea(void);
int checkDuplicates(char* nameOfFile);

//global Variables
DataList* gFirstData;   // 1. Node in the List
DataList* gLastData;    // 2. Node in the List
int gDataListsize;   //Size of the DataList
int gNumberOfNodes; //Number of the Nodes in DataList