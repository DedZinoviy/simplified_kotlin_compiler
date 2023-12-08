#pragma once
#include <stdlib.h>

struct ModifierHead {
    int isPrivate = 0;
    int isProtected = 0;
    int isInternal = 0;
    int isPublic = 0;
    int isOpen = 0;
    int isFinal = 0;
    int isOverride = 0;
};

struct ModifierHead * createEmptyModifierHead();

struct ModifierHead * clearModifierHead(struct ModifierHead * head);

struct ModifierHead * copyModifierHead(struct ModifierHead * head);
