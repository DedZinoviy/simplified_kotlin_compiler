#include "modifier_head.h"

struct ModifierHead * createEmptyModifierHead()
{
    struct ModifierHead * head = (struct ModifierHead *)malloc(sizeof(struct ModifierHead));
    head->isFinal = 0;
    head->isInternal = 0;
    head->isOpen = 0;
    head->isOverride = 0;
    head->isPrivate = 0;
    head->isProtected = 0;
    head->isPublic = 0;
    return head;
}

struct ModifierHead * clearModifierHead(struct ModifierHead * head)
{
    head->isFinal = 0;
    head->isInternal = 0;
    head->isOpen = 0;
    head->isOverride = 0;
    head->isPrivate = 0;
    head->isProtected = 0;
    head->isPublic = 0;
    return head;
}

struct ModifierHead * copyModifierHead(struct ModifierHead * head)
{
    struct ModifierHead * newHead = (struct ModifierHead *)malloc(sizeof(struct ModifierHead));
    newHead->isFinal = head->isFinal;
    newHead->isInternal = head->isInternal;
    newHead->isOpen = head->isOpen;
    newHead->isOverride = head->isOverride;
    newHead->isPrivate = head->isPrivate;
    newHead->isProtected = head->isProtected;
    newHead->isPublic = head->isPublic;
    return newHead;
}

/*! Проверить, являются ли все поля структуры равными 0.
* \param[in] head проверяемая структура.
* \return результат проверки: 1 = если все поля равны 0, 0 - если нет.
*/
int isZeroHead(struct ModifierHead * head)
{
    int isFlag = head->isFinal == 0 && head->isInternal == 0 && head->isOpen == 0 && head->isOverride == 0 && head->isPrivate == 0 &&
    head->isProtected == 0 && head->isPublic == 0;
    if(isFlag)
    {
        return 1;
    }
    return 0;
}
