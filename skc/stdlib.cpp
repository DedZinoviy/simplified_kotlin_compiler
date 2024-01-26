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

        ClassTable::items["JavaRTL/Int"]->methods->methods["greater"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = "JavaRTL/Boolean";
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Int"]->methods->methods["greater"]["(LJavaRTL/Int;)"] = new MethodTableElement(0,0,"greater","(LJavaRTL/Int;)LJavaRTL/Boolean;", NULL, retVal, std::vector<FuncParam>());

        ClassTable::items["JavaRTL/Int"]->methods->methods["less"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = "JavaRTL/Boolean";
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Int"]->methods->methods["less"]["(LJavaRTL/Int;)"] = new MethodTableElement(0,0,"less","(LJavaRTL/Int;)LJavaRTL/Boolean;", NULL, retVal, std::vector<FuncParam>());

        ClassTable::items["JavaRTL/Int"]->methods->methods["greaterEquals"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = "JavaRTL/Boolean";
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Int"]->methods->methods["greaterEquals"]["(LJavaRTL/Int;)"] = new MethodTableElement(0,0,"greaterEquals","(LJavaRTL/Int;)LJavaRTL/Boolean;", NULL, retVal, std::vector<FuncParam>());

        ClassTable::items["JavaRTL/Int"]->methods->methods["lessEquals"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = "JavaRTL/Boolean";
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Int"]->methods->methods["lessEquals"]["(LJavaRTL/Int;)"] = new MethodTableElement(0,0,"lessEquals","(LJavaRTL/Int;)LJavaRTL/Boolean;", NULL, retVal, std::vector<FuncParam>());
        
        ClassTable::items["JavaRTL/Int"]->methods->methods["equals"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = "JavaRTL/Boolean";
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Int"]->methods->methods["equals"]["(LJavaRTL/Int;)"] = new MethodTableElement(0,0,"equals","(LJavaRTL/Int;)LJavaRTL/Boolean;", NULL, retVal, std::vector<FuncParam>());

        ClassTable::items["JavaRTL/Int"]->methods->methods["notEquals"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = "JavaRTL/Boolean";
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Int"]->methods->methods["notEquals"]["(LJavaRTL/Int;)"] = new MethodTableElement(0,0,"notEquals","(LJavaRTL/Int;)LJavaRTL/Boolean;", NULL, retVal, std::vector<FuncParam>());


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
        
        /* ---------- Добавление конструктора ---------- */
        ClassTable::items["JavaRTL/Boolean"]->methods->methods["<init>"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = ClassTable::items["JavaRTL/Boolean"]->clsName;
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Boolean"]->methods->methods["<init>"]["(I)"] = new MethodTableElement(0,0,"<init>","(I)V", NULL, retVal, std::vector<FuncParam>());

        ClassTable::items["JavaRTL/Boolean"]->methods->methods["equals"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = "JavaRTL/Boolean";
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Boolean"]->methods->methods["equals"]["(LJavaRTL/Boolean;)"] = new MethodTableElement(0,0,"equals","(LJavaRTL/Boolean;)LJavaRTL/Boolean;", NULL, retVal, std::vector<FuncParam>());

        ClassTable::items["JavaRTL/Boolean"]->methods->methods["notEquals"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = "JavaRTL/Boolean";
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Boolean"]->methods->methods["notEquals"]["(LJavaRTL/Boolean;)"] = new MethodTableElement(0,0,"notEquals","(LJavaRTL/Boolean;)LJavaRTL/Boolean;", NULL, retVal, std::vector<FuncParam>());

        ClassTable::items["JavaRTL/Boolean"]->methods->methods["not"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = "JavaRTL/Boolean";
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Boolean"]->methods->methods["not"]["()"] = new MethodTableElement(0,0,"not","()LJavaRTL/Boolean;", NULL, retVal, std::vector<FuncParam>());

        ClassTable::items["JavaRTL/Boolean"]->methods->methods["and"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = "JavaRTL/Boolean";
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Boolean"]->methods->methods["and"]["(LJavaRTL/Boolean;)"] = new MethodTableElement(0,0,"and","(LJavaRTL/Boolean;)LJavaRTL/Boolean;", NULL, retVal, std::vector<FuncParam>());

        ClassTable::items["JavaRTL/Boolean"]->methods->methods["or"] = std::map<std::string, class MethodTableElement*>();
        retVal = new Type();
        retVal->className = "JavaRTL/Boolean";
        retVal->typ = TypeType::_CLS;
        ClassTable::items["JavaRTL/Boolean"]->methods->methods["or"]["(LJavaRTL/Boolean;)"] = new MethodTableElement(0,0,"or","(LJavaRTL/Boolean;)LJavaRTL/Boolean;", NULL, retVal, std::vector<FuncParam>());

    /* ----- Инициализация класса Any ------ */
    ClassTable::items["JavaRTL/Any"] = new ClassTableElement();
    ClassTable::items["JavaRTL/Any"]->clsName = "JavaRTL/Any";
    ClassTable::items["JavaRTL/Any"]->isOpen = 1;

    /* ----- Инициализация класса Unit ------ */
    ClassTable::items["JavaRTL/Unit"] = new ClassTableElement();
    ClassTable::items["JavaRTL/Unit"]->clsName = "JavaRTL/Unit";
    ClassTable::items["JavaRTL/Unit"]->isOpen = 0;

    /* ----- Инициализация функций ввода-вывода ------ */
    ClassTable::items["JavaRTL/InputOutput"] = new ClassTableElement();
    ClassTable::items["JavaRTL/InputOutput"]->clsName = "JavaRTL/InputOutput";
    ClassTable::items["JavaRTL/InputOutput"]->isOpen = 0;
        ClassTable::items["JavaRTL/InputOutput"]->methods->methods["println"] = std::map<std::string, class MethodTableElement*>();
        FunctionTable::items["print"] = std::map<std::string, class FunctionTableElement*>();
            retVal = new Type();
            retVal->className = ClassTable::items["JavaRTL/Unit"]->clsName;
            retVal->typ = TypeType::_CLS;
                ClassTable::items["JavaRTL/InputOutput"]->methods->methods["print"]["(LJavaRTL/Int;)"] = new MethodTableElement(0,0,"print","(LJavaRTL/Int;)LJavaRTL/Unit;", NULL, retVal, std::vector<FuncParam>());
                FunctionTable::items["print"]["(LJavaRTL/Int;)"] = new FunctionTableElement(0,0,"print","(LJavaRTL/Int;)LJavaRTL/Unit;", NULL, retVal, std::vector<FuncParam>());

                ClassTable::items["JavaRTL/InputOutput"]->methods->methods["print"]["(LJavaRTL/String;)"] = new MethodTableElement(0,0,"print","(LJavaRTL/String;)JavaRTL/Unit;", NULL, retVal, std::vector<FuncParam>());
                FunctionTable::items["print"]["(LJavaRTL/String;)"] = new FunctionTableElement(0,0,"print","(LJavaRTL/String;)JavaRTL/Unit;", NULL, retVal, std::vector<FuncParam>());

                ClassTable::items["JavaRTL/InputOutput"]->methods->methods["print"]["(LJavaRTL/Char;)"] = new MethodTableElement(0,0,"print","(LJavaRTL/Char;)JavaRTL/Unit;", NULL, retVal, std::vector<FuncParam>());
                FunctionTable::items["print"]["(LJavaRTL/Char;)"] = new FunctionTableElement(0,0,"print","(LJavaRTL/Char;)JavaRTL/Unit;", NULL, retVal, std::vector<FuncParam>());
                
                ClassTable::items["JavaRTL/InputOutput"]->methods->methods["print"]["(LJavaRTL/Boolean;)"] = new MethodTableElement(0,0,"print","(LJavaRTL/Boolean;)JavaRTL/Unit;", NULL, retVal, std::vector<FuncParam>());
                FunctionTable::items["print"]["(LJavaRTL/Boolean;)"] = new FunctionTableElement(0,0,"print","(LJavaRTL/Boolean;)JavaRTL/Unit;", NULL, retVal, std::vector<FuncParam>());
       
        ClassTable::items["JavaRTL/InputOutput"]->methods->methods["println"] = std::map<std::string, class MethodTableElement*>();
        FunctionTable::items["println"] = std::map<std::string, class FunctionTableElement*>();
            retVal = new Type();
            retVal->className = ClassTable::items["JavaRTL/Unit"]->clsName;
            retVal->typ = TypeType::_CLS;
                ClassTable::items["JavaRTL/InputOutput"]->methods->methods["println"]["(LJavaRTL/Int;)"] = new MethodTableElement(0,0,"println","(LJavaRTL/Int;)LJavaRTL/Unit;", NULL, retVal, std::vector<FuncParam>());
                FunctionTable::items["println"]["(LJavaRTL/Int;)"] = new FunctionTableElement(0,0,"println","(LJavaRTL/Int;)LJavaRTL/Unit;", NULL, retVal, std::vector<FuncParam>());

                ClassTable::items["JavaRTL/InputOutput"]->methods->methods["println"]["(LJavaRTL/String;)"] = new MethodTableElement(0,0,"println","(LJavaRTL/String;)JavaRTL/Unit;", NULL, retVal, std::vector<FuncParam>());
                FunctionTable::items["println"]["(LJavaRTL/String;)"] = new FunctionTableElement(0,0,"println","(LJavaRTL/String;)JavaRTL/Unit;", NULL, retVal, std::vector<FuncParam>());

                ClassTable::items["JavaRTL/InputOutput"]->methods->methods["println"]["(LJavaRTL/Char;)"] = new MethodTableElement(0,0,"println","(LJavaRTL/Char;)JavaRTL/Unit;", NULL, retVal, std::vector<FuncParam>());
                FunctionTable::items["println"]["(LJavaRTL/Char;)"] = new FunctionTableElement(0,0,"println","(LJavaRTL/Char;)JavaRTL/Unit;", NULL, retVal, std::vector<FuncParam>());
                
                ClassTable::items["JavaRTL/InputOutput"]->methods->methods["println"]["(LJavaRTL/Boolean;)"] = new MethodTableElement(0,0,"println","(LJavaRTL/Boolean;)JavaRTL/Unit;", NULL, retVal, std::vector<FuncParam>());
                FunctionTable::items["println"]["(LJavaRTL/Boolean;)"] = new FunctionTableElement(0,0,"println","(LJavaRTL/Boolean;)JavaRTL/Unit;", NULL, retVal, std::vector<FuncParam>());

        ClassTable::items["JavaRTL/InputOutput"]->methods->methods["readLine"] = std::map<std::string, class MethodTableElement*>();
        FunctionTable::items["readLine"] = std::map<std::string, class FunctionTableElement*>();
            retVal = new Type();
            retVal->className = ClassTable::items["JavaRTL/String"]->clsName;
            retVal->typ = TypeType::_CLS;
                ClassTable::items["JavaRTL/InputOutput"]->methods->methods["readLine"]["()"] = new MethodTableElement(0,0,"readLine","()LJavaRTL/String;", NULL, retVal, std::vector<FuncParam>());
                FunctionTable::items["readLine"]["()"] = new FunctionTableElement(0,0,"readLine","()LJavaRTL/String;", NULL, retVal, std::vector<FuncParam>());

}
