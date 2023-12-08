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
    newHead->isInternal = 0;
    newHead->isOpen = 0;
    newHead->isOverride = 0;
    newHead->isPrivate = 0;
    newHead->isProtected = 0;
    newHead->isPublic = 0;
    return newHead;
}
