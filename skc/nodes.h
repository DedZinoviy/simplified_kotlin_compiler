#pragma once
#include "stringBuffer.h"
#include "modifier_head.h"

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------ Expression -------------------------------------*/

/*! \brief Перечисление типов Expression. */
enum ExpressionType
{
    /// Идентификатор.
    _IDENTIFIER,

    /// Булевый (логический) литерал.
    _BOOLEAN_LIT,

    /// Целочисленный литерал.
    _INT_LIT,

    /// Литерал вещественного числа с плавающей точкой двойной точности.
    _DOUBLE_LIT,

    /// Символьный литерал.
    _CHAR_LIT,

    /// Строковый литерал.
    _STRING_LIT,

    /// Сложение.
    _PLUS,

    /// Вычитание.
    _MINUS,

    /// Деление.
    _DIV,

    /// Умножение.
    _MUL,

    /// Получение остатка от деления.
    _MOD,

    /// Сравнение "меньше".
    _LESS,

    /// Сравнение "больше".
    _GREAT,

    /// Сравнение "меньше или равно".
    _LESS_EQUAL,

    /// Сравнение "больше или равно".
    _GREAT_EQUAL,

    /// Сравнение "равно".
    _EQUAL,

    /// Сравнение "не равно".
    _NOT_EQUAL,

    /// Вызов функции.
    _FUNC_CALL,

    /// Выражение в круглых скобках.
    _BRACKETS,

    /// Доступ к полю.
    _FIELD_ACCESS,

    /// Доступ к методу.
    _METHOD_ACCESS,

    /// Присваивание.
    _ASSIGNMENT,

    /// Сложение с присваиванием.
    _PLUS_ASSIGNMENT,

    /// Вычитание с присваиванием.
    _MINUS_ASSIGNMENT,

    /// Умножение с присваиванием.
    _MUL_ASSIGNMENT,

    /// Деление с присваиванием.
    _DIV_ASSIGNMENT,

    /// Взятие остатка с присваиванием.
    _MOD_ASSIGNMENT,

    /// Обращение к текущему объекту.
    _THIS,

    /// Обращение к родителю.
    _SUPER,

    /// Создание диапазона.
    _RANGE,

    /// Префиксный инкремент.
    _PREF_INCREMENT,

    /// Префиксный декремент.
    _PREF_DECREMENT,

    /// Постфиксный инкремент.
    _POST_INCREMENT,

    /// Постфиксный декремент.
    _POST_DECREMENT,

    /// Унарный плюс.
    _UNARY_PLUS,

    /// Унарный минус.
    _UNARY_MINUS,

    /// Отрицание (Инверсия).
    _NOT,

    /// Дизъюнкция ("ИЛИ").
    _DISJUNCTION,

    /// Конъюнкция ("И").
    _CONJUNCTION,

    /// Создание массива.
    _ARRAY_CREATION,

    /// Доступ к члену массива.
    _ARRAY_ACCESS
};

/// Перечисление, указывающее на основании какого литерала произошло создание объекта.
enum BaseLiteral
{
    _FROM_NONE,
    _FROM_INT,
    _FROM_DOUBLE,
    _FROM_BOOLEAN,
    _FROM_CHAR,
    _FROM_STRING
};

/*! \brief Структура узла Expression. */
struct ExpressionNode
{
    /// Идентификатор узла.
    int id;

    /// Целочисленное значение (только для целочисленных констант).
    int intValue;

    /// Логичское (булевое) значение (только для логических констант).
    int boolValue;

    /// Значение числа с плавающей точкой двойной точности (только для контант типа DOUBLE).
    double doubleValue;

    /// Значение строкового литерала - строковый буффер (только для строковых литералов).
    struct stringBuffer * stringValue;

    /// Значение символьного литерала (только для символьных литералов).
    char charValue;

    /// Строка идентификатора (только для функций, методов и переменных).
    char* identifierString;

    /// Тип обозреваемого Expression - вариант перечисления.
    enum ExpressionType type;

    /// Указатель на левый операнд бинарного Expression (для бинарных выражений).
    struct ExpressionNode * left;

    /// Указатель на правый операнд бинарного Expression (для бинарных выражений).
    struct ExpressionNode * right;

    /// Указатель на следующий Expression в списке ExpressionList (использовать при работе со списком Expression).
    struct ExpressionNode * next;

    /// Указатель на список Expression (параметры при вызове функций и методов).
    struct ExpressionListNode * params;

    /// Флаг, указывающий, что данный узел получился в результате преобразования литерала.
    enum BaseLiteral fromLit;

    /// Указатель на тип выражения для аттрибутирования.
    struct TypeNode * typ;
};



/*------------------------------------ ExpressionList -------------------------------------*/

/*! \brief Структура узла списка Expression. */
struct ExpressionListNode
{
    /// Идентификатор узла.
    int id;

    /// Указатель на первый элемент списка Expression.
    struct ExpressionNode * first;

    /// Указатель на последний элемент списка Expression.
    struct ExpressionNode * last;
};



