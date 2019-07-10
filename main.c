#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include <conio.h>

#define upward 1
#define downward 2
#define leftward 3
#define rightward 4
#define VK_A 0x41
#define VK_D 0x44
#define VK_W 0x57
#define VK_S 0x53

//chars  ■  □
typedef HWND (WINAPI *PROCGETCONSOLEWINDOW)();
PROCGETCONSOLEWINDOW GetConsoleWindow;

typedef struct object{
    COORD pos = {0,0};
    struct object *head;
    struct object *end;
} object;
typedef struct pixel{
    COORD pos = {0,0};
    int x;
    int y;
} pixel;
//declare basic parameters
int score = 0;
int delta = 1;
int state = 0;
int delay = 200;
int length = 3;
//define snake and food
struct object *snake;
struct object *food;
//define windows parameters
HANDLE console;

//declare functions
void locate(int x,int y);
void setColor(int c);
void clearScreen();
void refresh();
void move(int *direction, COORD *pos);
void append(struct object *o);
void initScreen();
void printSnake();
*struct object initSnake(int len);
//get input from keyboard
//w -> 1  s -> 2  a -> 3  d -> 4
int getKey(int *direction);

//define functions
//initialize a snake of certain length(default 3)
*struct object initSnake(int len){
    struct pixel *head = NULL;
    struct pixel *p = NULL;
    struct pixel *current = NULL;
    snake = (*struct snake)malloc(sizeof(struct object));
    //set head and end to null
    snake.head = NULL;
    snake.end = NULL;
    for(int i = 0;i < len; i++){
        struct pixel *current = (*struct pixel)malloc(sizeof(struct pixel));
        if(head == NULL){
            head = current;
            p = head;
        }
        p.next = current;
        if (i != (len - 1))
            p = p.next;
    }
    snake.head = head;
    snake.end = p;
    return snake;
}
void clearScreen(){
    system("cls");
}
void setColor(int c){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void locate(int x, int y){
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setConsoleSize(int x, int y){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size = {x, y};
    SMALL_RECT rc = {0,0,size.X - 1,size.Y - 1};
    //hide cursor
    CONSOLE_CURSOR_INFO cur = {1, FALSE};
    SetConsoleWindowInfo(h, TRUE, &rc);
    SetConsoleScreenBufferSize(h, size);
    SetConsoleCursorInfo(h, &cur);

}
// x->row y->column
void initScreen(int size_x, int size_y){
    setConsoleSize(size_x, size_y);
}
//get input
int getKey(int *direction){
    if (GetAsyncKeyState(VK_A) && (direction != rightward)){
        *direction = 3;
        return 3;
    }
    if (GetAsyncKeyState(VK_D) && (direction != leftward)){
        *direction = 4;
        return 4;
    }
    if (GetAsyncKeyState(VK_W) && (direction != downward)){
        *direction = 1;
        return 1;
    }
    if (GetAsyncKeyState(VK_S) && (direction != upward)){
        *direction = 2;
        return 2;
    }
    //return *direction;
}
//move snake
//w -> 1  s -> 2  a -> 3  d -> 4
void move(int *direction, struct object *s){
    *direction = getKey(*direction);
    switch (*direction){
        case 1: pos->Y--;break;
        case 2: pos->Y++;break;
        case 3: pos->X-=2;break;
        case 4: pos->X+=2;break;
        default: break;
    }
}
void test(){

}
int main()
{
    //set initial coordinate is rows 20 cols 50
    COORD s = {50,20};
    //set initial direction is left
    int direction = 3;

    system("chcp 65001");
    initScreen(100, 40);
    clearScreen();
    printSnake();
    locate(s.X,s.Y);
    printf("■");
    while (1){
        move(&direction, &s);
        locate(s.X,s.Y);
        printf("■");


        Sleep(500);
    }
    printf("■ %d %d",s.X,s.Y);
    locate(0,0);
    printf(" ");
    initScreen(100,40);
    return 0;
}
