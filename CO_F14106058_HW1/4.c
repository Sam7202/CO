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
    	"add %[j], %[x0],%[x0]\n\t"	//reset j to new loop2

    	
    	"mv %[p_x], %[x_0]\n\t" //p_x = &x[0]
    	/* do matrix multiply */
    	//loop2
    	"loop2:\n\t"
    	"add %[f], %[x0],%[x0]\n\t"	//reset f to new loop3
    	"lw a5, 0(%[p_y])\n\t"//load *p_y to a5
    	
    	"mul %[temp1], %[i], %[num12]\n\t" //temp = i * 3
    	"add %[p_h], %[temp1], %[h0]\n\t" //p_h = temp + &h[0](may need *12)
    	
    	//loop3
    	"loop3:\n\t"
    	
    	"lw a6, 0(%[p_h])\n\t"// load *p_h

    	"lw a7, 0(%[p_x])\n\t"// load *p_x

    	"mul a6, a6, a7\n\t"//temp1 = *p_h * *p_x	

        "add a5, a5, a6\n\t"//*p_y =*p_y + temp1
        "addi %[p_h], %[p_h], 4\n\t"//p_h++
        "addi %[p_x], %[p_x], 8\n\t"//p_x+=8(1->3->5)
    	//loop3 end
    	"addi %[f], %[f], 1\n\t"//f++
    	"blt %[f], %[bound3], loop3\n\t"// back to loop3
    	
    	/* next element */
    	"sw a5, 0(%[p_y])\n\t"
    	"mv %[p_x], %[x_1]\n\t"//p_x = &x[1]
    	"addi %[p_y] , %[p_y], 4\n\t"//p_y++
    	//loop2 end
    	"addi %[j], %[j], 1\n\t"	//j++
    	"blt %[j], %[bound2], loop2\n\t"// back to loop2
    	//loop1 end
    	"addi %[i], %[i], 1\n\t"	//i++
    	"blt %[i], %[bound3], loop1\n\t"	//if(i<3) back ioop1
    	"Exit:\n\t"
    	:[i]"+r"(i1), [j]"+r"(j), [f]"+r"(f), [p_x]"+r"(p_x), [p_y]"+r"(p_y), [p_h]"+r"(p_h), [temp1]"+r"(temp1), [y_i]"=r"(*p_y)
    	:[x_0]"r"(&x[0]), [bound3]"r"(bound_3), [bound2]"r"(bound_2), [h0]"r"(&h[0]), [num12]"r"(num12), [x_1]"r"(&x[1]), [h_i]"r"(*p_h), [x_i]"r"(*p_x),[x0]"r"(0)//input
    	:"a5","a6","a7"
    );

    p_y = &y[0];
    for(i = 0; i < 6; i++)
        printf("%d ", *p_y++);
    printf("\n");
    return 0; 
 
}
