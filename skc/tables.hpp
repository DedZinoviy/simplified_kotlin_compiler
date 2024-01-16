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
        
        /*! Конструктор.
        * \param[in] type тип константы.
        * \param[in] id номер константы в таблице констант.
        * \param[in] utf8 строка-utf8.
        * \param[in] intVal целочисленное значение для цеочисленных констант.
        * \param[in] dVal значение числас плавающей точкой для дробных констант.
        * \param[in] fRef ссылка на первую контанту - номер в таблице констант.
        * \param[in] secondRef ссылка на вторую контанту - номер в таблице констант.
        */
        ConstantTableItem(enum ConstantType type, int id, char * utf8 = NULL, int intVal = NULL, double dVal = NULL, int fRef = NULL, int secondRef = NULL);
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
        int findOrAddConstant(enum ConstantType type, char * utf8string = NULL, int intVal = NULL, double dVal = NULL, int fRef = NULL, int sRef = NULL);
    
    private:
        
        /*! Найти константу в таблице констант.
        * \param[in] type тип константы.
        * \param[in] fRef номер константы первой ссылки.
        * \param[in] secondRef номер константы второй ссылки.
        * \param[in] intVal Переменная для целочисленных значений.
        * \param[in] dVal Переменная для дробных значений с плавающей точкой.
        * \return номер найденной константы; -1, если константа не найдена.
        */
        int findConstant(enum ConstantType type, char * utf8string, int fRef = NULL, int secondRef = NULL, int intVal = NULL, double dVal = NULL);
    
};

/* ----------------------------------- Class Table ----------------------------------- */

/*! Построить таблицу классов для заданного файла Котлин.
* \param[in] root Корневой узел файла Котлин.
* \param[in] fileName Имя файла Котлин.
* \return Возможная ошибка построения.
*/  
struct SemanticError * buildClassTable(struct KotlinFileNode * root, const char * fileName);

/*! Установить наследование для классов.
* \param[in] root Указатель на корневой узед дерева программы.
* \return Возможная семантическая ошибка; NULL, если отутствует.
*/
struct SemanticError * setInheritance(struct KotlinFileNode * root);

class FieldTable;

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
    class FieldTable * fields;

    /// Указатель на таблицу констант класса.
    class ConstantTable * constants;

    /// \brief Проверить, является ли класс с указанным именем суперклассом для текущего.
    /// \param[in] superName имя потенциального суперкласса.
    /// \return true - если является, false - если нет.
    bool isHaveSuperClass(std::string superName);
};

/*! Создать пустой элемент таблицы классов.
* \return пустой элемент таблицы классов.
*/
class ClassTableElement * createEmptyClassTableElement();

/*! \brief Структура, описывающая таблицу классов. */
class ClassTable
{
    public:
    /// Укащатель на контейнер элементов таблицы.
    static std::map<std::string, class ClassTableElement *> items;

};

/*! \brief Элемент таблицы полей класса. */
class FieldTableElement
{
    public:
        /// Ссылка на константу с именем поля.
        int name;

        /// Ссылка на константу с декриптором поля.
        int descriptor;

        /// Список модификаторов поля.
        struct ModifierHead * modifiers;

        FieldTableElement(int nm, int dsc, struct ModifierHead * mods);
};

/*! \brief Таблица полей класса. */
class FieldTable
{
    public:
        /// Указатель на контейнер элементов таблицы.
        std::map<std::string, class FieldTableElement*> * fields;
};

/*! \brief Элемент таблицы методов класса. */
class MethodTableElement
{
    public:
        /// Ссылка на номер константы с именем метода в таблице констант.
        int methodName = NULL;

        /// Ссылка на номер константы с дескриптором в таблице констант.
        int descriptor = NULL;

        /// Строковое название метода.
        std::string strName;

        /// Строковый дескриптор метода.
        std::string strDesc;

        /// Указатель на начало реализации (тела) метода
        struct StatementListNode * start = NULL;

        /// Тип возвращаемого значения.
        class Type* retType = NULL;

        /// Вектор параметров метода.
        std::vector<class FuncParam> params;
};

/*! \brief Класс параметра функции. */
class FuncParam
{
    public:

        /// Имя параметра.
        std::string name;

        /// тип параметра.
        class Type * typ;
        /*! Перегруженный оператор сравнения для 
        */
        bool operator == (class FuncParam & other) const;

        FuncParam(std::string n, class Type * t);
};

/*! \brief Класс типа. */
class Type
{
    public:
        /// Тип узла типа - пользовательский класс или массив. 
        enum TypeType typ;

        /// Указатель на класс - тип данных.
        class ClassTableElement * cls;

        /// Имя класса.
        std::string className;

        /// Размер массива.
        int arraySize;

        /// \brief Проверить, может ли заменить тип, переданный как аргумент метода текущий тип. 
        /// \param other Проверяемый тип
        /// \return  Возможность замены.
        bool isReplacable(class Type & other) const;

        Type();

        Type(struct TypeNode * type);
};

/*! \brief Таблица методов класса. */
struct MethodTable
{
    std::map<std::string, std::map<std::vector<class FuncParam>, struct MethodTableElement *>> methods;
};
