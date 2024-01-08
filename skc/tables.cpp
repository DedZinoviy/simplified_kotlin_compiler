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

int ConstantTable::findConstant(enum ConstantType type, char * utf8string)
{
    auto iterator = this->constants.cbegin();
    while(iterator != this->constants.cend()) // Пока не конец таблицы...
    {
        switch (iterator->second->cnst)
        {
            case Utf8:
                break;
            case Class:
                break;
            case MethodRef:
                break;
            case NameAndType:
                break;
            case Integer:
                break;
            case Double:
                break;
            case FieldRef:
                break;
        }
        iterator++; // Перейти к следующему элементу.
    }
    return 0;
}
