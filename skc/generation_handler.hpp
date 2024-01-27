#include <vector>
class FileConstants {
public:
	/* ------------------------- "Магическая константа" ------------------------- */
	static char magicConstant[4];

	/* ------------------------- "Малая" версия ------------------------- */
	static char smallVersion[2];

	/* ------------------------- "Большая" версия ------------------------- */
	static char bigVersion[2];
};
/* ------------------------- Команды работы со стеком ------------------------- */

std::vector<char> intToByteVector(int num, int arraySize);

void appendArrayToByteVector(std::vector<char>* data, char array[], int arraySize);

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
