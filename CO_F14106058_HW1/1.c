#include <stdio.h>
int main(){
	int a, b;
	FILE *input = fopen("../input/1.txt", "r");
	fscanf(input, "%d %d", &a, &b);
	fclose(input);
	//a = a - b;
	asm volatile(
		"sub %[a], %[a], %[b]\n\t" //AssemblerTemplate
		:[a] "+r"(a) //OutputOperands, "=r" means write-only, "+r"

		:[b] "r"(b) //InputOperands
		);
	printf("%d\n", a);
	return 0;
}


