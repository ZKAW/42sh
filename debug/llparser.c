#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    NB_TOKENS,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    int value;
} Token;

static const char *tokens_list[] = {
    NULL,
    "+",
    "-",
    "*",
    "/",
    "(",
    ")",
    NULL,
    NULL,
};

typedef struct {
    char *input;
    int position;
    Token current_token;
} Parser;

void error();
Token get_next_token(Parser* parser);
void consume(Parser* parser, TokenType token_type);
int factor(Parser* parser);
int term(Parser* parser);
int expr(Parser* parser);

void error(char *msg) {
    printf("Error parsing input. %s\n", msg);
    exit(1);
}

int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

Token get_next_token(Parser* parser) {
    char current_char = parser->input[parser->position];

    if (current_char == '\0') {
        return (Token){TOKEN_EOF};
    }

    if (is_digit(current_char)) {
        char *buffer = malloc(sizeof(char) * 10);
        int buffer_size = 0;
        while (is_digit(current_char)) {
            buffer[buffer_size] = current_char;
            buffer_size++;
            parser->position++;
            current_char = parser->input[parser->position];
        }
        int value = atoi(buffer);
        free(buffer);
        return (Token){TOKEN_NUMBER, value};
    }

    for (int i = 1; i < NB_TOKENS; i++) {
        if (tokens_list[i] != NULL && strncmp(&current_char, tokens_list[i], 1) == 0) {
            parser->position++;
            return (Token){i};
        }
    }

    error("Invalid character");
    return (Token){0};
}

void consume(Parser* parser, TokenType token_type) {
    if (parser->current_token.type == token_type) {
        parser->current_token = get_next_token(parser);
    } else {
        error("Not the expected token");
    }
}

int factor(Parser* parser) {
    Token token = parser->current_token;
    if (token.type == TOKEN_NUMBER) {
        consume(parser, TOKEN_NUMBER);
        return token.value;
    } else if (token.type == TOKEN_LPAREN) {
        consume(parser, TOKEN_LPAREN);
        int value = expr(parser);
        consume(parser, TOKEN_RPAREN);
        return value;
    } else if (token.type == TOKEN_PLUS) {
        consume(parser, TOKEN_PLUS);
        return factor(parser);
    } else if (token.type == TOKEN_MINUS) {
        consume(parser, TOKEN_MINUS);
        return -factor(parser);
    }
    error("Not a factor");
}

int term(Parser* parser) {
    int value = factor(parser);

    while (parser->current_token.type == TOKEN_MULTIPLY ||
        parser->current_token.type == TOKEN_DIVIDE) {
        Token token = parser->current_token;
        if (token.type == TOKEN_MULTIPLY) {
            consume(parser, TOKEN_MULTIPLY);
            value *= factor(parser);
        } else if (token.type == TOKEN_DIVIDE) {
            consume(parser, TOKEN_DIVIDE);
            value /= factor(parser);
        }
    }

    return value;
}

int expr(Parser* parser) {
    int value = term(parser);

    while (parser->current_token.type == TOKEN_PLUS ||
        parser->current_token.type == TOKEN_MINUS) {
        Token token = parser->current_token;
        if (token.type == TOKEN_PLUS) {
            consume(parser, TOKEN_PLUS);
            value += term(parser);
        } else if (token.type == TOKEN_MINUS) {
            consume(parser, TOKEN_MINUS);
            value -= term(parser);
        }
    }

    return value;
}

int main(int argc, char **argv) {
    if (argc != 2)
        return 84;
    Parser parser;
    parser.position = 0;
    parser.input = strdup(argv[1]);
    parser.current_token = get_next_token(&parser);
    int result = expr(&parser);
    printf("Result: %d\n", result);
    return 0;
}
