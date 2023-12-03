#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANTIDADNODOS 111
#define INFINITY 2147483647 //el valor maximo del int, asumiendo que tiene sistema 32 bits. dudo que no sea el caso



// ---------------------------------------------------------------------SECCIÓN DIJKSTRA---------------------------------------------------------------------------//
//para guardar caminos, el nodo al que se conecta y el peso del camino
struct Par{
  int n;
  int w;
};
struct Par* grafo[CANTIDADNODOS];//los nodos a los que esta conectado el nodo i-esimo
int cantidadConexiones[CANTIDADNODOS];//la cantidad de conexiones que tiene el nodo i-esimo
int distancias[CANTIDADNODOS];//al usar dijkstra guarda las distancias a cada nodo
int previo[CANTIDADNODOS];//al usar dijkstra, guarda el nodo anterior en el camino mas corto
int i;
int j;
void cargarGrafo(){
  FILE* file = fopen("conexiones.txt","r");
  if(file == NULL){printf("woopsie poopsie! no se pudo cargar las conexiones");return;}
  int canvec;
  for(i=0;fscanf(file,"%d",&canvec)!=EOF;i++){
    grafo[i] = (struct Par*)malloc(canvec * sizeof(struct Par));
    cantidadConexiones[i] = canvec;
    int n,w;
    for(j=0;j<canvec;j++){
      fscanf(file,"%d",&n);
      fscanf(file,"%d",&w);
      struct Par p = {n,w};
      grafo[i][j] = p;
    }
  }
}
void imprimirGrafo(){
  for(i=0;i<CANTIDADNODOS;i++){
    printf("%d:",i);
    for(j=0;j<cantidadConexiones[i];j++){
      printf(" (%d,%d)",grafo[i][j].n,grafo[i][j].w);
    }
    printf("\n");
  }
}


//esta estructura en realidad representa cada nodo de una linkedlist que representa el stack, al final el stack en si va a ser un puntero que apunta al primero de estos
struct Stack{
  int valor;
  struct Stack* siguiente;
};
//se le pasa un puntero al puntero que apunta a la cima del stack, crea un nuevo nodo apuntando a la cima y modifica el puntero para que ahora apunte a este nuevo creado
void push(struct Stack** pstack, int valor){
  struct Stack* newTop = (struct Stack*)malloc(sizeof(struct Stack));
  newTop->valor = valor;
  newTop->siguiente = (*pstack);
  *pstack = newTop;
}
int pop(struct Stack** pstack){
  if((*pstack)==NULL)return -1;
  int ret = (*pstack)->valor;
  struct Stack* newTop = (*pstack)->siguiente;
  free(*pstack);
  *pstack = newTop;
  return ret;
}
struct Stack* makeStack(int n){
  struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
  stack->valor = n;
  stack->siguiente = NULL;
  return stack;
}
int stackEmpty(struct Stack* stack){return stack==NULL;}


//retorna un stack con los nodos del camino mas corto entre nodoSalida y nodoLLegada, la distancia se guarda en distancias[nodoLLegada]
struct Stack* dijkstra(int nodoSalida, int nodoLLegada){
  for(i=0;i<CANTIDADNODOS;i++){
    distancias[i] = INFINITY;
  }
  distancias[nodoSalida] = 0;
  struct Stack* stack = makeStack(nodoSalida);
  while(!stackEmpty(stack)){
    int esteNodo = pop(&stack);
    if(esteNodo == nodoLLegada)continue;//no es necesario ver los caminos que pasan por el nodo de llegada, obviamente no seran el mas corto
    if(distancias[esteNodo]>distancias[nodoLLegada])continue;//si ya encontramos un camino mas corto que este, para que segirlo?
    //revisar los i vecinos de este nodo
    for(i=0;i<cantidadConexiones[esteNodo];i++){
      int aquelNodo = grafo[esteNodo][i].n;
      if((distancias[esteNodo]+grafo[esteNodo][i].w)<distancias[aquelNodo]){
        distancias[aquelNodo] = distancias[esteNodo]+grafo[esteNodo][i].w;
        previo[aquelNodo] = esteNodo;
        push(&stack,aquelNodo);
      }
    }
  }
  struct Stack* camino = makeStack(nodoLLegada);
  for(i=previo[nodoLLegada]; i != nodoSalida; i=previo[i])push(&camino,i);
  return camino;
}


