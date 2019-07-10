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
    COORD pos;
    struct object *head;
    struct object *end;
} object;
typedef struct pixel{
    COORD pos;
    struct pixel *next;
    struct pixel *before;
} pixel;


//declare functions
void locate(int x,int y);
void setColor(int c);
void clearScreen();
void move(int *direction, struct object *s);
void initScreen();
void printSnake(struct object *s);
struct object* initSnake(int len, COORD pos);
//get input from keyboard
//w -> 1  s -> 2  a -> 3  d -> 4
int getKey(int *direction);

//define functions
//initialize a snake of certain length(default 3)
struct object* initSnake(int len, COORD pos){
    struct pixel *head = NULL;
    struct pixel *p = NULL;
    struct pixel *current = NULL;
    struct object *s = (struct object*)malloc(sizeof(struct object));
    //set head and end to null,set pos
    s->head = NULL;
    s->end = NULL;
    s->pos = pos;
    for(int i = 0;i < len; i++){
        struct pixel *current = (struct pixel*)malloc(sizeof(struct pixel));
        current->next = NULL;
        current->before = NULL;
        current->pos = pos;
        pos.X += 2;
        if(head == NULL){
            head = current;
            p = head;
        }
        else{
            p->next = current;
            current->before = p;
            p = p->next;
        }

    }
    s->head = head;
    s->end = p;
    return s;
}
void printSnake(struct object *s){
    struct pixel *p;
    for(p = s->head;p != NULL;p = p->next){
        COORD pos = p->pos;
        locate(pos.X, pos.Y);
        printf("■");
    }
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
    if (GetAsyncKeyState(VK_A) && (*direction != rightward)){
        *direction = 3;
        return 3;
    }
    if (GetAsyncKeyState(VK_D) && (*direction != leftward)){
        *direction = 4;
        return 4;
    }
    if (GetAsyncKeyState(VK_W) && (*direction != downward)){
        *direction = 1;
        return 1;
    }
    if (GetAsyncKeyState(VK_S) && (*direction != upward)){
        *direction = 2;
        return 2;
    }
    return *direction;
}
//move snake
//w -> 1  s -> 2  a -> 3  d -> 4
void move(int *direction, struct object *s){
    *direction = getKey(direction);
    COORD pos = s->pos;

    switch (*direction){
        case 1: pos.Y--;break;
        case 2: pos.Y++;break;
        case 3: pos.X-=2;break;
        case 4: pos.X+=2;break;
        default: break;
    }
    //printf("after direction change(switch):(%d,%d)\n",pos.X,pos.Y);
    //append head in move direction
    struct pixel *p = (struct pixel*)malloc(sizeof(struct pixel));
    p->before = NULL;
    p->pos = pos;
    p->next = s->head;
    ((struct pixel*)(s->head))->before = p;
    s->head = p;
    s->pos = pos;
    locate(p->pos.X, p->pos.Y);
    printf("■");

    //remove tail
    p = s->end;
    locate(p->pos.X,p->pos.Y);
    printf(" ");
    p = p->before;
    //printf("mid(%d,%d)",p->pos.X,p->pos.Y);
    p->next = NULL;
    free(s->end);
    s->end = p;

}
void test(){

}
//declare basic parameters
int score = 0;
int delta = 1;
int state = 0;
int delay = 200;
int length = 3;
//set initial coordinate is rows 20 cols 50
COORD spawnPos = {50,20};

//define windows parameters
HANDLE console;
int main()
{
    //define snake and food
    struct object *snake = initSnake(length,spawnPos);
    struct object *food;
    //set initial direction is left
    int direction = 3;
    system("chcp 65001");
    initScreen(100, 40);
    clearScreen();
    printSnake(snake);
//    for(struct pixel *p = snake->head;p != NULL;p = p->next){
//        printf("(%d,%d)",p->pos.X,p->pos.Y);
//    }
//    printf("end(%d,%d)\n",snake->end->pos.X,snake->end->pos.Y);
//    for(struct pixel *p = snake->end;p != NULL;p = p->before){
//        printf("(%d,%d)",p->pos.X,p->pos.Y);
//    }
//    printf("head(%d,%d)\n",snake->head->pos.X,snake->head->pos.Y);
//    move(&direction, snake);
//
//    move(&direction, snake);
//
//    move(&direction, snake);
//    for(struct pixel *p = snake->head;p != NULL;p = p->next){
//        printf("(%d,%d)",p->pos.X,p->pos.Y);
//    }
//    printf("end(%d,%d)\n",snake->end->pos.X,snake->end->pos.Y);
//    for(struct pixel *p = snake->end;p != NULL;p = p->before){
//        printf("(%d,%d)",p->pos.X,p->pos.Y);
//    }
//    printf("head(%d,%d)\n",snake->head->pos.X,snake->head->pos.Y);

    //locate(0,39);

    while (1){
        move(&direction, snake);
        locate(0,39);
        for(struct pixel *p = snake->head;p != NULL;p = p->next){
            printf("(%d,%d)",p->pos.X,p->pos.Y);
        }
        Sleep(200);
    }

    return 0;
}
