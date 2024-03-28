#ifndef HELPER_H
#define HELPER_H

#include "structures.h"
#include <ctype.h>
#include <math.h>

#define functions "sctabdqnlm" // s-sin c-cos t-tan a-asin b-acos d-atan q-sqrt n-ln l-log m-mod
#define operands "+-*/^" //how to check for unary + and - idk
#define precedence "11223"
#define associativity "llllr"
#define numbers "01234567890"


float evaluateRPN(node_t **queue);
int getPrecedence(char c);
float calculate(char *s);


#endif