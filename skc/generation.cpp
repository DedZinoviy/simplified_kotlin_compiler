#include "generation.hpp"

std::vector<char> generateBytesForConstantTable(class ConstantTable * table);
std::vector<char> generateCodeForIdentifier(struct ExpressionNode * expr, class MethodTableElement * mElem);
std::vector<char> generateCodeForFunctionCall(struct ExpressionNode * expr, class ClassTableElement * cElem, class MethodTableElement * mElem);
std::vector<char> generateCodeForLiteralCreation(struct ExpressionNode * expr, class ClassTableElement * cElem);
std::vector<char> generateCodeForExpression(struct ExpressionNode* expr, class ClassTableElement* cElem, class MethodTableElement* mElem);
std::vector<char> generateMethodCode(class MethodTableElement * mElem, class ClassTableElement * cElem);
std::vector<char> generateCodeForStatement(struct StatementNode* stmt, class ClassTableElement* classElem, class MethodTableElement* mElem);
std::vector<char> generateCodeForExpressionStatement(struct StatementNode* stmt, class ClassTableElement* cElem, class MethodTableElement* mElem);
std::vector<char> generateCodeForReturnStatement(struct StatementNode *stmt, class ClassTableElement * cElem, class MethodTableElement * mElem);
std::vector<char> generateCodeForMethodAccess(struct ExpressionNode * expr, class ClassTableElement * cElem, class MethodTableElement * mElem);
std::vector<char> generateMain(class ClassTableElement *cls,  MethodTableElement * main);
void generateClassFile(std::string className)
{
    // Инициализация.
    std::string fileName = className + ".class";
    std::ofstream out(fileName, std::ios::out | std::ios::binary);

    // Ввод магических констант.
    out.write(FileConstants::magicConstant, 4);
    out.write(FileConstants::smallVersion, 2);
    out.write(FileConstants::bigVersion, 2);
    ClassTableElement * elem = ClassTable::items[className];
    std::stringstream sstream;
    printf("Constants count :%d\n", elem->constants->constants.size());


    std::vector<char> tableLen = intToByteVector(elem->constants->constants.size() + 1, 2);

    out.write(tableLen.data(), tableLen.size());
    sstream.clear();

    std::vector<char> data = generateBytesForConstantTable(elem->constants);
    data.push_back(0x00);
	data.push_back(0x21);

    std::vector<char> thisCls = intToByteVector(elem->thisClass, 2);
    std::vector<char> parentCls = intToByteVector(elem->superClass, 2);
    appendArrayToByteVector(&data, thisCls.data(), thisCls.size());
    appendArrayToByteVector(&data, parentCls.data(), parentCls.size());
    std::vector<char> interfaceCount = intToByteVector(0, 2);
    std::vector<char> fieldCount = intToByteVector(0, 2);

	for (auto i = elem->constants->constants.begin(); i != elem->constants->constants.end(); ++i)
	{
		if (i->second->cnst == Utf8)
		{
			printf("Utf8 : %s\n", i->second->string.c_str());
		}
		
		if (i->second->cnst == String)
		{
			printf("String : %d\n", i->second->firstRef);
		}
		
		if (i->second->cnst == Class)
		{
			printf("Class : %d\n", i->second->firstRef);
		}
		
		if (i->second->cnst == NameAndType)
		{
			printf("NaT : %d\n", i->second->firstRef, i->second->secRef);
		}
	}

	// Посчитать количество методов.
	int mCount = 0;
	mCount = 2;
	std::vector<char> cd = generateMethodCode(elem->methods->methods["main"]["()"], elem);
	
	std::vector<char> m = generateMain(elem, elem->methods->methods["main"]["()"]);
	appendArrayToByteVector(&cd, m.data(),m.size());
	/*for (auto i = elem->methods->methods.begin(); i != elem->methods->methods.end(); ++i)
	{
		for (auto it = i->second.begin(); it != i->second.end(); ++it)
			mCount++;
	}*/

    std::vector<char> methodCount = intToByteVector(mCount, 2);

    std::vector<char> attributeCount = intToByteVector(0, 2);
    appendArrayToByteVector(&data, interfaceCount.data(), interfaceCount.size());
    appendArrayToByteVector(&data, fieldCount.data(), fieldCount.size());
    appendArrayToByteVector(&data, methodCount.data(), methodCount.size());
	appendArrayToByteVector(&data, cd.data(), cd.size());
    appendArrayToByteVector(&data, attributeCount.data(), attributeCount.size());

    out.write(data.data(), data.size());
    // Закрытие файла.
    out.close();
}


