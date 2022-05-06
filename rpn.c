#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

/* program read stdin until:
encounters unknown token
reaches end of input.. doesnt happen
is given an operator with insufficient operands to evaluate it
or program ends with ctrl+d
then prints remaining values of stack presented on a single line, separated by commas within square brackets, with the top of the stack on the right*/

int main(){
   
size_t len = 0;
char *token;
char *buffer = NULL;
ssize_t lineSize = 0;
int i = 0;
int insuff = 0;
int val;
size_t isOp = 0;
int isNum = 0;
int B_SIZE = 100;
int *num = (int*)malloc(B_SIZE * sizeof(int));
char b4 = '[';
const char zero = '0';

while((lineSize = getdelim(&buffer, &len, '\n', stdin)) != -1){
    
    size_t nLine = strcspn(buffer, "\n");
    if(nLine >0) //pretty sure dont need this
        buffer[nLine] = '\0';

    for (token = strtok(buffer, " \n"); token != NULL; token = strtok(NULL, " \n")){    //strok seperates buffer by tokens of white space or new line
        isOp = 0;
        isNum = 0;
        insuff = 0;
        val = atoi(token);
        isOp = strspn(token, "+-/*");
        if(val != 0 || strncmp(token, &zero, strlen(token)) == 0){    // IS A NUMBER
            if(i >= B_SIZE){    // need to realloc
                num = (int *)realloc(num, (2 * B_SIZE * (sizeof(int))));
                B_SIZE = B_SIZE * 2;
            }

            num[i] = val;
            i = i+1;
            isNum = 1;
        }

        if((isOp == strlen(token)) && i < 2) //is operator but insufficent nums
            insuff = 1;

        if((isOp == strlen(token)) && i >= 2){  //is an operator and there are sufficent nums to operate on
            int num1 = num[i-2];
            int num2 = num[i-1];

            if(token[0] == '+')
                *(num+i-2) = num1+num2;
            
            if(token[0] == '-')
                *(num+i-2) = num1-num2;
            
            if(token[0] == '*')           
                *(num+i-2) = num1*num2;
            
            if(token[0] == '/')
                *(num+i-2) = num1/num2;

            i= i-1;         
        }

        if((!isNum && !isOp ) || insuff) { //if it is INVALID or INSUFF, stop tokenizing
            
            if(i == 0){ // no input
                puts("[ ]");
                free(buffer);
                free(num);
                return 0;
            }

            b4 = '[';
            for(int p=0; p<i; p+=1){
                printf("%c %d", b4, num[p]);
                b4=',';
            }
            puts(" ]");
            
            free(buffer);
            free(num);
            return 0;
        } 
           
    }

}
//input stopped by ctrl d
b4 = '[';
for(int p=0; p< i; p+=1){
    printf("%c %d", b4, num[p]);
    b4=',';
}
puts(" ]");

free(buffer);
free(num);

return 0;
}