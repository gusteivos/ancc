
#ifndef LEXICAL_H
#define LEXICAL_H

#include "ancc.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>

#include "buffer.h"
#include "hashfunc.h"
#include "hashmap.h"

void init_lexical(
    int stdc
    );

void quit_lexical(
	void
	);

enum token_kind_e
{

    TOKEN_KIND_EXCLAMATION_MARK         =  '!'  ,
    TOKEN_KIND_DOUBLE_QUOTATION_MARK,   /* '"' */
    TOKEN_KIND_HASH,                    /* '#' */
    /* $ */
    TOKEN_KIND_PERCENT                  =  '%'  ,
    TOKEN_KIND_AMPERSAND,               /* '&' */
    TOKEN_KIND_SINGLE_QUOTATION_MARK,   /* ''' */
    TOKEN_KIND_LEFT_PARENTHESIS,        /* '(' */
    TOKEN_KIND_RIGHT_PARENTHESIS,       /* ')' */
    TOKEN_KIND_ASTERISK,                /* '*' */
    TOKEN_KIND_PLUS,                    /* '+' */
    TOKEN_KIND_SEMI,                    /* ',' */
    TOKEN_KIND_MINUS,                   /* '-' */
    TOKEN_KIND_DOT,                     /* '.' */
    TOKEN_KIND_SLASH,                   /* '/' */
    /* 0 9 */
    TOKEN_KIND_COLON                    =  ':'  ,
    TOKEN_KIND_SEMICOLON,               /* ';' */
    TOKEN_KIND_LESS_THAN,               /* '<' */
    TOKEN_KIND_EQUAL,                   /* '=' */
    TOKEN_KIND_GREATER_THAN,            /* '>' */
    TOKEN_KIND_QUESTION_MARK,           /* '?' */
    /* @ Z */
    TOKEN_KIND_LEFT_BRACKET             =  '['  ,
    TOKEN_KIND_BACKSLASH,               /* '\' */
    TOKEN_KIND_RIGHT_BRACKET,           /* ']' */
    TOKEN_KIND_CARET,                   /* '^' */
    /* ` z */
    TOKEN_KIND_LEFT_BRACE               =  '{'  ,
    TOKEN_KIND_PIPE,                    /* '|' */
    TOKEN_KIND_RIGHT_BRACE,             /* '}' */
    TOKEN_KIND_TILDE,                   /* '~' */

	TOKEN_KIND_LINE_COMMENT = 256,
	TOKEN_KIND_BLOCK_COMMENT,

    TOKEN_KIND_NUMBER_LITERAL,
    TOKEN_KIND_CHARACTER_LITERAL,
    TOKEN_KIND_STRING_LITERAL,

    TOKEN_KIND_IDENTIFIER,

#define __ckeyword(name, kind) kind,
#include "ckeywords.inc"
#include "c99keywords.inc"

#undef __ckeyword

    TOKEN_KIND_EOF = EOF

};

typedef enum token_kind_e token_kind_t;

const char *token_kind_to_string(token_kind_t kind);

struct token_s
{

    token_kind_t kind;

    char *value;

    const char *filename;

    size_t line;

    size_t column;

};

typedef struct token_s token_t;

token_t *new_token(
    token_kind_t kind,
    char *value,
    const char *filename,
    size_t line,
    size_t column
    );

void free_token(token_t *token);

const char *token_to_string(token_t *token);

#ifndef LEXER_BUFFER_INITIAL_CAPACITY
#define LEXER_BUFFER_INITIAL_CAPACITY 1024
#endif

struct lexer_s
{

    FILE *file;

    const char *filename;

    size_t line;

    size_t column;

    struct lexer_s *next;

    int int_c;

    char char_c;

    buffer_t *buffer;

};

typedef struct lexer_s lexer_t;

lexer_t *new_lexer(
    FILE *file,
    const char *filename,
    size_t line,
    size_t column,
    struct lexer_s *next
    );

int lexer_lex(
    lexer_t *lexer,
    token_t *token
    );

void free_lexer(
    lexer_t *lexer
    );

#endif/*LEXICAL_H*/
