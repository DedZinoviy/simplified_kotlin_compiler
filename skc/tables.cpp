#include "tables.hpp"
#include <iostream>

/* --------------------------------- Построение таблицы классов. ------------------------------------ */

/*! Проверить, является ли класс открытым для наследования.
* \param[in] Узел класса.
* \return результат проверки: true = если открыт, false - если нет.
*/
static bool _isOpenClass(struct KotlinFileElementNode * cls);

/*! Заполнить таблицу модификаторов для класса.
* \param[in] Таблциа модификаторов класса.
* \param[in] узел модификатора.
*/
static void _fillModifierTableForClass(struct ModifierHead * head, struct ModifierNode * node);

/*! [PRIVATE] Добавить класс в таблицу классов при его наличии.
* \param[in] fileElem рассматриваемый элемент файла Kotlin.
* \param[in, out] classTable обновляемая таблица.
*/
static struct SemanticError * _addClassToClassTable(struct KotlinFileElementNode * fileElem, struct ClassTable * classTable)
{
    struct SemanticError * err = NULL;
    if (fileElem != NULL)
    {
        if (fileElem->type == _CLASS)
        {
            char * className = fileElem->clas->identifier;
            if (classTable->items->find(fileElem->clas->identifier) != classTable->items->end()){
                std::string msg = "There is already a class with the specified identifier: ";
                msg += fileElem->clas->identifier;
                return createSemanticError(4, msg.c_str());
            }
            struct ClassTableElement * elem = createEmptyClassTableElement();
            if (_isOpenClass(fileElem)) elem->isOpen = 1;
            classTable->items->insert(std::pair<std::string, struct ClassTableElement *>(fileElem->clas->identifier, elem));
        }
        if (fileElem->next != NULL)
        {
            return _addClassToClassTable(fileElem->next, classTable);
        }
    }
    return err;
}

static struct SemanticError * _setInheritanceForClass(struct KotlinFileElementNode * cls)
{
    return NULL;
}

struct SemanticError * setInheritance(struct KotlinFileNode * root)
{
    return NULL;
}

static void _fillModifierTableForClass(struct ModifierHead * head, struct ModifierNode * node)
{
    switch (node->type)
    {
        case _PUBLIC:
            head->isPublic = 1;
            break;
            
        case _PRIVATE:
            head->isPrivate = 1;
            break;

        case _INTERNAL:
            head->isInternal = 1;
            break;

        case _OPEN:
            head->isOpen = 1;
            break;
        
        case _FINAL:
            head->isFinal = 1;
            break;
    }
    if (node->next != NULL)
    {
        _fillModifierTableForClass(head, node->next);
    }
}

static bool _isOpenClass(struct KotlinFileElementNode * cls)
{
    struct ModifierHead * head = createEmptyModifierHead();
    if (cls->type == _CLASS)
    {
        if (cls->modifiers != NULL)
        {
            if (cls->modifiers->first != NULL)
            {
                _fillModifierTableForClass(head, cls->modifiers->first);
                if (head->isOpen == 1 && head->isFinal == 0)
                {
                    return true;
                } else return false;
            }
        }
    }
}

/*! Построить таблицу классов для заданного файла Котлин.
* \param[in] root Корневой узел файла Котлин.
* \param[in] fileName Имя файла Котлин.
* \param[in,out] emptyTable Собираемая таблица классов; в случае ошибки построения вернется NULL.
* \return Возможная ошибка построения.
*/  
struct SemanticError * buildClassTable(struct KotlinFileNode * root, const char * fileName, struct ClassTable * emptyTable)
{
    struct SemanticError * err = NULL; 
    struct ClassTable* classes = createEmptyClassTable();
    if (root->elemList->first != NULL)
    {
        err = _addClassToClassTable(root->elemList->first, classes);
        if (err != NULL)
        {
            emptyTable = NULL;
        } 
        else emptyTable = classes;
    }

    return err;
}



/* ----------------------------------- Class Table ----------------------------------- */


/*! Создать пустой элемент таблицы классов.
* \return пустой элемент таблицы классов.
*/
class ClassTableElement * createEmptyClassTableElement()
{
    class ClassTableElement * tableElem = (class ClassTableElement *)malloc(sizeof(class ClassTableElement));
    tableElem->fields = NULL;
    tableElem->methods = NULL;
    tableElem->name = -1;
    tableElem->isOpen = 0;
    tableElem->superClass = -1;
    tableElem->superName = -1;
    tableElem->constants = new ConstantTable();
    return tableElem;
}

/*! Создать пустую таблицу классов.
* \return Указатель на пустую таблицу классов.
*/
struct ClassTable * createEmptyClassTable()
{
    struct ClassTable * table = (struct ClassTable *)malloc(sizeof(struct ClassTable));
    table->items = new std::map<std::string, struct ClassTableElement*>();
    return table;
}

bool FuncParam::operator==(class FuncParam & other) const 
{
    return false;
}

bool Type::isReplacable(class Type & other) const
{
    return false;
}


/* --------------------------- Таблица констант ---------------------------------- */

ConstantTable::ConstantTable()
{

}

int ConstantTable::findOrAddConstant(enum ConstantType type, char * utf8string)
{
    // Найти константу в списке констант.
    // Создать новую константу, если константа не найдена.
    // Вернуть результат.
    return 0;
}

int ConstantTable::findConstant(enum ConstantType type, char * utf8string, int firstRef, int secondRef, int intVal, double dVal)
{
    auto iterator = this->constants.cbegin();
    while(iterator != this->constants.cend()) // Пока не конец таблицы...
    {
        if (type == iterator->second->cnst) // Если тип константы совпадает с рассматриваемым типом...
        {
            switch (iterator->second->cnst)
            {
                case Utf8: // В случае, если контанта - Utf8...
                    if (std::string(utf8string) == std::string(iterator->second->string)) // Вернуть номер константы, если совпадают значения строк-констант Utf-8
                        return iterator->first;
                    break;
                case Class: // В случае, если константа - класс...
                    if (iterator->second->firstRef == firstRef) // Вернуть номер константы, если совпадают значения номеров констант-ссылок.
                        return iterator->first;
                    break;
                case MethodRef: // В случае, если константа - ссылка на метод...
                    if (iterator->second->firstRef == firstRef && iterator->second->secRef == secondRef) // Вернуть номер константы, если совпадают значения номеров констант-ссылок.
                        return iterator->first;
                    break;
                case NameAndType: // В случае, если константа - имя и класс...
                    if (iterator->second->firstRef == firstRef && iterator->second->secRef == secondRef) // Вернуть номер константы, если совпадают значения номеров констант-ссылок.
                        return iterator->first;
                    break;
                case Integer: // В случае, если константа - литерал integer...
                    if (iterator->second->Integer == intVal) // Вернуть номер константы, если совпадают значения номеров констант-ссылок.
                        return iterator->first;
                    break;
                case Double: // В случае, если константа - литерал double...
                    if (iterator->second->Double == dVal) // Вернуть номер константы, если совпадают значения номеров констант-ссылок.
                        return iterator->first;
                    break;
                case FieldRef: // В случае, если константа - ссылка на поле...
                    if (iterator->second->firstRef == firstRef && iterator->second->secRef == secondRef)  // Вернуть номер константы, если совпадают значения номеров констант-ссылок.
                        return iterator->first;
                    break;
            }
        }
        iterator++; // Перейти к следующему элементу.
    }
    return -1;
}
