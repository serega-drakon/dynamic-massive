# dynamic-massive
### Тестовая версия самописного динамического массива на языке си

На самом деле я написал функции управления указателем и динамического выделения памяти под него, сама главная функция **dArray()** массива не содержит, она содержит ссылку на структуру, в которой лежит ссылка на массив) такое устройство дает возможность в рамках одного проекта использовать несколько моих великолепных массивов! структура это типа флешки, вставляешь в комп, а комп (как и функции здесь) управляет данными на ней, и флешки можно менять.

## Устройство проекта:
- **dArray** - основная функция массива, хранит указатель на структуру с которой она работает, ну и в зависимости от данного ей флага производит операцию
- **arrayExtend** - расширяет массив в данной ей структуре, те берет указатель из нее, выделяет новую память с шагом *step*, и возвращает потерянные значения через буферный указатель
- **arrayCheckout** - с помошью этой функции можно менять структуру, над которой *dArray* проводит операции, + тут маленькая оптимизация с помошью була *hasChanged*
- **arraySwitch** - обертка к *arrayCheckout*
- **dArray_r** - обертка к *dArray* на чтение
- **dArray_w** - обертка к *dArray* на запись
- **newdArray(name)** - *макрос* для упрощенного создания подходящeй структуры *name* для массива (n должно *обязательно* быть равно нулю, поэтому чтобы не разбираться в ньюансах лучше создавать через мой макрос)