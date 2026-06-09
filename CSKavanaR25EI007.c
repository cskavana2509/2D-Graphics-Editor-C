#include <stdio.h>
#include <stdlib.h>

#define ROWS 20
#define COLS 60
#define MAX  10

/* ───────────── Canvas ───────────── */
char canvas[ROWS][COLS];

void clearCanvas() {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            canvas[i][j] = ' ';
}

void display() {
    printf("\n");
    for (int j = 0; j < COLS+2; j++) printf("-");
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        printf("|");
        for (int j = 0; j < COLS; j++) printf("%c", canvas[i][j]);
        printf("|\n");
    }
    for (int j = 0; j < COLS+2; j++) printf("-");
    printf("\n");
}

void dot(int r, int c, char ch) {
    if (r >= 0 && r < ROWS && c >= 0 && c < COLS)
        canvas[r][c] = ch;
}

/* ───────────── Draw Shapes ───────────── */

void drawLine(int r1, int c1, int r2, int c2) {
    int dr = abs(r2-r1), dc = abs(c2-c1);
    int sr = (r1<r2)?1:-1, sc = (c1<c2)?1:-1;
    int err = dr - dc, e2;
    while (1) {
        dot(r1, c1, '*');
        if (r1==r2 && c1==c2) break;
        e2 = 2*err;
        if (e2 > -dc) { err -= dc; r1 += sr; }
        if (e2 <  dr) { err += dr; c1 += sc; }
    }
}

void drawRect(int r, int c, int w, int h) {
    for (int j = c; j < c+w; j++) { dot(r, j, '_'); dot(r+h-1, j, '_'); }
    for (int i = r; i < r+h; i++) { dot(i, c, '*'); dot(i, c+w-1, '*'); }
}

void drawCircle(int cx, int cy, int rad) {
    int x = 0, y = rad, d = 1 - rad;
    while (x <= y) {
        dot(cx+x,cy+y,'*'); dot(cx-x,cy+y,'*');
        dot(cx+x,cy-y,'*'); dot(cx-x,cy-y,'*');
        dot(cx+y,cy+x,'*'); dot(cx-y,cy+x,'*');
        dot(cx+y,cy-x,'*'); dot(cx-y,cy-x,'*');
        if (d < 0) d += 2*x + 3;
        else     { d += 2*(x-y) + 5; y--; }
        x++;
    }
}

void drawTriangle(int r1,int c1,int r2,int c2,int r3,int c3) {
    drawLine(r1,c1, r2,c2);
    drawLine(r2,c2, r3,c3);
    drawLine(r3,c3, r1,c1);
}

/* ───────────── Object Store ───────────── */
struct { int type, on, a,b,c,d,e,f; } obj[MAX];
int n = 0;

void redraw() {
    clearCanvas();
    for (int i = 0; i < n; i++) {
        if (!obj[i].on) continue;
        if (obj[i].type == 1) drawLine    (obj[i].a, obj[i].b, obj[i].c, obj[i].d);
        if (obj[i].type == 2) drawRect    (obj[i].a, obj[i].b, obj[i].c, obj[i].d);
        if (obj[i].type == 3) drawCircle  (obj[i].a, obj[i].b, obj[i].c);
        if (obj[i].type == 4) drawTriangle(obj[i].a, obj[i].b, obj[i].c, obj[i].d, obj[i].e, obj[i].f);
    }
}

void listAll() {
    printf("\n ID  Shape       Parameters\n");
    printf(" --  ----------  ----------\n");
    for (int i = 0; i < n; i++) {
        if (!obj[i].on) { printf(" %2d  (deleted)\n", i); continue; }
        printf(" %2d  ", i);
        if (obj[i].type==1) printf("Line        r1=%d c1=%d  r2=%d c2=%d\n",        obj[i].a,obj[i].b,obj[i].c,obj[i].d);
        if (obj[i].type==2) printf("Rectangle   r=%d c=%d  w=%d h=%d\n",            obj[i].a,obj[i].b,obj[i].c,obj[i].d);
        if (obj[i].type==3) printf("Circle      cx=%d cy=%d  radius=%d\n",           obj[i].a,obj[i].b,obj[i].c);
        if (obj[i].type==4) printf("Triangle    (%d,%d) (%d,%d) (%d,%d)\n",         obj[i].a,obj[i].b,obj[i].c,obj[i].d,obj[i].e,obj[i].f);
    }
}

