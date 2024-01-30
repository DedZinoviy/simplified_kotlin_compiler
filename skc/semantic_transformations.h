#pragma once
#include "parsing_tree.h"
#include "semantic_errors.h"
#include "print_functions.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! Заменить узлы непосредственных литералов на комбинацию из создания объекта и доступа к полю _value этого класса.
* \param[in,out] root дерево программы - указатель на узел KotlinFile.
*/
void replaceLiteralsToObjects(struct KotlinFileNode * root);

/*! Заменить узлы модифицирующих присваиваний на кобинацию из арифметиеской операции и присваивания.
* \param[in,out] root дерево программы - указатель на узел KotlinFile.
*/
void replaceModifyingAssignments(struct KotlinFileNode * root);

void replaceOperators(struct KotlinFileNode * root);

/*! Проверить списки модификаторов на наличие взаимоиключающих модификаторов. Проверить применяемые модификаторы и сущности на совместимость.
* \param[in,out] root дерево программы - указатель на узел KotlinFile.
* \return Возможная семантическая ошибка, связанная с модификаторами; NULL, если таковая отсуствует.
*/
struct SemanticError * checkModifierLists(struct KotlinFileNode * root);

struct SemanticError * checkAndAddReturn(struct KotlinFileNode * root);

#ifdef __cplusplus
};
#endif
