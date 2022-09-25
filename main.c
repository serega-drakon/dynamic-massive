#include <stdio.h>
#include <stdlib.h>

//пользовательские ф.
struct dArray;
int dArray_w(int x, int y, int value);
int dArray_r(int x, int y);
void arraySwitch(struct dArray *ptrdArray);
void* arrayInit();
void dArrayFree();

int main() {
    int x = 10;
    int y = 2;
    struct dArray *array = arrayInit();
    arraySwitch(array);
    printf("|%d\n", dArray_w(1,1,100));
    printf("%d\n", dArray_r(1,1));


    return 0;
}

/////////////////////////////////////библиотечные//////////////////////////////////////////
#define READ 0
#define WRITE 1
#define STEP 10  //шаг на который будет расширяться массив
#define MEM_ERR 1
#define MAX_X 300

struct dArray {
    int *array;
    int maxX;     //const value
    int y;     //default = 0
    _Bool memErr;//default = 0
};

void arrayCheckout(int flag, struct dArray *dArray_W, struct dArray **dArray_R);
int arrayExtend(int y, struct dArray *ptrdArray);

int dArray_Main(int flag, int x, int y, int value) {
    struct dArray *ptrdArray;
    _Bool err = 0;
    arrayCheckout(READ, 0,&ptrdArray);
    if(ptrdArray->memErr)
        return 0;
    if(y >= ptrdArray->y){
        if(arrayExtend(y, ptrdArray) == MEM_ERR){
            printf("memory allocation error\n");
            ptrdArray->memErr = 1;
            return 0;
        }
        err = 1;
    }

    switch (flag) {
        case READ:
            if (err)
                printf("Значение X = %d, Y = %d получено из неопределенной переменной\n", x, y);
            return ptrdArray->array[y * ptrdArray->maxX + x];
        case WRITE:
            return (ptrdArray->array[y * ptrdArray->maxX + x] = value);
    }
}

int arrayExtend(int y, struct dArray *ptrdArray){
    int *buff = ptrdArray->array;
    //переменная х теряет смысл, теперь это новое кол-во элементов массива
    y = y + 1 + (STEP - (y + 1) % STEP);
    ptrdArray->array = malloc(y * ptrdArray->maxX * sizeof(int));
    if(ptrdArray->array == NULL)
        return MEM_ERR;
    for(int i = 0; i < ptrdArray->y; i++)
        ptrdArray->array[i] = buff[i];
    ptrdArray->y = y;
    free(buff);
    return 0;
}

void arrayCheckout(int flag, struct dArray *dArray_W, struct dArray **dArray_R) { //обожаю дрочево со ссылками оаоаоа
    static struct dArray *branch;//а хули пусть будет как гит

    switch (flag) {
        case READ:
            *dArray_R = branch;
            break;
        case WRITE:
            branch = dArray_W;
            break;
    }
}

/////////////////////////////////////пользовательские////////////////////////////////////////
void* arrayInit(){ //сразу выделяет память под массив
    struct dArray *ptrdArray = malloc(sizeof(struct dArray));
    ptrdArray->maxX = MAX_X;
    ptrdArray->y = 0;
    ptrdArray->memErr = 0;
    if(arrayExtend(ptrdArray->y,ptrdArray) == MEM_ERR){
        printf("memory error\n");
        ptrdArray->memErr = 1;
    }
    return ptrdArray;
}

void dArrayFree(struct dArray *ptrdArray){
    if(ptrdArray->memErr == 0)
        free(ptrdArray->array);
    free(ptrdArray);
}

_Bool arrayMemErr(){
    struct dArray *ptrdArray;
    arrayCheckout(READ, 0, &ptrdArray);
    return ptrdArray->memErr;
}

void arraySwitch(struct dArray *ptrdArray){
    arrayCheckout(WRITE, ptrdArray, 0);
}

int dArray_r(int x, int y){
    if (x >= 0 && x < MAX_X && y >= 0)
        return dArray_Main(READ, x, y, 0);
    else{
        printf("dArray_r error: X = %d or Y = %d < 0\n", x, y);
        return 0;
    }
}

int dArray_w(int x, int y, int value){
    if(x >= 0 && x < MAX_X && y >= 0)
        return dArray_Main(WRITE, x, y, value);
    else{
        printf("dArray_w error: X = %d < 0 or Y = %d\n", x, y);
        return 0;
    }
}