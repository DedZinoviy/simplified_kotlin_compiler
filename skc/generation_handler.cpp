#include "generation_handler.hpp"

char FileConstants::magicConstant[4] = { 0xCA, 0xFE, 0xBA, 0xBE };
char FileConstants::smallVersion[2]= { 0x00, 0x00 };
char FileConstants::bigVersion[2] = { 0x00, 0x3E };
std::vector<char> intToByteVector(int num, int arraySize)
{
	std::vector<char> res(arraySize);
	for (int i = 0; i < arraySize; i++)
	{
		res[arraySize - i - 1] = (num >> ( i * 8));
	}
	return res;
}

void appendArrayToByteVector(std::vector<char>* data, char array[], int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		data->push_back(array[i]);
	}
}

std::vector<char> iload(int num)
{
    std::vector<char> res;
	if (num >= 0 && num <= 255) { // Использовать iload, если значение помещается в 1 байт.
		res.push_back(0x15); //iload
		res.push_back(num);
	}
	else if (num >= 256 && num <= 65535) { // Иначе испльзовать двухбайтовую команду.
		// wide iload
		res.push_back(0xC4); //wide
		res.push_back(0x15); //iload
		std::vector <char> temp = intToByteVector(num, 2);
		appendArrayToByteVector(&res, temp.data(), temp.size());
	}
	else { // Иначе сообщить об ошибке.
		throw std::exception("Error in iload: Invalid number");
	}

	return res;
}

std::vector<char> aload(int num)
{
   	std::vector<char> res;
	if (num >= 0 && num <= 255) { // Использовать aload, если значение помещается в 1 байт.
		res.push_back(0x19); //aload
		res.push_back(num); 
	}
	else if (num >= 256 && num <= 65535) { // Иначе испльзовать двухбайтовую команду.
		// wide aload
		res.push_back(0xC4); //wide
		res.push_back(0x19); //aload
		std::vector <char> temp = intToByteVector(num, 2);
		appendArrayToByteVector(&res, temp.data(), temp.size());
	}
	else { // Иначе сообщить об ошибке.
		throw std::exception("Error in aload: Invalid number");
	}

	return res;
}

std::vector<char> istore(int num)
{
	std::vector<char> res;
	if (num >= 0 && num <= 255) { // Использовать istore, если значение помещается в 1 байт.
		res.push_back(0x36); //istore
		res.push_back(num);
	}
	else if (num >= 256 && num <= 65535) { // Иначе испльзовать двухбайтовую команду.
		// wide istore
		res.push_back(0xC4); //wide
		res.push_back(0x36); //istore
		std::vector <char> temp = intToByteVector(num, 2);
		appendArrayToByteVector(&res, temp.data(), temp.size());
	}
	else { // Иначе сообщить об ошибке.
		throw std::exception("Error in istore: Invalid number");
	}

	return res;
}

std::vector<char> astore(int num)
{
	std::vector<char> res;
	if (num >= 0 && num <= 255) { // Использовать astore, если значение помещается в 1 байт.
		res.push_back(0x3A); //astore
		res.push_back(num);
	}
	else if (num >= 256 && num <= 65535) { // Иначе испльзовать двухбайтовую команду.
		// wide astore
		res.push_back(0xC4); //wide
		res.push_back(0x3A); //astore
		std::vector <char> temp = intToByteVector(num, 2);
	    appendArrayToByteVector(&res, temp.data(), temp.size());
	}
	else { // Иначе сообщить об ошибке.
		throw std::exception("Error in astore: Invalid number");
	}

	return res;
}


std::vector<char> ldc(int num)
{
	std::vector<char> res;
	if (num >= 0 && num <= 255) { // Использовать ldc, если значение помещается в 1 байт.
		//ldc
		res.push_back(0x12); //ldc
		res.push_back(num);
	}
	else if (num >= 256 && num <= 65535) { // Иначе испльзовать двухбайтовую команду.
		//ldc_w
		res.push_back(0x13); //ldc_w
		std::vector <char> temp = intToByteVector(num, 2);
		appendArrayToByteVector(&res, temp.data(), temp.size());
	}
	else { // Иначе сообщить об ошибке.
		throw std::exception("Error in ldc, ldc_w: Invalid number");
	}

	return res;
}

std::vector<char> pop()
{
	std::vector <char> res;
	res.push_back(0x57); //pop
	return res;
}

std::vector<char> dup()
{
	std::vector <char> res;
	res.push_back(0x59); //dup
	return res;
}

std::vector<char> dup2()
{
	std::vector <char> res;
	res.push_back(0x5C); //dup2
	return res;
}

std::vector<char> go_to(int offset)
{
	std::vector<char> res;
	res.push_back(0xA7); //goto
	std::vector <char> temp;
	if (offset < 0) // Если смещение отрицательно...
		temp = intToByteVector(offset, 2);
	else
		temp = intToByteVector(offset + 3, 2);
	appendArrayToByteVector(&res, temp.data(), temp.size());
	return res;
}
