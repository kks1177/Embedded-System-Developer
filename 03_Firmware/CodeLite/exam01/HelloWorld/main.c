#include <stdio.h>

char* str = "abcd\n";

void print_str(void);

int main(int argc, char **argv)
{
    char* str = "hello World!\n";
	printf("%s", str);
    
    print_str();
	return 0;
}


void print_str(void) {
    printf("%s", str+6);
}