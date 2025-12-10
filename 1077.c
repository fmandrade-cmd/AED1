#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 305

char stack[MAX_SIZE];
int top = -1;

// Funções da pilha
void push(char c) {
    stack[++top] = c;
}

char pop() {
    if (top == -1) return '\0';
    return stack[top--];
}

char peek() {
    if (top == -1) return '\0';
    return stack[top];
}

int isEmpty() {
    return top == -1;
}

// Retorna a precedência do operador
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Verifica se é operador
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Verifica se é operando (letra ou número)
int isOperand(char c) {
    return isalnum(c);
}

// Converte infixa para posfixa
void infixToPostfix(char* infix, char* postfix) {
    int i, j = 0;
    char c;
    
    top = -1; // Reseta a pilha
    
    for (i = 0; infix[i] != '\0' && infix[i] != '\n'; i++) {
        c = infix[i];
        
        // Se for espaço, ignora
        if (c == ' ') continue;
        
        // Se for operando, adiciona à saída
        if (isOperand(c)) {
            postfix[j++] = c;
        }
        // Se for parêntese esquerdo, empilha
        else if (c == '(') {
            push(c);
        }
        // Se for parêntese direito
        else if (c == ')') {
            while (!isEmpty() && peek() != '(') {
                postfix[j++] = pop();
            }
            if (!isEmpty() && peek() == '(') {
                pop(); // Remove o '('
            }
        }
        // Se for operador
        else if (isOperator(c)) {
            // ^ é associativo à direita, os outros à esquerda
            if (c == '^') {
                // Para ^, desempilha apenas operadores de maior precedência
                while (!isEmpty() && precedence(peek()) > precedence(c)) {
                    postfix[j++] = pop();
                }
            } else {
                // Para outros operadores, desempilha operadores de >= precedência
                while (!isEmpty() && precedence(peek()) >= precedence(c)) {
                    postfix[j++] = pop();
                }
            }
            push(c);
        }
    }
    
    // Desempilha todos os operadores restantes
    while (!isEmpty()) {
        postfix[j++] = pop();
    }
    
    postfix[j] = '\0';
}

int main() {
    int n;
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];
    
    scanf("%d", &n);
    getchar(); // Consome o '\n' após o número
    
    while (n--) {
        fgets(infix, MAX_SIZE, stdin);
        
        // Remove o '\n' se existir
        int len = strlen(infix);
        if (len > 0 && infix[len-1] == '\n') {
            infix[len-1] = '\0';
        }
        
        infixToPostfix(infix, postfix);
        printf("%s\n", postfix);
    }
    
    return 0;
}
