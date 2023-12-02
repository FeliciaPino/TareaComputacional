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
  for(int i=0;fscanf(file,"%d",&canvec)!=EOF;i++){
    grafo[i] = (struct Par*)malloc(canvec * sizeof(struct Par));
    cantidadConexiones[i] = canvec;
    int n,w;
    for(int j=0;j<canvec;j++){
      fscanf(file,"%d",&n);
      fscanf(file,"%d",&w);
      struct Par p = {n,w};
      grafo[i][j] = p;
    }
  }
}
void imprimirGrafo(){
  for(int i=0;i<CANTIDADNODOS;i++){
    printf("%d:",i);
    for(int j=0;j<cantidadConexiones[i];j++){
      printf(" (%d,%d)",grafo[i][j].n,grafo[i][j].w);
    }
    printf("\n");
  }
}


// nodo de linked list, representa los stack y filas
struct LlNode{
  int valor;
  struct LlNode* siguiente;
  struct LlNode* anterior;
};
struct Queue{
  struct LlNode* front;
  struct LlNode* back;
};
struct Stack{
  struct LlNode* top;
};
struct Stack makeStack(int n){
  struct Stack stack = {(struct LlNode*)malloc(sizeof(struct LlNode))};
  stack.top->valor = n;
  stack.top->siguiente = NULL;
  stack.top->anterior = NULL;
  return stack;
}
struct Queue makeQueue(int n){
  struct LlNode* node = (struct LlNode*)malloc(sizeof(struct LlNode));
  node->valor = n;
  node->siguiente = NULL;
  node->anterior = NULL;
  struct Queue queue = {node,node};
  return queue;
}
//se le pasa un puntero al puntero que apunta a la cima de la estructura, crea un nuevo nodo apuntando a la cima y modifica el puntero para que ahora apunte a este nuevo creado
void pushStack(struct Stack* pstack, int valor){
  if(pstack->top == NULL){
    *pstack = makeStack(valor);
    return;
  }
  struct LlNode* newTop = (struct LlNode*)malloc(sizeof(struct LlNode));
  pstack->top->anterior = newTop;
  newTop->valor = valor;
  newTop->siguiente = pstack->top;
  pstack->top = newTop;
}
void pushQ(struct Queue* pq, int valor){
  if(pq->front == NULL){
    *pq = makeQueue(valor);
    return;
  }
  struct LlNode* newBack = (struct LlNode*)malloc(sizeof(struct LlNode));
  pq->back->anterior = newBack;
  newBack->valor = valor;
  newBack->siguiente = pq->back;
  pq->back = newBack;
}
//sele pasa puntero al stack y le hace pop
int pop(struct Stack* pstack){
  if(pstack->top==NULL)return -1;
  int ret = pstack->top->valor;
  struct LlNode* newTop = (pstack->top)->siguiente;
  free(pstack->top);
  pstack->top = newTop;
  return ret;
}
//se le pasa puntero a la fila y le hace pop
int popQ(struct Queue* pqueue){
  if(pqueue->front == NULL)return -1;
  int ret = pqueue->front->valor;
  struct LlNode* newFront = pqueue->front->anterior;
  free(pqueue->front);
  pqueue->front = newFront;
  return ret;
}
int stackEmpty(struct Stack stack){return stack.top == NULL;}
int queueEmpty(struct Queue queue){return queue.front == NULL;}

//retorna un stack con los nodos del camino mas corto entre nodoSalida y nodoLLegada, la distancia se guarda en distancias[nodoLLegada]
struct Stack dijkstra(int nodoSalida, int nodoLLegada){
  for(int i=0;i<CANTIDADNODOS;i++){
    distancias[i] = INFINITY;
  }
  distancias[nodoSalida] = 0;
  struct Queue queue = makeQueue(nodoSalida);
  while(!queueEmpty(queue)){
    int esteNodo = popQ(&queue);
    //printf("visitando %d\n",esteNodo);
    if(esteNodo == nodoLLegada)continue;//no es necesario ver los caminos que pasan por el nodo de llegada, obviamente no seran el mas corto
    if(distancias[esteNodo]>distancias[nodoLLegada])continue;//si ya encontramos un camino mas corto que este, para que segirlo?
    //revisar los i vecinos de este nodo
    for(int i=0;i<cantidadConexiones[esteNodo];i++){
      int aquelNodo = grafo[esteNodo][i].n;
      if((distancias[esteNodo]+grafo[esteNodo][i].w)<distancias[aquelNodo]){
        distancias[aquelNodo] = distancias[esteNodo]+grafo[esteNodo][i].w;
        previo[aquelNodo] = esteNodo;
        pushQ(&queue,aquelNodo);
      }
    }
  }
  struct Stack camino = makeStack(nodoLLegada);
  for(int i=previo[nodoLLegada]; i != nodoSalida; i=previo[i])pushStack(&camino,i);
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
  for(int i=0;i<CANTIDADNODOS;i++){
    if(fscanf(file,"%s",&nombresIntersecciones[i])==EOF)printf("woopsiepoopsie!!, no hay suficientes nombres en el archivo de intersecciones!");
  }
}


// ----------------------------------------------------------------------SECCIÓN LECTOR---------------------------------------------------------------------------//
void lector(const char* hola, int* lectura) {
    char frase[50];
    strcpy(frase, hola);
    for (i = 0; i < 6; i++) {
        lectura[i] = NULL;
    }
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
  char* entrada;
  entrada = argv[1];
  for(i=2; i<argc ; i++){
  	strcat(entrada, " "); 
  	strcat(entrada, argv[i]); 
  }
  
  int lectura[6];
  lector(entrada,lectura);


  cargarNombresIntersecciones();
  cargarGrafo();
  int nodoSalida = 0; int nodoLLegada = 16;
  //TODO inicializar nodo salida y llegada
  for(int i=0;i<(argc-1)*2,i++){
    lectura
  }
  }
  struct Stack camino = dijkstra(nodoSalida,nodoLLegada);
  printf("distancia: %d\n",distancias[nodoLLegada]);
  while(!stackEmpty(camino)){
    printf("%d ",pop(&camino));
  }
  
  return 0;
}
