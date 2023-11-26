#include "stringBuffer.h"

/*------------------------------------ Expression -------------------------------------*/

/*! \brief Перечисление типов Expression. */
enum ExpressionType
{
    IDENTIFIER,
    BOOLEAN_LIT,
    INT_LIT,
    DOUBLE_LIT,
    CHAR_LIT,
    STRING_LIT,
    PLUS,
    MINUS,
    DIV,
    MUL,
    MOD,
    LESS,
    GREAT,
    LESS_EQUAL,
    GREAT_EQUAL,
    EQUAL,
    NOT_EQUAL,
    FUNC_CALL,
    BRACKETS,
    FIELD_ACCESS,
    METHOD_ACCESS,
    ASSIGNMENT,
    PLUS_ASSIGNMENT,
    MINUS_ASSIGNMENT,
    MUL_ASSIGNMENT,
    DIV_ASSIGNMENT,
    MOD_ASSIGNMENT,
    THIS,
    SUPER,
    RANGE,
    PREF_INCREMENT,
    PREF_DECREMENT,
    POST_INCREMENT,
    POST_DECREMENT,
    UNARY_PLUS,
    UNARY_MINUS,
    NOT,
    DISJUNCTION,
    CONJUNCTION
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
    EXPRESSION,
    WHILE,
    DOWHILE,
    FOR,
    EMPTY,
    VAR,
    VAL
};

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
    char * varValType;

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
    char * type;

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
    PRIVATE,
    PUBLIC,
    INTERNAL,
    PROTECTED,
    OPEN,
    OVERRIDE
};

/*! \brief Узел единичного модификатора. */
struct ModifierNode
{
    /// Идентификатор узла.
    int id;

    /// Тип узла.
    enum ModifierType type;
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
    struct VarDeclarationNode * params;
    
    /// Возвращаемой значение функции.
    char * returnValue;

    /// Тело функции.
    struct StatementListNode * body;
};



/*------------------------------------ Class -------------------------------------*/

/*! \brief Структура, описывающая классы. */
struct ClassNode
{
    /// Идентификатор узла.
    int id; 
};


/*------------------------------------ KotlinFileElement -------------------------------------*/

/*! \brief Перечисление типа элемента файла Kotlin. */
enum KotlinFileElementType
{
    CLASS,
    FUNCTION
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
    struct ClassNode * class;

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