std::vector<char> generateForEach(struct StatementNode * forEach)
{
    return std::vector<char>();
}

std::vector<char> generateBytesForConstantTableItem(class ConstantTableItem * elem);
std::vector<char> generateBytesForConstantTable(class ConstantTable * table)
{
	std::vector <char> res;
	for (auto iter = table->constants.cbegin(); iter != table->constants.cend(); ++iter) {
		std::vector<char> bytes = generateBytesForConstantTableItem(iter->second);
		appendArrayToByteVector(&res, bytes.data(), bytes.size());
	}
		
	return res;
}

std::vector<char> generateBytesForConstantTableItem(class ConstantTableItem * elem)
{
	std::vector<char> res = intToByteVector(elem->cnst, 1);
	
	// Добавление типа константы
	

	switch (elem->cnst)
	{
	case Utf8: {
		std::vector<char> len = intToByteVector(elem->string.length(), 2); //Размер строки в байтах
		char *str = new char[elem->string.length() + 1]; //Строка
		strcpy(str, elem->string.c_str());
		appendArrayToByteVector(&res, len.data(), len.size());
		appendArrayToByteVector(&res, str, elem->string.length());
		delete[] str;
	}
		break;
	case Integer: {
		std::vector<char> num = intToByteVector(elem->Integer, 4); //Число в байтах
		appendArrayToByteVector(&res, num.data(), num.size());
	}
		break;
	case String:
	case Class: {
		std::vector<char> ref = intToByteVector(elem->firstRef, 2); //Номер константы UTF-8
		appendArrayToByteVector(&res, ref.data(), ref.size());
	}
		break;
	case NameAndType: {
		std::vector<char> firstRef = intToByteVector(elem->firstRef, 2); //Номер константы UTF-8 с именем
		std::vector<char> secondRef = intToByteVector(elem->secRef, 2); //Номер константы UTF-8 с типом
		appendArrayToByteVector(&res, firstRef.data(), firstRef.size());
	    appendArrayToByteVector(&res, secondRef.data(), secondRef.size());
	}
		break;
	case FieldRef:
	case MethodRef: {
		std::vector<char> firstRef = intToByteVector(elem->firstRef, 2); //Номер константы Class с классом
		std::vector<char> secondRef = intToByteVector(elem->secRef, 2); //Номер константы NameAndType с типом и именем
		appendArrayToByteVector(&res, firstRef.data(), firstRef.size());
		appendArrayToByteVector(&res, secondRef.data(), secondRef.size());
	}
		break;
	default:
		break;
	}

	return res;
}

std::vector<char> generateMethodAttribute(class MethodTableElement * mElem, ClassTableElement * cElem)
{
	std::vector<char> res;

	int cd = cElem->constants->findOrAddConstant(Utf8, "Code");
	std::vector<char> codeAttributeSizeBytes = intToByteVector(cd, 2);
	appendArrayToByteVector(&res, codeAttributeSizeBytes.data(), codeAttributeSizeBytes.size());
	//std::vector<char> b = generateCodeForStatement(mElem->start->first, cElem, mElem);
	//appendArrayToByteVector(&res, b.data(), b.size());

	std::vector<char> codeBytes;
	if (mElem->start != NULL) {
		StatementNode * curStatement = mElem->start->first;
		while (curStatement != NULL) {
			std::vector<char> bytes = generateCodeForStatement(curStatement, cElem, mElem);
			appendArrayToByteVector(&codeBytes, bytes.data(), bytes.size());
			curStatement = curStatement->next;
		}
	}
	printf("Code bytes len: %d\n", codeBytes.size());

	//Добавление длины атрибута
	std::vector<char> lengthBytes = intToByteVector(12 + codeBytes.size(), 4);
	appendArrayToByteVector(&res, lengthBytes.data(), lengthBytes.size());

	//Добавление размера стека операндов
	std::vector<char> stackSizeBytes = intToByteVector(FileConstants::stackSize, 2);
	appendArrayToByteVector(&res, stackSizeBytes.data(), stackSizeBytes.size());

	//Добавление количества локальных переменных
	int localsSize = mElem->varTable->items.size();
	std::vector<char> localsSizeBytes = intToByteVector(localsSize, 2);
	appendArrayToByteVector(&res, localsSizeBytes.data(), localsSizeBytes.size());


	//Добавление длины байт-кода TODO: сделать
	std::vector<char> codeSizeBytes = intToByteVector(codeBytes.size(), 4);
	appendArrayToByteVector(&res, codeSizeBytes.data(), codeSizeBytes.size());

	//Добавление байт-кода
	appendArrayToByteVector(&res, codeBytes.data(), codeBytes.size());

	//Добавление количества записей в таблице исключений
	std::vector<char> exceptionTableSizeBytes = intToByteVector(0, 2);
	appendArrayToByteVector(&res, exceptionTableSizeBytes.data(), exceptionTableSizeBytes.size());

	//Добавление количества атрибутов
	std::vector<char> attributesCountBytes = intToByteVector(0, 2);
	appendArrayToByteVector(&res, attributesCountBytes.data(), attributesCountBytes.size());

	return res;
}