// --------------------------------------------------------------------SECCIÓN BIBLIOTECA---------------------------------------------------------------------------//
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
    
    strcpy(dictionary[16].key, "Freire");
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
    
	for (i=0 ; i < 21 ; i++) {
        if (strcmp(ubicacion, dictionary[i].key) == 0) {
            return dictionary[i].value; // Devuelve el valor correspondiente si se encuentra la clave
        }
    }
    return -1; // Devuelve -1 si la clave no se encuentra en el diccionario
        
}


char nombresIntersecciones[CANTIDADNODOS][50];
void cargarNombresIntersecciones(){
  FILE* file = fopen("Intersecciones.txt","r");
  if(file == NULL){printf("woopsie poopsie! no se pudo cargar las intersecciones");return;}
  for(i=0;i<CANTIDADNODOS;i++){
    if(fscanf(file,"%s",&nombresIntersecciones[i])==EOF)printf("woopsiepoopsie!!, no hay suficientes nombres en el archivo de intersecciones!");
  }
}


// ----------------------------------------------------------------------SECCIÓN LECTOR---------------------------------------------------------------------------//
void lector(const char* hola, int* lectura) {
    char frase[50];
    strcpy(frase, hola);
    char* token = strtok(frase, " ");
    int aux = 0;
    while (token != NULL && aux < 6) {
        if (strcmp(token, " ") != 0 && strcmp(token, "") != 0) {
          char* palabra =strdup(token);
        	if(aux%2==0){
        		lectura[aux] = diccionario(palabra);
    			}
    			else{
            int numero = atoi(palabra);
    				lectura[aux] = (numero+50)/100;
            if(lectura[aux-1]<14){
              lectura[aux] = 8 - lectura[aux];
            }
    			}
            aux++;
        }
        token = strtok(NULL, " ");
    }
}


// ---------------------------------------------------------------------------MAIN-----------------------------------------------------------------------------//
int main(int argc, char* argv[]){
  cargarNombresIntersecciones();
  char* entrada;
  entrada = argv[1];
  for(i=2; i<argc ; i++){
  	strcat(entrada, " "); 
  	strcat(entrada, argv[i]); 
  }
  
  int lectura[6];
  lector("Ongolmo 100 Rengo 400 Barros_Arana 200",lectura);

  cargarGrafo();
  int nodoSalida = 0; int nodoLLegada = 1;
  if(lectura[0]>=14) {
    printf("nodo salida es : fila %d y columna %d\n",lectura[1],lectura[0]);
    nodoSalida = lectura[1]-14 + lectura[0]*14;
  }else{
    printf("nodo salidaa es : fila %d y columna %d\n",lectura[0],lectura[1]);
    nodoSalida = lectura[0] + lectura[1]*14;
  } 
  if(lectura[2]>=14){
    printf("nodo llegada es : fila %d y columna %d\n",lectura[3],lectura[2]);
    nodoLLegada = lectura[3]-14 + lectura[2]*14;
  }else {
    printf("nodo llegadaa es : fila %d y columna %d\n",lectura[2],lectura[3]);
    nodoLLegada = lectura[2] + lectura[3]*14;
  }
  int distancia = 0;
  printf("dijkstra: %d -> %d\n",nodoSalida,nodoLLegada);
  struct Stack* camino = dijkstra(nodoSalida,nodoLLegada);
  distancia += distancias[nodoLLegada];
  struct Stack* camino2;
  int nodoIntermedio;
  if(argc >= 4){
    nodoIntermedio = nodoLLegada;
    if(lectura[4]>=14){
      printf("nodo llegada es : fila %d y columna %d\n",lectura[5],lectura[4]);
      nodoLLegada = lectura[5]-14 + lectura[4]*14;
    }else {
      printf("nodo llegadaa es : fila %d y columna %d\n",lectura[4],lectura[5]);
      nodoLLegada = lectura[4] + lectura[5]*14;
    }
    printf("dijkstra: %d -> %d\n",nodoIntermedio,nodoLLegada);
    camino2 = dijkstra(nodoIntermedio,nodoLLegada);
    distancia += distancias[nodoLLegada];
  }
  printf("queremos llegar desde %d a %d \n",nodoSalida, nodoLLegada);
  printf("queremos llegar desde %s a %s \n",nombresIntersecciones[nodoSalida], nombresIntersecciones[nodoLLegada]);
  printf("distancia: %d\n",distancia);
  while(!stackEmpty(camino)){
    int n = pop(&camino);
    printf("%s -> ",nombresIntersecciones[n]);
  }
  while(!stackEmpty(camino2)){
    int n = pop(&camino2);
    printf("%s -> ",nombresIntersecciones[n]);
  }
  return 0;
}
