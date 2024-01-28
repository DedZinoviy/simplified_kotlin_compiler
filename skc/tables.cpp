#include "tables.hpp"
#include <iostream>

/* --------------------------------- Построение таблицы классов. ------------------------------------ */

std::map<std::string, class ClassTableElement*> ClassTable::items = std::map<std::string, class ClassTableElement*>();
std::map<std::string, std::map<std::string, class FunctionTableElement*>> FunctionTable::items = std::map<std::string, std::map<std::string, class FunctionTableElement*>>();
void fillLiterals(class ClassTableElement * cls);
void fillMethodRefs(class ClassTableElement * cls);

static struct SemanticError * _fillMethodTableForClass(struct ClassNode * clas, class ClassTableElement* elem);
struct SemanticError * attributingAndFillingLocals(class MethodTableElement * meth);
static SemanticError * _fillFunctionTable(class ClassTableElement * mainClass, struct KotlinFileElementNode * fileElem);

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

static SemanticError * _addConstructor(class ClassTableElement * classElem, struct ClassNode * classNode);

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
            if (FunctionTable::items.count(fileElem->clas->identifier) != 0)
            {
                std::string msg = "There is already a function with the specified identifier: ";
                msg += fileElem->clas->identifier;
                return createSemanticError(4, msg.c_str());
            }
            class ClassTableElement * elem = new ClassTableElement();
            if (_isOpenClass(fileElem)) elem->isOpen = 1;
            elem->clsName = fileElem->clas->identifier;

            int utf8 = elem->constants->findOrAddConstant(ConstantType::Utf8, fileElem->clas->identifier);
            int cls = elem->constants->findOrAddConstant(ConstantType::Class, NULL, NULL, NULL, utf8);
            elem->name = utf8;
            elem->thisClass = cls;
            ClassTable::items.insert(std::pair<std::string, class ClassTableElement *>(fileElem->clas->identifier, elem));
            err = _addConstructor(ClassTable::items[fileElem->clas->identifier], fileElem->clas);
            err = _fillMethodTableForClass(fileElem->clas, ClassTable::items[fileElem->clas->identifier]);

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
    class ClassTableElement * elem = new ClassTableElement();
    
    elem->clsName = path;
    
    int utf8 = elem->constants->findOrAddConstant(ConstantType::Utf8, path);
    int cls = elem->constants->findOrAddConstant(ConstantType::Class, "", NULL, NULL, utf8);
     
    elem->name = utf8;
    elem->thisClass = cls;

    int parent = elem->constants->findOrAddConstant(ConstantType::Utf8, (char*)"java/lang/Object");
    int parentCls = elem->constants->findOrAddConstant(ConstantType::Class, "", NULL, NULL, parent);
    elem->constants->findOrAddConstant(ConstantType::Utf8, "Code");

    elem->superName = parent;
    elem->superClass = parentCls;
    ClassTable::items[path] = elem;
    if (root->elemList->first != NULL)
    { 
        err = _fillFunctionTable(ClassTable::items[path], root->elemList->first);
        if (err != NULL) return err; 
    }

    if (root->elemList->first != NULL)
    {
        err = _addClassToClassTable(root->elemList->first);
    }
    for (auto it = ClassTable::items[path]->methods->methods.begin(); it != ClassTable::items[path]->methods->methods.end(); ++it)
    {
        for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
        {
            err = attributingAndFillingLocals(iter->second);
            if (err != NULL) return err; 
        }
    }
    fillLiterals(elem);
    fillMethodRefs(elem);
    if (elem->methods->methods.count("main") != 0)
    {
        if (elem->methods->methods["main"].count("()") != 0)
        {
            std::string mainDesc = "([Ljava/lang/String])V";
            int n = elem->constants->findOrAddConstant(Utf8, "main");
            int d = elem->constants->findOrAddConstant(Utf8, "([Ljava/lang/String;)V");
           
           
            n = elem->methods->methods["main"]["()"]->methodName;
            d = elem->methods->methods["main"]["()"]->descriptor;
            int nat = elem->constants->findOrAddConstant(NameAndType, "", 0,0,n,d);
            int cls = elem->thisClass;
            int mRef = elem->constants->findOrAddConstant(MethodRef, "",0,0,cls,nat);
           
           
            elem->methods->methods["main"][mainDesc] = new MethodTableElement(n ,d,"main", mainDesc, NULL, NULL, std::vector<FuncParam>());
        }
    }
    return err;
}



/* ----------------------------------- Class Table ----------------------------------- */

ClassTableElement::ClassTableElement()
{
    this->fields = new FieldTable();
    this->methods = new MethodTable();
    this->name = NULL;
    this->isOpen = 0;
    this->superClass = NULL;
    this->superName = NULL;
    this->constants = new ConstantTable();
    this->params = new ClassParamTable();
}
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
    if (this->superName == NULL) {  return false;}
    else
    {
        std::string sName = this->constants->constants[this->superName]->string; // Получить имя спупер класса.
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
            if (thisClass != NULL) return thisClass->isHaveSuperClass(other.className);
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
            if (thisClass != NULL) { return thisClass->isHaveSuperClass(other.className);}
        }
    }
    return false;
}


/* --------------------------- Таблица констант ---------------------------------- */

