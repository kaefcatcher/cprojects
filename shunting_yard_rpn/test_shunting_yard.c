#include "helper.h"

int main() {
    char expression[] = "2+2*2/2";
    float result = calculate(expression);
    printf("Result: %5f\n", result);


    char expression1[] = "s(2+2)";
    float result1 = calculate(expression1);
    printf("Result: %5f\n", result1);

    return 0;
}
