#include "interface.h"

void init(void)
{
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
}

void finish(void)
{
    gotoXY(0,FRAMEHEIGHT + 1);
    CursorOnOff(1);
}