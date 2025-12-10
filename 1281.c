#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 55
#define MAX_NAME 55

typedef struct {
    char name[MAX_NAME];
    double price;
} Product;

int main() {
    int N;
    scanf("%d", &N);
    
    while (N--) {
        int M;
        scanf("%d", &M);
        
        Product products[MAX_PRODUCTS];
        
        // Lê os produtos disponíveis e seus preços
        for (int i = 0; i < M; i++) {
            scanf("%s %lf", products[i].name, &products[i].price);
        }
        
        int P;
        scanf("%d", &P);
        
        double total = 0.0;
        
        // Lê a lista de compras e calcula o total
        for (int i = 0; i < P; i++) {
            char itemName[MAX_NAME];
            int quantity;
            scanf("%s %d", itemName, &quantity);
            
            // Procura o produto na lista de produtos disponíveis
            for (int j = 0; j < M; j++) {
                if (strcmp(products[j].name, itemName) == 0) {
                    total += products[j].price * quantity;
                    break;
                }
            }
        }
        
        printf("R$ %.2lf\n", total);
    }
    
    return 0;
}
