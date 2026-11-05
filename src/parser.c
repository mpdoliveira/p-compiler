#include <stdio.h>
#include <stdlib.h>

#include "token.h"

typedef struct Parser
{
    const TokenList list;
    int position;
} Parser;

static TokenType peek_token(Parser *parser)
{
    if (parser->position < parser->list.count)
    {
        return parser->list.items[parser->position + 1].type;
    }

    return END;
}

static void advance_token(Parser *parser)
{
    parser->position++;
}

static TokenType curr_token(Parser *parser)
{
    return parser->list.items[parser->position].type;
}

static void write_erorr(Parser *parser)
{
    printf("Erro\n");
}


static int type(parser)
{
    if (peek_token(parser) == INT)
    {
        advance_token(parser);
        return;
    }

    if (peek_token(parser) == FLOAT)
    {
        advance_token(parser);
        return;
    }

    if (peek_token(parser) == CHAR)
    {
        advance_token(parser);
        return;
    }

    write_erorr(parser);
}

static int function_return_type(Parser *parser)
{
}

static void sequence(Parser *parser)
{
}

static void block(Parser *parser)
{
    if (peek_token(parser) != LBRACE)
    {
        write_erorr(parser);
    }
    advance_token(parser);

    sequence(parser);

    if (peek_token(parser) != RBRACE)
    {
        write_erorr(parser);
    }
    advance_token(parser);
}

static int parameter_list(Parser *parser)
{
    if (peek_token(parser) != ID)
    {
        write_erorr(parser);
    }
    advance_token(parser);

    if (peek_token(parser) != COLON)
    {
        write_erorr(parser);
    }
    advance_token(parser);

    type(parser);

    if (peek_token(parser) != COMMA)
    {
        parameter_list(parser);
    }
}

static int function_name(Parser *parser)
{
    if (peek_token(parser) != ID)
    {
        write_erorr(parser);
    }
    advance_token(parser);

    if (peek_token(parser) != MAIN)
    {
        write_error(parser);
    }
    advance_token(parser);
}

static void function(Parser *parser)
{
    if (peek_token(parser) != FUNCTION)
    {
        write_erorr(parser);
    }
    advance_token(parser);

    function_name(parser);

    if (peek_token(parser) != LBRACKET)
    {
        write_erorr(parser);
    }
    advance_token(parser);

    if (peek_token(parser) != RBRACKET)
    {
        parameter_list(parser);
        if (peek_token(parser) != RBRACKET)
        {
            write_erorr(parser);
        }
    }
    advance_token;

    function_return_type(parser);

    block(parser);
}

static int program(Parser *parser)
{
    function(parser);
}