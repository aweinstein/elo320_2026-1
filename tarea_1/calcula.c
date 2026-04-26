#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXSIZE 100

typedef struct {
    int n;           /* numero de elementos en el stack */
    int data[MAXSIZE];
} stack;

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

/* Prototipos de Funciones */
stack *make_stack(void);
void   push(stack *sp, int a);
int    pop(stack *sp);
int    stack_top(stack *sp);
int    stack_empty(stack *sp);
int    tokenize(const char *expr, TokenList *list);
int    check_balanced(const TokenList *list);
int    precedence(char op);
void   apply_op(stack *operands, char op);
int    evaluate(const TokenList *list, int *result);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s \"<expresion>\"\n", argv[0]);
        return 1;
    }

    const char *expr = argv[1];
    TokenList list;

    /* Tokenizar */
    if (tokenize(expr, &list) != 0) {
        return 1;
    }

    /* Verificar paréntesis balanceados usando un stack */
    if (!check_balanced(&list)) {
        fprintf(stderr, "Error: los parentesis no estan balanceados\n");
        return 1;
    }

    /* Evaluar con dos stacks */
    int result;
    evaluate(&list, &result);

    printf("Resultado: %d\n", result);
    return 0;
}

/* Implementación de Stack */

stack *make_stack(void) {
    stack *sp = malloc(sizeof(stack));
    if (sp == NULL) {
        fprintf(stderr, "Error: no se pudo reservar memoria para el stack\n");
        exit(1);
    }
    sp->n = 0;
    return sp;
}

void push(stack *sp, int a) {
    if (sp->n == MAXSIZE) {
        fprintf(stderr, "Error: stack overflow\n");
        exit(1);
    }
    sp->data[sp->n++] = a;
}

int pop(stack *sp) {
    if (sp->n == 0) {
        fprintf(stderr, "Error: stack underflow\n");
        exit(1);
    }
    return sp->data[--(sp->n)];
}

int stack_top(stack *sp) {
    return sp->data[sp->n - 1];
}

int stack_empty(stack *sp) {
    return sp->n == 0;
}

/* Tokenizer */
/* Copiado desde  https://github.com/aweinstein/elo320_2026-1/blob/main/tarea_1/tokenizer.c*/
int tokenize(const char *expr, TokenList *list) {
    list->count = 0;
    const char *p = expr;
    while (*p != '\0') {
        if (isspace((unsigned char)*p)) { p++; continue; }
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

int check_balanced(const TokenList *list) {
    stack *s = make_stack();
    int balanced = 1;

    for (int i = 0; i < list->count; i++) {
        TokenType t = list->tokens[i].type;
        if (t == TOKEN_LPAREN) {
            push(s, '(');
        } else if (t == TOKEN_RPAREN) {
            if (stack_empty(s)) {
                balanced = 0;
                break;
            }
            pop(s);
        }
    }

    if (!stack_empty(s)) balanced = 0;
    free(s);
    return balanced;
}


int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void apply_op(stack *operands, char op) {
    int b = pop(operands);
    int a = pop(operands);
    int result;
    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': result = a / b; break;
        default:  result = 0;
    }
    push(operands, result);
}

int evaluate(const TokenList *list, int *result) {
    stack *operators = make_stack();  /* guarda ASCII del operador/paréntesis */
    stack *operands  = make_stack();  /* guarda valores enteros */

    for (int i = 0; i < list->count; i++) {
        const Token *tok = &list->tokens[i];

        if (tok->type == TOKEN_NUMBER) {
            push(operands, atoi(tok->value));

        } else if (tok->type == TOKEN_OP) {
            char op = tok->value[0];
            /* Mientras el tope tenga mayor o igual precedencia, aplicar */
            while (!stack_empty(operators) &&
                   (char)stack_top(operators) != '(' &&
                   precedence((char)stack_top(operators)) >= precedence(op)) {
                apply_op(operands, (char)pop(operators));
            }
            push(operators, (int)op);

        } else if (tok->type == TOKEN_LPAREN) {
            push(operators, (int)'(');

        } else if (tok->type == TOKEN_RPAREN) {
            /* Aplicar operadores hasta el '(' correspondiente */
            while (!stack_empty(operators) && (char)stack_top(operators) != '(') {
                apply_op(operands, (char)pop(operators));
            }
            if (!stack_empty(operators)) pop(operators); /* descarta '(' */
        }
    }

    /* Aplicar operadores restantes */
    while (!stack_empty(operators)) {
        apply_op(operands, (char)pop(operators));
    }

    *result = pop(operands);
    free(operators);
    free(operands);
    return 0;
}
