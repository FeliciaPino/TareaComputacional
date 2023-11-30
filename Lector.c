#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** lector(const char* hola, char** lectura) {
    char frase[50];
    strcpy(frase, hola);
    for (int i = 0; i < 6; i++) {
        lectura[i] = NULL;
    }
    char* token = strtok(frase, " \"");
    int aux = 0;
    while (token != NULL && aux < 6) {
        if (strcmp(token, " ") != 0 && strcmp(token, "") != 0) {
            lectura[aux] = strdup(token);
            aux++;
        }
        token = strtok(NULL, " \"");
    }
    return lectura;
}

int main() {
    char* lectura[6];
    lector("\"Ongolmo 325\" \"paicavi 309\" \"san_martin 567\"", lectura);
    for (int i = 0; i < 6; i++) {
        if (lectura[i] != NULL) {
            printf("%s\n", lectura[i]);
        }
    }
    return 0;
}
