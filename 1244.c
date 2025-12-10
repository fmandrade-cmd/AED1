#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 55
#define MAX_LEN 55

typedef struct {
    char word[MAX_LEN];
    int length;
    int originalOrder;
} Word;

// Função de comparação para qsort
// Ordena por tamanho decrescente, mantendo ordem original em caso de empate
int compare(const void *a, const void *b) {
    Word *w1 = (Word *)a;
    Word *w2 = (Word *)b;
    
    // Se os tamanhos são diferentes, ordena por tamanho decrescente
    if (w1->length != w2->length) {
        return w2->length - w1->length;
    }
    
    // Se os tamanhos são iguais, mantém a ordem original
    return w1->originalOrder - w2->originalOrder;
}

int main() {
    int n;
    scanf("%d", &n);
    getchar(); // Consome o '\n'
    
    while (n--) {
        char line[2600]; // Buffer para a linha inteira
        Word words[MAX_WORDS];
        int wordCount = 0;
        
        // Lê a linha inteira
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
        
        // Remove o '\n' do final se existir
        int len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        
        // Separa as palavras
        char *token = strtok(line, " ");
        while (token != NULL && wordCount < MAX_WORDS) {
            strcpy(words[wordCount].word, token);
            words[wordCount].length = strlen(token);
            words[wordCount].originalOrder = wordCount;
            wordCount++;
            token = strtok(NULL, " ");
        }
        
        // Ordena as palavras
        qsort(words, wordCount, sizeof(Word), compare);
        
        // Imprime o resultado
        for (int i = 0; i < wordCount; i++) {
            if (i > 0) printf(" ");
            printf("%s", words[i].word);
        }
        printf("\n");
    }
    
    return 0;
}
