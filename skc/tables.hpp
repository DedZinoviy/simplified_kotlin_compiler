#pragma once
#include <map>
#include <utility>
#include <string>
#include <vector>
#include "nodes.h"

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

/*! Построить таблицу классов для заданного файла Котлин.
* \param[in] root Корневой узел файла Котлин.
* \param[in] fileName Имя файла Котлин.
* \return созданная таблица классов.
*/  
struct ClassTable * buildClassTable(struct KotlinFileNode * root, const char * fileName);

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

/*! Создать пустой элемент таблицы классов.
* \return пустой элемент таблицы классов.
*/
struct ClassTableElement * createEmptyClassTableElement();

/*! \brief Структура, описывающая таблицу классов. */
struct ClassTable
{
    /// Укащатель на контейнер элементов таблицы.
    std::map<std::string, ClassTableElement *> * items;
};

/*! Создать пустую таблицу классов.
* \return Указатель на пустую таблицу классов.
*/
struct ClassTable * createEmptyClassTable();

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

/*! \brief Класс параметра функции. */
class FuncParam
{
    public:
        /*! Перегруженный оператор сравнения для 
        */
        bool operator == (class FuncParam & other) const;
};

/*! \brief Класс типа. */
class Type
{
    public:
        /// Тип узла типа - пользовательский класс или массив. 
        enum TypeType typ;

        /// Указатель на класс - тип данных.
        class ClassTableElement * cls;

        /// \brief Проверить, может ли заменить тип, переданный как аргумент метода текущий тип. 
        /// \param other Проверяемый тип
        /// \return  Возможность замены.
        bool isReplacable(class Type & other) const;
};

/*! \brief Таблица методов класса. */
struct MethodTable
{
    std::map<std::string, std::map<std::vector<class FuncParam>, struct MethodTableElement *>> methods;
};
