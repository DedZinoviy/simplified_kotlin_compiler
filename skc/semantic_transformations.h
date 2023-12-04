#pragma once
#include "parsing_tree.h"

/*! Заменить узлы непосредственных литералов на комбинацию из создания объекта и доступа к полю _value этого класса.
* \param[in,out] root дерево программы - указатель на узел KotlinFile.
*/
void replaceLiteralsToObjects(struct KotlinFileNode * root);

/*! Заменить узлы модифицирующих присваиваний на кобинацию из арифметиеской операции и присваивания.
* \param[in,out] root дерево программы - указатель на узел KotlinFile.
*/
void replaceModifyingAssignments(struct KotlinFileNode * root);
