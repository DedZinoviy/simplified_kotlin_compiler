#pragma once
#include <map>
#include <utility>
#include <string>
#include <vector>
#include "nodes.h"
#include "semantic_errors.h"

/* ----------------------------------- Constatnt Table ----------------------------------- */

/*! Тип константы в таблице констант. */
enum ConstantType
{
    Utf8,
    Class,
    MethodRef,
    NameAndType,
    Integer,
    Double,
    FieldRef
};

/*! Элемент таблицы констант. */
class ConstantTableItem
{
    public: 
        int id; // Номер константы.
        enum ConstantType cnst; // Тип константы.
        char * string; // Строка для Utf-8 констант.
        int Integer; // Целое число для целочисленной константы.
        double Double; // Число с плавающий точкой.
        int firstRef; // Сслыка на первую константу.
        int secRef;  // Ссылка на вторую константу.
};

/*! Таблица констант. */
class ConstantTable
{
    public:
        int maxId; // Текущее максимальное значение номера констант в таблице констант.
        std::map<int, class ConstantTableItem *> constants; // Словарь - таблица констант.
        ConstantTable();

        /*! Найти константу в таблице констант или добавить ее в таблицу, если отсутствуюет. 
        * \param[in] type Тип константы.
        * \param[in] utf8string строка константы UTF-8.
        * \return номер константы в таблице констант, если таковая имеется; номер добавленной константы, если таковой не было.
        */
        int findOrAddConstant(enum ConstantType type, char * utf8string);
    
    private:
        
        /*! Найти константу в таблице констант.
        * \param[in] type тип константы.
        */
        int findConstant(enum ConstantType type, char * utf8string);
    
};

/* ----------------------------------- Class Table ----------------------------------- */

/*! Построить таблицу классов для заданного файла Котлин.
* \param[in] root Корневой узел файла Котлин.
* \param[in] fileName Имя файла Котлин.
* \param[in,out] emptyTable Собираемая таблица классов; в случае ошибки построения вернется NULL.
* \return Возможная ошибка построения.
*/  
struct SemanticError * buildClassTable(struct KotlinFileNode * root, const char * fileName, struct ClassTable * emptyTable);

/*! Установить наследование для классов.
* \param[in] root Указатель на корневой узед дерева программы.
* \return Возможная семантическая ошибка; NULL, если отутствует.
*/
struct SemanticError * setInheritance(struct KotlinFileNode * root);

struct FieldTable;

struct MethodTable;

/*! \brief Элемент таблицы класса. */
class ClassTableElement
{
    public: 
    // Ссылка на константу с именем класса - номер константы.
    int name;

    /// Флаг, показывающий открыт ли класс для наследования.
    int isOpen;

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

    /// Указатель на таблицу констант класса.
    class ConstantTable * constants;
};

/*! Создать пустой элемент таблицы классов.
* \return пустой элемент таблицы классов.
*/
class ClassTableElement * createEmptyClassTableElement();

/*! \brief Структура, описывающая таблицу классов. */
struct ClassTable
{
    /// Укащатель на контейнер элементов таблицы.
    std::map<std::string, class ClassTableElement *> * items;
};

/*! Создать пустую таблицу классов.
* \return Указатель на пустую таблицу классов.
*/
struct ClassTable * createEmptyClassTable();

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
