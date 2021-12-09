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
                printf("Add new Data...");
                GenList();
                clearStatusArea();
                gotoXY(1,SATUSAREA_Y);
                printf("Done!");
                break;
            case '2': //copy all data
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
                    printf("Copy Test Data... Please, wait until a signal \"Done\".");


                    pthread_t ID[TCOUNT];

                    for(int i=0; i <= TCOUNT; i++)
                    {
                        deleteLog(i);
                    }

                    for(i=0; i<gNumberOfNodes; i++){
                        pthread_mutex_init(&mutex[i], NULL);
                    }

                    for(i=0; i < TCOUNT; i++)
                    {
                        pthread_create(&ID[i], NULL, &ThrdFunc, &ID[i]);
                    }

                    for(i=0; i < TCOUNT; i++)
                    {
                        pthread_join(ID[i], NULL);
                    }

                    //InitThread();


                    clearStatusArea();
                    gotoXY(1,SATUSAREA_Y);
                    printf("Done!");
                    gotoXY(SATUSAREA_X+1, 3);
                    printf("Number of threads: %d", TCOUNT);
                    gotoXY(SATUSAREA_X+1, 4);
                    printf("Execution delay: %d seconds", THDELAY);
                    gotoXY(SATUSAREA_X+1, 6);
                    printf("All information about  ");
                    gotoXY(SATUSAREA_X+1, 7);
                    printf("the threads's work can be ");
                    gotoXY(SATUSAREA_X+1, 8);
                    printf("found in the files: ");

                    for(int i=0;i<TCOUNT;i++)
                    {
                        gotoXY(SATUSAREA_X+1, 10+i);
                        printf("./logThreadNumber%d.txt", i+1);
                    }

                }

                break;
            case '3': //delete data and list
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
                    printf("Delete Data...");
                    clearStatusArea();
                    deleteOldData(pathA);
                    deleteList();
                }
                break;
            case '4': //show the Lis
                clearStatusArea();
                ShowList();
                break;
            case '5': //show the Lis
                clearStatusArea();
                gotoXY(1,SATUSAREA_Y);
                printf("Create Test Data...");
                createTestData(20);
                clearStatusArea();
                gotoXY(1,SATUSAREA_Y);
                printf("Done!");
                break;
            default:
                break;
        }
    }
    while(x != K_ESC);

    finish();

    return 0;
}