std::vector<char> generateMethodCode(class MethodTableElement * mElem, class ClassTableElement * cElem)
{
	std::vector<char> res;

	char publicStaticFlag[2] = { 0x00, 0x09 }; //ACC_PUBLIC + ACC_STATIC
	appendArrayToByteVector(&res, publicStaticFlag, 2);

		//Добавление имени метода
	std::vector<char> nameBytes = intToByteVector(mElem->methodName, 2);
	appendArrayToByteVector(&res, nameBytes.data(), nameBytes.size());
	
		// Добавление дескриптора метода
	std::vector<char> typeBytes = intToByteVector(mElem->descriptor, 2);
	appendArrayToByteVector(&res, typeBytes.data(), typeBytes.size());

	//Добавление атрибутов TODO:Code
		std::vector<char> codeAttributeSizeBytes = intToByteVector(1, 2);
	appendArrayToByteVector(&res, codeAttributeSizeBytes.data(), codeAttributeSizeBytes.size());
		std::vector<char> codeAttributeBytes = generateMethodAttribute(mElem, cElem);
		appendArrayToByteVector(&res, codeAttributeBytes.data(), codeAttributeBytes.size());

	return res;
}


std::vector<char> generateCodeForStatement(struct StatementNode *stmt, class ClassTableElement * classElem, class MethodTableElement * mElem)
{
	std::vector<char> res;
	if (stmt->type == _EXPRESSION)
	{
		return generateCodeForExpressionStatement(stmt, classElem, mElem);
	}
	else if (stmt->type == _RETURN)
	{
		return generateCodeForReturnStatement(stmt, classElem, mElem);
	}
	return res;
}

std::vector<char> generateCodeForExpressionStatement(struct StatementNode *stmt, class ClassTableElement * cElem, class MethodTableElement * mElem)
{
	return generateCodeForExpression(stmt->expression, cElem, mElem);
}

std::vector<char> generateCodeForReturnStatement(struct StatementNode *stmt, class ClassTableElement * cElem, class MethodTableElement * mElem)
{
	std::vector<char> res;
	std::vector<char> b = generateCodeForExpression(stmt->expression, cElem, mElem);
	appendArrayToByteVector(&res, b.data(), b.size());
	std::vector<char> ret = areturn();
	appendArrayToByteVector(&res, ret.data(), ret.size());
	return res;
}

std::vector<char> generateCodeForExpression(struct ExpressionNode * expr, class ClassTableElement * cElem, class MethodTableElement * mElem)
{
	if (expr->type == _IDENTIFIER)
	{
		return generateCodeForIdentifier(expr, mElem);
	}
	if (expr->type == _FUNC_CALL)
	{
		return generateCodeForFunctionCall(expr, cElem, mElem);
	}
	if (expr->type == _METHOD_ACCESS)
	{
		return generateCodeForMethodAccess(expr, cElem, mElem);
	}
}


