#include "interface.h"

int main(void)
{
    char x;

    printf("\nIf you want to create test data type 1");
    printf("\nIf you want to copy test data from A to B type 2");
    printf("\nIf you want to delete test data from A type 3");
    printf("\nIf you want to Iterate the List type 4\n");

    do
    {
        switch (checkDir()) {
            case 1:
                printf("\nYou seem to be missing folder A. I would create it.\n");
                makeDir(pathA);
                break;
            case 2:
                printf("\nYou seem to be missing folder B. I would create it.\n");
                makeDir(pathB);
                break;
            case 3:
                printf("\nYou seem to be missing folders A and B. I would create it.\n");
                makeDir(pathA);
                makeDir(pathB);
                break;
            default:break;
        }


        x = getch();
        switch (x) {
            case '1':
                printf("\n Create Test Data...\n");
                createTestData(20);
                copyDataToList(pathA);
                break;
            case '2':
                printf("\n Copy Test Data...\n");
                iterateListAndCopy(pathA);
                break;
            case '3':
                printf("\n Delete Test Data...\n");
                deleteOldData(pathA);
                deleteList();
                break;
            case '4':
                iterateList();
                break;
            default:
                break;
        }
    }
    while(x != K_ESC);


    return 0;
}