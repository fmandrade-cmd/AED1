#include <stdio.h>
#include <string.h>

#define MAX_COUNTRIES 25
#define MAX_NAME 20
#define MAX_PHRASE 35

typedef struct {
    char country[MAX_NAME];
    char phrase[MAX_PHRASE];
} CountryPhrase;

// Inicializa o banco de dados de países e frases
void initializeDatabase(CountryPhrase db[], int *count) {
    *count = 0;
    
    strcpy(db[*count].country, "brasil"); 
    strcpy(db[*count].phrase, "Feliz Natal!"); (*count)++;
    
    strcpy(db[*count].country, "alemanha"); 
    strcpy(db[*count].phrase, "Frohliche Weihnachten!"); (*count)++;
    
    strcpy(db[*count].country, "austria"); 
    strcpy(db[*count].phrase, "Frohe Weihnacht!"); (*count)++;
    
    strcpy(db[*count].country, "coreia"); 
    strcpy(db[*count].phrase, "Chuk Sung Tan!"); (*count)++;
    
    strcpy(db[*count].country, "espanha"); 
    strcpy(db[*count].phrase, "Feliz Navidad!"); (*count)++;
    
    strcpy(db[*count].country, "grecia"); 
    strcpy(db[*count].phrase, "Kala Christougena!"); (*count)++;
    
    strcpy(db[*count].country, "estados-unidos"); 
    strcpy(db[*count].phrase, "Merry Christmas!"); (*count)++;
    
    strcpy(db[*count].country, "inglaterra"); 
    strcpy(db[*count].phrase, "Merry Christmas!"); (*count)++;
    
    strcpy(db[*count].country, "australia"); 
    strcpy(db[*count].phrase, "Merry Christmas!"); (*count)++;
    
    strcpy(db[*count].country, "portugal"); 
    strcpy(db[*count].phrase, "Feliz Natal!"); (*count)++;
    
    strcpy(db[*count].country, "suecia"); 
    strcpy(db[*count].phrase, "God Jul!"); (*count)++;
    
    strcpy(db[*count].country, "turquia"); 
    strcpy(db[*count].phrase, "Mutlu Noeller"); (*count)++;
    
    strcpy(db[*count].country, "argentina"); 
    strcpy(db[*count].phrase, "Feliz Navidad!"); (*count)++;
    
    strcpy(db[*count].country, "chile"); 
    strcpy(db[*count].phrase, "Feliz Navidad!"); (*count)++;
    
    strcpy(db[*count].country, "mexico"); 
    strcpy(db[*count].phrase, "Feliz Navidad!"); (*count)++;
    
    strcpy(db[*count].country, "antardida"); 
    strcpy(db[*count].phrase, "Merry Christmas!"); (*count)++;
    
    strcpy(db[*count].country, "canada"); 
    strcpy(db[*count].phrase, "Merry Christmas!"); (*count)++;
    
    strcpy(db[*count].country, "irlanda"); 
    strcpy(db[*count].phrase, "Nollaig Shona Dhuit!"); (*count)++;
    
    strcpy(db[*count].country, "belgica"); 
    strcpy(db[*count].phrase, "Zalig Kerstfeest!"); (*count)++;
    
    strcpy(db[*count].country, "italia"); 
    strcpy(db[*count].phrase, "Buon Natale!"); (*count)++;
    
    strcpy(db[*count].country, "libia"); 
    strcpy(db[*count].phrase, "Buon Natale!"); (*count)++;
    
    strcpy(db[*count].country, "siria"); 
    strcpy(db[*count].phrase, "Milad Mubarak!"); (*count)++;
    
    strcpy(db[*count].country, "marrocos"); 
    strcpy(db[*count].phrase, "Milad Mubarak!"); (*count)++;
    
    strcpy(db[*count].country, "japao"); 
    strcpy(db[*count].phrase, "Merii Kurisumasu!"); (*count)++;
}

// Busca a frase correspondente ao país
char* searchPhrase(CountryPhrase db[], int count, char *country) {
    for (int i = 0; i < count; i++) {
        if (strcmp(db[i].country, country) == 0) {
            return db[i].phrase;
        }
    }
    return NULL;
}

int main() {
    CountryPhrase database[MAX_COUNTRIES];
    int dbCount;
    char country[MAX_NAME];
    
    // Inicializa o banco de dados
    initializeDatabase(database, &dbCount);
    
    // Processa as consultas
    while (scanf("%s", country) != EOF) {
        char *phrase = searchPhrase(database, dbCount, country);
        
        if (phrase != NULL) {
            printf("%s\n", phrase);
        } else {
            printf("--- NOT FOUND ---\n");
        }
    }
    
    return 0;
}
