#include "helper.h"


int getPrecedence(char c) {
    if (c == '*' || c == '/') {
        return 2;
    } else { 
        return 1;
    }
}
float evaluateRPN(node_t **queue) {
    sf numstack;
    create_stack_f(&numstack);
    float first = 0.0, second = 0.0;
    while (*queue != NULL) {
        float token = dequeue(queue);
        if (strchr(operands, token) == NULL && strchr(functions, token) == NULL) {
            push_f(&numstack, token);
        } else {
            float result = 0.0;
            if (strchr(operands, token) != NULL) {
                second = pop_f(&numstack);
                first = pop_f(&numstack);
                switch ((int)token){
                    case '+':
                        result = first+second;
                        break;
                    case '-':
                        result = first-second;
                        break;
                    case '*':
                        result = first*second;
                        break;
                    case '/':
                        result = first/second;
                        break;
                }
            } else {
                first = pop_f(&numstack);
                switch ((int)token) {
                    case 's':
                        result = sinf(first);
                        break;
                    case 'c':
                        result = cosf(first);
                        break;
                    case 't':
                        result = tanf(first);
                        break;
                    case 'a':
                        result = asinf(first);
                        break;
                    case 'b':
                        result = acosf(first);
                        break;
                    case 'd':
                        result = atanf(first);
                        break;
                    case 'q':
                        result = sqrtf(first);
                        break;
                    case 'n':
                        result = logf(first);
                        break;
                    case 'l':
                        result = log10f(first);
                        break;
                }
                
            }
            push_f(&numstack, result);
        }
    }
    return pop_f(&numstack);
}

float calculate(char *s) {
    node_t *queue = NULL;
    ss stack;
    create_stack_s(&stack);
    int len = strlen(s);
    bool checkUnary = true;

    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (c == ' ') {
            continue;
        }

        if (checkUnary) {
            checkUnary = false;
            if (c == '+' || c == '-') {
                push_s(&stack, '0');
            }
        }

        if (isdigit(c)) {
            int num = c - '0';
            while (i + 1 < len && isdigit(s[i + 1])) {
                num = num * 10 + s[i + 1] - '0';
                i++;
            }
            enqueue(&queue, num);
        } else if (c == '(') {
            checkUnary = true;
            push_s(&stack, '(');
        } else if (c == ')') {
            while (view_top_s(&stack) != '(') {
                enqueue(&queue, pop_s(&stack));
            }
            pop_s(&stack);
        } else if (strchr(functions, c) != NULL) {
            push_s(&stack, c);
            checkUnary = true;
        } else {
            while (!is_empty_s(&stack) && view_top_s(&stack) != '(' && getPrecedence(c) <= getPrecedence(view_top_s(&stack))) {
                enqueue(&queue, pop_s(&stack));
            }
            push_s(&stack, c);
        }
    }

    while (!is_empty_s(&stack)) {
        enqueue(&queue, pop_s(&stack));
    }

    return evaluateRPN(&queue);
}
