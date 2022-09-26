#ifndef DYNAMIC_MASSIVE_MAIN_H
#define DYNAMIC_MASSIVE_MAIN_H

//пользовательские ф.
struct dArray;
int array_w(struct dArray *ptrArray, int x, int value);
int array_r(struct dArray *ptrArray, int x);
_Bool arrayMemErr(struct dArray *ptrArray);
void* arrayInit(); //returns NULL if memory error occur
void arrayFree(struct dArray *ptrArray);

#endif //DYNAMIC_MASSIVE_MAIN_H
