#include "lexical.h"

#ifndef _KEYWORD_HASHMAP_SIZE
#define _KEYWORD_HASHMAP_SIZE 50
#endif

STATIC
hashmap_t *_keyword_hashmap = NULL;

#define _KEYWORD_HASHMAP_PUT(name, kind)    \
do                                          \
{                                           \
    if (                                    \
        hashmap_put(                        \
            _keyword_hashmap,               \
            strlen((const char *)name),     \
            (void*)name,                    \
            (void *)kind                    \
            ) != 0                          \
        )                                   \
    {                                       \
        error_novarg(EXIT_FAILURE, ".");    \
    }                                       \
} while (0)                                 \

void init_lexical(
    int stdc
    )
{

    if (_keyword_hashmap != NULL)
    {

        error_novarg(EXIT_FAILURE, ".");

    }

    _keyword_hashmap = new_hashmap(_KEYWORD_HASHMAP_SIZE, Idjb2hashfunc); /* Ifnv1ahashfunc */

    if (_keyword_hashmap == NULL)
    {

        error_novarg(EXIT_FAILURE, ".");

    }

#define __ckeyword(name, kind) _KEYWORD_HASHMAP_PUT(name, kind);
#include "ckeywords.inc"

    switch (stdc)
    {

    case ANCC_STDC89:
        break;

    case ANCC_STDC99:
#include "c99keywords.inc"
        break;

    default:
        free_hashmap(_keyword_hashmap);
        _keyword_hashmap = NULL;
        error(EXIT_FAILURE, "STDC %d not recognized or implemented.", stdc);
    	return;

    }

    return;

#undef __ckeyword

}

void quit_lexical(
	void
	)
{

    if (_keyword_hashmap == NULL)
    {

        error_novarg(EXIT_FAILURE, ".");

    }

    free_hashmap(_keyword_hashmap);
    _keyword_hashmap = NULL;

    return;

}

STATIC
const token_kind_t token_kind_to_str_first_symbol = TOKEN_KIND_EXCLAMATION_MARK;

STATIC
const token_kind_t token_kind_to_str_last_symbol  = TOKEN_KIND_TILDE           ;

STATIC
const char *token_kind_to_str_symbol[] =
{

    [TOKEN_KIND_EXCLAMATION_MARK     ] = "!" ,
    [TOKEN_KIND_DOUBLE_QUOTATION_MARK] = "\"",
    [TOKEN_KIND_HASH                 ] = "#" ,
    /* $ */
    [TOKEN_KIND_PERCENT              ] = "%" ,
    [TOKEN_KIND_AMPERSAND            ] = "&" ,
    [TOKEN_KIND_SINGLE_QUOTATION_MARK] = "'" ,
    [TOKEN_KIND_LEFT_PARENTHESIS     ] = "(" ,
    [TOKEN_KIND_RIGHT_PARENTHESIS    ] = ")" ,
    [TOKEN_KIND_ASTERISK             ] = "*" ,
    [TOKEN_KIND_PLUS                 ] = "+" ,
    [TOKEN_KIND_SEMI                 ] = "," ,
    [TOKEN_KIND_MINUS                ] = "-" ,
    [TOKEN_KIND_DOT                  ] = "." ,
    [TOKEN_KIND_SLASH                ] = "/" ,
    /* 0 9 */
    [TOKEN_KIND_COLON                ] = ":" ,
    [TOKEN_KIND_SEMICOLON            ] = ";" ,
    [TOKEN_KIND_LESS_THAN            ] = "<" ,
    [TOKEN_KIND_EQUAL                ] = "=" ,
    [TOKEN_KIND_GREATER_THAN         ] = ">" ,
    [TOKEN_KIND_QUESTION_MARK        ] = "?" ,
    /* @ Z */
    [TOKEN_KIND_LEFT_BRACKET         ] = "[" ,
    [TOKEN_KIND_BACKSLASH            ] = "\\",
    [TOKEN_KIND_RIGHT_BRACKET        ] = "]" ,
    [TOKEN_KIND_CARET                ] = "^" ,
    /* ` z */
    [TOKEN_KIND_LEFT_BRACE           ] = "{" ,
    [TOKEN_KIND_PIPE                 ] = "|" ,
    [TOKEN_KIND_RIGHT_BRACE          ] = "}" ,
    [TOKEN_KIND_TILDE                ] = "~"

};

STATIC
const token_kind_t token_kind_to_str_first_keyword = TOKEN_KIND_KEYWORD_AUTO    ;

STATIC
const token_kind_t token_kind_to_str_last_keyword  = TOKEN_KIND_KEYWORD_RESTRICT;

STATIC
const char *token_kind_to_str_keyword[] =
{

#define __ckeyword(name, kind) [kind] = name,
#include "ckeywords.inc"

#include "c99keywords.inc"

#undef __ckeyword

};

