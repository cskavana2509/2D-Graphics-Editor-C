#include <stdio.h>
#include "graphics.h"

int main()
{
    int choice;

    initializeCanvas();

    do
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Draw Line\n");
        printf("2. Draw Rectangle\n");
        printf("3. Draw Triangle\n");
        printf("4. Draw Circle\n");
        printf("5. Display Picture\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                drawLine(5,5,20,5);
                printf("Line Drawn\n");
                break;

            case 2:
                drawRectangle(10,10,15,6);
                printf("Rectangle Drawn\n");
                break;

            case 3:
                drawTriangle(30,5,6);
                printf("Triangle Drawn\n");
                break;

            case 4:
                drawCircle(40,20,5);
                printf("Circle Drawn\n");
                break;

            case 5:
                displayCanvas();
                break;

            case 6:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid Choice\n");
        }

    } while(choice!=6);

    return 0;
}