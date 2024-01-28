#include <vector>
class FileConstants {
public:
	/* ------------------------- "Магическая константа" ------------------------- */
	static char magicConstant[4];

	/* ------------------------- "Малая" версия ------------------------- */
	static char smallVersion[2];

	/* ------------------------- "Большая" версия ------------------------- */
	static char bigVersion[2];

	static const int stackSize = 1000;
};

enum IfCommandType {
	EQ,
	NE,
	LT,
	GT,
	LE,
	GE
};

/* ------------------------- Команды работы со стеком ------------------------- */

std::vector<char> intToByteVector(int num, int arraySize);

void appendArrayToByteVector(std::vector<char>* data, char array[], int arraySize);

std::vector<char> iconstBipushSipush(int num);

/*! Сгенерировать команду iload.
* \param[in] num номер константы в таблице констант.
* \return вектор байт - команда.
*/
std::vector<char> iload(int num);

/*! Сгенерировать команду aload.
* \param[in] num номер константы в таблице констант.
* \return вектор байт - команда.
*/
std::vector<char> aload(int num);

/*! Сгенерировать команду istore.
* \param[in] num номер константы в таблице констант.
* \return вектор байт - команда.
*/
std::vector<char> istore(int num);

/*! Сгенерировать команду astore.
* \param[in] num номер константы в таблице констант.
* \return вектор байт - команда.
*/
std::vector<char> astore(int num);

/*! Сгенерировать команду ldc.
* \param[in] num номер константы в таблице констант.
* \return вектор байт - команда.
*/
std::vector<char> ldc(int num);

/*! Сгенерировать команду pop.
* \return вектор байт - команда.
*/
std::vector<char> pop();

/*! Сгенерировать команду dup.
* \return вектор байт - команда.
*/
std::vector<char> dup();

/*! Сгенерировать команду dup2.
* \return вектор байт - команда.
*/
std::vector<char> dup2();

/*! Сгенерировать команду goto.
* \param[in] offset смещение.
* \return вектор байт - команда.
*/
std::vector<char> go_to(int offset);

std::vector<char> if_acmp(IfCommandType type, int offset);
std::vector<char> if_icmp(IfCommandType type, int offset);
std::vector<char> if_(IfCommandType type, int offset);

/*! Сгенерировать команду new.
* \param[in] constant константа класса объекта.
* \return вектор байт - команда.
*/
std::vector<char> _new(int constant);

std::vector<char> getfield(int constant);

std::vector<char> putfield(int constant);

/*! Сгенерировать команду invokespecial.
* \param[in] constant константа ссылки на метод.
* \return вектор байт - команда.
*/
std::vector<char> invokespecial(int constant);

/*! Сгенерировать команду invokeVirtual.
* \param[in] constant константа ссылки на метод.
* \return вектор байт - команда.
*/
std::vector<char> invokevirtual(int constant);

/*! Сгенерировать команду invokestatic.
* \param[in] constant константа ссылки на метод.
* \return вектор байт - команда.
*/
std::vector<char> invokestatic(int constant);

/*! Сгенерировать команду ireturn.
* \return вектор байт - команда.
*/
std::vector<char> ireturn();

/*! Сгенерировать команду return.
* \return вектор байт - команда.
*/
std::vector<char> _return();

/*! Сгенерировать команду areturn.
* \return вектор байт - команда.
*/
std::vector<char> areturn();

std::vector<char> anewarray(int constant);

std::vector<char> arraylength();

std::vector<char> aaload();

std::vector<char> aastore();

std::vector<char> iadd();
