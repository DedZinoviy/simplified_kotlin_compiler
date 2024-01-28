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



std::vector<char> iconstBipushSipush(int num)
{
	std::vector<char> res;

	// iconst
	if (num == -1) {
		res.push_back(0x2); //iconst_m1
	}
	else if (num == 0) {
		res.push_back(0x3); //iconst_0
	}
	else if (num == 1) {
		res.push_back(0x4); //iconst_1
	}
	else if (num == 2) {
		res.push_back(0x5); //iconst_2
	}
	else if (num == 3) {
		res.push_back(0x6); //iconst_3
	}
	else if (num == 4) {
		res.push_back(0x7); //iconst_4
	}
	else if (num == 5) {
		res.push_back(0x8); //iconst_5
	}

	if (num <= 5 && num >= -1) {
		return res;
	}

	if (num >= -128 && num <= 127) {
		// bipush
		res.push_back(0x10); //bipush
		res.push_back(num);
		return res;
	}

	if (num >= -32768 && num <= 32767) {
		// sipush
		res.push_back(0x11); //sipush
		std::vector <char> temp = intToByteVector(num, 2);
		appendArrayToByteVector(&res, temp.data(), temp.size());
		return res;
	}
	else {
		throw std::exception("Error in iconstBipushSipush: Invalid number");
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

std::vector<char> if_icmp(IfCommandType type, int offset)
{
	std::vector<char> res;
	switch (type)
	{
	case EQ:
		res.push_back(0x9F); //if_icmpeq
		break;
	case NE:
		res.push_back(0xA0); //if_icmpne
		break;
	case LT:
		res.push_back(0xA1); //if_icmplt
		break;
	case LE:
		res.push_back(0xA4); //if_icmple
		break;
	case GT:
		res.push_back(0xA3); //if_icmpgt
		break;
	case GE:
		res.push_back(0xA2); //if_icmpge
		break;
	default:
		break;
	}

	std::vector <char> temp;
	if (offset < 0)
		temp = intToByteVector(offset, 2);
	else
		temp = intToByteVector(offset + 3, 2);
	appendArrayToByteVector(&res, temp.data(), temp.size());

	return res;
}

// ---------- if ----------
std::vector<char> if_(IfCommandType type, int offset)
{
	std::vector<char> res;

	switch (type)
	{
	case EQ:
		res.push_back(0x99); //ifeq
		break;
	case NE:
		res.push_back(0x9A); //ifne
		break;
	case LT:
		res.push_back(0x9B); //iflt
		break;
	case LE:
		res.push_back(0x9E); //ifle
		break;
	case GT:
		res.push_back(0x9D); //ifgt
		break;
	case GE:
		res.push_back(0x9C); //ifge
		break;
	default:
		break;
	}

	std::vector <char> temp;
	if (offset < 0)
		temp = intToByteVector(offset, 2);
	else
		temp = intToByteVector(offset + 3, 2);
	appendArrayToByteVector(&res, temp.data(), temp.size());

	return res;
}

// ---------- if_acmp ----------
std::vector<char> if_acmp(IfCommandType type, int offset)
{
	std::vector<char> res;

	switch (type)
	{
	case EQ:
		res.push_back(0xA5); //if_acmpeq
		break;
	case NE:
		res.push_back(0xA6); //if_acmpne
		break;
	default:
	{
		throw std::exception("Error in if_acmp: Invalid type");
	}
		break;
	}
	std::vector <char> temp;
	if (offset < 0)
		temp = intToByteVector(offset, 2);
	else
		temp = intToByteVector(offset + 3, 2);
	appendArrayToByteVector(&res, temp.data(), temp.size());

	return res;
}



std::vector<char> _new(int constant)
{
	std::vector<char> res;
	res.push_back(0xBB); //new
	std::vector <char> temp = intToByteVector(constant, 2);
	appendArrayToByteVector(&res, temp.data(), temp.size());
	return res;
}

std::vector<char> invokespecial(int constant)
{
	std::vector<char> res;
	res.push_back(0xB7); //invokespecial
	std::vector <char> temp = intToByteVector(constant, 2);
	appendArrayToByteVector(&res, temp.data(), temp.size());
	return res;
}

std::vector<char> invokevirtual(int constant)
{
	std::vector <char> res;
	res.push_back(0xB6); //invokevirtual
	std::vector <char> temp = intToByteVector(constant, 2);
	appendArrayToByteVector(&res, temp.data(), temp.size());
	return res;
}

std::vector<char> invokestatic(int constant)
{
	std::vector<char> res;
	res.push_back(0xB8); //invokestatic
	std::vector <char> temp = intToByteVector(constant, 2);
	appendArrayToByteVector(&res, temp.data(), temp.size());
	return res;
}


std::vector<char> ireturn()
{
	std::vector<char> res;
	res.push_back(0xAC); //ireturn
	return res;
}

std::vector<char> areturn()
{
	std::vector<char> res;
	res.push_back(0xB0); //areturn
	return res;
}

std::vector<char> _return()
{
	std::vector<char> res;
	res.push_back(0xB1); //return
	return res;
}

std::vector<char> getfield(int constant)
{
	std::vector <char> res;
	res.push_back(0xB4); //getfield
	std::vector <char> temp = intToByteVector(constant, 2);
	appendArrayToByteVector(&res, temp.data(), temp.size());
	return res;
}

std::vector<char> putfield(int constant)
{
	std::vector<char> res;
	res.push_back(0xB5); //putfield
	std::vector <char> temp = intToByteVector(constant, 2);
	appendArrayToByteVector(&res, temp.data(), temp.size());
	return res;
}