std::vector<char> generateCodeForIdentifier(struct ExpressionNode * expr, class MethodTableElement * mElem)
{
	std::vector<char> res;
	
	if (mElem->varTable->items.count(expr->identifierString) != 0)
	{
		std::vector<char> bytes;
		if (mElem->varTable->items[expr->identifierString]->typ->className == "I")
		{
			bytes = iload(mElem->varTable->items[expr->identifierString]->id);
		}
		else
		{
			bytes = aload(mElem->varTable->items[expr->identifierString]->id);
		}
		appendArrayToByteVector(&res, bytes.data(), bytes.size());
	}
	else{ 
		std :: string msg = "Unknown identifier";
		throw new std::exception(msg.c_str());
	}
	return res;
}

std::vector<char> generateCodeForFunctionCall(struct ExpressionNode * expr, class ClassTableElement * cElem, class MethodTableElement * mElem)
{
	std::vector<char> res;
	if (expr->fromLit != _FROM_NONE)
	{
		return generateCodeForLiteralCreation(expr, cElem);
	}
	else
	{
		struct ExpressionNode * cur = NULL;
		if (expr->params != NULL) cur = expr->params->first;
		std::string desc = "(";
		while(cur != NULL)
		{
			std::vector<char> p = generateCodeForExpression(cur, cElem, mElem);
			appendArrayToByteVector(&res, p.data(), p.size());
			if (cur->typ->type == _ARRAY) desc += "[L";
			else desc += "L";
			desc += Type(cur->typ).className;
			desc += ";";
			cur = cur->next;
		}
		desc += ")";
		std::string keyDesc = desc;
		if (std::string(expr->identifierString) == "print" || std::string(expr->identifierString) == "println" || std::string(expr->identifierString) == "readLine")		
		{
			if (std::string(expr->identifierString) == "readLine") desc += "LJavaRTL/String;";
			else desc += "LJavaRTL/Unit;";
			int cu = cElem->constants->findOrAddConstant(Utf8, "JavaRTL/InputOutput");
			int cc = cElem->constants->findOrAddConstant(Class, "", 0,0,cu);
			int n = cElem->constants->findOrAddConstant(Utf8, expr->identifierString);
			int t = cElem->constants->findOrAddConstant(Utf8, desc);
			int nat = cElem->constants->findOrAddConstant(NameAndType, "", 0,0,n,t);
			int mRef = cElem->constants->findOrAddConstant(MethodRef, "", 0,0,cc,nat);
			std::vector<char> io = invokestatic(mRef);
			appendArrayToByteVector(&res, io.data(), io.size());
		}
	}
	return res;
}

