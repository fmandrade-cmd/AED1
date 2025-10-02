#include <stdio.h>
#include <string.h>

int bemFormada(char s[]){
    //char *p; //Cria um vetor
    int t, i;

    //n = strlen(s);
    //p = malloc(n * sizeof(char)); //Determina o tamanho do vetor
    t = 0;
    for(i = 0; s[i] != '\0'; i++){
        if(s[i] == '(') t++;  
        if(s[i] == ')') t--;
    }
    if(t == 0) return 1;
    return 0;
}

int main(){

    char v[1000];
    int ref, N;
    int count = 0;
    
    scanf("%d", &N);

    while(count < N){
        scanf("%s", v);
        ref = bemFormada(v);
        if(ref == 1) 
            printf("correct");
        else
            printf("incorrect");
        count++;
    }

    return 0;
}
