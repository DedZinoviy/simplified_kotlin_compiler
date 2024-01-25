#include <vector>

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
