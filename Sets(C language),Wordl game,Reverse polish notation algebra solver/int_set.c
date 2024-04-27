#include <stdio.h>
#include <stdlib.h>

struct set {
    int *set;
    int length;
    int number;
};
void start_set(struct set *data, int begin){
    (*data).set = (int*)malloc(begin*sizeof(int));
    (*data).number = -1;
    (*data).length = begin;

}
void larger(struct set *data, int increase){
    int *wilderness = (int*)malloc(2*increase*sizeof(int));
    for(int i = 0; i <(*data).number+1; i++){
        wilderness[i]= (*data).set[i];
    }
    free((*data).set);
    (*data).set = wilderness;
    (*data).length = 2*increase;
}

void adder(struct set *data, int value){
    if ((*data).number == (*data).length - 1) {
        larger(data, (*data).number+1);
    }
    for(int j = 0; j < (*data).number+1; j++){
        if ( (*data).set[j] == value ){
            return;
        }
    }
    int i = data->number;
    while (i >= 0 && (*data).set[i] >= value) {
        (*data).set[i + 1] = (*data).set[i];
        i--;
    }
    (*data).set[i + 1] = value;
    (*data).number++;;
}
void remover_set(struct set *data, int value){
    if((*data).number < 0 ){
        printf("Nothing in here");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    for (; i < (*data).number; i++){
        if ( (*data).set[i] == value){
            break;
        }
    }
    
    if(i > (*data).number){
        return;
    }
    for (; i < (*data).number ; ++i){
        (*data).set[i] = (*data).set[i+1];
    }
    (*data).number--;
}

void intersectional(struct set *data_x, struct set *data_y){
    if((*data_x).number < 0 || (*data_y).number < 0){
        return;
    }
    int k = 0;
    for (int i = 0; i<(*data_x).number+1; i++){
        for(int j = 0; j < (*data_y).number+1; j++){
            if((*data_x).set[j] == (*data_y).set[i]){
                k = 1;
                printf("%d",(*data_y).set[i]);
            }
            if (k == 1 && j != (*data_y).number){
                printf(" ");
                k=0;
            }
        if (k == 1 && j == (*data_y).number){
                printf("\n");
                k = 0;
            }
        }
    }
}

void set_free(struct set *end){
    free((*end).set);
}
void print_set(struct set *data){
    if((*data).number < 0){
        return;
    }
    for(int i = 0; i <= (*data).number+1; i++){
        if (i < (*data).number+1){
        printf("%d",(*data).set[i]);
        if( i != (*data).number ){
            printf(" ");
        }
        if(i == (*data).number){
            printf("\n");
        }
        }
    }
}
void unity_union(struct set *data_x, struct set *data_y){
    struct set unit_maker;
    start_set(&unit_maker, ((*data_x).length + (*data_y).length));
    for (int i = 0; i <= (*data_x).number; i++) {
        adder(&unit_maker, (*data_x).set[i]);
    }
    for (int i = 0; i <= (*data_y).number; i++) {
        adder(&unit_maker, (*data_y).set[i]);
    }
    print_set(&unit_maker);
    set_free(&unit_maker);
}

int main(){
    int start_x = 32;
    int start_y = 32;
    char token = 'N' ;
    int numb = 0;
    struct set x;
    start_set(&x,start_x);
    struct set y;
    start_set(&y,start_y);
    while (token != 'q') {
        char set_choice ;
        scanf(" %c",&token);
        if (token == 'a'){
            scanf(" %c", &set_choice);
            scanf(" %d", &numb);
            if(set_choice == 'x'){
                adder(&x,numb);
            }
            else if (set_choice == 'y'){
                adder(&y,numb);
            }
            }
        if (token == 'r'){
            scanf(" %c", &set_choice);
            scanf(" %d", &numb);
            if(set_choice == 'x'){
                remover_set(&x,numb);
            }
            else if (set_choice == 'y'){
                remover_set(&y,numb);
            }
        }
        if (token == 'p'){
            scanf(" %c", &set_choice);
            if(set_choice == 'x'){
                print_set(&x);
            }
            else if (set_choice == 'y'){
                print_set(&y);
            }
        }
        if (token == 'i'){
            intersectional(&x,&y);
        }
        if (token == 'u'){
            unity_union(&x,&y);
        }
    }
    set_free(&x);
    set_free(&y);
}
