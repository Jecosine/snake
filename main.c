#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define up 1
#define down 2
#define left 3
#define right 4

typedef struct object{
    int pos_x;
    int pos_y;
    struct object *next;
} object;
//define basic parameters
int score = 0;
int delta = 1;
int state = 0;
int delay = 200;
//define snake and food
struct object *snake;
struct object *food;
//define windows parameters
HANDLE console;

//define functions
void locate(int x,int y);
void setColor(int c);
void clearScreen();

int main()
{
    printf("Hello world!\n");
    return 0;
}
