#pragma once
#include <map>
#include <utility>
#include <string>
#include <vector>
#include "nodes.h"
#include "semantic_errors.h"

/* ----------------------------------- Constatnt Table ----------------------------------- */

class ClassTable;

class ClassTableElement;

/*! Тип константы в таблице констант. */
enum ConstantType
{
    Utf8 = 1,
    Class = 7,
    MethodRef = 10,
    NameAndType = 12,
    Integer = 3,
    Double = 6,
    FieldRef = 9,
    String = 8
};

/*! Элемент таблицы констант. */
class ConstantTableItem
{
    public: 
        int id; // Номер константы.
        enum ConstantType cnst; // Тип константы.
        std::string string; // Строка для Utf-8 констант.
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
        ConstantTableItem(enum ConstantType type, int id, std::string utf8 = NULL, int intVal = NULL, double dVal = NULL, int fRef = NULL, int secondRef = NULL);
};

/*! Таблица констант. */
class ConstantTable
{
    public:
        int maxId = 1; // Текущее максимальное значение номера констант в таблице констант.
        std::map<int, class ConstantTableItem *> constants; // Словарь - таблица констант.
        ConstantTable();

        /*! Найти константу в таблице констант или добавить ее в таблицу, если отсутствуюет. 
        * \param[in] type Тип константы.
        * \param[in] utf8string строка константы UTF-8.
        * \return номер константы в таблице констант, если таковая имеется; номер добавленной константы, если таковой не было.
        */
        int findOrAddConstant(enum ConstantType type, std::string utf8string = NULL, int intVal = NULL, double dVal = NULL, int fRef = NULL, int sRef = NULL);
    
    private:
        
        /*! Найти константу в таблице констант.
        * \param[in] type тип константы.
        * \param[in] fRef номер константы первой ссылки.
        * \param[in] secondRef номер константы второй ссылки.
        * \param[in] intVal Переменная для целочисленных значений.
        * \param[in] dVal Переменная для дробных значений с плавающей точкой.
        * \return номер найденной константы; -1, если константа не найдена.
        */
        int findConstant(enum ConstantType type, std::string utf8string, int fRef = NULL, int secondRef = NULL, int intVal = NULL, double dVal = NULL);
    
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

class MethodTable;

class ClassParamTable;

/*! \brief Элемент таблицы класса. */
class ClassTableElement
{
    public: 
    // Ссылка на константу с именем класса - номер константы.
    int name;

    /// Флаг, показывающий открыт ли класс для наследования.
    int isOpen;

    // Ссылка на константу с именем родительского класса - номер константы.
    int superName = NULL; 

    // Ссылка на константу текущего класса.
    int thisClass;

    // Ссылка на константу родительского класса.
    int superClass;

    /// Указатель на таблицу методов класса.
    class MethodTable * methods;

    /// Указатель на таблицу полей класса.
    class FieldTable * fields;

    /// Указатель на таблицу констант класса.
    class ConstantTable * constants;

    /// Указатель на таблицу параметров класса.
    class ClassParamTable * params;

    /// Строка - имя класса.
    std::string clsName;

    /// \brief Проверить, является ли класс с указанным именем суперклассом для текущего.
    /// \param[in] superName имя потенциального суперкласса.
    /// \return true - если является, false - если нет.
    bool isHaveSuperClass(std::string superName);

    ClassTableElement();
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

        std::string strName;

        std::string stdDesc;

        /// Список модификаторов поля.
        struct ModifierHead * modifiers;

        /// Является ли указанное поле изменяемым.
        int isConst;

        FieldTableElement(int nm, int dsc, std::string strNm, std::string strDsc, struct ModifierHead * mods, int isCnst);
};

/*! \brief Таблица полей класса. */
class FieldTable
{
    public:
        /// Указатель на контейнер элементов таблицы.
        std::map<std::string, class FieldTableElement*> fields;
};

class LocalVariableTable;

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

        /// Ссылка на таблицу локальных переменных.
        class LocalVariableTable * varTable = NULL;

        /// Флаг показывающий, является ли указанный метод первым кандидатом.
        int isFirst = NULL;

        MethodTableElement(int nameCnst, int descCnst, std::string nam, std::string dsc, struct StatementListNode * strt, class Type * ret, std::vector<class FuncParam> pars);
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

        bool operator < (class FuncParam & other) const;
        

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

        struct TypeNode * toTypeNode();

        Type();

        Type(struct TypeNode * type);
};

/*! \brief Таблица методов класса. */
class MethodTable
{
public:
    std::map<std::string, std::map<std::string, class MethodTableElement *>> methods;
};

class LocalVariableElement
{
    public:
        std::string name; // Имя локальной переменной.
        int id; // Идентификатор локальной переменной.
        class Type * typ; // Тип локальной переменной.
        int isConst; // Флаг, показывающий, является ли переменная изменяемой.
        int isInit; // Флаг, показывающий, инициализрована переменная.

        LocalVariableElement(std::string nam, int ident, class Type * t, int isCnst, int isInitial = 0);

};

/*! \brief Таблица локальных переменных. */
class LocalVariableTable
{
    public:
        
        /// Текущее максимальное значение идентификатора переменной.
        int maxId = 0;

        /// Контейнер элементов.
        std::map<std::string, class LocalVariableElement*> items;

        int findOrAddLocalVar(std::string name, class Type * typ, int isCnst, int isInit);
};

/*! \brief Элемент таблицы параметров класса. */
class ClassParamElement
{
    public:
    std::string name;
    class Type * typ = NULL;
    int isProperty;

    ClassParamElement(std::string n, class Type * t, int isProp);
};

/*! \brief Таблица параметров класса. */
class ClassParamTable
{
    public:
    /// Контейнер элементов.
    std::map<std::string, class ClassParamElement *> items;
};

/*! \brief Элемент таблицы функций. */
class FunctionTableElement
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

        /// Ссылка на таблицу локальных переменных.
        class LocalVariableTable * varTable = NULL;

        FunctionTableElement(int nameCnst, int descCnst, std::string nam, std::string dsc, struct StatementListNode * strt, class Type * ret, std::vector<class FuncParam> pars);
};

/*! \brief Таблица функций. */
class FunctionTable
{
    public:
    /// Контейнер элементов.
    static std::map<std::string, std::map<std::string, class FunctionTableElement *>> items;
};
