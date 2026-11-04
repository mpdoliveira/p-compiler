#ifndef TOKEN_H
#define TOKEN_H

typedef enum TokenType
{
    TOKEN_ERROR,
    FUNCTION,
    MAIN,
    LET,
    INT,
    FLOAT,
    CHAR,
    IF,
    ELSE,
    WHILE,
    PRINTLN,
    RETURN,
    LBRACKET,
    RBRACKET,
    LBRACE,
    RBRACE,
    ARROW,
    COLON,
    SEMICOLON,
    COMMA,
    ASSIGN,
    EQ,
    NE,
    GT,
    GE,
    LT,
    LE,
    PLUS,
    MINUS,
    MULT,
    DIV,
    ID,
    INT_CONST,
    FLOAT_CONST,
    CHAR_LITERAL,
    FMT_STRING
} TokenType;

typedef struct Token
{
    char *lexeme;
    TokenType type;
    int line;
} Token;

void print_token (Token token);

typedef struct TokenList
{
    Token *items;
    int capacity;
    int count;
} TokenList;

const char *token_type_name(TokenType type);

TokenList create_token_list();

void add_token(TokenList *list, Token token);

void print_token_list(TokenList *list);

void free_token_list(TokenList *list);

#endif