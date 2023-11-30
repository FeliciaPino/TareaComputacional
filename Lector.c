#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* lector(char* hola, int cual) {
    char frase[50];  
    strcpy(frase, hola);
    int aux = 0;
    char* token = strtok(frase, " \"");
    while (token != NULL) {
        aux++;
        if (aux == cual) {
            return strdup(token);
        }
        token = strtok(NULL, " \"");
    }
    return "Error al leer la dirrecion o indice incorrecto.";
}

int main() {
    printf("%s\n", lector("\"Ongolmo 325\" \"paicavi 309\" \"san_martin 567\"", 3));
    
    return 0;
}
