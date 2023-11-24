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
