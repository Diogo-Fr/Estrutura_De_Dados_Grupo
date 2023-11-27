#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

// Estrutura de pilha
typedef struct {
    double *items;
    int top;
    int capacity;
} Stack;

// Funções para operações da pilha
void initialize(Stack *stack, int capacity) {
    stack->capacity = capacity;
    stack->top = -1;
    stack->items = (double *)malloc(sizeof(double) * capacity);
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

void push(Stack *stack, double item) {
    if (!isFull(stack)) {
        stack->items[++stack->top] = item;
    } else {
        printf("Erro: Pilha cheia\n");
        exit(EXIT_FAILURE);
    }
}

double pop(Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->items[stack->top--];
    } else {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

// Função para avaliar expressões posfixas
double evaluatePostfix(char *expression) {
    Stack stack;
    initialize(&stack, 100);

    char *token = strtok(expression, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&stack, atof(token));
        } else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/') {
            if (stack.top >= 1) {
                double operand2 = pop(&stack);
                double operand1 = pop(&stack);
                switch (token[0]) {
                    case '+':
                        push(&stack, operand1 + operand2);
                        break;
                    case '-':
                        push(&stack, operand1 - operand2);
                        break;
                    case '*':
                        push(&stack, operand1 * operand2);
                        break;
                    case '/':
                        push(&stack, operand1 / operand2);
                        break;
                    default:
                        break;
                }
            } else {
                printf("Erro: Operador %c sem operandos suficientes\n", token[0]);
                exit(EXIT_FAILURE);
            }
   		} else if (strcmp(token, "^") == 0) {
   			if (stack.top >= 1) {
       		 	double base = pop(&stack);
        		double exponent = pop(&stack);
       		 	push(&stack, pow(base, exponent));
   		} else {
       		 printf("Erro: Operador ^ sem operandos suficientes\n");
       		 exit(EXIT_FAILURE);
   			}
        } else if (strcmp(token, "log") == 0) {
            if (!isEmpty(&stack)) {
                double x = pop(&stack);
                push(&stack, log10(x));
            } else {
                printf("Erro: Função log sem argumento\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(token, "sin") == 0) {
            if (!isEmpty(&stack)) {
                double angle = pop(&stack);
                push(&stack, sin(angle));
            } else {
                printf("Erro: Função sin sem argumento\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(token, "cos") == 0) {
            if (!isEmpty(&stack)) {
                double angle = pop(&stack);
                push(&stack, cos(angle));
            } else {
                printf("Erro: Função cos sem argumento\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(token, "tan") == 0) {
            if (!isEmpty(&stack)) {
                double angle = pop(&stack);
                push(&stack, tan(angle));
            } else {
                printf("Erro: Função tan sem argumento\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " ");
    }

    if (!isEmpty(&stack)) {
        double result = pop(&stack);
        if (isEmpty(&stack)) {
            return result;
        } else {
            printf("Erro: Operandos restantes na pilha\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Erro: Nenhum resultado na pilha\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Testes
    char expressions[][50] = {
        "3 4 + 5 *",  // Notação posfixa
        "7 2 * 4 +",  // Notação posfixa
        "8 5 2 4 + * + ",  // Notação posfixa
        "6 2 / 3 + 4 *",  // Notação posfixa
        "9 5 2 8 * 4 + * + ",  // Notação posfixa
        "2 3 + log 5 /",  // Notação posfixa
        "10 log 3 ^ 2 +",  // Notação posfixa
        "45 60 + 30 cos * ",  // Notação posfixa
        "0.5 45 sin 2 ^ +",  // Notação posfixa
        "3 4 + 5 tan * ",  // Notação posfixa
    };

    double results[] = {35, 18, 38, 24, 109, 0.14, 5, 16.2, 2.3, -23.66};

    for (int i = 0; i < 10; i++) {
        double result = evaluatePostfix(expressions[i]);
        printf("Teste %d: Resultado = %.2f (Esperado = %.2f)\n", i + 1, result, results[i]);
    }

    return 0;
}
