#include "tables.hpp"
#include <iostream>

/* --------------------------------- Построение таблицы классов. ------------------------------------ */

std::map<std::string, class ClassTableElement*> ClassTable::items = std::map<std::string, class ClassTableElement*>();

static MethodTable * _fillMethodTableForClass(struct ClassNode * clas, class ClassTableElement* elem);

/*! Проверить, является ли класс открытым для наследования.
* \param[in] Узел класса.
* \return результат проверки: true = если открыт, false - если нет.
*/
static bool _isOpenClass(struct KotlinFileElementNode * cls);

/*! Заполнить таблицу модификаторов для класса.
* \param[in] Таблциа модификаторов класса.
* \param[in] узел модификатора.
*/
static void _fillModifierTable(struct ModifierHead * head, struct ModifierNode * node);

/*! [PRIVATE] Добавить класс в таблицу классов при его наличии.
* \param[in] fileElem рассматриваемый элемент файла Kotlin.
*/
static struct SemanticError * _addClassToClassTable(struct KotlinFileElementNode * fileElem)
{
    struct SemanticError * err = NULL;
    if (fileElem != NULL)
    {
        if (fileElem->type == _CLASS)
        {
            char * className = fileElem->clas->identifier;
            if (ClassTable::items.find(fileElem->clas->identifier) != ClassTable::items.end()){
                std::string msg = "There is already a class with the specified identifier: ";
                msg += fileElem->clas->identifier;
                return createSemanticError(4, msg.c_str());
            }
            class ClassTableElement * elem = createEmptyClassTableElement();
            if (_isOpenClass(fileElem)) elem->isOpen = 1;
            elem->clsName = fileElem->clas->identifier;

            int utf8 = elem->constants->findOrAddConstant(ConstantType::Utf8, fileElem->clas->identifier);
            int cls = elem->constants->findOrAddConstant(ConstantType::Class, NULL, NULL, NULL, utf8);
            elem->name = utf8;
            elem->thisClass = cls;
            ClassTable::items.insert(std::pair<std::string, class ClassTableElement *>(fileElem->clas->identifier, elem));
            _fillMethodTableForClass(fileElem->clas, ClassTable::items[fileElem->clas->identifier]);

        }
        if (fileElem->next != NULL)
        {
            return _addClassToClassTable(fileElem->next);
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

static void _fillModifierTable(struct ModifierHead * head, struct ModifierNode * node)
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

        case _PROTECTED :
            head->isProtected = 1;
            break;

        case _OPEN:
            head->isOpen = 1;
            break;
        
        case _FINAL:
            head->isFinal = 1;
            break;
        case _OVERRIDE:
            head->isOverride = 1;
            break;
    }
    if (node->next != NULL)
    {
        _fillModifierTable(head, node->next);
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
                _fillModifierTable(head, cls->modifiers->first);
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
* \return Возможная ошибка построения.
*/  
struct SemanticError * buildClassTable(struct KotlinFileNode * root, const char * fileName)
{
    struct SemanticError * err = NULL;
    
    // Получить имя класса для свободных функций.
    std::string path = fileName;
    size_t sep = path.find_last_of("\\/");
    if (sep != std::string::npos)
        path = path.substr(sep + 1, path.size() - sep - 1);
    sep = path.find_last_of(".");
    if (sep != std::string::npos)
        path[sep + 1] = std::toupper(path[sep + 1]);
    path[0] = std::toupper(path[0]);
    path.erase(sep, 1);

    // Создать класс для свбодных функций.
    class ClassTableElement * elem = createEmptyClassTableElement();
    elem->clsName = path;
    int utf8 = elem->constants->findOrAddConstant(ConstantType::Utf8, (char*)path.c_str());
    int cls = elem->constants->findOrAddConstant(ConstantType::Class, NULL, NULL, NULL, utf8);
    elem->name = utf8;
    elem->thisClass = cls;

    ClassTable::items[path] = elem;


    if (root->elemList->first != NULL)
    {
        err = _addClassToClassTable(root->elemList->first);
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
    tableElem->fields = new FieldTable();
    tableElem->methods = new MethodTable();
    tableElem->name = -1;
    tableElem->isOpen = 0;
    tableElem->superClass = -1;
    tableElem->superName = -1;
    tableElem->constants = new ConstantTable();
    tableElem->params = new ClassParamTable();
    return tableElem;
}

bool ClassTableElement:: isHaveSuperClass(std::string super)
{
    if (this->superName == NULL) return false;
    else
    {
        char * sName = this->constants->constants[this->superName]->string; // Получить имя спупер класса.
        if (sName == super) // Считать, что класс имеет рассматриваемые суперкласс, если имена совпадают.
            return true;
        else return ClassTable::items[sName]->isHaveSuperClass(super); // Иначе проверить наличие требуемого родителя у суперкласа.
    }
    return false;
}

/*! Создать пустую таблицу классов.
* \return Указатель на пустую таблицу классов.
*/
class ClassTable * createEmptyClassTable()
{
    class ClassTable * table = (class ClassTable *)malloc(sizeof(class ClassTable));
    ///table->items = new std::map<std::string, class ClassTableElement*>();
    return table;
}

bool FuncParam::operator==(class FuncParam & other) const 
{
    if (this->typ->typ == other.typ->typ){
        return this->typ->className == other.typ->className;
    }
    return false;
}

bool FuncParam::operator< ( class FuncParam & other) const
{
    if (this->typ->typ == other.typ->typ){
        return this->typ->className < other.typ->className;
    }
    else if (this->typ->typ == TypeType::_ARRAY && other.typ->typ == TypeType::_CLS)
        return false;
        
    else if (this->typ->typ == TypeType::_CLS && other.typ->typ == TypeType::_ARRAY)
        return true;
}

bool Type::isReplacable(class Type & other) const
{
    if (this->typ != other.typ) // Сообщить о невозможности приведения между массивом и простым типом.
        return false;
    if (this->typ == _CLS && other.typ == _CLS) // Сравнить типы, если оба типа это классы.
    {
        if (this->className == other.className) // Сообщить о равенстве типов, если это классы с одинаковым названием.
            return true;
        else // Иначе...
        {
            class ClassTableElement * thisClass = ClassTable::items[this->className];
            class ClassTableElement * otherClass = ClassTable::items[other.className];
            return thisClass->isHaveSuperClass(other.className);
        }
    }
    else if (this->typ == _ARRAY && other.typ == _ARRAY) // Проверить типы классов, образующих массив.
    {
        if (this->className == other.className) // Сообщить о равенстве типов, если это классы с одинаковым названием.
            return true;
        else // Иначе...
        {
            class ClassTableElement * thisClass = ClassTable::items[this->className];
            class ClassTableElement * otherClass = ClassTable::items[other.className];
            return thisClass->isHaveSuperClass(other.className);
        }
    }
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

FieldTableElement::FieldTableElement(int nm, int dsc, std::string strNm, std::string strDsc, struct ModifierHead * mods, int isCnst)
{
    this->name = name;
    this->descriptor = dsc;
    this->modifiers = mods;
    this->isConst = isCnst;
    this->strName = strNm;
    this->stdDesc = strDsc;
}

static struct SemanticError * _addFieldFromClassBody(class ClassTableElement *cls, class FieldTable* table, struct ClassMemberNode * member)
{
    struct SemanticError * err = NULL;
    if (member->type == ClassMemberType::_FIELD) // Если указанный член является полем класса.
    {
        std::string name = member->stmt->varValId; // Идентификатор переменной.
        if (table->fields.count(name) > 0) // Проверить таблицу полей на наличие такого поля.
        {
            std::string msg = "There is already a field in class ";
            msg += cls->clsName;
            msg += " with the specified identifier: ";
            msg += name;
            return createSemanticError(4, msg.c_str());
        }
        else
        {
            Type * typ = NULL;
            if (member->stmt->varValType != NULL) // Присвоить тип поля, если таковой явно указан.
            {
                typ = new Type(member->stmt->varValType);
            }
            else // Иначе.
            {
                
            }
        }
    }
    if (member->next != NULL)
    {
        err = _addFieldFromClassBody(cls, table, member);
    }
    return err;
}

/* --------------------------- Таблица полей --------------------------- */

static FieldTable * _fillFieldsTableForClass(struct ClassNode * clas)
{
    class FieldTable * table = new FieldTable();

    // Проверить поля, находящиеся в теле класса.
    if (clas->members != NULL)
    {
        if (clas->members->first != NULL)
        {

        }
    }
    return table;
}



/* ------------------------------ Таблица методов ------------------------------*/

static struct SemanticError * _addMethodForClass(class ClassTableElement *cls, class MethodTable* table, struct ClassMemberNode* member )
{
    struct SemanticError * err = NULL;
    if (member->type == ClassMemberType::_METHOD) // Если рассматриваемый член класса является методом.
    {
        // Получить идентификатор метода.
        std::string ident = member->method->identifier;

        // Получить возвращаемое значение метода.
        class Type *  retVal = new Type(member->method->returnValue);

        // Получить набор параметров метода.
        std::vector<FuncParam> vec;
        if (member->method->params != NULL)
        {
            struct VarDeclarationNode * par = NULL;
            if (member->method->params->first != NULL)
                par = member->method->params->first;

            while (par != NULL)
            {
                vec.push_back(FuncParam(par->identifier, new Type(par->type)));
                par = par->next; // Перейти к следующему элементу.
            }
            
        }

        // Получить дескриптор метода.
        std::string desc = "("; 
        for (int i = 0; i < (int)vec.size(); i++)
        {
            if (vec[i].typ->typ == TypeType::_CLS)
                desc += "L";

            else if (vec[i].typ->typ == TypeType::_ARRAY)
                desc += "[L";

            desc += vec[i].typ->className;
            desc += ";";
        }
        desc += ")";

        std::string descKey = desc;

        if (retVal->typ == TypeType::_CLS)
            desc += "L";

        else if (retVal->typ == TypeType::_ARRAY)
            desc += "[L";
                
        desc += retVal->className;
        desc += ";";
        
        // Создать элемент в таблице методов, если таковго метода еще не существует.
        if (table->methods.count(ident) != 0)
        {
            if (table->methods.find(ident)->second.find(descKey) != table->methods.find(ident)->second.cend()) // Сообщить об ошибке, если такой метод существует.
            {
                // TODO сообщение об ошибке.
                std::string msg = "There is already a method with the specified identifier: ";
                msg += ident;
                return createSemanticError(4, msg.c_str());
            }
            else // Иначе
            {   
                // Создать запись в таблице констант класса.
                int nam = cls->constants->findOrAddConstant(ConstantType::Utf8, (char*)ident.c_str()); // Добавить или получить номер константы названия метода.
                int dsc = cls->constants->findOrAddConstant(ConstantType::Utf8, (char*)desc.c_str()); // Добавить или получить номер константы дескриптора метода.
                
                table->methods.find(ident)->second[descKey] = new MethodTableElement(nam, dsc, ident, desc, member->method->body, retVal, vec); // Добавить новый элемент в таблицу методов.
            }
        }
        else
        {
            // Создать запись в таблице констант класса.
            int nam = cls->constants->findOrAddConstant(ConstantType::Utf8, (char*)ident.c_str()); // Добавить или получить номер константы названия метода.
            int dsc = cls->constants->findOrAddConstant(ConstantType::Utf8, (char*)desc.c_str()); // Добавить или получить номер константы дескриптора метода.

            table->methods[ident] = std::map<std::string, MethodTableElement *>();
            table->methods.find(ident)->second[descKey] = new MethodTableElement(nam, dsc, ident, desc, member->method->body, retVal, vec); // Добавить новый элемент в таблицу методов.*/
        }
        
        Type * ths = new Type();
        ths->cls = cls;
        ths->className = cls->clsName;
        ths->typ = TypeType::_CLS;
        table->methods.find(ident)->second[descKey]->varTable->findOrAddLocalVar("this", ths, 1);

        // Заполнить таблицу локальных переменных.
        for (int i = 0; i < vec.size(); i++)
        {
            table->methods.find(ident)->second[descKey]->varTable->findOrAddLocalVar(vec[i].name, vec[i].typ, 1);
        }
    }
    if (member->next != NULL)
    {
        err = _addMethodForClass(cls, table, member->next);
    }
    return err; 
}

static MethodTable * _fillMethodTableForClass(struct ClassNode * clas, class ClassTableElement* elem)
{
    class MethodTable * table = new MethodTable();
    if (clas->members != NULL)
    {
        if (clas->members->first != NULL)
        {
            _addMethodForClass(elem, elem->methods, clas->members->first);
        }
    }
    return table;
}

FuncParam::FuncParam(std::string n, class Type * t)
{
    this->name = n;
    this->typ = t;
}

Type::Type()
{

}

Type::Type(struct TypeNode * type)
{
    this->typ = type->type;
    if (this->typ == TypeType::_ARRAY)
    {
        this->className = type->complexType->ident;
    }
    else if (this->typ == TypeType::_CLS)
    {
        this->className = type->ident;
    }   
}

MethodTableElement::MethodTableElement(int nameCnst, int descCnst, std::string nam, std::string dsc, struct StatementListNode * strt, class Type * ret, std::vector<class FuncParam> pars)
{
    this->methodName = nameCnst;
    this->descriptor = descCnst;
    this->strName = nam;
    this->strDesc = dsc;
    this->start = strt;
    this->retType = ret;
    this->params = pars;
    this->varTable= new LocalVariableTable();
}



/* ---------------------------- Таблица локальных переменных -----------------------------*/

LocalVariableElement::LocalVariableElement(std::string nam, int ident, class Type * t, int isCnst)
{
    this->id = ident;
    this->name = nam;
    this->typ = t;
    this->isConst = isCnst;
}

int LocalVariableTable::findOrAddLocalVar(std::string name, class Type * typ, int isCnst)
{
    if (items.find(name) == items.cend()) // Если переменная с указанным именем не найдена.
    {
        items[name] = new LocalVariableElement(name, maxId++, typ, isCnst);
    }
    else 
    {
        return items[name]->id;
    }
}

static void fillLocalVarsTable()
{

}

ClassParamElement::ClassParamElement(std::string n, class Type * t, int isProp)
{
    this->name = n;
    this->typ = t;
    this->isProperty = isProp;
}

static SemanticError * _fillClassParamtable(class ClassTableElement * clsElem, struct ClassNode* clsNode)
{
    struct SemanticError * err = NULL;
    if (clsNode->constr != NULL) // Если у класса есть первичный конструктор.
    {
        if (clsNode->constr->params != NULL) // Если у конструктора есть параметры класса.
        {
            struct ClassParamNode * par = NULL;
            par = clsNode->constr->params->first;
            while (par != NULL) // Пока имеются параметры класса...
            {
                std::string name;
                Type * typ = NULL;
                int isPr = 0;
                if (par->varDecl != NULL)
                {
                    name = par->varDecl->identifier;
                    typ = new Type(par->varDecl->type);
                }
                else if (par->valVar != NULL)
                {
                    name = par->valVar->varValId;
                    typ = new Type(par->valVar->varValType);
                    isPr = 1;
                }
                if (clsElem->params->items.count(name) != 0) // Если уже содержится параметр с идентификатором.
                {
                    std::string msg = "There is already a method with the specified identifier: ";
                    msg += name;
                    return createSemanticError(4, msg.c_str());
                }
                else
                {
                    clsElem->params->items[name] = new ClassParamElement(name, typ, isPr);
                    if (isPr == 1) // Добавить поле в таблицу полей.
                    {
                        std::string desc = "";
                        if (typ->typ == TypeType::_ARRAY)
                        {
                            desc += "[";
                        }
                        desc += "L";
                        desc += typ->className;
                        int isCnst = 0;
                        int nameUtf8 = clsElem->constants->findOrAddConstant(ConstantType::Utf8, (char*)name.c_str());
                        int descUtf8 = clsElem->constants->findOrAddConstant(ConstantType::Utf8, (char*)desc.c_str());
                        struct ModifierHead * head = createEmptyModifierHead();
                        if (par->mods != NULL) if (par->mods->first != NULL) _fillModifierTable(head, par->mods->first);
                        if (par->valVar->type == StatementType::_VAL) isCnst = 1; 
                        clsElem->fields->fields[name] = new FieldTableElement(nameUtf8, descUtf8, name, desc, head, isCnst);
                    }
                }
                par = par->next; // Перейти к следующему параметру.
            }
        }
    }
    return err;
}

 FunctionTableElement::FunctionTableElement(int nameCnst, int descCnst, std::string nam, std::string dsc, struct StatementListNode * strt, class Type * ret, std::vector<class FuncParam> pars)
 {
    this->methodName = nameCnst;
    this->descriptor = descCnst;
    this->strName = nam;
    this->strDesc = dsc;
    this->start = strt;
    this->retType = ret;
    this->params = pars;
    this->varTable= new LocalVariableTable();
 }

static SemanticError * _fillFunctionTable(class ClassTableElement * mainClass, struct KotlinFileElementNode * fileElem)
{
    struct SemanticError * err = NULL;

    struct KotlinFileElementNode * curElem = fileElem;
    while (curElem != NULL) // Пока остались элементы файла котлин...
    {
        if(curElem->type == KotlinFileElementType::_FUNCTION) // Если рассматриваемый элемент является функцией.
        {
        std::string ident = fileElem->func->identifier;

        // Получить возвращаемое значение метода.
        class Type *  retVal = new Type(fileElem->func->returnValue);

        // Получить набор параметров метода.
        std::vector<FuncParam> vec;
        if (fileElem->func->params != NULL)
        {
            struct VarDeclarationNode * par = NULL;
            if (fileElem->func->params->first != NULL)
                par = fileElem->func->params->first;

            while (par != NULL)
            {
                vec.push_back(FuncParam(par->identifier, new Type(par->type)));
                par = par->next; // Перейти к следующему элементу.
            }
            
        }

        // Получить дескриптор метода.
        std::string desc = "("; 
        for (int i = 0; i < (int)vec.size(); i++)
        {
            if (vec[i].typ->typ == TypeType::_CLS)
                desc += "L";

            else if (vec[i].typ->typ == TypeType::_ARRAY)
                desc += "[L";

            desc += vec[i].typ->className;
            desc += ";";
        }
        desc += ")";

        std::string descKey = desc;

        if (retVal->typ == TypeType::_CLS)
            desc += "L";

        else if (retVal->typ == TypeType::_ARRAY)
            desc += "[L";
                
        desc += retVal->className;
        desc += ";";
        
        // Создать элемент в таблице методов, если таковго метода еще не существует.
        if (mainClass->methods->methods.count(ident) != 0)
        {
            if (mainClass->methods->methods.find(ident)->second.find(descKey) != mainClass->methods->methods.find(ident)->second.cend()) // Сообщить об ошибке, если такой метод существует.
            {
                // TODO сообщение об ошибке.
                std::string msg = "There is already a method with the specified identifier: ";
                msg += ident;
                return createSemanticError(4, msg.c_str());
            }
            else // Иначе
            {   
                // Создать запись в таблице констант класса.
                int nam = mainClass->constants->findOrAddConstant(ConstantType::Utf8, (char*)ident.c_str()); // Добавить или получить номер константы названия метода.
                int dsc = mainClass->constants->findOrAddConstant(ConstantType::Utf8, (char*)desc.c_str()); // Добавить или получить номер константы дескриптора метода.
                
                mainClass->methods->methods.find(ident)->second[descKey] = new MethodTableElement(nam, dsc, ident, desc, curElem->func->body, retVal, vec); // Добавить новый элемент в таблицу методов.
                FunctionTable::items.find(ident)->second[descKey] = new FunctionTableElement(nam, dsc, ident, desc, curElem->func->body, retVal, vec);
            }
        }
        else
        {
            // Создать запись в таблице констант класса.
            int nam = mainClass->constants->findOrAddConstant(ConstantType::Utf8, (char*)ident.c_str()); // Добавить или получить номер константы названия метода.
            int dsc = mainClass->constants->findOrAddConstant(ConstantType::Utf8, (char*)desc.c_str()); // Добавить или получить номер константы дескриптора метода.

            mainClass->methods->methods[ident] = std::map<std::string, MethodTableElement *>();
            mainClass->methods->methods.find(ident)->second[descKey] = new MethodTableElement(nam, dsc, ident, desc, curElem->func->body, retVal, vec); // Добавить новый элемент в таблицу методов.*/
            FunctionTable::items[ident] = std::map<std::string, class FunctionTableElement*>();
            FunctionTable::items.find(ident)->second[descKey] = new FunctionTableElement(nam, dsc, ident, desc, curElem->func->body, retVal, vec);
        }

        // Заполнить таблицу локальных переменных.
        for (int i = 0; i < vec.size(); i++)
        {
            FunctionTable::items.find(ident)->second[descKey]->varTable->findOrAddLocalVar(vec[i].name, vec[i].typ, 1);
            mainClass->methods->methods.find(ident)->second[descKey]->varTable->findOrAddLocalVar(vec[i].name, vec[i].typ, 1);
        }
        }


        curElem = curElem->next; // Перейти к следующему элементу.
    }
    return err;
}
