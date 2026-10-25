#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

typedef struct ReservedWord
{
    char *literal;
    TokenType type;
} ReservedWord;

ReservedWord RESERVED_WORDS[11] =
    {
        {"fn", FUNCTION},
        {"if", IF},
        {"let", LET},
        {"int", INT},
        {"main", MAIN},
        {"char", CHAR},
        {"else", ELSE},
        {"float", FLOAT},
        {"while", WHILE},
        {"return", RETURN},
        {"println", PRINTLN}};

typedef struct Lexer
{
    char *source;
    int length;
    int position;
    int line;
} Lexer;

// Helper file reading function
char *read_file(char *path)
{
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    unsigned long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *source_code = malloc(sizeof(char) * file_size);
    if (source_code == NULL)
    {
        return NULL;
    }

    fread(source_code, 1, file_size + 1, file);

    fclose(file);

    source_code[file_size] = '\0';

    return source_code;
}

// Helper char dealing functions
char curr_char(Lexer *lexer)
{
    return lexer->source[lexer->position];
}

char peek_char(Lexer *lexer)
{
    if (lexer->position + 1 < lexer->length)
    {
        return lexer->source[lexer->position + 1];
    }
    return '\0';
}

void advance_char(Lexer *lexer)
{
    lexer->position++;
}

char *cp_lexeme(Lexer *lexer, int start)
{
    int length = lexer->position - start + 1;
    char *lexeme = malloc((length + 1) * sizeof(char));

    if (lexeme == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < length; i++)
    {
        lexeme[i] = lexer->source[start + i];
    }
    lexeme[length] = '\0';

    return lexeme;
}

// Ignore the first and last quote in the lexeme if it is a char or string
char *cp_inner_lexeme(Lexer *lexer, int start)
{
    int length = lexer->position - start - 1;

    if (length < 0) length = 0;

    char *lexeme = malloc((length + 1) * sizeof(char));
    if (lexeme == NULL) return NULL;

    for (int i = 0; i < length; i++)
    {
        lexeme[i] = lexer->source[start + 1 + i];
    }
    lexeme[length] = '\0';

    return lexeme;
}

// Helper char cathegorization functions
int issymb(char c)
{
    if (c == '=' || c == '!' || c == '>' || c == '<' || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '{' || c == '}' || c == ':' || c == ';' || c == ',')
    {
        return 1;
    }
    return 0;
}

int issep(char c)
{
    if (issymb(c) || isspace(c) || c == '\0')
    {
        return 1;
    }
    return 0;
}

int isquotes(char c)
{
    if (c == '\'' || c == '"')
    {
        return 1;
    }
    return 0;
}

// Helper printing functions
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

// Lexeme scanning functions
TokenType scan_reserved(Lexer *lexer, int start)
{
    int length = lexer->position - start + 1;

    // Early return
    if (length < 2 || length > 7)
    {
        return ID;
    }

    switch (length)
    {
    case 2:
        if (strncmp(&lexer->source[start], "fn", 2) == 0)
            return FUNCTION;
        if (strncmp(&lexer->source[start], "if", 2) == 0)
            return IF;
        break;
    case 3:
        if (strncmp(&lexer->source[start], "let", 3) == 0)
            return LET;
        if (strncmp(&lexer->source[start], "int", 3) == 0)
            return INT;
        break;
    case 4:
        if (strncmp(&lexer->source[start], "main", 4) == 0)
            return MAIN;
        if (strncmp(&lexer->source[start], "char", 4) == 0)
            return CHAR;
        if (strncmp(&lexer->source[start], "else", 4) == 0)
            return ELSE;
        break;
    case 5:
        if (strncmp(&lexer->source[start], "float", 5) == 0)
            return FLOAT;
        if (strncmp(&lexer->source[start], "while", 5) == 0)
            return WHILE;
        break;
    case 6:
        if (strncmp(&lexer->source[start], "return", 6) == 0)
            return RETURN;
        break;
    case 7:
        if (strncmp(&lexer->source[start], "println", 7) == 0)
            return PRINTLN;
        break;
    }
    return ID;
}

/*
TokenType scan_reserved(Lexer *lexer, int start)
{
    int length = lexer->position - start + 1;
    int n_reserved = sizeof(RESERVED_WORDS) / sizeof(RESERVED_WORDS[0]);

    for (int i = 0; i < n_reserved; i++)
    {
        if (strlen(RESERVED_WORDS->literal) == length &&
            strncmp(&lexer->source[start], RESERVED_WORDS[i].literal, length))
        {
            return RESERVED_WORDS[i].type;
        }
    }
    return ID;
}
*/

TokenType scan_word(Lexer *lexer)
{
    int start = lexer->position;
    int possible_reserved = 1;

    char c = curr_char(lexer);
    if(islower(c))
    {
        while (1)
        {
            c = peek_char(lexer);
            if (isdigit(c) || c == '_')
            {
                possible_reserved = 0;
                advance_char(lexer);
            }
            else if (isalpha(c))
            {
                advance_char(lexer);
            }
            else if (issep(c))
            {
                if (possible_reserved)
                {
                    return scan_reserved(lexer, start);
                }
                return ID;
            }
            else
            {
                return TOKEN_ERROR;
            }
        }
    }
    else
    {
        while (1)
        {
            char c = peek_char(lexer);
            if (issep(c))
            {
                break;
            }
            advance_char(lexer);
        }
        return TOKEN_ERROR;
    }
}

