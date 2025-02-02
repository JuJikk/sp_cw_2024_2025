#pragma once

#include "header.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern struct Token* TokenTable;
extern unsigned int TokensNum;

extern struct id* idTable;
extern unsigned int idNum;

extern struct id* labelTable;
extern unsigned int labelNum;

namespace Parser {
    void Parser();
    void Semantic();
    void match(enum TypeOfToken expectedType);
    unsigned int IdIdentification(struct id idTable[], struct Token TokenTable[], unsigned int tokenCount);
    unsigned int LabelIdentification(struct id labelTable[], struct Token TokenTable[], unsigned int tokenCount);
    void printIdentifiers(int num, struct id* table);
    void fprintIdentifiers(FILE* F, int num, struct id* table);

    void program();
    void programBody();
    void variableDeclaration();
    void variableList();
    void statement();
    void inputStatement();
    void outputStatement();
    void arithmeticExpression();
    void lowPriorityExpression();
    void middlePriorityExpression();
    void assignStatement();
    void ifStatement();
    void logicalExpression();
    void andExpression();
    void comparison();
    void comparisonExpression();
    void gotoStatement();
    void labelPoint();
    void forStatement();
    void whileStatement();
    void statementInWhile();
    void repeatStatement();
    void compoundStatement();
}