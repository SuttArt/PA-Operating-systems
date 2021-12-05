#include "interface.h"

void init(void)
{
    int i;
    CursorOnOff(0);
    createFrame();

    switch (checkDir()) {
        case 1:
            gotoXY(1,SATUSAREA_Y);
            printf("You seem to be missing folder A. I would create it.");
            makeDir(pathA);
            break;
        case 2:
            gotoXY(1,SATUSAREA_Y);
            printf("You seem to be missing folder B. I would create it.");
            makeDir(pathB);
            break;
        case 3:
            gotoXY(1,SATUSAREA_Y);
            printf("You seem to be missing folders A and B. I would create it.");
            makeDir(pathA);
            makeDir(pathB);
            break;
        default:break;
    }

    gFirstData = NULL;
    gLastData = gFirstData;
    gDataListsize = 0;
    gNumberOfNodes = 0;

    pthread_mutex_init(&gLock, NULL);

    GenList();
}

void finish(void)
{
    int i;
    DataList* current = gFirstData;


    for(i=0; i<gNumberOfNodes; i++) {
        pthread_mutex_destroy(&mutex[i]);
    }

    pthread_mutex_destroy(&gLock);

    gotoXY(0,FRAMEHEIGHT + 1);
    CursorOnOff(1);

}