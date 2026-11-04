#include <stdio.h>
#include <stdlib.h>

#include "token.h"

const char *token_type_name(TokenType type)
{
    switch (type)
    {
    case TOKEN_ERROR:
        return "TOKEN_ERROR";

    case FUNCTION:
        return "FUNCTION";

    case MAIN:
        return "MAIN";

    case LET:
        return "LET";

    case INT:
        return "INT";

    case FLOAT:
        return "FLOAT";

    case CHAR:
        return "CHAR";

    case IF:
        return "IF";

    case ELSE:
        return "ELSE";

    case WHILE:
        return "WHILE";

    case PRINTLN:
        return "PRINTLN";

    case RETURN:
        return "RETURN";

    case LBRACKET:
        return "LBRACKET";

    case RBRACKET:
        return "RBRACKET";

    case LBRACE:
        return "LBRACE";

    case RBRACE:
        return "RBRACE";

    case ARROW:
        return "ARROW";

    case COLON:
        return "COLON";

    case SEMICOLON:
        return "SEMICOLON";

    case COMMA:
        return "COMMA";

    case ASSIGN:
        return "ASSIGN";

    case EQ:
        return "EQ";

    case NE:
        return "NE";

    case GT:
        return "GT";

    case GE:
        return "GE";

    case LT:
        return "LT";

    case LE:
        return "LE";

    case PLUS:
        return "PLUS";

    case MINUS:
        return "MINUS";

    case MULT:
        return "MULT";

    case DIV:
        return "DIV";

    case ID:
        return "ID";

    case INT_CONST:
        return "INT_CONST";

    case FLOAT_CONST:
        return "FLOAT_CONST";

    case CHAR_LITERAL:
        return "CHAR_LITERAL";

    case FMT_STRING:
        return "FMT_STRING";

    default:
        return "UNKNOWN_TOKEN";
    }
}

void print_token (Token token) {
    printf("l%d: <%s>(%s)", token.line, token_type_name(token.type), token.lexeme);
}

TokenList create_token_list()
{
    TokenList list;
    list.capacity = 10;
    list.count = 0;
    list.items = malloc(sizeof(Token) * list.capacity);
    return list;
}

void add_token(TokenList *list, Token token)
{
    if (list->count >= list->capacity)
    {
        list->capacity *= 2;
        list->items = realloc(list->items, sizeof(Token) * list->capacity);
    }
    list->items[list->count++] = token;
}

void print_token_list(TokenList *list)
{
    for (int i = 0; i < list->count; i++) {
        print_token(list->items[i]);
        printf("\n");
    }
}

void free_token_list(TokenList *list)
{
    for (int i = 0; i < list->count; i++)
    {
        free(list->items[i].lexeme);
    }
    free(list->items);
}