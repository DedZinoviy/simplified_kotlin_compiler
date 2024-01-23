#include "stdlib.hpp"

void initStdClasses()
{
    Type * retVal = NULL;
    /* ----- Инициализация класса Int ------ */
    ClassTable::items["JavaRTL/Int"] = new ClassTableElement();
    ClassTable::items["JavaRTL/Int"]->clsName = "JavaRTL/Int";
    ClassTable::items["JavaRTL/Int"]->isOpen = 0;

        /* ---------- Добавление конструктора ---------- */
        ClassTable::items["JavaRTL/Int"]->methods->methods["<init>"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = ClassTable::items["JavaRTL/Int"]->clsName;
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Int"]->methods->methods["<init>"]["(I)"] = new MethodTableElement(0,0,"<init>","(I)V", NULL, retVal, std::vector<FuncParam>());

        /* ---------- Добавление метода сложения ---------- */
        ClassTable::items["JavaRTL/Int"]->methods->methods["plus"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = ClassTable::items["JavaRTL/Int"]->clsName;
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Int"]->methods->methods["plus"]["(LJavaRTL/Int;)"] = new MethodTableElement(0,0,"plus","(LJavaRTL/Int;)LJavaRTL/Int;", NULL, retVal, std::vector<FuncParam>());

        /* ---------- Добавление метода вычитания ---------- */
        ClassTable::items["JavaRTL/Int"]->methods->methods["minus"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = ClassTable::items["JavaRTL/Int"]->clsName;
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Int"]->methods->methods["minus"]["(LJavaRTL/Int;)"] = new MethodTableElement(0,0,"minus","(LJavaRTL/Int;)LJavaRTL/Int;", NULL, retVal, std::vector<FuncParam>());

                /* ---------- Добавление метода умножения ---------- */
        ClassTable::items["JavaRTL/Int"]->methods->methods["times"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = ClassTable::items["JavaRTL/Int"]->clsName;
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Int"]->methods->methods["times"]["(LJavaRTL/Int;)"] = new MethodTableElement(0,0,"times","(LJavaRTL/Int;)LJavaRTL/Int;", NULL, retVal, std::vector<FuncParam>());
        
                /* ---------- Добавление метода деления ---------- */
        ClassTable::items["JavaRTL/Int"]->methods->methods["div"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = ClassTable::items["JavaRTL/Int"]->clsName;
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Int"]->methods->methods["div"]["(LJavaRTL/Int;)"] = new MethodTableElement(0,0,"div","(LJavaRTL/Int;)LJavaRTL/Int;", NULL, retVal, std::vector<FuncParam>());



    /* ----- Инициализация класса Char ------ */
    ClassTable::items["JavaRTL/Char"] = new ClassTableElement();
    ClassTable::items["JavaRTL/Char"]->clsName = "JavaRTL/Char";
    ClassTable::items["JavaRTL/Char"]->isOpen = 0;

    /* ----- Инициализация класса String ------ */
    ClassTable::items["JavaRTL/String"] = new ClassTableElement();
    ClassTable::items["JavaRTL/String"]->clsName = "JavaRTL/String";
    ClassTable::items["JavaRTL/String"]->isOpen = 0;

    /* ----- Инициализация класса Boolean ------ */
    ClassTable::items["JavaRTL/Boolean"] = new ClassTableElement();
    ClassTable::items["JavaRTL/Boolean"]->clsName = "JavaRTL/Boolean";
    ClassTable::items["JavaRTL/Boolean"]->isOpen = 0;

    /* ----- Инициализация класса Any ------ */
    ClassTable::items["JavaRTL/Any"] = new ClassTableElement();
    ClassTable::items["JavaRTL/Any"]->clsName = "JavaRTL/Any";
    ClassTable::items["JavaRTL/Any"]->isOpen = 1;

    /* ----- Инициализация класса Unit ------ */
    ClassTable::items["JavaRTL/Unit"] = new ClassTableElement();
    ClassTable::items["JavaRTL/Unit"]->clsName = "JavaRTL/Unit";
    ClassTable::items["JavaRTL/Unit"]->isOpen = 0;

    /* ----- Инициализация функций ввода-вывода ------ */
}
