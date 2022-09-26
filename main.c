#include "main.h"
#include <stdio.h>
#include <stdlib.h>

int main(){ return 0; }

/////////////////////////////////////библиотечные//////////////////////////////////////////
#define READ 0
#define WRITE 1
#define STEP 10  //шаг на который будет расширяться массив
#define MEM_ERR 1

struct dArray {
    int *array;  //если ошибка памяти считаем указатель равным NULL
    int maxX;     //default = 0
};

int arrayExtend(int x, struct dArray *ptrArray);

int array_Main(int flag, int x, int value, struct dArray *ptrArray) {
    _Bool err = 0;
    if(ptrArray->array == NULL)
        return 0;
    if(x >= ptrArray->maxX){
        if(arrayExtend(x, ptrArray) == MEM_ERR){
            printf("memory allocation error\n");
            //*array == null
            return 0;
        }
        err = 1;
    }

    switch (flag) {
        case READ:
            if (err)
                printf("Значение X = %d получено из неопределенной переменной\n", x);
            return ptrArray->array[x];
        case WRITE:
            return (ptrArray->array[x] = value);
    }
}

int arrayExtend(int x, struct dArray *ptrArray){
    int *buff = ptrArray->array;
    //переменная х теряет смысл, теперь это новое кол-во элементов массива
    x = x + 1 + (STEP - (x + 1) % STEP);
    ptrArray->array = malloc(x * sizeof(int));
    if(ptrArray->array == NULL) {
        return MEM_ERR;
    }
    for(int i = 0; i < ptrArray->maxX; i++)
        ptrArray->array[i] = buff[i];
    ptrArray->maxX = x;
    free(buff);
    return 0;
}

/////////////////////////////////////пользовательские////////////////////////////////////////
void* arrayInit(){ //сразу выделяет память под массив
    struct dArray *ptrArray = malloc(sizeof(struct dArray));
    if(ptrArray != NULL) {
        ptrArray->maxX = 0;
        if (arrayExtend(ptrArray->maxX, ptrArray) == MEM_ERR) {
            printf("arrayExtend: memory error\n");
            //*array == null
        }
    }
    else
        printf("arrayInit: memory allocation error\n");
    return ptrArray;
}

void arrayFree(struct dArray *ptrArray) {
    if (ptrArray != NULL) {
        if (ptrArray->array != NULL)
            free(ptrArray->array);
        free(ptrArray);
    }
}

_Bool arrayMemErr(struct dArray *ptrArray) {
    return ptrArray->array == NULL ? 1 : 0;
}

int array_r(struct dArray *ptrArray, int x){
    if (x >= 0)
        return array_Main(READ, x, 0, ptrArray);
    else{
        printf("array_r error: X = %d\n", x);
        return 0;
    }
}

int array_w(struct dArray *ptrArray, int x, int value){
    if(x >= 0)
        return array_Main(WRITE, x, value, ptrArray);
    else{
        printf("array_w error: X = %d\n", x);
        return 0;
    }
}