#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "graphics.h"

char canvas[ROWS][COLS];

void initializeCanvas()
{
    int i,j;

    for(i=0;i<ROWS;i++)
    {
        for(j=0;j<COLS;j++)
        {
            canvas[i][j]='_';
        }
    }
}

void displayCanvas()
{
    int i,j;

    for(i=0;i<ROWS;i++)
    {
        for(j=0;j<COLS;j++)
        {
            printf("%c",canvas[i][j]);
        }
        printf("\n");
    }
}

void drawLine(int x1,int y1,int x2,int y2)
{
    int x;

    for(x=x1;x<=x2;x++)
    {
        canvas[y1][x]='*';
    }
}

void drawRectangle(int x,int y,int width,int height)
{
    int i,j;

    for(i=y;i<y+height;i++)
    {
        for(j=x;j<x+width;j++)
        {
            if(i==y || i==y+height-1 ||
               j==x || j==x+width-1)
            {
                canvas[i][j]='*';
            }
        }
    }
}

void drawTriangle(int x,int y,int size)
{
    int i,j;

    for(i=0;i<size;i++)
    {
        for(j=0;j<=i;j++)
        {
            canvas[y+i][x+j]='*';
        }
    }
}

void drawCircle(int xc,int yc,int r)
{
    int x,y;

    for(y=0;y<ROWS;y++)
    {
        for(x=0;x<COLS;x++)
        {
            int d=(x-xc)*(x-xc)+(y-yc)*(y-yc);

            if(abs(d-r*r)<=r)
            {
                canvas[y][x]='*';
            }
        }
    }
}