/* ───────────── Main ───────────── */
int main() {
    clearCanvas();
    int ch, id;

    while (1) {
        printf("\n==== 2D Graphics Editor ====\n");
        printf(" 1. Add Line\n");
        printf(" 2. Add Rectangle\n");
        printf(" 3. Add Circle\n");
        printf(" 4. Add Triangle\n");
        printf(" 5. Delete Object\n");
        printf(" 6. Modify Object\n");
        printf(" 7. Display Canvas\n");
        printf(" 8. List All Objects\n");
        printf(" 9. Clear Canvas\n");
        printf(" 0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        if (ch == 0) break;

        /* ── ADD LINE ── */
        if (ch == 1) {
            printf("Enter start row    : "); scanf("%d", &obj[n].a);
            printf("Enter start column : "); scanf("%d", &obj[n].b);
            printf("Enter end row      : "); scanf("%d", &obj[n].c);
            printf("Enter end column   : "); scanf("%d", &obj[n].d);
            obj[n].type=1; obj[n].on=1; n++;
            printf("Line added. ID = %d\n", n-1);
        }

        /* ── ADD RECTANGLE ── */
        else if (ch == 2) {
            printf("Enter top-left row : "); scanf("%d", &obj[n].a);
            printf("Enter top-left col : "); scanf("%d", &obj[n].b);
            printf("Enter width        : "); scanf("%d", &obj[n].c);
            printf("Enter height       : "); scanf("%d", &obj[n].d);
            obj[n].type=2; obj[n].on=1; n++;
            printf("Rectangle added. ID = %d\n", n-1);
        }

        /* ── ADD CIRCLE ── */
        else if (ch == 3) {
            printf("Enter center row   : "); scanf("%d", &obj[n].a);
            printf("Enter center col   : "); scanf("%d", &obj[n].b);
            printf("Enter radius       : "); scanf("%d", &obj[n].c);
            obj[n].type=3; obj[n].on=1; n++;
            printf("Circle added. ID = %d\n", n-1);
        }

        /* ── ADD TRIANGLE ── */
        else if (ch == 4) {
            printf("Enter vertex 1 row : "); scanf("%d", &obj[n].a);
            printf("Enter vertex 1 col : "); scanf("%d", &obj[n].b);
            printf("Enter vertex 2 row : "); scanf("%d", &obj[n].c);
            printf("Enter vertex 2 col : "); scanf("%d", &obj[n].d);
            printf("Enter vertex 3 row : "); scanf("%d", &obj[n].e);
            printf("Enter vertex 3 col : "); scanf("%d", &obj[n].f);
            obj[n].type=4; obj[n].on=1; n++;
            printf("Triangle added. ID = %d\n", n-1);
        }

        /* ── DELETE ── */
        else if (ch == 5) {
            listAll();
            printf("Enter ID to delete : "); scanf("%d", &id);
            if (id >= 0 && id < n && obj[id].on)
                { obj[id].on = 0; printf("Object %d deleted.\n", id); }
            else
                printf("Invalid ID.\n");
        }

        /* ── MODIFY ── */
        else if (ch == 6) {
            listAll();
            printf("Enter ID to modify : "); scanf("%d", &id);
            if (id < 0 || id >= n || !obj[id].on) { printf("Invalid ID.\n"); continue; }
            printf("Enter new values:\n");
            if (obj[id].type==1) {
                printf("Enter start row    : "); scanf("%d", &obj[id].a);
                printf("Enter start column : "); scanf("%d", &obj[id].b);
                printf("Enter end row      : "); scanf("%d", &obj[id].c);
                printf("Enter end column   : "); scanf("%d", &obj[id].d);
            }
            if (obj[id].type==2) {
                printf("Enter top-left row : "); scanf("%d", &obj[id].a);
                printf("Enter top-left col : "); scanf("%d", &obj[id].b);
                printf("Enter width        : "); scanf("%d", &obj[id].c);
                printf("Enter height       : "); scanf("%d", &obj[id].d);
            }
            if (obj[id].type==3) {
                printf("Enter center row   : "); scanf("%d", &obj[id].a);
                printf("Enter center col   : "); scanf("%d", &obj[id].b);
                printf("Enter radius       : "); scanf("%d", &obj[id].c);
            }
            if (obj[id].type==4) {
                printf("Enter vertex 1 row : "); scanf("%d", &obj[id].a);
                printf("Enter vertex 1 col : "); scanf("%d", &obj[id].b);
                printf("Enter vertex 2 row : "); scanf("%d", &obj[id].c);
                printf("Enter vertex 2 col : "); scanf("%d", &obj[id].d);
                printf("Enter vertex 3 row : "); scanf("%d", &obj[id].e);
                printf("Enter vertex 3 col : "); scanf("%d", &obj[id].f);
            }
            printf("Object %d modified.\n", id);
        }

        /* ── DISPLAY ── */
        else if (ch == 7) {
            redraw(); display();
            continue;
        }

        /* ── LIST ── */
        else if (ch == 8) {
            listAll();
            continue;
        }

        /* ── CLEAR ── */
        else if (ch == 9) {
            n = 0;
            clearCanvas();
            printf("Canvas cleared.\n");
            display();
            continue;
        }

        redraw();
        display();
    }

    printf("GoodBye!\n");
    return 0;
}
