#include "stdlib.hpp"

void initStdClasses()
{
    Type * retVal = NULL;
    /* ----- Инициализация класса Int ------ */
    ClassTable::items["Int"] = new ClassTableElement();
    ClassTable::items["Int"]->clsName = "JavaRTL/Int";
    ClassTable::items["Int"]->isOpen = 0;

        /* ---------- Добавление конструктора ---------- */
        ClassTable::items["Int"]->methods->methods["<init>"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = ClassTable::items["Int"]->clsName;
        retVal->typ = TypeType::_CLS;
        ClassTable::items["Int"]->methods->methods["<init>"]["(I)"] = new MethodTableElement(0,0,"<init>","(I)V", NULL, retVal, std::vector<FuncParam>());

        /* ---------- Добавление метода сложения ---------- */
        ClassTable::items["Int"]->methods->methods["plus"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = ClassTable::items["Int"]->clsName;
        retVal->typ = TypeType::_CLS;
        ClassTable::items["Int"]->methods->methods["plus"]["(LJavaRTL/Int;)"] = new MethodTableElement(0,0,"plus","(LJavaRTL/Int;)LJavaRTL/Int;", NULL, retVal, std::vector<FuncParam>());

        /* ---------- Добавление метода вычитания ---------- */
        ClassTable::items["Int"]->methods->methods["minus"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = ClassTable::items["Int"]->clsName;
        retVal->typ = TypeType::_CLS;
        ClassTable::items["Int"]->methods->methods["minus"]["(LJavaRTL/Int;)"] = new MethodTableElement(0,0,"minus","(LJavaRTL/Int;)LJavaRTL/Int;", NULL, retVal, std::vector<FuncParam>());

                /* ---------- Добавление метода умножения ---------- */
        ClassTable::items["Int"]->methods->methods["times"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = ClassTable::items["Int"]->clsName;
        retVal->typ = TypeType::_CLS;
        ClassTable::items["Int"]->methods->methods["times"]["(LJavaRTL/Int;)"] = new MethodTableElement(0,0,"times","(LJavaRTL/Int;)LJavaRTL/Int;", NULL, retVal, std::vector<FuncParam>());
        
                /* ---------- Добавление метода деления ---------- */
        ClassTable::items["Int"]->methods->methods["div"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = ClassTable::items["Int"]->clsName;
        retVal->typ = TypeType::_CLS;
        ClassTable::items["Int"]->methods->methods["div"]["(LJavaRTL/Int;)"] = new MethodTableElement(0,0,"div","(LJavaRTL/Int;)LJavaRTL/Int;", NULL, retVal, std::vector<FuncParam>());



    /* ----- Инициализация класса Char ------ */
    ClassTable::items["Char"] = new ClassTableElement();
    ClassTable::items["Char"]->clsName = "JavaRTL/Char";
    ClassTable::items["Char"]->isOpen = 0;

    /* ----- Инициализация класса String ------ */
    ClassTable::items["String"] = new ClassTableElement();
    ClassTable::items["String"]->clsName = "JavaRTL/String";
    ClassTable::items["String"]->isOpen = 0;

    /* ----- Инициализация класса Boolean ------ */
    ClassTable::items["Boolean"] = new ClassTableElement();
    ClassTable::items["Boolean"]->clsName = "JavaRTL/Boolean";
    ClassTable::items["Boolean"]->isOpen = 0;

    /* ----- Инициализация класса Any ------ */
    ClassTable::items["Any"] = new ClassTableElement();
    ClassTable::items["Any"]->clsName = "JavaRTL/Any";
    ClassTable::items["Any"]->isOpen = 1;

    /* ----- Инициализация класса Unit ------ */
    ClassTable::items["Unit"] = new ClassTableElement();
    ClassTable::items["Unit"]->clsName = "JavaRTL/Unit";
    ClassTable::items["Unit"]->isOpen = 0;

    /* ----- Инициализация функций ввода-вывода ------ */
}
