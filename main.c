#include "interface.h"

int main(void)
{
    char x;

    init();

    do
    {

        x = getch();
        switch (x) {
            case '1':
                clearStatusArea();
                gotoXY(1,SATUSAREA_Y);
                printf("Create Test Data...");
                createTestData(20);
                copyDataToList(pathA);
                break;
            case '2':
                if(gFirstData == NULL)
                {
                    clearStatusArea();
                    gotoXY(1,SATUSAREA_Y);
                    printf("Seems your List is Empty...");
                }
                else
                {
                    clearStatusArea();
                    gotoXY(1,SATUSAREA_Y);
                    printf("Copy Test Data...");
                    iterateListAndCopy(pathA);
                }

                break;
            case '3':
                if(gFirstData == NULL)
                {
                    clearStatusArea();
                    gotoXY(1,SATUSAREA_Y);
                    printf("Seems your List is Empty...");
                }
                else
                {
                    clearStatusArea();
                    gotoXY(1,SATUSAREA_Y);
                    printf("Delete Test Data...");
                    clearStatusArea();
                    deleteOldData(pathA);
                    deleteList();
                }
                break;
            case '4':
                clearStatusArea();
                iterateList();
                break;
            default:
                break;
        }
    }
    while(x != K_ESC);

    finish();

    return 0;
}