std::vector<char> generateCodeForLiteralCreation(struct ExpressionNode * expr, class ClassTableElement * cElem)
{
	std::vector<char> res;
	int clas; 
	if (expr->fromLit == _FROM_INT)
	{
		int n = cElem->constants->findOrAddConstant(Utf8, "JavaRTL/Int");
		clas = cElem->constants->findOrAddConstant(Class, "",NULL,NULL,n);
		if (n != -1)
		{
			res = _new(clas);
			std::vector<char> dp = dup(); // dup
			appendArrayToByteVector(&res, dp.data(), dp.size());
			
			// Параметры
			
			// invokespecial
			int mn = cElem->constants->findOrAddConstant(Utf8, "<init>");
			int md = cElem->constants->findOrAddConstant(Utf8, "(I)V");
			int nat = cElem->constants->findOrAddConstant(NameAndType, "", 0, 0, mn, md);
			int mref = cElem->constants->findOrAddConstant(MethodRef, "", 0, 0, clas, nat);
			std::vector<char> is = invokespecial(mref);
		}
	}
	else if (expr->fromLit == _FROM_CHAR)
	{
		int n = cElem->constants->findOrAddConstant(Utf8, "JavaRTL/Char");
		clas = cElem->constants->findOrAddConstant(Class, "",NULL,NULL,n);
		if (n != -1)
		{
			res = _new(clas);
			std::vector<char> dp = dup(); // dup
			appendArrayToByteVector(&res, dp.data(), dp.size());
		}
	}
	else if (expr->fromLit == _FROM_STRING)
	{
		int n = cElem->constants->findOrAddConstant(Utf8, "JavaRTL/String");
		clas = cElem->constants->findOrAddConstant(Class, "",NULL,NULL,n);
		if (n != -1)
		{
			res = _new(clas);
			std::vector<char> dp = dup(); // dup
			appendArrayToByteVector(&res, dp.data(), dp.size());

			// Параметры.
			int utConst = cElem->constants->findOrAddConstant(Utf8, getSafeCString(expr->stringValue));
			int strConst = cElem->constants->findOrAddConstant(String, "", 0, 0, utConst);
			std::vector<char> ld = ldc(strConst);
			appendArrayToByteVector(&res, ld.data(), ld.size());

			int mn = cElem->constants->findOrAddConstant(Utf8, "<init>"); // invokespecial
			int md = cElem->constants->findOrAddConstant(Utf8, "(Ljava/lang/String;)V");
			int nat = cElem->constants->findOrAddConstant(NameAndType, "", 0, 0, mn, md);
			int mref = cElem->constants->findOrAddConstant(MethodRef, "", 0, 0, clas, nat);
			std::vector<char> is = invokespecial(mref);
			appendArrayToByteVector(&res, is.data(), is.size());
		}
	}
	else if (expr->fromLit == _FROM_BOOLEAN)
	{
		int n = cElem->constants->findOrAddConstant(Utf8, "JavaRTL/Boolean");
		clas = cElem->constants->findOrAddConstant(Class, "",NULL,NULL,n);
		if (n != -1)
		{
			res = _new(clas);
			std::vector<char> dp = dup(); // dup
			appendArrayToByteVector(&res, dp.data(), dp.size());
			// Параметры

			std::vector<char> z;
			if (expr->boolValue == 1)
				z = iconstBipushSipush(1);
			else if (expr->boolValue == 0)
				z = iconstBipushSipush(0);
			appendArrayToByteVector(&res, z.data(), z.size());

			int mn = cElem->constants->findOrAddConstant(Utf8, "<init>"); // invokespecial
			int md = cElem->constants->findOrAddConstant(Utf8, "(I)V");
			int nat = cElem->constants->findOrAddConstant(NameAndType, "", 0, 0, mn, md);
			int mref = cElem->constants->findOrAddConstant(MethodRef, "", 0, 0, clas, nat);
			std::vector<char> is = invokespecial(mref);
			appendArrayToByteVector(&res, is.data(), is.size());
		}
	}
	else if (expr->fromLit == _FROM_UNIT)
	{
		int n = cElem->constants->findOrAddConstant(Utf8, "JavaRTL/Unit");
		clas = cElem->constants->findOrAddConstant(Class, "",NULL,NULL,n);
		if (n != -1)
		{
			res = _new(clas);
			std::vector<char> dp = dup(); // dup
			appendArrayToByteVector(&res, dp.data(), dp.size());

			int mn = cElem->constants->findOrAddConstant(Utf8, "<init>"); // invokespecial
			int md = cElem->constants->findOrAddConstant(Utf8, "()V");
			int nat = cElem->constants->findOrAddConstant(NameAndType, "", 0, 0, mn, md);
			int mref = cElem->constants->findOrAddConstant(MethodRef, "", 0, 0, clas, nat);
			std::vector<char> is = invokespecial(mref);
			appendArrayToByteVector(&res, is.data(), is.size());
		}
	}
	return res;
}

std::vector<char> generateCodeForMethodAccess(struct ExpressionNode * expr, class ClassTableElement * cElem, class MethodTableElement * mElem)
{
	std::vector<char> res;

		std::vector<char> obj = generateCodeForExpression(expr->left, cElem, mElem);
		appendArrayToByteVector(&res, obj.data(), obj.size());

		struct ExpressionNode * cur = NULL;
		if (expr->params != NULL) cur = expr->params->first;
		std::string desc = "(";
		while(cur != NULL)
		{
			std::vector<char> p = generateCodeForExpression(cur, cElem, mElem);
			appendArrayToByteVector(&res, p.data(), p.size());
			if (cur->typ->type == _ARRAY) desc += "[L";
			else desc += "L";
			desc += Type(cur->typ).className;
			desc += ";";
			cur = cur->next;
		}
		desc += ")";
		std::string keyDesc = desc;

	std::string clsn = Type(expr->left->typ).className;

	int cn = cElem->constants->findOrAddConstant(Utf8, clsn);
	int cls = cElem->constants->findOrAddConstant(Class, "",0,0,cn);
	Type * r = ClassTable::items[clsn]->methods->methods[expr->identifierString][keyDesc]->retType;
	if (r->typ == _ARRAY)desc += "[";
	desc += "L";
	desc += r->className;
	desc += ";";

	int n = cElem->constants->findOrAddConstant(Utf8, expr->identifierString);
	int d = cElem->constants->findOrAddConstant(Utf8, desc);
	int nat = cElem->constants->findOrAddConstant(NameAndType, "", 0,0, n, d);
	int mref = cElem->constants->findOrAddConstant(MethodRef, "", 0,0, cls, nat);

			
	std::vector<char> iv = invokevirtual(mref);
	appendArrayToByteVector(&res, iv.data(), iv.size());

	return res;
}

