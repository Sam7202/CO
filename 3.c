#include<stdio.h>
int main()
{ 
    int f, i, j;
    int h[9] = {0}, x[6] = {0}, y[6] = {0}; 
    FILE *input = fopen("../input/3.txt", "r");
    for(i = 0; i < 9; i++) fscanf(input, "%d", &h[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &x[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &y[i]);
    fclose(input);
    int *p_x = &x[0] ;
    int *p_h = &h[0] ;
    int *p_y = &y[0] ;
    for (i = 0; i < 3; i++){ 
	/* p_x points to the beginning of the input vector */
	p_x = &x[0];
	/* do matrix multiply */
        for (j = 0; j < 2; j++){   
            p_h = &h[i * 3];     	
            for (f = 0; f < 3; f++){
            int reg = 0;
               	asm volatile(
                    "mul %[reg], %[h_i], %[x_i]\n\t"//reg = h[f] * x[f]	
                    "add %[y_i], %[y_i], %[reg]\n\t"//y[f] =y[f] + reg
                    "addi %[p_h], %[p_h], 4\n\t"//p_h++
                    "addi %[p_x], %[p_x], 8\n\t"//p_x+=8(1->3->5)
                    
                    
                    :[y_i]"+r"(*p_y), [p_x]"+r"(p_x), [p_h]"+r"(p_h),[reg] "+r" (reg)//output
                    :[h_i]"r"(*p_h), [x_i]"r"(*p_x)//input
                    :
               	);
            }
            /* next element */
	    p_x = &x[1];
	    p_y++;
	}
    }
    p_y = &y[0];
    for(i = 0; i < 6; i++)
    printf("%d ", *p_y++);
    printf("\n");
    return 0; 
 
}
