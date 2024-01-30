#include "attributing.hpp"
#include <iostream>

static void _replaceRTLTypesInTypeNode(struct TypeNode * type);

static void _replaceRTLTypesInStatement(struct StatementNode * stmt);

static void _replaceRTLTypesInFucntion(struct FunctionNode * func)
{
    if (func->returnValue != NULL) _replaceRTLTypesInTypeNode(func->returnValue);
    if (func->params != NULL)
    {
        struct VarDeclarationNode * varDecl = func->params->first;
        while (varDecl != NULL)
        {
            _replaceRTLTypesInTypeNode(varDecl->type);
            varDecl = varDecl->next;
        }
    }
    if (func->body != NULL) if (func->body->first != NULL) _replaceRTLTypesInStatement(func->body->first);
}

static void _replaceRTLTypesInStatement(struct StatementNode * stmt)
{
    if (stmt->varValType != NULL)
        _replaceRTLTypesInTypeNode(stmt->varValType);
    if (stmt->varDeclList != NULL)
    { 
        struct VarDeclarationNode * varDecl = stmt->varDeclList->first;
        while (varDecl != NULL)
        {
            _replaceRTLTypesInTypeNode(varDecl->type);
            varDecl = varDecl->next;
        }
    }
    
    if (stmt ->singleBody != NULL) _replaceRTLTypesInStatement(stmt->singleBody);
    if (stmt ->complexBody != NULL) if (stmt->complexBody->first != NULL) _replaceRTLTypesInStatement(stmt->complexBody->first);
    if (stmt->next != NULL) _replaceRTLTypesInStatement(stmt->next);
    
}

static void _replaceRTLTypesInTypeNode(struct TypeNode * type)
{
    if (type != NULL)
    {
        if (type->type == TypeType::_CLS)
        {
            if (std::string(type->ident) == "Int") type->ident = (char*)"JavaRTL/Int";
            else if (std::string(type->ident) == "Char") type->ident = (char*)"JavaRTL/Char";
            else if (std::string(type->ident) == "String") type->ident = (char*)"JavaRTL/String";
            else if (std::string(type->ident) == "Boolean") type->ident = (char*)"JavaRTL/Boolean";
            else if (std::string(type->ident) == "Any") type->ident = (char*)"JavaRTL/Any";
            else if (std::string(type->ident) == "Unit") type->ident = (char*)"JavaRTL/Unit";
        }
        else if (type->type == TypeType::_ARRAY)
        {
            _replaceRTLTypesInTypeNode(type->complexType);
        }
    }
   
}

static void _replaceRTLTypesInKotlinFileElement(struct KotlinFileElementNode * elem)
{
    if (elem->type == _FUNCTION) _replaceRTLTypesInFucntion(elem->func);
    if (elem->next != NULL) _replaceRTLTypesInKotlinFileElement(elem->next);
}

void replaceRTLTypes(struct KotlinFileNode * root)
{
    if (root->elemList != NULL) if (root->elemList->first != NULL) _replaceRTLTypesInKotlinFileElement(root->elemList->first);
}


void attributeBaseTypes(struct KotlinFileNode * root);

struct SemanticError * attributeExpressions(struct ExpressionNode * expr)
{
    struct SemanticError * err = NULL;
    //if (expr->fromLit != _FROM_NONE) attributeBaseTypes(expr);
    //else {

    //}
    return err;
}

void attributeBaseTypesInExpression(struct ExpressionNode * expr)
{
    if (expr->fromLit == BaseLiteral::_FROM_INT) {
        expr->typ = (struct TypeNode *)malloc(sizeof(struct TypeNode));
        expr->typ->type = TypeType::_CLS;
        expr->typ->complexType = NULL;
        expr->typ->ident = (char*)"JavaRTL/Int";
    }
    
    else if (expr->fromLit == BaseLiteral::_FROM_CHAR) {
        expr->typ = (struct TypeNode *)malloc(sizeof(struct TypeNode));
        expr->typ->type = TypeType::_CLS;
        expr->typ->complexType = NULL;
        expr->typ->ident = (char*)"JavaRTL/Char";
    }

    else if (expr->fromLit == BaseLiteral::_FROM_STRING) {
        expr->typ = (struct TypeNode *)malloc(sizeof(struct TypeNode));
        expr->typ->type = TypeType::_CLS;
        expr->typ->complexType = NULL;
        expr->typ->ident = (char*)"JavaRTL/String";
    }

    else if (expr->fromLit == BaseLiteral::_FROM_BOOLEAN) {
        expr->typ = (struct TypeNode *)malloc(sizeof(struct TypeNode));
        expr->typ->type = TypeType::_CLS;
        expr->typ->complexType = NULL;
        expr->typ->ident = (char*)"JavaRTL/Boolean";
    }
    else if (expr->fromLit == BaseLiteral::_FROM_UNIT) {
        expr->typ = (struct TypeNode *)malloc(sizeof(struct TypeNode));
        expr->typ->type = TypeType::_CLS;
        expr->typ->complexType = NULL;
        expr->typ->ident = (char*)"JavaRTL/Unit";
    }
    if (expr->left != NULL) attributeBaseTypesInExpression(expr->left);
    if (expr->right != NULL) attributeBaseTypesInExpression(expr->right);
    if (expr->params != NULL)
    {
        struct ExpressionNode * param = expr->params->first;
        while (param != NULL) { 
            attributeBaseTypesInExpression(param);
            param = param->next;
        }
    }
}

void attributeBaseTypesInStatements(struct StatementNode * stmt)
{
    if (stmt->condition != NULL) attributeBaseTypesInExpression(stmt->condition);
    if (stmt->expression != NULL) attributeBaseTypesInExpression(stmt->expression);
    if (stmt->singleBody != NULL) attributeBaseTypesInStatements(stmt->singleBody); 
    if (stmt->complexBody != NULL) 
    {
        struct StatementNode * st = stmt->complexBody->first;
        while(st != NULL)
        {
            attributeBaseTypesInStatements(st);
            st = st->next;
        }
    }
    if (stmt->next != NULL) attributeBaseTypesInStatements(stmt->next);
}


void attributeBaseTypes(struct KotlinFileNode * root)
{
    if (root->elemList != NULL)
    {
        struct KotlinFileElementNode * elem = root->elemList->first;
        while(elem != NULL)
        {
            if (elem->type == _FUNCTION)
            {
                if (elem->func->body != NULL)
                {
                    struct StatementNode * st = elem->func->body->first;
                    while(st != NULL)
                    {
                        attributeBaseTypesInStatements(st);
                        st = st->next;
                    }
                }
            }
            elem = elem->next;
        }
    }
}

void attributeTree(struct KotlinFileNode * root)
{
    attributeBaseTypes(root);
}
