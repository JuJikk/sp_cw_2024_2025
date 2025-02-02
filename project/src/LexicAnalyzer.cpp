#include "LexicAnalyzer.h"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern struct Token* TokenTable;   // ������� ������
extern unsigned int TokensNum;     // ʳ������ ������

unsigned int LexicAnalyzer::getTokens(FILE* F) {
    enum States state = Start;
    struct Token tempToken;

    char ch, buf[16];
    unsigned int tokenCount = 0;
    int line = 1;
    int tokenLength = 0;

    ch = getc(F);

    while (true) {
        switch (state) {
        case Start: {
            if (ch == EOF) {
                state = EndOFile;
            }
            else if (('0' <= ch && ch <= '9') || ch == '-' || ch == '.') {
                state = Digit;
            }
            else if (ch == '#') {
                state = SComment;
            }
            else if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z') || ch == '_') {
                state = Letter;
            }
            else if (ch == ' ' || ch == '\t' || ch == '\n') {
                state = Separator;
            }
            else {
                state = Another;
            }
            break;
        }

        case Digit: {
            buf[0] = ch;
            int j = 1;
            ch = getc(F);
            while (((ch <= '9' && ch >= '0') || ch == '.') && j < 10) {
                buf[j++] = ch;
                ch = getc(F);
            }

            buf[j] = '\0';


            if (!strcmp(buf, ".")) {
                strcpy_s(tempToken.name, ".");
                tempToken.type = Unknown_;
                tempToken.value = 0;
                tempToken.line = line;
                state = Finish;
                break;
            }

            short dotCounter = 0, currCharIndex = 0;
            while (buf[currCharIndex] != '\0') {
                if (buf[currCharIndex] == '.') {
                    ++dotCounter;
                }
                ++currCharIndex;
            }

            if (dotCounter > 1) {
                strcpy_s(tempToken.name, buf);
                tempToken.type = Unknown_;
                tempToken.value = 0;
                tempToken.line = line;
                state = Finish;
                break;
            }

            if (dotCounter == 1) {
                strcpy_s(tempToken.name, buf);
                tempToken.type = Float;
                tempToken.value = atof(buf);
                tempToken.line = line;
                state = Finish;
                break;
            }

            if ((buf[0] == '0' && buf[1] != '\0') || (buf[0] == '-' && buf[1] == '0')) {
                strcpy_s(tempToken.name, buf);
                tempToken.type = Unknown_;
                tempToken.value = 0;
                tempToken.line = line;
                state = Finish;
                break;
            }
            strcpy_s(tempToken.name, buf);
            tempToken.type = Number;
            tempToken.value = atoi(buf);
            tempToken.line = line;
            state = Finish;
            break;
        }

        case Separator: {
            if (ch == '\n') {
                line++;
            }
            ch = getc(F);

            state = Start;
            break;
        }

        case SComment: {
            ch = getc(F);
            if (ch == '*') {
                state = Comment;
            } else {
                strcpy_s(tempToken.name, "#");
                tempToken.type = Unknown_;
                tempToken.value = 0;
                tempToken.line = line;
                state = Finish;
            }
            break;
        }

        case Comment: {
            while (ch != EOF) {
                if (ch == '*' && (ch = getc(F)) == '#') {
                    break;
                }
                ch = getc(F);
            }
            ch = getc(F);
            state = Start;
            break;
        }

        case Finish: {
            if (tokenCount < MAX_TOKENS) {
                TokenTable[tokenCount++] = tempToken;
                if (ch != EOF) {
                    state = Start;
                }
                else {
                    state = EndOFile;
                }
            }
            else {
                printf("\n\t\t\ttoo many tokens !!!\n");
                return TokensNum = tokenCount - 1;
            }
            break;
        }

        case EndOFile: {
            return TokensNum = tokenCount;
        }

        case Letter: {
            buf[0] = ch;
            int j = 1;

            ch = getc(F);
            while ((('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ('0' <= ch && ch <= '9') || ch == '_') && j < 15) {
                buf[j++] = ch;
                ch = getc(F);
            }

            buf[j] = '\0';

            enum TypeOfToken tempType = Unknown_;

            if (!strcmp(buf, "STARTPROGRAM")) {
                tempType = StartProgram;
            }
            else if (!strcmp(buf, "VARIABLE")) {
                tempType = Variable;
            }
            else if (!strcmp(buf, "STARTBLOCK")) {
                tempType = StartBlock;
            }
            else if (!strcmp(buf, "INT_4")) {
                tempType = Type;
            }
            else if (!strcmp(buf, "ENDBLOCK")) {
                tempType = EndBlock;
            }
            else if (!strcmp(buf, "READ")) {
                tempType = Input;
            }
            else if (!strcmp(buf, "WRITE")) {
                tempType = Output;
            }
            else if (!strcmp(buf, "IF")) {
                tempType = If;
            }
            else if (!strcmp(buf, "MUL")) {
                tempType = Mul;
            }
            else if (!strcmp(buf, "DIV")) {
                tempType = Div;
            }
            else if (!strcmp(buf, "ADD")) {
                tempType = Add;
            }
            else if (!strcmp(buf, "MOD")) {
                tempType = Mod;
            }
            else if (!strcmp(buf, "SUB")) {
                tempType = Sub;
            }
            else if (!strcmp(buf, "|")) {
                tempType = Or;
            }
            else if (!strcmp(buf, "&")) {
                tempType = And;
            }
            else if (!strcmp(buf, "!")) {
                tempType = Not;
            }
            else if (!strcmp(buf, "EQ")) {
                tempType = Equality;
            }
            else if (!strcmp(buf, "NE")) {
                tempType = NotEquality;
            }
            else if (!strcmp(buf, "ELSE")) {
                tempType = Else;
            }
            else if (!strcmp(buf, "GOTO")) {
                tempType = Goto;
            }
            else if (!strcmp(buf, "FOR")) {
                tempType = For;
            }
            else if (!strcmp(buf, "TO")) {
                tempType = To;
            }
            else if (!strcmp(buf, "DOWNTO")) {
                tempType = Downto;
            }
            else if (!strcmp(buf, "DO")) {
                tempType = Do;
            }
            else if (!strcmp(buf, "WHILE")) {
                tempType = While;
            }
            else if (!strcmp(buf, "END")) {
                tempType = End;
            }
            else if (!strcmp(buf, "CONTINUE")) {
                tempType = Continue;
            }
            else if (!strcmp(buf, "EXIT")) {
                tempType = Exit;
            }
            else if (!strcmp(buf, "LT")) {
                tempType = Less;
            }
            else if (!strcmp(buf, "GT")) {
                tempType = Greate;
            }
            else if (!strcmp(buf, "REPEAT")) {
                tempType = Repeat;
            }
            else if (!strcmp(buf, "UNTIL")) {
                tempType = Until;
            }
            else if (strlen(buf) <= 4 && buf[0] == '_'
                && ('a' <= buf[1] && buf[1] <= 'z')
                && ('a' <= buf[2] && buf[2] <= 'Z')
                && ('a' <= buf[3] && buf[3] <= 'Z')
                ) {
                tempType = Identifier;
                }
            else {
                tempType = Identifier;
            }

            strcpy_s(tempToken.name, buf);
            tempToken.type = tempType;
            tempToken.value = 0;
            tempToken.line = line;
            state = Finish;
            break;
        }

        case Another: {
            switch (ch) {
            case '&': {
                strcpy_s(tempToken.name, "&");
                tempToken.type = And;
                tempToken.value = 0;
                tempToken.line = line;
                state = Finish;
                ch = getc(F);
                break;
            }

            case '|': {
                strcpy_s(tempToken.name, "|");
                tempToken.type = Or;
                tempToken.value = 0;
                tempToken.line = line;
                state = Finish;
                ch = getc(F);
                break;
            }

            case '!': {
                strcpy_s(tempToken.name, "!");
                tempToken.type = Not;
                tempToken.value = 0;
                tempToken.line = line;
                state = Finish;
                ch = getc(F);
                break;
            }

            case '(': {
                strcpy_s(tempToken.name, "(");
                tempToken.type = LBracket;
                tempToken.value = 0;
                tempToken.line = line;
                state = Finish;
                ch = getc(F);
                break;
            }

            case ')': {
                strcpy_s(tempToken.name, ")");
                tempToken.type = RBracket;
                tempToken.value = 0;
                tempToken.line = line;
                state = Finish;
                ch = getc(F);
                break;
            }

            case ',': {
                strcpy_s(tempToken.name, ",");
                tempToken.type = Comma;
                tempToken.value = 0;
                tempToken.line = line;
                state = Finish;
                ch = getc(F);
                break;
            }

            case ';': {
                strcpy_s(tempToken.name, ";");
                tempToken.type = Semicolon;
                tempToken.value = 0;
                tempToken.line = line;
                state = Finish;
                ch = getc(F);
                break;
            }

            case ':': {
                strcpy_s(tempToken.name, ":");
                tempToken.type = Colon;
                tempToken.value = 0;
                tempToken.line = line;
                state = Finish;
                ch = getc(F);
                break;
            }

            case '<': {
                ch = getc(F);
                if (ch == '-') {
                    strcpy_s(tempToken.name, "<-");
                    tempToken.type = Assign;
                    tempToken.value = 0;
                    tempToken.line = line;
                    state = Finish;
                    ch = getc(F);
                }
                else {
                    strcpy_s(tempToken.name, "<");
                    tempToken.type = Unknown_;
                    tempToken.value = 0;
                    tempToken.line = line;
                    state = Finish;
                }
                break;
            }

            case '>': {
                ch = getc(F);
                if (ch == '=') {
                    strcpy_s(tempToken.name, ">=");
                    tempToken.type = Unknown_;
                    tempToken.value = 0;
                    tempToken.line = line;
                    state = Finish;;
                }
                else {
                    strcpy_s(tempToken.name, ">");
                    tempToken.type = Unknown_;
                    tempToken.value = 0;
                    tempToken.line = line;
                    state = Finish;
                }
                break;
            }

            default: {
                tempToken.name[0] = ch;
                tempToken.name[1] = '\0';
                tempToken.type = Unknown_;
                tempToken.value = 0;
                tempToken.line = line;
                ch = getc(F);
                state = Finish;
                break;
            }
            }
        }
        }
    }

    return TokensNum = tokenCount;
}

// ������� ����� ������� ������ �� �����
void LexicAnalyzer::printTokens(void) {
    char type_tokens[16];
    printf("---------------------------------------------------------------------------\n");
    printf("| TOKEN TABLE                                                             |\n");
    printf("---------------------------------------------------------------------------\n");
    printf("| line number | token           | value      | token code | type of token |\n");
    printf("---------------------------------------------------------------------------\n");

    for (unsigned int i = 0; i < TokensNum; i++) {
        strcpy_s(type_tokens, lexemeTypeName(TokenTable[i].type));

        printf("|%12d |%16s |%11d |%11d | %-13s |\n",
            TokenTable[i].line,
            TokenTable[i].name,
            TokenTable[i].value,
            TokenTable[i].type,
            type_tokens);
        printf("---------------------------------------------------------------------------\n");
    }
}

void LexicAnalyzer::fprintTokens(FILE* F) {

    char type_tokens[16];
    fprintf(F, "\n\n---------------------------------------------------------------------------\n");
    fprintf(F, "| TOKEN TABLE                                                             |\n");
    fprintf(F, "---------------------------------------------------------------------------\n");
    fprintf(F, "| line number | token           | value      | token code | type of token |\n");
    fprintf(F, "---------------------------------------------------------------------------\n");

    for (unsigned int i = 0; i < TokensNum; i++) {
        strcpy_s(type_tokens, lexemeTypeName(TokenTable[i].type));

        fprintf(F, "|%12d |%16s |%11d |%11d | %-13s |\n",
            TokenTable[i].line,
            TokenTable[i].name,
            TokenTable[i].value,
            TokenTable[i].type,
            type_tokens);
        fprintf(F, "---------------------------------------------------------------------------\n");
    }
}
