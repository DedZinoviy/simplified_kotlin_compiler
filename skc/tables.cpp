#include "tables.hpp"

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
            classTable->items->insert(std::pair<std::string, struct ClassTableElement *>(fileElem->clas->identifier, elem));
        }
        if (fileElem->next != NULL)
        {
            _addClassToClassTable(fileElem->next, classTable);
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