TokenType scan_number(Lexer *lexer)
{
    TokenType num_type = INT_CONST;
    while (1)
    {
        char c = peek_char(lexer);
        if (isdigit(c))
        {
            advance_char(lexer);
        }
        else if (c == '.')
        {
            if (num_type == FLOAT_CONST)
            {
                return TOKEN_ERROR;
            }

            advance_char(lexer);
            if (!isdigit(peek_char(lexer)))
            {
                return TOKEN_ERROR;
            }
            num_type = FLOAT_CONST;
            advance_char(lexer);
        }
        else if (issep(c))
        {
            return num_type;
        }
        else
        {
            return TOKEN_ERROR;
        }
    }
}

TokenType scan_symbol(Lexer *lexer)
{
    char c = curr_char(lexer);
    char next_c = peek_char(lexer);

    switch (c)
    {
    case '=':
        if (next_c == '=')
        {
            advance_char(lexer);
            return EQ;
        }
        return ASSIGN;

    case '!':
        if (next_c == '=')
        {
            advance_char(lexer);
            return NE;
        }
        return TOKEN_ERROR;

    case '>':
        if (next_c == '=')
        {
            advance_char(lexer);
            return GE;
        }
        return GT;

    case '<':
        if (next_c == '=')
        {
            advance_char(lexer);
            return LE;
        }
        return LT;

    case '+':
        return PLUS;

    case '-':
        if (next_c == '>')
        {
            advance_char(lexer);
            return ARROW;
        }
        return MINUS;

    case '*':
        return MULT;

    case '/':
        return DIV;

    case '{':
        return LBRACE;

    case '}':
        return RBRACE;

    case '(':
        return LBRACKET;

    case ')':
        return RBRACKET;

    case ':':
        return COLON;

    case ';':
        return SEMICOLON;

    case ',':
        return COMMA;
    default:
        return TOKEN_ERROR;
    }
}

TokenType scan_quotes(Lexer *lexer)
{
    char c = curr_char(lexer);
    switch (c)
    {
        case '\'':
            advance_char(lexer);
            advance_char(lexer);
            c = curr_char(lexer);
            if (c == '\'')
            {
                return CHAR_LITERAL;
            }
            else{
                return TOKEN_ERROR;
            }
        case '"':
            c = peek_char(lexer);
            while (peek_char(lexer) != '"' && peek_char(lexer) != '\n' && peek_char(lexer) != '\0')
            {
                advance_char(lexer);
            }

            if (peek_char(lexer) == '"')
            {
                advance_char(lexer); // Consome a aspa de fechamento
                return FMT_STRING;
            }
            return TOKEN_ERROR;

        default:
            return TOKEN_ERROR;
    }
}

Token scan_token(Lexer *lexer)
{
    char c = curr_char(lexer);
    int start = lexer->position;

    TokenType type = TOKEN_ERROR;
    if (isalpha(c))
        type = scan_word(lexer);
    if (isdigit(c))
        type = scan_number(lexer);
    if (issymb(c))
        type = scan_symbol(lexer);
    if (isquotes(c))
        type = scan_quotes(lexer);

    char *lexeme;
    if (type == CHAR_LITERAL || type == FMT_STRING)
    {
        lexeme = cp_inner_lexeme(lexer, start);
    }
    else
    {
        lexeme = cp_lexeme(lexer, start);
    }

    Token token = {
        .lexeme = lexeme,
        .type = type,
        .line = lexer->line};

    return token;
}

typedef struct TokenList
{
    Token *items;
    int capacity;
    int count;
} TokenList;

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

void free_token_list(TokenList *list)
{
    for (int i = 0; i < list->count; i++)
    {
        free(list->items[i].lexeme);
    }
    free(list->items);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Proper usage: compiler path.txt\n");
        return 1;
    }

    char *source_code = read_file(argv[1]);
    if (source_code == NULL)
    {
        return 0;
    }

    Lexer lexer = {
        .source = source_code,
        .length = strlen(source_code),
        .position = 0,
        .line = 1};

    TokenList token_list = create_token_list();
    
    while (lexer.position < lexer.length)
    {
        char c = curr_char(&lexer);

        if (isspace(c))
        {
            if (c == '\n')
                lexer.line++;
            advance_char(&lexer);
        }
        else
        {
            Token token = scan_token(&lexer);
            add_token(&token_list, token); 
            advance_char(&lexer);
        }
    }

    for (int i = 0; i < token_list.count; i++)
    {
        printf("%d: <%s>(%s)\n", 
               token_list.items[i].line, 
               token_type_name(token_list.items[i].type), 
               token_list.items[i].lexeme);
    }

    free_token_list(&token_list);
    free(source_code);
    return 0;
}