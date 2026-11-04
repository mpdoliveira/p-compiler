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
