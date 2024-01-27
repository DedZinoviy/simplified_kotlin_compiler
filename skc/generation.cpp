#include "generation.hpp"

std::vector<char> generateBytesForConstantTable(class ConstantTable * table);
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
    data.push_back(0x21);

    std::vector<char> thisCls = intToByteVector(elem->thisClass, 2);
    std::vector<char> parentCls = intToByteVector(elem->superClass, 2);
    appendArrayToByteVector(&data, thisCls.data(), thisCls.size());
    appendArrayToByteVector(&data, parentCls.data(), parentCls.size());
    std::vector<char> interfaceCount = intToByteVector(0, 2);
    std::vector<char> fieldCount = intToByteVector(0, 2);
    std::vector<char> methodCount = intToByteVector(0, 2);
    std::vector<char> attributeCount = intToByteVector(0, 2);
    appendArrayToByteVector(&data, interfaceCount.data(), interfaceCount.size());
    appendArrayToByteVector(&data, fieldCount.data(), fieldCount.size());
    appendArrayToByteVector(&data, methodCount.data(), methodCount.size());
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
