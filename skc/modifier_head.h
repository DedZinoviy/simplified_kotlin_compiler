#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include <stdlib.h>

/*! \brief Структура, определяющая применяемые модификаторы к элементу. */
struct ModifierHead 
{
    int isPrivate;
    int isProtected;
    int isInternal;
    int isPublic;
    int isOpen;
    int isFinal;
    int isOverride;
};

/*! Создать пустую структуру модификаторов.
* \return Пустая структура модификаторов.
*/
struct ModifierHead * createEmptyModifierHead();

/*! Очистить структуру модификаторов.
* \param[in] head очищаемая структура модификаторов.
* \return Пустая структура модификаторов.
*/
struct ModifierHead * clearModifierHead(struct ModifierHead * head);

/*! Скопировать структуру модификаторов.
* \param[in] head копируемая структура модификаторов.
* \return копия структуры модификаторов.
*/
struct ModifierHead * copyModifierHead(struct ModifierHead * head);

/*! Проверить, являются ли все поля структуры равными 0.
* \param[in] head проверяемая структура.
* \return результат проверки: 1 = если все поля равны 0, 0 - если нет.
*/
int isZeroHead(struct ModifierHead * head);

#ifdef __cplusplus
};
#endif

