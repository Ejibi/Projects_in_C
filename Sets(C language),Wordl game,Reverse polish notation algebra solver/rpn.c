#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Node{
    unsigned int length;
    int top;
    int *data;
};

void node_start(struct Node *start,int length){
    (*start).data = (int*)malloc(sizeof(int)*length);
    (*start).top = -1;
    (*start).length = length;
}

void bigger(struct Node *big, int something) {
    int *wild_data = (int*)malloc(2*something*(*big).length*sizeof(int));
    for(int i = 0; i < (*big).top + 1; i++) {
        wild_data[i] = (*big).data[i];
    }
    free((*big).data);
    (*big).data = wild_data;
    (*big).length = 2*something;
}

int remover(struct Node *popper){
    if ((*popper).top<0){
        printf("%s","ERROR\n");
        exit(EXIT_FAILURE);
    }
return (*popper).data[((*popper).top)--];
}


void push(struct Node *pushed, int something){
    if ((*pushed).top == (*pushed).length - 1){
        bigger(pushed,(*pushed).length * 2);
    }
    (*pushed).data[++(*pushed).top] = something;

}

void node_free(struct Node *end){
    free((*end).data);
}

int performer(char thing, int first_value_found,int second_value_found){
    int send_back = 0;
    int *ptr = &send_back;
    if (thing == 'p'){
        *ptr = first_value_found + second_value_found;
    }
    if (thing == 's' ){
        *ptr = first_value_found - second_value_found   ;
    }
    if (thing == '*' ){
        *ptr = (second_value_found)*(first_value_found);
    }
    if (thing == '/'){
        if (first_value_found != 0){
        *ptr = (first_value_found)/( second_value_found);
        }
        else{
            printf("%s","Divide by 0 error\n");
            exit(EXIT_FAILURE);
        }
    }
    return send_back;
}
int RPN(struct Node *cat) {
    char token = '\0';
    int operand = 0;
    int numbers = 0;
    int decrementer = 2;
    while (scanf(" %c", &token) == 1) {
        if (token >= '0' && token <= '9') {
            ungetc(token, stdin); 
            scanf("%d", &operand);
            push(cat, operand);
            decrementer--;
            numbers++;
            if(decrementer <0 && numbers >1){
                printf("Invalid input, not all operands consumed\n");
                    exit(EXIT_FAILURE);
            }
        }
        else if (token == 'p' || token == 's' || token == '*' || token == '/') {
            if ((*cat).top >= 1) {
                int second_op = remover(cat);
                int first_op = remover(cat);
                int result = performer(token, first_op, second_op);
                push(cat, result);
            } else {
                printf("Invalid input - operator without enough operands\n");
                exit(EXIT_FAILURE);
            }
        }
        numbers = 0;
    }
    return remover(cat);
}


int main(){
    int start = 4;
    struct Node cat;
    node_start(&cat, start);
    int result = RPN(&cat);
    printf("%d\n", result);
    node_free(&cat);
    return 0;
}           