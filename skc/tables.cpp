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

            int utf8 = elem->constants->findOrAddConstant(ConstantType::Utf8, fileElem->clas->identifier);
            int cls = elem->constants->findOrAddConstant(ConstantType::Class, NULL, NULL, NULL, utf8);
            elem->name = utf8;
            elem->thisClass = cls;
            //classTable->items[fileElem->clas->identifier] = elem;
            classTable->items->insert(std::pair<std::string, class ClassTableElement *>(fileElem->clas->identifier, elem));
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
    table->items = new std::map<std::string, class ClassTableElement*>();
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

int ConstantTable::findOrAddConstant(enum ConstantType type, char * utf8string, int intVal, double dVal, int fRef, int sRef)
{
    int constant = findConstant(type, utf8string, fRef, sRef, intVal, dVal); // Найти константу в списке констант.
    if (constant == -1) // Создать новую константу, если константа не найдена.
    {
        constant = maxId++;
        if (type == ConstantType::Utf8) constants[constant] = new ConstantTableItem(type, constant, utf8string);
        else if (type == ConstantType::Class) constants[constant] = new ConstantTableItem(type, constant, NULL, NULL, NULL, fRef);
        else if (type == ConstantType::Integer) constants[constant] = new ConstantTableItem(type, constant, NULL, intVal);
        else if (type == ConstantType::Double) constants[constant] = new ConstantTableItem(type, constant, NULL, NULL, dVal);
        else if (type == ConstantType::NameAndType) constants[constant] = new ConstantTableItem(type, constant, NULL, NULL, NULL,fRef, sRef);
        else if (type == ConstantType::FieldRef) constants[constant] = new ConstantTableItem(type, constant, NULL, NULL, NULL,fRef, sRef);
        else if (type == ConstantType::MethodRef) constants[constant] = new ConstantTableItem(type, constant, NULL, NULL, NULL,fRef, sRef);
    }
    // Вернуть результат.
    return constant;
}

int ConstantTable::findConstant(enum ConstantType type, char * utf8string, int fRef, int secondRef, int intVal, double dVal)
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
                    if (iterator->second->firstRef == fRef) // Вернуть номер константы, если совпадают значения номеров констант-ссылок.
                        return iterator->first;
                    break;
                case MethodRef: // В случае, если константа - ссылка на метод...
                    if (iterator->second->firstRef == fRef && iterator->second->secRef == secondRef) // Вернуть номер константы, если совпадают значения номеров констант-ссылок.
                        return iterator->first;
                    break;
                case NameAndType: // В случае, если константа - имя и класс...
                    if (iterator->second->firstRef == fRef && iterator->second->secRef == secondRef) // Вернуть номер константы, если совпадают значения номеров констант-ссылок.
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
                    if (iterator->second->firstRef == fRef && iterator->second->secRef == secondRef)  // Вернуть номер константы, если совпадают значения номеров констант-ссылок.
                        return iterator->first;
                    break;
            }
        }
        iterator++; // Перейти к следующему элементу.
    }
    return -1;
}

/* --------------------------- Элемент таблицы констант --------------------------- */

ConstantTableItem:: ConstantTableItem(enum ConstantType type, int id, char * utf8, int intVal, double dVal, int fRef, int secondRef)
{
    this->id = id;
    this->cnst = type;
    if (type == ConstantType::Utf8) this->string = utf8;
    if (type == ConstantType::Integer) this->Integer = intVal;
    if (type == ConstantType::Double) this->Double = dVal;
    if (type == ConstantType::Class) this->firstRef = fRef;
    if (type == ConstantType::NameAndType) { this->firstRef = fRef; this->secRef = secondRef; }
    if (type == ConstantType::FieldRef) { this->firstRef = fRef; this->secRef = secondRef; }
    if (type == ConstantType::MethodRef) { this->firstRef = fRef; this->secRef = secondRef; }
}



/* --------------------------- Элемент таблицы полей --------------------------- */

FieldTableElement::FieldTableElement(int nm, int dsc, struct ModifierHead * mods)
{
    this->name = name;
    this->descriptor = dsc;
    this->modifiers = mods;
}

static struct SemanticError * _addFieldFromClassParam(class FieldTable * table, struct ClassParamNode * param)
{
    struct SemanticError * err = NULL;
    if (param->valVar != NULL)
    {
        //int fieldName = findOrAddConstant();
        char * fieldName = param->valVar->varValId; // Получить идентификатор переменной-поля.
        if (table->fields->find(fieldName) != table->fields->end()){
            std::string msg = "There is already a field with the specified identifier: ";
            msg += fieldName;
            return createSemanticError(4, msg.c_str());
        }
        //table->fields->insert(std::pair());
    }
    if (param->next != NULL)
    {
        err = _addFieldFromClassParam(table, param->next);
    }
    return err;
}

/* --------------------------- Таблица полей --------------------------- */

static void _fillFieldsTableForClass(struct ClassNode * clas)
{
    class FieldTable * table = new FieldTable();
    // Проверить поля, находящиеся в первичном конструкторе.
    if (clas->constr != NULL)
    {
        if (clas->constr->params != NULL)
        {
            if (clas->constr->params->first != NULL)
            {
                _addFieldFromClassParam(table, clas->constr->params->first);
            }
        }
    }
    // Проверить поля, находящиеся в теле класса.
    if (clas->members != NULL)
    {
        if (clas->members->first != NULL)
        {

        }
    }
}

