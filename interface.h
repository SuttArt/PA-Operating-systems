#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>


//Precompiler-Variablen
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
void createTestData (int number);
int checkDir(void);
void makeDir(char* nameOfDirectory);
void makeList(char* nameOfFile);
void iterateList(void);
void iterateListAndCopy(char* path);
void deleteList(void);
void copyData(char* path);
void deleteOldData(char* path);

//global Variables
DataList* gFirstData;   // 1. Node in the List
DataList* gLastData;    // 2. Node in the List
int gDataListsize;   //Size of the DataList