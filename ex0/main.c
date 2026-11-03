#include <stdio.h>

int b;
int foo(){
    printf("this is foo");
    return 0;
}
int main() {
    int x;
    int y;
    x=5;
    y=3;
    printf("%p\n",&b);
    printf("%p" ,foo);
    return 0;
}