/*------------------------------------ Statement -------------------------------------*/

/*! \brief Перечисление типов Statement. */
enum StatementType
{
    /// Выражениие.
    _EXPRESSION,

    /// Управляющий оператор цикла WHILE.
    _WHILE,

    /// Управляющий оператор цикла DO..WHILE.
    _DOWHILE,

    /// Управляющий оператор цикла FOR.
    _FOR,

    /// Пустой Statement.
    _EMPTY,

    /// Объявление переменной VAR.
    _VAR,

    /// Объявление переменной VAL.
    _VAL,

    /// Множественное объявление переменной VAL.
    _MULTI_VAL,

    /// Множественное объявление переменной VAR.
    _MULTI_VAR,

    /// Возврат из функции.
    _RETURN
};

struct TypeNode;
struct StatementListNode;
struct VarDeclarationListNode;

/*! \brief Структура узла Statement. */
struct StatementNode
{
    /// Идентификатор узла.
    int id;

    /// Тип обозреваемого Statement - вариант перечисления.
    enum StatementType type;

    /// Идентификатор переменной для выражения объявления переменной.
    char * varValId;

    /// Тип переменной для выражения объявления переменной с явным указанием типа.
    struct TypeNode * varValType;

    /// Ссылка на Expression, которое используется при созании Statement.
    struct ExpressionNode * expression;

    /// Ссылка на выражение условия (для циклов WHILE и DO..WHILE). 
    struct ExpressionNode * condition;

    /// Ссылка на простое тело цикла.
    struct StatementNode * singleBody;

    /// Ссылка на составное тело цикла.
    struct StatementListNode * complexBody;

    /// Указатель на следующий Statement в списке StatementList (использовать при работе со списком Statement).
    struct StatementNode * next;

    /// Указатель на список переменных.
    struct VarDeclarationListNode  * varDeclList;

    /// Временное хранилище модификаторов.
    struct ModifierHead * _tempHead;
};



/*------------------------------------ StatementList -------------------------------------*/

/*! \brief Структура узла списка Statement. */
struct StatementListNode
{
    /// Идентификатор узла.
    int id;

    /// Указатель на первый элемент списка Statement.
    struct StatementNode * first;

    /// Указатель на последний элемент списка Statement.
    struct StatementNode * last;
};



/*------------------------------------ VarDeclaration -------------------------------------*/

/*! \brief Структура узла, описывающего объявление переменной. */
struct VarDeclarationNode
{
    /// Идентификатор узла.
    int id;

    /// Идентификатор переменной.
    char * identifier;

    /// Тип переменной.
    struct TypeNode * type;

    /// Указатель на следующий узел объявления переменной в списке.
    struct VarDeclarationNode * next;
};



/*------------------------------------ VarDeclarationList -------------------------------------*/

/*! \brief Структура, описывающая список объявлений переменных.*/
struct VarDeclarationListNode
{
    /// Идентификатор узла.
    int id;

    /// Указатель на первый узел объявления переменной.
    struct VarDeclarationNode * first;

    /// Указатель на последний узел объявления переменной.
    struct VarDeclarationNode * last;
};



/*------------------------------------ Modifier -------------------------------------*/

/// \brief Перечисление типов модификатора.
enum ModifierType
{
    _PRIVATE,
    _PUBLIC,
    _INTERNAL,
    _PROTECTED,
    _OPEN,
    _OVERRIDE,
    _FINAL
};

/*! \brief Узел единичного модификатора. */
struct ModifierNode
{
    /// Идентификатор узла.
    int id;

    /// Тип узла.
    enum ModifierType type;

    /// Указатель на следующий узел модификатора в списке.
    struct ModifierNode * next;
};



/*------------------------------------ ModifierList -------------------------------------*/

/*! \brief Узел списка модификаторов.*/
struct ModifierListNode
{
    /// Идентификатор узла.
    int id;

    /// Указатель на первый элемент-узел модификатора. 
    struct ModifierNode * first;

    /// Указатель на последний элемент-узел модификатора.
    struct ModifierNode * last;
};



/*------------------------------------ Function -------------------------------------*/

/*! \brief Структура, описывающая функции и методы. */
struct FunctionNode
{
    /// Идентификатор узла.
    int id;

    /// Идентфикатор (название) функции.
    char * identifier;

    /// Список параметорв функции.
    struct VarDeclarationListNode * params;
    
    /// Возвращаемой значение функции.
    struct TypeNode * returnValue;

    /// Тело функции.
    struct StatementListNode * body;

    /// Временное хранилище модификаторов.
    struct ModifierHead * _tempHead;
};



/*------------------------------------ Class Member -------------------------------------*/

/*! \brief Перечисление типов члена класса. */
enum ClassMemberType
{
    /// Поле класса.
    _FIELD,

    /// Метод класса.
    _METHOD,

    /// Пустой член класса.
    _C_EMPTY
};

/*! \brief Структура, описывающая узлы членов класса. */
struct ClassMemberNode
{
    /// Идентификатор узла.
    int id; 
    
