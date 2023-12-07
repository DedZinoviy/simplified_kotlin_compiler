#pragma once

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
};

/*! \brief Элемент таблицы полей класса. */
struct FieldTableElement
{
    /// Ссылка на константу с именем поля.
    int name;

    /// Ссылка на константу с декриптором поля.
    int descriptor;
};
