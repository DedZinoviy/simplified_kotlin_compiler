#include <vector>

/* ------------------------- "Магическая константа" ------------------------- */
char magicConstant[4] = {0xCA, 0xFE, 0xBA, 0xBE};

/* ------------------------- "Малая" версия ------------------------- */
char smallVersion[2] = {0x00, 0x00};

/* ------------------------- "Большая" версия ------------------------- */
char bigVersion[2] = { 0x00, 0x3E };

/* ------------------------- Команды работы со стеком ------------------------- */

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
