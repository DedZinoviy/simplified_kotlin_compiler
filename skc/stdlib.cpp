#include "stdlib.hpp"

void initStdClasses()
{
    /* ----- Инициализация класса Int ------ */
    ClassTable::items["Int"] = new ClassTableElement();
    ClassTable::items["Int"]->clsName = "JavaRTL/Int";
    ClassTable::items["Int"]->isOpen = 0;

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
