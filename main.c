#include <stdio.h>
#include <stdlib.h>

#define newdArray(name) struct dynamicArray name = {0,0};

struct dynamicArray {
    int *array;
    int n; //обязательно обращаем в нуль!
};

int dArray_w(int x, int value);
int dArray_r(int x);
void arraySwitch(struct dynamicArray *structOfdArray);

int main() {
    int x = 0;
    struct dynamicArray test = {0, -1};
    arraySwitch(&test);
    dArray_w(x,123);
    printf("n = %d\n", test.n);
    printf("arr[%d] = %d\n", x, dArray_r(x));
    printf("array[%d] = %d\n", x, test.array[x]);

    struct dynamicArray second = {0,0};
    arraySwitch(&second);
    dArray_w(x,321);
    printf("second: arr[%d] = %d\n", x, dArray_r(x));

    arraySwitch(&test);
    printf("first: arr[%d] = %d\n", x, dArray_r(x));

    newdArray(cock);
    arraySwitch(&cock);
    printf("||%d\n", dArray_w(12,999));
    return 0;
}

#define READ 0
#define WRITE 1
#define STEP 10
#define MEM_ERR 1

void arrayCheckout(int flag, struct dynamicArray *structOfdArray_W, struct dynamicArray **structOfdArray_R);
int arrayExtend(int x, int step, struct dynamicArray *structOfArray);

int dArray(int flag, int x, int value) {
    static struct dynamicArray *structOfdArray;
    _Bool err = 0;
    arrayCheckout(READ, 0,&structOfdArray);
    if(x >= structOfdArray->n){
        if(arrayExtend(x,STEP, structOfdArray) == MEM_ERR){
            printf("memory allocation error\n");
            return 0;
        }
        err = 1;
    }

    switch (flag) {
        case READ:
            if (err)
                printf("Значение X = %d получено из неопределенной переменной\n", x);
            return structOfdArray->array[x];
        case WRITE:
            return (structOfdArray->array[x] = value);
    }
}

int arrayExtend(int x, int step, struct dynamicArray *structOfArray){
    int *buff = structOfArray->array;
    //переменная х теряет смысл, теперь это новое кол-во элементов массива
    x = x + 1 + (step - (x + 1) % step);
    structOfArray->array = malloc(x * sizeof(int));
    if(structOfArray->array == NULL)
        return MEM_ERR;
    for(int i = 0; i < structOfArray->n; i++)
        structOfArray->array[i] = buff[i];
    structOfArray->n = x;
    free(buff);
    return 0;
}

void arrayCheckout(int flag, struct dynamicArray *structOfdArray_W, struct dynamicArray **structOfdArray_R) { //обожаю дрочево со ссылками оаоаоа
    static struct dynamicArray *branch;//а хули пусть будет как гит
    static _Bool hasChanged = 0;

    switch (flag) {
        case READ:
            if (hasChanged) {
                *structOfdArray_R = branch;
                hasChanged = 0;
            }
            break;
        case WRITE:
            branch = structOfdArray_W;
            hasChanged = 1;
            break;
    }
}

void arraySwitch(struct dynamicArray *structOfdArray){
    arrayCheckout(WRITE, structOfdArray,0);
}

int dArray_r(int x){
    return dArray(READ, x, 0);
}

int dArray_w(int x, int value){
    return dArray(WRITE, x, value);
}