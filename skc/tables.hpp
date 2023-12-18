#pragma once
#include <map>

enum Constant
{
    Utf8,
    Class,
    MethodRef,
    NameAndType,
    Integer,
    Double,
    FieldRef
};

struct TableItem
{
    int id;
    enum Constant cnst;
    struct TableItem *  next;
    char * string;
    int firstRef;
    int secRef; 
};

/* ----------------------------------- Class Table ----------------------------------- */

struct FieldTable;

struct MethodTable;

/*! \brief Элемент таблицы класса. */
struct ClassTableElement
{
    // Ссылка на константу с именем класса - номер константы.
    int name; 

    // Ссылка на константу с именем родительского класса - номер константы.
    int superName; 

    // Ссылка на константу текущего класса.
    int thisClass;

    // Ссылка на константу родительского класса.
    int superClass;

    /// Указатель на таблицу методов класса.
    struct MethodTable * methods;

    /// Указатель на таблицу полей класса.
    struct FieldTable * fields;
};

/*! \brief Структура, описывающая таблицу классов. */
struct ClassTable
{
    /// Укащатель на контейнер элементов таблицы.
    std::map<char*, ClassTableElement *> * items;
};

/*! Создать пустую таблицу классов.
* \return Указатель на пустую таблицу классов.
*/
struct ClassTable * createClassTable();

/*! Добавить элемент таблицы классов в таблицу классов.
* \param[in,out] table таблица, в которую происходит добавление.
* \param[in] classname имя добавляемого класса. 
* \param[in] elem Добавляемый элемент класса.
* \return Измененная таблица классов с добавленным значением.
*/
struct ClassTable * addClassToTable(struct ClassTable * table, char * classname, struct ClassTableElement * elem);

/*! \brief Элемент таблицы полей класса. */
struct FieldTableElement
{
    /// Ссылка на константу с именем поля.
    int name;

    /// Ссылка на константу с декриптором поля.
    int descriptor;
};

/*! \brief Таблица полей класса. */
struct FieldTable
{

};

/*! \brief Элемент таблицы методов класса. */
struct MethodTableElement
{

};

/*! \brief Таблица методов класса. */
struct MethodTable
{

};
