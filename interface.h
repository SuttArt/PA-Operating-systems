#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>
#include <windows.h>



//Precompiler-Variablen
#define K_ESC 27 //Esc Button
#define FRAMEWIDTH 100 //Width of whole Frame
#define FRAMEHEIGHT 29 //Height of whole Frame
#define SATUSAREA_X 72 //X-coordinate of the end of Status Frame
#define SATUSAREA_Y 9 //Y-coordinate of the start of Status Frame
#define pathA "./A" //path to first Directory
#define pathB "./B" //path to second Directory
#define TCOUNT 4 //Number of Threads
#define THDELAY 1 //Delay of threads executions

//Datatypes
typedef struct DataList
{
    char name[80];
    pthread_mutex_t mutex;
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
void Add2List(char* nameOfFile);
void ShowList(void);
void Cpy(char* nameOfFile);
void deleteList(void);
void GenList(void);
void deleteOldData(char* path);
void gotoXY (int x, int y);
void createFrame (void);
void CursorOnOff(int x);
void clearStatusArea(void);
int checkDuplicates(char* nameOfFile);
void InitThread (void);
void* ThrdFunc (void* arg);
void createLog(DataList* current);
void deleteLog(int ThreadNumber);

//global Variables
DataList* gFirstData;   // 1. Node in the List
DataList* gLastData;    // 2. Node in the List
int gDataListsize;   //Size of the DataList
int gNumberOfNodes; //Number of the Nodes in DataList
pthread_mutex_t gLock; // Mutex
pthread_mutex_t mutex[200]; //Also mutex, but it's array. PS:I'm not sure if it correct