    struct ModifierListNode * mods;

    /// Тип члена класса
    enum ClassMemberType type;

    /// Statement члена класса - поля.
    struct StatementNode * stmt;

    /// Указатель на узел метода (функции).
    struct FunctionNode * method;

    /// Указатель на следующий член класса.
    struct ClassMemberNode * next;
};



/*------------------------------------ Class Member -------------------------------------*/

/*! \brief Структура, описывающая узлы списков членов класса. */
struct ClassMemberListNode
{
    /// Идентификатор узла.
    int id;

    /// Указатель на первый член класса.
    struct ClassMemberNode * first;

    /// Указатель на последний член класса.
    struct ClassMemberNode * last;
};



/*------------------------------------ Class Param -------------------------------------*/

/*! \brief Структура, описывающая узлы параметров класса. */
struct ClassParamNode
{
    /// Идентификатор узла.
    int id;

    /// Указатель на узел списка модификаторов параметра. 
    struct ModifierListNode * mods;

    /// Указатель на узел Объявления переменной.
    struct VarDeclarationNode * varDecl;

    /// Указатель на выражение переменной.
    struct StatementNode * valVar;

    /// Указатель на следующий узел параметра класса.
    struct ClassParamNode * next;

    struct ExpressionNode * expr;
};



/*------------------------------------ Class Param List -------------------------------------*/

/*! \brief Структура, описывающая узлы списков параметров класса. */
struct ClassParamListNode
{
    /// Идентификатор узла.
    int id;

    /// Указатель на первый элемент списка параметров класса.
    struct ClassParamNode * first;

    /// Указатель на последний элемент списка параметров класса.
    struct ClassParamNode * last;
};



/*------------------------------------ Primary Constructor  -------------------------------------*/

/*! \brief Структура, описывающая узлы первичных конструкторов класса. */
struct PrimaryConstructorNode
{
    /// Идентификатор узла.
    int id;

    /// Указатель на узел списка модификаторов.
    struct ModifierListNode * mods;

    /// Указатель на список параметорв класса.
    struct ClassParamListNode * params;
};



/*------------------------------------ Class -------------------------------------*/

/*! \brief Структура, описывающая классы. */
struct ClassNode
{
    /// Идентификатор узла.
    int id;

    /// Идентификатор класса.
    char * identifier;

    /// Указатель на узел первичного конструктора.
    struct PrimaryConstructorNode * constr;

    /// Указатель на узел списка членов класса.
    struct ClassMemberListNode * members;

    /// Указатель на выражение - родительский класс.
    struct ExpressionNode * base;

    /// Временное хранилище модификаторов.
    struct ModifierHead * _tempHead;
};



/*------------------------------------ KotlinFileElement -------------------------------------*/

/*! \brief Перечисление типа элемента файла Kotlin. */
enum KotlinFileElementType
{
    /// Класс.
    _CLASS,

    /// Свободная функция.
    _FUNCTION,

    /// Пустой элемент.
    _EMPT
};

/*! \brief Структура, описывающая элемент файла Kotlin. */
struct KotlinFileElementNode
{
    /// Идентификатор узла.
    int id;

    /// Указатель на список модификаторов.
    struct ModifierListNode * modifiers;

    /// Тип элемента Kotlin.
    enum KotlinFileElementType type;

    /// Указатель на узел функции, если элемент - функция.
    struct FunctionNode * func;

    /// Указатель на узел класса, если элемент - класс.
    struct ClassNode * clas;

    /// Указатель на следующий элемент Kotlin в списке элементов.
    struct KotlinFileElementNode * next;
};



/*------------------------------------ KotlinFileElementList -------------------------------------*/

/*! \brief Структура, описывающая список элементов файла Kotlin.*/
struct KotlinFileElementListNode
{
    /// Идентификатор узла.
    int id;

    /// Указатель на первый элемент списка.
    struct KotlinFileElementNode * first;

    /// Указатель на последний элемент списка.
    struct KotlinFileElementNode * last;
};



/*------------------------------------ KotlinFile-------------------------------------*/

/*! \brief Структура, описывающая корневой узел программы - файл Kotlin. */
struct KotlinFileNode
{
    /// Идентификатор узла.
    int id;

    /// Указатель на список элементов Kotlin, из которых состоит файл Kotlin.
    struct KotlinFileElementListNode * elemList;
};



/*------------------------------------ Type -------------------------------------*/

/// Тип узла типа.
enum TypeType
{
    /// Шаблонизированный массив.
    _ARRAY,

    /// Пользовательский класс.
    _CLS
};

/*! \brief Структура, описывающая узел типа. */
struct TypeNode
{
    /// Идентификатор узла.
    int id;

    /// Тип узла типа - пользовательский класс или класс массива.
    enum TypeType type;

    /// Идентификатор пользовательского типа.
    char * ident;

    /// Указатель на структуру сложного типа - шаблонизированного массива.
    struct TypeNode * complexType;
};

#ifdef __cplusplus
};
#endif
