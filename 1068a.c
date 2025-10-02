#include <stdio.h>
#include <string.h>

int bemFormada(char *p){
    //char *p; //Cria um vetor
    int t, i;
    t = 0;
    for(i = 0; p[i] != '\0'; i++){
        if(p[i] == '(') t++;  
        if(p[i] == ')') t--;
        //Verifica erro do tipo: ')(' seria considerado CORRETO
        if(t < 0) return 0;
    }
    return (t == 0); //1 para verdadeiro e 0 para falso
}

int main(){
    //Aloca memória e cria um vetor
    char *p;
    p = (char *)malloc(1001 * sizeof(char));
    
    int ref, N;
    int count = 0;
    //Número de espressões
    scanf("%d", &N);

    while(count < N){
        //Lê uma String com até 1000 caracteres
        scanf("%1000s", p);
        //Verifica a expresão
        ref = bemFormada(p);
        if(ref == 1) 
            printf("correct");
        else
            printf("incorrect");
        count++;
        
    }
    //Libera a mamória alocada
    free(p);

    return 0;
}
