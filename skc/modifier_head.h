#pragma once
#include <stdlib.h>

/*! Структура, определяющая применяемые модификаторы к элементу. */
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