std::vector<char> generateMain(class ClassTableElement *cls,  MethodTableElement * main)
{
	std::vector<char> res;
	int d = main->descriptor;
	int n = main->methodName;
	int nam = cls->constants->findOrAddConstant(Utf8, "main");
	int desc = cls->constants->findOrAddConstant(Utf8, "([Ljava/lang/String;)V");
	int nat = cls->constants->findOrAddConstant(NameAndType, "",0,0,n,d);
	int mRef = cls->constants->findOrAddConstant(MethodRef, "",0,0,cls->thisClass,nat);


	char publicStaticFlag[2] = { 0x00, 0x09 }; //ACC_PUBLIC + ACC_STATIC
	appendArrayToByteVector(&res, publicStaticFlag, 2);

		//Добавление имени метода
	std::vector<char> nameBytes = intToByteVector(nam, 2);
	appendArrayToByteVector(&res, nameBytes.data(), nameBytes.size());
	
		// Добавление дескриптора метода
	std::vector<char> typeBytes = intToByteVector(desc, 2);
	appendArrayToByteVector(&res, typeBytes.data(), typeBytes.size());

	//Добавление атрибутов TODO:Code
		std::vector<char> codeAttributeSizeBytes = intToByteVector(1, 2);
	appendArrayToByteVector(&res, codeAttributeSizeBytes.data(), codeAttributeSizeBytes.size());


	int cd = cls->constants->findOrAddConstant(Utf8, "Code");
	codeAttributeSizeBytes = intToByteVector(cd, 2);
	appendArrayToByteVector(&res, codeAttributeSizeBytes.data(), codeAttributeSizeBytes.size());

	std::vector<char> codeBytes;

	codeBytes = invokestatic(mRef);

	std::vector<char> ret = _return();

	appendArrayToByteVector(&codeBytes, ret.data(), ret.size());

	//Добавление длины атрибута
	std::vector<char> lengthBytes = intToByteVector(12 + codeBytes.size(), 4);
	appendArrayToByteVector(&res, lengthBytes.data(), lengthBytes.size());

	//Добавление размера стека операндов
	std::vector<char> stackSizeBytes = intToByteVector(FileConstants::stackSize, 2);
	appendArrayToByteVector(&res, stackSizeBytes.data(), stackSizeBytes.size());

	//Добавление количества локальных переменных
	int localsSize = 1;
	std::vector<char> localsSizeBytes = intToByteVector(localsSize, 2);
	appendArrayToByteVector(&res, localsSizeBytes.data(), localsSizeBytes.size());


	//Добавление длины байт-кода TODO: сделать
	std::vector<char> codeSizeBytes = intToByteVector(codeBytes.size(), 4);
	appendArrayToByteVector(&res, codeSizeBytes.data(), codeSizeBytes.size());

	//Добавление байт-кода
	appendArrayToByteVector(&res, codeBytes.data(), codeBytes.size());

	//Добавление количества записей в таблице исключений
	std::vector<char> exceptionTableSizeBytes = intToByteVector(0, 2);
	appendArrayToByteVector(&res, exceptionTableSizeBytes.data(), exceptionTableSizeBytes.size());

	//Добавление количества атрибутов
	std::vector<char> attributesCountBytes = intToByteVector(0, 2);
	appendArrayToByteVector(&res, attributesCountBytes.data(), attributesCountBytes.size());


	return res;
}
