#include "structures.h"


int main(){
    sf *s=(sf *)malloc(sizeof(sf));
    create_stack_i(s);
    for (int i=0;i<10;i++){
        push_i(s,i);
    }
    print_si(s);

    ss *s1=(ss *)malloc(sizeof(ss));
    create_stack_s(s1);
    for (int i=0;i<10;i++){
        push_s(s1,'A');
    }
    print_ss(s1);

    return 0;
}