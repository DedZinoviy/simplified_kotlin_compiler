#include "tables.hpp"

/* ----------------------------------- Class Table ----------------------------------- */

/*! Создать пустую таблицу классов.
* \return Указатель на пустую таблицу классов.
*/
struct ClassTable * createClassTable()
{
    return NULL;
}

/*! Добавить элемент таблицы классов в таблицу классов.
* \param[in,out] table таблица, в которую происходит добавление.
* \param[in] classname имя добавляемого класса. 
* \param[in] elem Добавляемый элемент класса.
* \return Измененная таблица классов с добавленным значением.
*/
struct ClassTable * addClassToTable(struct ClassTable * table, char * classname, struct ClassTableElement * elem)
{
    return NULL;
}
