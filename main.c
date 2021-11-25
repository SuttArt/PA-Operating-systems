#include "interface.h"

int main(void)
{
    switch (checkDir()) {
        case 1:
            makeDir(pathA);
            break;
        case 2:
            makeDir(pathB);
            break;
        case 3:
            makeDir(pathA);
            makeDir(pathB);
            break;
        default:break;

    }
    createTestData(20);
    copyData(pathA);
    //deleteOldData(pathA);
    return 0;
}