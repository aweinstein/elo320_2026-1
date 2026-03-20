#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
 
#define MAX_TOKENS 64
#define MAX_TOKEN_LEN 16
 
typedef enum {
    TOKEN_NUMBER,
    TOKEN_OP,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_UNKNOWN
} TokenType;
 
typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LEN];
} Token;
 
typedef struct {
    Token tokens[MAX_TOKENS];
    int count;
} TokenList;
 
/*
 * tokenize()
 * Analiza la cadena de la expresión y la convierte en una lista de tokens.
 * Retorna 0 en caso de exito y -1 en caso de error
 (e.g. buffer overflow o un caracter desconocido).
 */
int tokenize(const char *expr, TokenList *list) {
    list->count = 0;
    const char *p = expr;
 
    while (*p != '\0') {
        if (isspace((unsigned char)*p)) {
            p++;
            continue;
        }
 
        if (list->count >= MAX_TOKENS) {
            fprintf(stderr, "Error: too many tokens (max %d)\n", MAX_TOKENS);
            return -1;
        }
 
        Token *tok = &list->tokens[list->count];
 
        if (isdigit((unsigned char)*p)) {
            int len = 0;
            while (isdigit((unsigned char)*p)) {
                if (len >= MAX_TOKEN_LEN - 1) {
                    fprintf(stderr, "Error: number too long\n");
                    return -1;
                }
                tok->value[len++] = *p++;
            }
            tok->value[len] = '\0';
            tok->type = TOKEN_NUMBER;
            list->count++;
 
        } else if (*p == '+' || *p == '-' || *p == '*' || *p == '/') {
            tok->value[0] = *p;
            tok->value[1] = '\0';
            tok->type = TOKEN_OP;
            list->count++;
            p++;
 
        } else if (*p == '(') {
            tok->value[0] = '(';
            tok->value[1] = '\0';
            tok->type = TOKEN_LPAREN;
            list->count++;
            p++;
 
        } else if (*p == ')') {
            tok->value[0] = ')';
            tok->value[1] = '\0';
            tok->type = TOKEN_RPAREN;
            list->count++;
            p++;
 
        } else {
            fprintf(stderr, "Error: unexpected character '%c'\n", *p);
            return -1;
        }
    }
 
    return 0;
}
 

/* Por conveniencia: imprime la lista de tokens para debuggear*/
void print_tokens(const TokenList *list) {
    const char *type_names[] = {"NUMBER", "OP", "LPAREN", "RPAREN", "UNKNOWN"};
    for (int i = 0; i < list->count; i++) {
        printf("[%s \"%s\"]\n", type_names[list->tokens[i].type], list->tokens[i].value);
    }
}

/* Probemos el tokenizer */
int main(void) {
    const char *expr = "(12 + 5 * 3) / 27";
    TokenList list;
 
    printf("Expresion: %s\n\n", expr);
 
    if (tokenize(expr, &list) != 0) {
        return 1;
    }
 
    printf("Tokens (%d):\n", list.count);
    print_tokens(&list);
 
    return 0;
}
