#include "tables.hpp"

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
static void _addClassToClassTable(struct KotlinFileElementNode * fileElem, struct ClassTable * classTable)
{
    if (fileElem != NULL)
    {
        if (fileElem->type == _CLASS)
        {
            char * className = fileElem->clas->identifier;
            //if (classTable->items->find())
            struct ClassTableElement * elem = createEmptyClassTableElement();
            if (_isOpenClass(fileElem)) elem->isOpen = 1;
            classTable->items->insert(std::pair<std::string, struct ClassTableElement *>(fileElem->clas->identifier, elem));
        }
        if (fileElem->next != NULL)
        {
            _addClassToClassTable(fileElem->next, classTable);
        }
    }
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
* \return созданная таблица классов.
*/  
struct ClassTable * buildClassTable(struct KotlinFileNode* root, const char* fileName)
{
    struct ClassTable* classes = createEmptyClassTable();
    if (root->elemList->first != NULL)
    {
        _addClassToClassTable(root->elemList->first, classes);
    }

    return classes;
}



/* ----------------------------------- Class Table ----------------------------------- */


/*! Создать пустой элемент таблицы классов.
* \return пустой элемент таблицы классов.
*/
struct ClassTableElement * createEmptyClassTableElement()
{
    struct ClassTableElement * tableElem = (struct ClassTableElement *)malloc(sizeof(struct ClassTableElement));
    tableElem->fields = NULL;
    tableElem->methods = NULL;
    tableElem->name = -1;
    tableElem->isOpen = 0;
    tableElem->superClass = -1;
    tableElem->superName = -1;
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

/*! Добавить элемент таблицы классов в таблицу классов.
* \param[in,out] table таблица, в которую происходит добавление.
* \param[in] classname имя добавляемого класса. 
* \param[in] elem Добавляемый элемент класса.
* \return Измененная таблица классов с добавленным значением.
*/
struct ClassTable * addClassToTable(struct ClassTable * table, char * classname, struct ClassTableElement * elem)
{
    return NULL;
}

bool FuncParam::operator==(class FuncParam & other) const 
{
    return false;
}

bool Type::isReplacable(class Type & other) const
{
    return false;
}
