#include <stdlib.h>
#include <stdio.h>


int main(int argc, char **argv){
    (void) argc;
    int a= strtol(argv[1], NULL, 10);
    perror("strol");
    printf("%d\n", a);
}