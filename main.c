#include <stdio.h>
#include <stdlib.h>

//пользовательские ф.
struct dArray;
int array_w(struct dArray *ptrArray, int x, int y, int value);
int array_r(struct dArray *ptrArray, int x, int y);
_Bool arrayMemErr(struct dArray *ptrArray);
void* arrayInit(); //returns NULL if memory error occur
void arrayFree(struct dArray *ptrArray);

int main() {
    int x = 10;
    int y = 2;
    struct dArray *array = arrayInit();
    if(array == NULL || arrayMemErr(array) == 1) return 0;
    int j = 0;
    while(j < 100) {
        for(int i = 0; i < 1; i++)
            array_w(array, i, j, getchar());
        for (int i = 0; i < 1; i++)
            printf("%c", array_r(array, i, j));
        j++;
    }
    arrayFree(array);
    return 0;
}

/////////////////////////////////////библиотечные//////////////////////////////////////////
#define READ 0
#define WRITE 1
#define STEP 5  //шаг на который будет расширяться массив
#define MEM_ERR 1
#define MAX_X 300

struct dArray {
    int *array;
    int maxX;     //const value
    int y;     //default = 0
    _Bool memErr;//default = 0
};

int arrayExtend(int y, struct dArray *ptrArray);

int array_Main(int flag, int x, int y, int value, struct dArray *ptrArray) {
    _Bool err = 0;
    if(ptrArray->memErr)
        return 0;
    if(y >= ptrArray->y){
        if(arrayExtend(y, ptrArray) == MEM_ERR){
            printf("memory allocation error\n");
            ptrArray->memErr = 1;
            return 0;
        }
        err = 1;
    }

    switch (flag) {
        case READ:
            if (err)
                printf("Значение X = %d, Y = %d получено из неопределенной переменной\n", x, y);
            return ptrArray->array[y * ptrArray->maxX + x];
        case WRITE:
            return (ptrArray->array[y * ptrArray->maxX + x] = value);
    }
}

int arrayExtend(int y, struct dArray *ptrArray){
    int *buff = ptrArray->array;
    //переменная х теряет смысл, теперь это новое кол-во элементов массива
    y = y + 1 + (STEP - (y + 1) % STEP);
    ptrArray->array = malloc(y * ptrArray->maxX * sizeof(int));
    if(ptrArray->array == NULL)
        return MEM_ERR;
    for(int j = 0, i; j < ptrArray->y; j++)
        for(i = 0; i < ptrArray->maxX; i++)//
            ptrArray->array[j * ptrArray->maxX + i] = buff[j * ptrArray->maxX + i];
    ptrArray->y = y;
    free(buff);
    return 0;
}

/////////////////////////////////////пользовательские////////////////////////////////////////
void* arrayInit(){ //сразу выделяет память под массив
    struct dArray *ptrArray = malloc(sizeof(struct dArray));
    if(ptrArray != NULL) {
        ptrArray->maxX = MAX_X;
        ptrArray->y = 0;
        ptrArray->memErr = 0;
        if (arrayExtend(ptrArray->y, ptrArray) == MEM_ERR) {
            printf("arrayExtend: memory error\n");
            ptrArray->memErr = 1;
        }
    }
    else
        printf("arrayInit: memory allocation error\n");
    return ptrArray;
}

void arrayFree(struct dArray *ptrArray) {
    if (ptrArray != NULL) {
        if (ptrArray->memErr == 0)
            free(ptrArray->array);
        free(ptrArray);
    }
}

_Bool arrayMemErr(struct dArray *ptrArray) {
    return ptrArray->memErr;
}

int array_r(struct dArray *ptrArray, int x, int y){
    if (x >= 0 && x < MAX_X && y >= 0)
        return array_Main(READ, x, y, 0, ptrArray);
    else{
        printf("array_r error: X = %d Y = %d\n", x, y);
        return 0;
    }
}

int array_w(struct dArray *ptrArray, int x, int y, int value){
    if(x >= 0 && x < MAX_X && y >= 0)
        return array_Main(WRITE, x, y, value, ptrArray);
    else{
        printf("array_w error: X = %d Y = %d\n", x, y);
        return 0;
    }
}