ConstantTable::ConstantTable()
{
    this->constants = std::map<int, class ConstantTableItem *> ();
    this->constants[maxId] = new ConstantTableItem(Utf8, maxId, "Code");
}

int ConstantTable::findOrAddConstant(enum ConstantType type, std::string utf8string, int intVal, double dVal, int fRef, int sRef)
{
    int constant = findConstant(type, utf8string, fRef, sRef, intVal, dVal); // Найти константу в списке констант.
    if (constant == -1) // Создать новую константу, если константа не найдена.
    {
        constant = maxId++;
        if (type == ConstantType::Utf8){constants[constant] = new ConstantTableItem(type, constant, utf8string);}
        else if (type == ConstantType::Class) {constants[constant] = new ConstantTableItem(type, constant, "", NULL, NULL, fRef);}
        else if (type == ConstantType::Integer) constants[constant] = new ConstantTableItem(type, constant, "", intVal);
        else if (type == ConstantType::Double) constants[constant] = new ConstantTableItem(type, constant, "", NULL, dVal);
        else if (type == ConstantType::NameAndType) constants[constant] = new ConstantTableItem(type, constant, "", NULL, NULL,fRef, sRef);
        else if (type == ConstantType::FieldRef) constants[constant] = new ConstantTableItem(type, constant, "", NULL, NULL,fRef, sRef);
        else if (type == ConstantType::MethodRef) constants[constant] = new ConstantTableItem(type, constant, "", NULL, NULL,fRef, sRef);
        else if (type == ConstantType::String) constants[constant] = new ConstantTableItem(type, constant, "", NULL, NULL,fRef);
    }
    // Вернуть результат.
    return constant;
}

int ConstantTable::findConstant(enum ConstantType type, std::string utf8string, int fRef, int secondRef, int intVal, double dVal)
{
    auto iterator = constants.cbegin();
    while(iterator != constants.cend()) // Пока не конец таблицы...
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
                case String:
                    if (iterator->second->firstRef == fRef)
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
        ++iterator; // Перейти к следующему элементу.
    }
    return -1;
}

/* --------------------------- Элемент таблицы констант --------------------------- */

ConstantTableItem:: ConstantTableItem(enum ConstantType type, int id, std::string utf8, int intVal, double dVal, int fRef, int secondRef)
{
    this->id = id;
    this->cnst = type;
    this->string;
    this->Integer = 0;
    this->Double = 0;
    this->firstRef = 0;
    this->secRef = 0;
    if (type == ConstantType::Utf8){this->string = utf8;}
    else if (type == ConstantType::Integer) this->Integer = intVal;
    else if (type == ConstantType::Double) this->Double = dVal;
    else if (type == ConstantType::Class) this->firstRef = fRef;
    else if (type == ConstantType::String) this->firstRef = fRef;
    else if (type == ConstantType::NameAndType) { this->firstRef = fRef; this->secRef = secondRef; }
    else if (type == ConstantType::FieldRef) { this->firstRef = fRef; this->secRef = secondRef; }
    else if (type == ConstantType::MethodRef) { this->firstRef = fRef; this->secRef = secondRef; }
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
        table->methods.find(ident)->second[descKey]->varTable->findOrAddLocalVar("this", ths, 1, 1);

        // Заполнить таблицу локальных переменных.
        for (int i = 0; i < vec.size(); i++)
        {
            table->methods.find(ident)->second[descKey]->varTable->findOrAddLocalVar(vec[i].name, vec[i].typ, 1, 1);
        }
    }
    if (member->next != NULL)
    {
        err = _addMethodForClass(cls, table, member->next);
    }
    return err; 
}

