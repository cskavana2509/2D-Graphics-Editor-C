#ifndef GRAPHICS_H
#define GRAPHICS_H

#define ROWS 30
#define COLS 60

extern char canvas[ROWS][COLS];

void initializeCanvas();
void displayCanvas();

void drawLine(int x1,int y1,int x2,int y2);
void drawRectangle(int x,int y,int width,int height);
void drawTriangle(int x,int y,int size);
void drawCircle(int xc,int yc,int r);

#endif