const char *token_kind_to_string(token_kind_t kind)
{

    if (
        kind >= token_kind_to_str_first_symbol &&
        kind <= token_kind_to_str_last_symbol
        )
    {

        return token_kind_to_str_symbol[kind];

    }

    if (
        kind >= token_kind_to_str_first_keyword &&
        kind <= token_kind_to_str_last_keyword
        )
    {

        return token_kind_to_str_keyword[kind];

    }

    switch (kind)
    {

    case TOKEN_KIND_LINE_COMMENT : return "[<LINE_COMMENT>]" ;
	case TOKEN_KIND_BLOCK_COMMENT: return "[<BLOCK_COMMENT>]";

    case TOKEN_KIND_NUMBER_LITERAL   : return "[<NUMBER_LITERAL>]"   ;
    case TOKEN_KIND_CHARACTER_LITERAL: return "[<CHARACTER_LITERAL>]";
    case TOKEN_KIND_STRING_LITERAL   : return "[<STRING_LITERAL>]"   ;

    case TOKEN_KIND_IDENTIFIER: return "[<IDENTIFIER>]";

    case TOKEN_KIND_EOF: return "[<EOF>]";

    default:
        return NULL;

    }

    return NULL;

}

token_t *new_token(
    token_kind_t kind,
    char *value,
    const char *filename,
    size_t line,
    size_t column
)
{

    token_t *token = (token_t *)malloc(sizeof(token_t));

    if (token == NULL)
    {

        return NULL;

    }

    token->kind = kind;

    token->value = value;

    token->filename = filename;

    token->line = line;

    token->column = column;

    return token;

}

void free_token(token_t *token)
{

    if (
        token == NULL
        )
    {

        return;

    }

    if (token->value == NULL)
    {

        free(token->value);

    }

    free(token);

}

const char *token_to_string(token_t *token) /* TODO: Find a better way to write this function. */
{

    if (token == NULL)
    {

        return NULL;

    }

    if (
        token->kind >= token_kind_to_str_first_symbol &&
        token->kind <= token_kind_to_str_last_symbol
        )
    {

        return token_kind_to_str_symbol[token->kind];

    }

    if (
        token->kind >= token_kind_to_str_first_keyword &&
        token->kind <= token_kind_to_str_last_keyword
        )
    {

        return (const char *)token->value;

    }

    switch (token->kind)
    {

    case TOKEN_KIND_LINE_COMMENT : return "[<LINE_COMMENT>]" ;
	case TOKEN_KIND_BLOCK_COMMENT: return "[<BLOCK_COMMENT>]";

    case TOKEN_KIND_NUMBER_LITERAL   :
    case TOKEN_KIND_CHARACTER_LITERAL:
    case TOKEN_KIND_STRING_LITERAL   :
        return (const char *)token->value;

    case TOKEN_KIND_IDENTIFIER:
        return (const char *)token->value;

    case TOKEN_KIND_EOF: return "[<EOF>]";

    default:
        return NULL;

    }

    return NULL;

}

STATIC
int lexer_next_char(
    lexer_t *lexer
    )
{

    lexer->int_c = getc(lexer->file);

    lexer->char_c = (char) lexer->int_c == EOF ? 0 : lexer->int_c;

    int file_error = ferror(lexer->file);

    if (file_error != 0)
    {

        error_novarg(EXIT_FAILURE, ".");

    }

    return 0;

}

lexer_t *new_lexer(
    FILE *file,
    const char *filename,
    size_t line,
    size_t column,
    struct lexer_s *next
    )
{

    if (
        file == NULL
        )
    {

        return NULL;

    }

    lexer_t *lexer = (lexer_t *)malloc(sizeof(lexer_t));

    if (lexer == NULL)
    {

        return NULL;

    }

    lexer->file = file;

    if (lexer_next_char(lexer) == 0)
    {

        free(lexer);

        return NULL;

    }

    lexer->buffer = new_buffer(LEXER_BUFFER_INITIAL_CAPACITY);

    if (lexer->buffer == NULL)
    {

        free(lexer);

        return NULL;

    }

    lexer->filename = filename;

    lexer->line = line;

    lexer->column = column;

    lexer->next = next;

    return lexer;

}

STATIC
int is_ascii_char(int c)
{
    return
    (
    /*  c == '\a'   || */
    /*  c == '\b'   || */
        c == '\t'   ||
        c == '\n'   ||
    /*  c == '\v'   || */
    /*  c == '\f'   || */
        c == '\r'   ||
    /*  c == '\x1B' || */ /* '\b' */
        (c >= ' ' && c <= '~') /* '~' or '\x7F' */
    );
}

STATIC
int is_symbol_char(int c)
{
    return
    (
          c != '$'              &&
        !(c >= '0' && c <= '9') &&
        !(c >= '@' && c <= 'Z') &&
        !(c >= '`' && c <= 'z') &&
        is_ascii_char(c)
    );
}

int lexer_lex(
    lexer_t *lexer,
    token_t *token
    );

void free_lexer(
    lexer_t *lexer
    )
{

    if (
        lexer == NULL
        )
    {

        return;

    }

    /* TODO: . */

    if (lexer->next != NULL)
    {

        free_lexer((lexer_t *)lexer->next);

    }

    free(lexer);

}
