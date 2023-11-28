#include <stdio.h>
#include <string.h>

struct KeyValue {
    char key[50];
    int value;
};

int diccionario(const char* ubicacion) {

    struct KeyValue dictionary[22];

    strcpy(dictionary[0].key, "Arturo_Prat");
    dictionary[0].value = 0;

    strcpy(dictionary[1].key, "Serrano");
    dictionary[1].value = 1;

    strcpy(dictionary[2].key, "Salas");								
    dictionary[2].value = 2;
    
    strcpy(dictionary[3].key, "Angol");
    dictionary[3].value = 3;
    
    strcpy(dictionary[4].key, "Lincoyan");
    dictionary[4].value = 4;
    
    strcpy(dictionary[5].key, "Rengo");
    dictionary[5].value = 5;
    
    strcpy(dictionary[6].key, "Caupolican");
    dictionary[6].value = 6;
    
    strcpy(dictionary[7].key, "Anibal_Pinto");
    dictionary[7].value = 7;
    
    strcpy(dictionary[8].key, "Colo_Colo");
    dictionary[8].value = 8;
    
    strcpy(dictionary[9].key, "Castellon");
    dictionary[9].value = 9;
    
    strcpy(dictionary[10].key, "Tucapel");
    dictionary[10].value = 10;
    
    strcpy(dictionary[11].key, "Orompello");
    dictionary[11].value = 11;
    
    strcpy(dictionary[12].key, "Ongolmo");
    dictionary[12].value = 12;
    
    strcpy(dictionary[13].key, "Paicavi");
    dictionary[13].value = 13;
    
    strcpy(dictionary[14].key, "los_Carrera");
    dictionary[14].value = 14;
    
    strcpy(dictionary[15].key, "Maipu");
    dictionary[15].value = 15;
    
    strcpy(dictionary[16].key, "Fraire");
    dictionary[16].value = 16;
    
    strcpy(dictionary[17].key, "Barros_Arana");
    dictionary[17].value = 17;
    
    strcpy(dictionary[18].key, "O'Higgins");
    dictionary[18].value = 18;
    
    strcpy(dictionary[19].key, "San_Martin");
    dictionary[19].value = 19;
    
    strcpy(dictionary[20].key, "Cochrane");
    dictionary[20].value = 20;
    
    strcpy(dictionary[21].key, "Chacabuco");
    dictionary[21].value = 21;
    
    int i = 0;
	for (i ; i < 21 ; i++) {
        if (strcmp(ubicacion, dictionary[i].key) == 0) {
            return dictionary[i].value; // Devuelve el valor correspondiente si se encuentra la clave
        }
    }
    return -1; // Devuelve -1 si la clave no se encuentra en el diccionario
        
}

void main(){
	printf("%d\n",diccionario("Cochrane"));
	printf("%d\n",diccionario("Barros_Arana"));
	printf("%d\n",diccionario("Mi_Casa"));
}
