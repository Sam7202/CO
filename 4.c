#include<stdio.h>
int main()
{ 
    int i = 0;
    int h[9] = {0}, x[6] = {0}, y[6] = {0}; 
    FILE *input = fopen("../input/4.txt", "r");
    for(i = 0; i < 9; i++) fscanf(input, "%d", &h[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &x[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &y[i]);
    fclose(input);
    
    int *p_x = &x[0];
    int *p_h = &h[0];
    int *p_y = &y[0];
    
    
    int i1 = 0;
    int j = 0;
    int f = 0;
    int temp1 = 0;
    //for nums
    
    int bound_3 = 3;
    int bound_2 = 2;
    int num12 =12;
    asm volatile(
    	//loop1
    	"loop1:\n\t"
    	"beq %[i],%[bound3], Exit\n\t"
    	"addi %[i], %[i], 1\n\t"
    	"add %[p_x], %[p_x], %[x0]\n\t" //p_x = &x[0]
    	"add %[j], x0,x0\n\t"	//reset j to new loop2
    	
    	/* do matrix multiply */
    	//loop2
    	"loop2:\n\t"
    	"beq %[j],%[bound2], loop1\n\t"
    	"addi %[j], %[j], 1\n\t"
    	"mul %[temp1], %[i], %[num12]\n\t" //temp = i * 3
    	"add %[p_h], %[temp1], %[h0]\n\t" //p_h = temp + &h[0](may need *12)
    	"add %[f], x0,x0\n\t"	//reset f to new loop2
    	//loop3
    	"loop3:\n\t"
    	"beq %[f],%[bound3], nextElement\n\t"
    	"addi %[f], %[f], 1\n\t"
    	//next element
    	"nextElement:\n\t"
    	"add %[p_x] , x0, %[x1]\n\t"
    	
    	"Exit:\n\t"
    	:[i]"+r"(i1), [j]"+r"(j), [f]"+r"(f), [p_x]"+r"(p_x),[p_ys]"+r"(p_y), [p_h]"+r"(p_h), [temp1]"+r"(temp1)
    	:[x0]"r"(&x[0]), [bound3]"r"(bound_3), [bound2]"r"(bound_2), [h0]"r"(&h[0]), [num12]"r"(num12), [x1]"r"(&x[1]),
    	:
    );

    p_y = &y[0];
    for(i = 0; i < 6; i++)
        printf("%d ", *p_y++);
    printf("\n");
    return 0; 
 
}