static SemanticError * _fillMethodTableForClass(struct ClassNode * clas, class ClassTableElement* elem)
{
    struct SemanticError * err = NULL;
    if (clas->members != NULL)
    {
        if (clas->members->first != NULL)
        {
            err =  _addMethodForClass(elem, elem->methods, clas->members->first);
        }
    }
    return err;
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

struct TypeNode * Type::toTypeNode()
{
    struct TypeNode * t = (struct TypeNode *)malloc(sizeof(struct TypeNode));
    if (this->typ == TypeType::_CLS)
    {
        t->type = TypeType::_CLS;
        t->id = 0;
        t->ident = (char*)this->className.c_str();
        t->complexType = NULL;
    }
    else if (this->typ == TypeType::_ARRAY)
    {
        t->type = TypeType::_ARRAY;
        t->id = 0;
        t->complexType = (struct TypeNode *)malloc(sizeof(struct TypeNode));
        t->complexType->id = 0;
        t->complexType->ident = (char*)this->className.c_str();
        t->complexType->type = TypeType::_CLS;
    }
    return t;
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

LocalVariableElement::LocalVariableElement(std::string nam, int ident, class Type * t, int isCnst, int isInitial)
{
    this->id = ident;
    this->name = nam;
    this->typ = t;
    this->isConst = isCnst;
    this->isInit = isInitial;
}

int LocalVariableTable::findOrAddLocalVar(std::string name, class Type * typ, int isCnst, int isInit)
{
    if (items.find(name) == items.cend()) // Если переменная с указанным именем не найдена.
    {
        items[name] = new LocalVariableElement(name, maxId++, typ, isCnst, isInit);
        return items[name]->id;
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

            std::string ident = std::string(curElem->func->identifier);
      
            // Получить возвращаемое значение метода.
            class Type *  retVal = new Type(curElem->func->returnValue);

            // Получить набор параметров метода.
            std::vector<FuncParam> vec;
            if (curElem->func->params != NULL)
            {
                struct VarDeclarationNode * par = NULL;
                if (curElem->func->params->first != NULL)
                    par = curElem->func->params->first;

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
                if (mainClass->methods->methods[ident].count(descKey) != 0) // Сообщить об ошибке, если такой метод существует.
                {
                    // TODO сообщение об ошибке.
                    std::string msg = "There is already a Function with the specified identifier and signature: ";
                    msg += ident;
                    msg += descKey;
                    return createSemanticError(4, msg.c_str());
                }
                else // Иначе
                {   
                    // Создать запись в таблице констант класса.
                    int nam = mainClass->constants->findOrAddConstant(ConstantType::Utf8, ident); // Добавить или получить номер константы названия метода.
                    int dsc = mainClass->constants->findOrAddConstant(ConstantType::Utf8, desc); // Добавить или получить номер константы дескриптора метода.
                    
                    mainClass->methods->methods.find(ident)->second[descKey] = new MethodTableElement(nam, dsc, ident, desc, curElem->func->body, retVal, vec); // Добавить новый элемент в таблицу методов.
                    FunctionTable::items.find(ident)->second[descKey] = new FunctionTableElement(nam, dsc, ident, desc, curElem->func->body, retVal, vec);
                }
            }
            else
            {
                
                // Создать запись в таблице констант класса.
                int nam = mainClass->constants->findOrAddConstant(ConstantType::Utf8, ident); // Добавить или получить номер константы названия метода.
                int dsc = mainClass->constants->findOrAddConstant(ConstantType::Utf8, desc); // Добавить или получить номер константы дескриптора метода.

                mainClass->methods->methods[ident] = std::map<std::string, MethodTableElement *>();
                mainClass->methods->methods.find(ident)->second[descKey] = new MethodTableElement(nam, dsc, ident, desc, curElem->func->body, retVal, vec); // Добавить новый элемент в таблицу методов.*/
                FunctionTable::items[ident] = std::map<std::string, class FunctionTableElement*>();
                FunctionTable::items.find(ident)->second[descKey] = new FunctionTableElement(nam, dsc, ident, desc, curElem->func->body, retVal, vec);
            }

            // Заполнить таблицу локальных переменных.
            for (int i = 0; i < vec.size(); i++)
            {
                FunctionTable::items.find(ident)->second[descKey]->varTable->findOrAddLocalVar(vec[i].name, vec[i].typ, 1,1);
                mainClass->methods->methods.find(ident)->second[descKey]->varTable->findOrAddLocalVar(vec[i].name, vec[i].typ, 1,1);
            }
        }

        curElem = curElem->next; // Перейти к следующему элементу.
    }
    return err;
}

static SemanticError * _addConstructor(class ClassTableElement * classElem, struct ClassNode * classNode)
{
    struct SemanticError * err = NULL;
    std::string methName = "<init>"; // Создать имя конструктора для класса.
    std::string descr = "(";

    Type * retVal = new Type();
    retVal->typ = TypeType::_CLS;
    retVal->className = classElem->clsName;
    // Получить набор параметров метода.
    std::vector<FuncParam> vec;
    if (classNode->constr != NULL)
    {
        
        if (classNode->constr->params != NULL)
        {

            // Для каждого параметра класса...
            struct ClassParamNode * par = NULL;
            if (classNode->constr->params->first != NULL)
                par = classNode->constr->params->first;

            while (par != NULL)
            {
                std::string ident;
                Type * typ = NULL;
                if (par->valVar != NULL)
                {
                    ident = par->valVar->varValId;
                    typ = new Type(par->valVar->varValType);
                }
                else if (par->varDecl != NULL)
                {
                    ident = par->varDecl->identifier;
                    typ = new Type(par->varDecl->type);
                }
                vec.push_back(FuncParam(ident, typ));
                par = par->next; // Перейти к следующему элементу.
            }
        }
        for (int i = 0; i < (int)vec.size(); i++)
        {
            if (vec[i].typ->typ == TypeType::_CLS)
                descr += "L";

            else if (vec[i].typ->typ == TypeType::_ARRAY)
                descr += "[L";

            descr += vec[i].typ->className;
            descr += ";";
        }
    }
    descr += ")";
    std::string descKey = descr;
    descr += "V";
    
    if (classElem->methods->methods.count(methName) != 0)
    {
        if (classElem->methods->methods.find(methName)->second.find(descKey) != classElem->methods->methods.find(methName)->second.cend()) // Сообщить об ошибке, если такой метод существует.
        {
            // TODO сообщение об ошибке.
            std::string msg = "There is already a contructor with the specified params.";
            
            return createSemanticError(4, msg.c_str());
        }
        else // Иначе
        {   
            // Создать запись в таблице констант класса.
            int nam = classElem->constants->findOrAddConstant(ConstantType::Utf8, methName); // Добавить или получить номер константы названия метода.
            int dsc = classElem->constants->findOrAddConstant(ConstantType::Utf8, descr); // Добавить или получить номер константы дескриптора метода.
                    
            classElem->methods->methods.find(methName)->second[descKey] = new MethodTableElement(nam, dsc, methName, descr, /*curElem->func->body*/NULL, retVal, vec); // Добавить новый элемент в таблицу методов.
        }
    }
    else
    {
        // Создать запись в таблице констант класса.
        int nam = classElem->constants->findOrAddConstant(ConstantType::Utf8, methName); // Добавить или получить номер константы названия метода.
        int dsc = classElem->constants->findOrAddConstant(ConstantType::Utf8, descr); // Добавить или получить номер константы дескриптора метода.

        classElem->methods->methods[methName] = std::map<std::string, MethodTableElement *>();
        classElem->methods->methods.find(methName)->second[descKey] = new MethodTableElement(nam, dsc, methName, descr, /*curElem->func->body*/NULL, retVal, vec); // Добавить новый элемент в таблицу методов.*/
    }    


    return err;
}
struct SemanticError * attributeExpression(struct ExpressionNode * expression, class MethodTableElement * mElem);

struct SemanticError * attributingAndFillingLocalsInStatement(class MethodTableElement * meth, struct StatementNode * curStmt)
{
    struct SemanticError * err = NULL;

    if (curStmt->type == StatementType::_EXPRESSION)
    {
        err = attributeExpression(curStmt->expression, meth);
        if (err != NULL) return err;
    }
    if (curStmt->type == StatementType::_VAL || curStmt->type == StatementType::_VAR)
    {
                // Попытаться найти переменную с указанным именем.
                if (meth->varTable->items.count(curStmt->varValId) != 0) // Если в таблице уже имеется такая переменная...
                {
                    // Сообщить об ошибке.
                    std::string msg = "There is already a local var with the identifier: ";
                    msg += curStmt->varValId;
                    return createSemanticError(4, msg.c_str());
                }
                else // Иначе...
                {
                    int isCnst = 0;
                    int isInit = 0;
                    if (curStmt->type == StatementType::_VAL) isCnst = 1; // Является ли переменная константой.
                    if (curStmt->expression != NULL) isInit = 1; // Явялется ли переменная инициализированной.
                    if (curStmt->expression != NULL)
                    {
                        if (curStmt->expression->type == ExpressionType::_ASSIGNMENT)
                        {
                            std::string msg = "Assignments are not allowed in this context.";
                            return createSemanticError(13, msg.c_str());
                        }
                        err = attributeExpression(curStmt->expression, meth);
                        if (err != NULL) return err;
                    }
                    if (curStmt->varValType != NULL) // Если у переменной уже имеется тип.
                    {
                        if (isInit)
                        { 
                            Type left = Type(curStmt->varValType);
                            Type right = Type(curStmt->expression->typ);
                            if (!left.isReplacable(right))
                            {
                                std::string msg = "Type mismatch in assignment : ";
                                msg += left.className;
                                msg += " and ";
                                msg += right.className;
                                return createSemanticError(15, msg.c_str());    
                            }
                        }

                        meth->varTable->items[curStmt->varValId] = new LocalVariableElement(curStmt->varValId, meth->varTable->maxId++, new Type(curStmt->varValType), isCnst, isInit);
                    }
                    else // Иначе...
                    {
                        // Сообщить об ошибке - отсуствии в текущей версии компилятора.
                        std::string msg = "Autotypes are not supported in this version.";
                        return createSemanticError(10, msg.c_str());
                        /*
                        if (isInit == 1) // Если переменная инициализируется...
                        {
                            if (curStmt->expression->typ != NULL) meth->varTable->items[curStmt->varValId] = new LocalVariableElement(curStmt->varValId, func->varTable->maxId++, new Type(curStmt->expression->typ), isCnst, isInit);
                        }*/
                    }
                } 
    }

    if (curStmt->type == StatementType::_DOWHILE || curStmt->type == StatementType::_WHILE)
    {
        err = attributeExpression(curStmt->condition, meth);
        if (err != NULL) return err;
        Type etalon = Type();
        etalon.className = "JavaRTL/Boolean";
        etalon.typ = _CLS;
        Type t = Type(curStmt->condition->typ);
        if (!etalon.isReplacable(t))
        {
            std::string msg = "Only Boolean allowed as condition type.";
            return createSemanticError(16, msg.c_str());
        }
        if (curStmt->singleBody != NULL) {
            err = attributingAndFillingLocalsInStatement(meth, curStmt->singleBody);
            if(err != NULL) return err;
        }
        if (curStmt->complexBody != NULL) {
            if (curStmt->complexBody->first != NULL)
            err = attributingAndFillingLocalsInStatement(meth, curStmt->complexBody->first);
            if(err != NULL) return err;
        }
    }

    if (curStmt->type == StatementType::_RETURN)
    {
        Type * ret = meth->retType;
        Type t;
        if (curStmt->expression != NULL) t = Type(curStmt->expression->typ);
        if (curStmt->expression == NULL || !(ret->isReplacable(t)))
        {
            std::string msg = "Return type mismatch in function ";
            msg += meth->strName;
            msg += meth->strDesc;
            return createSemanticError(23, msg.c_str());
        }
        err = attributeExpression(curStmt->expression, meth);
        if (err != NULL) return err;
    }

    if (curStmt->next != NULL)
    {
        err = attributingAndFillingLocalsInStatement(meth, curStmt->next);
    }
    return err;
}

struct SemanticError * attributingAndFillingLocals(class MethodTableElement * meth)
{
    struct SemanticError * err = NULL;
    if (meth->start != NULL)
    {
        struct StatementNode * curStmt = meth->start->first;
        if (curStmt != NULL)
        err = attributingAndFillingLocalsInStatement(meth, curStmt);
          
    }
    return err;
}

struct SemanticError * attributeExpression(struct ExpressionNode * expression, class MethodTableElement * mElem)
{
    struct SemanticError * err = NULL;
    // Если у переменной отсутствует тип...
    if (expression->typ == NULL)
    {
        struct TypeNode * leftType = NULL;
        struct TypeNode * rightType = NULL;
        if (expression->left != NULL)
        {
            if (expression->left->type == ExpressionType::_ASSIGNMENT)
            {
                std::string msg = "Assignments are not allowed in this context.";
                return createSemanticError(13, msg.c_str());
            }
            if (expression->left->typ == NULL) err = attributeExpression(expression->left, mElem);
            if (err != NULL) {if (expression->type != ExpressionType::_ASSIGNMENT) {return err;} else {if (err->code != 17) return err;}}
            leftType = expression->left->typ;
        }
        if (expression->right != NULL)
        {
            if (expression->right->type == ExpressionType::_ASSIGNMENT)
            {
                std::string msg = "Assignments are not allowed in this context.";
                return createSemanticError(13, msg.c_str());
            }
            if (expression->right->typ == NULL) err = attributeExpression(expression->right, mElem);
            if (err != NULL) return err;
            rightType = expression->right->typ;
        }

        // Определить типы параметров у вызовов функций или методов.
        if (expression->type == ExpressionType::_FUNC_CALL || expression->type == ExpressionType::_METHOD_ACCESS)
        {
            std::string id = expression->identifierString; // Получить идентификатор функции или метода.
            struct ExpressionListNode * params = expression->params;
            struct ExpressionNode * curExpr = params->first;
            while(curExpr != NULL) // Пока есть параметры...
            {
                if (curExpr->type == ExpressionType::_ASSIGNMENT)
                {
                    std::string msg = "Passing parameters by Identifier are not supported in this version.";
                    return createSemanticError(10, msg.c_str());
                }
                err = attributeExpression(curExpr, mElem);
                if (err != NULL) return err;
                curExpr = curExpr->next; // Перейти к следующему параметру.
            }

            // Сформировать дескриптор набора параметров.
            std::string desc = "(";
            curExpr = params->first;
            while(curExpr != NULL) // Пока есть параметры...
            {
                Type * typ = new Type(curExpr->typ);
                if (curExpr->typ->type == TypeType::_CLS) desc += "L";
                if (curExpr->typ->type == TypeType::_ARRAY) desc += "[L";
                desc += typ->className;
                desc += ";";
                curExpr = curExpr->next; // Перейти к следующему параметру.
            }
            desc += ")";
            if (expression->type == ExpressionType::_FUNC_CALL)
            {
                if (FunctionTable::items.count(id) == 0)
                {
                    std::string msg = "Function candidate is missing : ";
                    msg += id;
                    return createSemanticError(7, msg.c_str());
                }
                else 
                {
                    if (FunctionTable::items[id].count(desc) == 0)
                    {
                        std::string msg = "Function candidate is missing : ";
                        msg += id;
                        msg += desc;
                        return createSemanticError(8, msg.c_str());
                    }
                    else
                    {
                        expression->typ = FunctionTable::items[id][desc]->retType->toTypeNode();
                    }
                }
            }
            else if (expression->type == ExpressionType::_METHOD_ACCESS)
            {
                std::string clsType = (new Type(leftType))->className;
                if (ClassTable::items.count(clsType) == 0)
                {
                    std::string msg = "Class declaration is missing : ";
                    msg += clsType;
                    return createSemanticError(6, msg.c_str());
                }
                else
                {
                    if (ClassTable::items[clsType]->methods->methods.count(id) == 0)
                    {
                        std::string msg = "Method declaration is missing : ";
                        msg += id;
                        msg += " in class ";
                        msg += clsType;
                        return createSemanticError(7, msg.c_str());
                    }
                    else
                    {
                        if (ClassTable::items[clsType]->methods->methods[id].count(desc) == 0)
                        {
                            std::string msg = "Method candidate is missing : ";
                            msg += id;
                            msg += desc;
                            msg += " in class ";
                            msg += clsType;
                            return createSemanticError(8, msg.c_str());
                        }
                        else
                        {
                            expression->typ = ClassTable::items[clsType]->methods->methods[id][desc]->retType->toTypeNode();
                        }   
                    }
                }
            }
        }
        // Определить тип при создании массива.
        else if (expression->type == ExpressionType::_ARRAY_CREATION) 
        {
            if (expression->right->type == ExpressionType::_ARRAY_CREATION) // Сообщить об ошибке при попытке создания многомерного массива.
            {
                std::string msg = "Multidimensional arrays are not supported in this version.";
                return createSemanticError(10, msg.c_str());
            }
            else
            {
                struct TypeNode * node = (struct TypeNode *)malloc(sizeof(struct TypeNode));
                node->type = _ARRAY;
                node->complexType = rightType;
                node->ident = NULL;
                expression->typ = node;
            }
        }

        else if (expression->type == ExpressionType::_ARRAY_ACCESS)
        {
            if (leftType->type != TypeType::_ARRAY)
            {
                std::string msg = "Addressing to a non-container object.";
                return createSemanticError(11, msg.c_str());
            }
            if (rightType->type == TypeType::_CLS)
            {
                if (std::string(rightType->ident) != "JavaRTL/Int")
                {
                    std::string msg = "Incorrect key to an array element.";
                    return createSemanticError(12, msg.c_str());
                }
                else
                {
                    Type * arrayType = new Type(leftType->complexType);
                    expression->typ = arrayType->toTypeNode();
                }
            }
            else
            {
                std::string msg = "Incorrect key to an array element.";
                return createSemanticError(12, msg.c_str());
            }
        }

        // Определить тип для идентификатора.
        else if (expression->type == ExpressionType::_IDENTIFIER)
        {
            // Сообщить об ошибке, если в таблице отсуствует такая переменная.
            if (mElem->varTable->items.count(expression->identifierString) == 0)
            {
                std::string msg = "Using of an undeclared variable: ";
                msg += expression->identifierString;
                return createSemanticError(9, msg.c_str());
            }
            else
            {
                expression->typ = mElem->varTable->items[expression->identifierString]->typ->toTypeNode();
                if (mElem->varTable->items[expression->identifierString]->isInit == 0)
                {
                    std::string msg = "Using of an uninitialized variable: ";
                    msg += expression->identifierString;
                    return createSemanticError(17, msg.c_str());
                }
            }
        }
        else if (expression->type == ExpressionType::_BRACKETS)
        {
            expression->typ = leftType;
        }
        else if (expression->type == ExpressionType::_ASSIGNMENT)
        {
            if (expression->left->type == ExpressionType::_ARRAY_ACCESS || expression->left->type == ExpressionType::_IDENTIFIER)
            {
                if (expression->left->type == ExpressionType::_IDENTIFIER)
                {
                    // Проверить, является ли переменная константой.
                    if (mElem->varTable->items[expression->left->identifierString]->isConst != 0)
                    {
                        if (mElem->varTable->items[expression->left->identifierString]->isInit != 0)  // Проверить, инициализирована ли переменная, если константа.
                        {
                            std::string msg = "Val can not be reassignment : ";
                            msg += expression->left->identifierString;
                            msg += " in function ";
                            msg += mElem->strName;
                            return createSemanticError(15, msg.c_str());   
                        }
                    }
                    mElem->varTable->items[expression->left->identifierString]->isInit = 1;
                }
                
                // Проверить типы слева и справа от присваивания.
                Type left = Type(expression->left->typ);
                Type right = Type(expression->right->typ);
                if (!left.isReplacable(right))
                {
                    std::string msg = "Type mismatch in assignment : ";
                    msg += left.className;
                    msg += " and ";
                    msg += right.className;
                    return createSemanticError(15, msg.c_str());    
                }
                else 
                {
                    struct TypeNode * node = (struct TypeNode *)malloc(sizeof(struct TypeNode));
                    node->type = _CLS;
                    node->complexType = NULL;
                    node->ident = (char*)std::string("JavaRTL/Unit").c_str();
                    expression->typ = node;
                }
            }
            else
            {
                std::string msg = "Assignments are not allowed in this context (not a variable).";
                return createSemanticError(13, msg.c_str());
            }
        }
    }
    return err;
}

void fillMethodRefs(class ClassTableElement * cls);
void fillLiterals(class ClassTableElement * cls);
void fillConstantTableForClass(class ClassTableElement * cls)
{
    cls->constants->findOrAddConstant(ConstantType::Utf8, "Code");
    fillMethodRefs(cls);

}

void fillMethodRefsInExpression(struct ExpressionNode * expression, class ClassTableElement * cls)
{
        if (expression->left != NULL)
        {
            fillMethodRefsInExpression(expression->left, cls);
        }
        if (expression->right != NULL)
        {
            fillMethodRefsInExpression(expression->right, cls);
        }
        if (expression->type == ExpressionType::_FUNC_CALL || expression->type == ExpressionType::_METHOD_ACCESS)
        {
            
            std::string id = expression->identifierString; // Получить идентификатор функции или метода.
            struct ExpressionListNode * params = expression->params;
            struct ExpressionNode * curExpr = NULL;
            if(params != NULL) curExpr = params->first;
            
            while(curExpr != NULL) // Пока есть параметры...
            {
                fillMethodRefsInExpression(curExpr, cls);
                curExpr = curExpr->next; // Перейти к следующему параметру.
            }
 
            // Сформировать дескриптор набора параметров.
            std::string desc = "(";
            if(params != NULL) curExpr = params->first;
            while(curExpr != NULL) // Пока есть параметры...
            {
                Type * typ = new Type(curExpr->typ);
                if (curExpr->typ->type == TypeType::_CLS) desc += "L";
                if (curExpr->typ->type == TypeType::_ARRAY) desc += "[L";
                desc += typ->className;
                desc += ";";
                curExpr = curExpr->next; // Перейти к следующему параметру.
            }
            desc += ")";

            if (expression->type == ExpressionType::_FUNC_CALL && expression->fromLit == BaseLiteral::_FROM_NONE)
            {
                Type * ret = FunctionTable::items[id][desc]->retType;
                if (ret->typ == TypeType::_ARRAY) desc += "[L";
                else desc += "L";
                desc += ret->className;
                desc += ";";
                int nam = cls->constants->findOrAddConstant(ConstantType::Utf8, id);
                int dsc = cls->constants->findOrAddConstant(ConstantType::Utf8, desc);
                int NaT = cls->constants->findOrAddConstant(ConstantType::NameAndType, "", NULL, NULL,nam, dsc);
                if (id == "print" || id == "println" || id == "readLine")
                {
                    int ioN = cls->constants->findOrAddConstant(ConstantType::Utf8,"JavaRTL/InputOutput");
                    int ioCl = cls->constants->findOrAddConstant(ConstantType::Class,"",NULL,NULL,ioN);
                    int mRef = cls->constants->findOrAddConstant(ConstantType::MethodRef, "", NULL, NULL, ioCl, NaT);
                }
                else
                    int mRef = cls->constants->findOrAddConstant(ConstantType::MethodRef, "", NULL, NULL, cls->thisClass, NaT);

            }
            else if (expression->type == ExpressionType::_METHOD_ACCESS)
            {
                // Получить ссылку на константу класса, в котором находится метод.
                struct ExpressionNode * obj = expression->left;
                std::string className = obj->typ->ident;
                
                int clsNameConst = cls->constants->findOrAddConstant(ConstantType::Utf8, className);
                int clsConst = cls->constants->findOrAddConstant(ConstantType::Class, "", NULL, NULL, clsNameConst);
                Type * ret = ClassTable::items[className]->methods->methods[id][desc]->retType;
                if (ret->typ == TypeType::_ARRAY) desc += "[L";
                else desc += "L";
                desc += ret->className;
                desc += ";";
                int nam = cls->constants->findOrAddConstant(ConstantType::Utf8, id);
                int dsc = cls->constants->findOrAddConstant(ConstantType::Utf8, desc);
                int NaT = cls->constants->findOrAddConstant(ConstantType::NameAndType, "", NULL, NULL,nam, dsc);
                int mRef = cls->constants->findOrAddConstant(ConstantType::MethodRef, "", NULL, NULL, clsConst, NaT);
            }
        }
}

void fillMethodRefsInStatement(struct StatementNode * stmt, class ClassTableElement * cls)
{
    if (stmt->type == StatementType::_EXPRESSION)
    {
        fillMethodRefsInExpression(stmt->expression, cls);
    }
    else if (stmt->type == StatementType::_VAL || stmt->type == StatementType::_VAR)
    {
        if (stmt->expression != NULL) fillMethodRefsInExpression(stmt->expression, cls);
    }
    else if (stmt->type == StatementType::_DOWHILE || stmt->type == StatementType::_WHILE)
    {
        fillMethodRefsInExpression(stmt->condition, cls);
        if (stmt->singleBody != NULL) fillMethodRefsInStatement(stmt->singleBody, cls);
        if (stmt->complexBody != NULL) fillMethodRefsInStatement(stmt->complexBody->first, cls);
    }
    if (stmt->next != NULL) fillMethodRefsInStatement(stmt->next, cls);
}

void fillMethodRefs(class ClassTableElement * cls)
{
    for(auto it = cls->methods->methods.begin(); it != cls->methods->methods.end(); ++it)
    {
        for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
        {
            struct StatementNode * curStmt = iter->second->start->first;
            fillMethodRefsInStatement(curStmt, cls);
        }
    }
}

void fillLiteralsInExpression(struct ExpressionNode * expression, class ClassTableElement * cls)
{
    if (expression->fromLit == BaseLiteral::_FROM_BOOLEAN)
    {
        std::string clsName = "JavaRTL/Boolean";
        std::string methodName = "<init>";
        std::string desc = "(I)V";
        std::string fd = "I";
        int fdn = cls->constants->findOrAddConstant(Utf8, fd);
        std::string fn = "_ivalue";
        int fnn = cls->constants->findOrAddConstant(Utf8, fn);
        int fnt = cls->constants->findOrAddConstant(NameAndType, "", 0, 0, fnn, fdn);
        int clsNameConst = cls->constants->findOrAddConstant(ConstantType::Utf8, clsName);
        int clsConst = cls->constants->findOrAddConstant(ConstantType::Class, "", NULL, NULL, clsNameConst);
        int methodNameConst = cls->constants->findOrAddConstant(ConstantType::Utf8, methodName);
        int descConst = cls->constants->findOrAddConstant(ConstantType::Utf8, desc);
        int NaT = cls->constants->findOrAddConstant(ConstantType::NameAndType, "", NULL, NULL, methodNameConst, descConst);
        int mRef = cls->constants->findOrAddConstant(ConstantType::MethodRef, "", NULL, NULL, clsConst, NaT);
        int fRef = cls->constants->findOrAddConstant(ConstantType::FieldRef, "", NULL, NULL, clsConst, fnt);
    }
    else if (expression->fromLit == BaseLiteral::_FROM_CHAR)
    {
        std::string clsName = "JavaRTL/Char";
        std::string methodName = "<init>";
        std::string desc = "(C)V";
        int clsNameConst = cls->constants->findOrAddConstant(ConstantType::Utf8, (char*)clsName.c_str());
        int clsConst = cls->constants->findOrAddConstant(ConstantType::Class, "", NULL, NULL, clsNameConst);
        int methodNameConst = cls->constants->findOrAddConstant(ConstantType::Utf8, (char*)methodName.c_str());
        int descConst = cls->constants->findOrAddConstant(ConstantType::Utf8, (char*)desc.c_str());
        int NaT = cls->constants->findOrAddConstant(ConstantType::NameAndType, "", NULL, NULL, methodNameConst, descConst);
        int mRef = cls->constants->findOrAddConstant(ConstantType::MethodRef, "", NULL, NULL, clsConst, NaT);
    }
    else if (expression->fromLit == BaseLiteral::_FROM_STRING)
    {
        int str = cls->constants->findOrAddConstant(ConstantType::Utf8, getSafeCString(expression->stringValue));
        int strConst = cls->constants->findOrAddConstant(ConstantType::String, "", NULL, NULL, str);
        std::string clsName = "JavaRTL/String";
        std::string methodName = "<init>";
        std::string desc = "(Ljava/lang/String;)V";
        int clsNameConst = cls->constants->findOrAddConstant(ConstantType::Utf8, (char*)clsName.c_str());
        int clsConst = cls->constants->findOrAddConstant(ConstantType::Class, "", NULL, NULL, clsNameConst);
        int methodNameConst = cls->constants->findOrAddConstant(ConstantType::Utf8, (char*)methodName.c_str());
        int descConst = cls->constants->findOrAddConstant(ConstantType::Utf8, (char*)desc.c_str());
        int NaT = cls->constants->findOrAddConstant(ConstantType::NameAndType, "", NULL, NULL, methodNameConst, descConst);
        int mRef = cls->constants->findOrAddConstant(ConstantType::MethodRef, "", NULL, NULL, clsConst, NaT);
    }
    else if (expression->fromLit == BaseLiteral::_FROM_INT)
    {
        std::string clsName = "JavaRTL/Int";
        std::string methodName = "<init>";
        std::string desc = "(I)V";
        int clsNameConst = cls->constants->findOrAddConstant(ConstantType::Utf8, (char*)clsName.c_str());
        int clsConst = cls->constants->findOrAddConstant(ConstantType::Class, "", NULL, NULL, clsNameConst);
        int methodNameConst = cls->constants->findOrAddConstant(ConstantType::Utf8, (char*)methodName.c_str());
        int descConst = cls->constants->findOrAddConstant(ConstantType::Utf8, (char*)desc.c_str());
        int NaT = cls->constants->findOrAddConstant(ConstantType::NameAndType, "", NULL, NULL, methodNameConst, descConst);
        int mRef = cls->constants->findOrAddConstant(ConstantType::MethodRef, "", NULL, NULL, clsConst, NaT);
    }
    else if (expression->fromLit == BaseLiteral::_FROM_UNIT)
    {
        std::string clsName = "JavaRTL/Unit";
        std::string methodName = "<init>";
        std::string desc = "()V";
        int clsNameConst = cls->constants->findOrAddConstant(ConstantType::Utf8, (char*)clsName.c_str());
        int clsConst = cls->constants->findOrAddConstant(ConstantType::Class, "", NULL, NULL, clsNameConst);
        int methodNameConst = cls->constants->findOrAddConstant(ConstantType::Utf8, (char*)methodName.c_str());
        int descConst = cls->constants->findOrAddConstant(ConstantType::Utf8, (char*)desc.c_str());
        int NaT = cls->constants->findOrAddConstant(ConstantType::NameAndType, "", NULL, NULL, methodNameConst, descConst);
        int mRef = cls->constants->findOrAddConstant(ConstantType::MethodRef, "", NULL, NULL, clsConst, NaT);
    }
    if(expression->left != NULL)
    {
        fillLiteralsInExpression(expression->left, cls);
    }
    if (expression->right != NULL)
    {
        fillLiteralsInExpression(expression->right, cls);
    }
    if (expression->params != NULL)
    {
        struct ExpressionNode * first = expression->params->first;
        while (first != NULL)
        {
            fillLiteralsInExpression(first, cls);
            first = first->next;
        }
    }
}

void fillLiteralsInStatement(struct StatementNode * stmt, struct ClassTableElement * cls)
{
    if (stmt->type == StatementType::_EXPRESSION)
    {
      
        fillLiteralsInExpression(stmt->expression, cls);
    }
    else if (stmt->type == StatementType::_RETURN)
    {
        fillLiteralsInExpression(stmt->expression, cls);
    }

    else if (stmt->type == StatementType::_VAL || stmt->type == StatementType::_VAR)
    {
        if (stmt->expression != NULL) fillLiteralsInExpression(stmt->expression, cls);
    }
    if(stmt->next!= NULL)
    {   
        fillLiteralsInStatement(stmt->next, cls);
    }
}

void fillLiterals(class ClassTableElement * cls)
{
    for(auto it = cls->methods->methods.begin(); it != cls->methods->methods.end(); ++it)
    {
        for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
        {
            struct StatementNode * curStmt = iter->second->start->first;
            fillLiteralsInStatement(curStmt, cls);
        }
    }
}
