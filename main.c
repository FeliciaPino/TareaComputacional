#include <stdio.h>
#include <stdlib.h>

#define CANTIDADNODOS 111
#define INFINITY 2147483647 //el valor maximo del int, asumiendo que tiene sistema 32 bits. dudo que no sea el caso
//para guardar caminos, el nodo al que se conecta y el peso del camino
struct Par{
  int n;
  int w;
};
struct Par* grafo[CANTIDADNODOS];//los nodos a los que esta conectado el nodo i-esimo
int cantidadConexiones[CANTIDADNODOS];//la cantidad de conexiones que tiene el nodo i-esimo
int distancias[CANTIDADNODOS];//al usar dijkstra guarda las distancias a cada nodo
int previo[CANTIDADNODOS];//al usar dijkstra, guarda el nodo anterior en el camino mas corto

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
};
struct Queue{
  struct Llnode* front;
  struct Llnode* back;
};
//se le pasa un puntero al puntero que apunta a la cima de la estructura, crea un nuevo nodo apuntando a la cima y modifica el puntero para que ahora apunte a este nuevo creado
void push(struct LlNode** topPointer, int valor){
  struct LlNode* newTop = (struct LlNode*)malloc(sizeof(struct LlNode));
  newTop->valor = valor;
  newTop->siguiente = (*topPointer);
  *topPointer = newTop;
}
//sele pasa puntero al puntero de la cima del stack y le hace pop
int pop(struct LlNode** pstack){
  if((*pstack)==NULL)return -1;
  int ret = (*pstack)->valor;
  struct LlNode* newTop = (*pstack)->siguiente;
  free(*pstack);
  *pstack = newTop;
  return ret;
}
struct LlNode* makeStack(int n){
  struct LlNode* stack = (struct LlNode*)malloc(sizeof(struct LlNode));
  stack->valor = n;
  stack->siguiente = NULL;
  return stack;
}
int stackEmpty(struct LlNode* stack){return stack==NULL;}

//retorna un stack con los nodos del camino mas corto entre nodoSalida y nodoLLegada, la distancia se guarda en distancias[nodoLLegada]
struct LlNode* dijkstra(int nodoSalida, int nodoLLegada){
  for(int i=0;i<CANTIDADNODOS;i++){
    distancias[i] = INFINITY;
  }
  distancias[nodoSalida] = 0;
  struct LlNode* stack = makeStack(nodoSalida);
  while(!stackEmpty(stack)){
    int esteNodo = pop(&stack);
    if(esteNodo == nodoLLegada)continue;//no es necesario ver los caminos que pasan por el nodo de llegada, obviamente no seran el mas corto
    if(distancias[esteNodo]>distancias[nodoLLegada])continue;//si ya encontramos un camino mas corto que este, para que segirlo?
    //revisar los i vecinos de este nodo
    for(int i=0;i<cantidadConexiones[esteNodo];i++){
      int aquelNodo = grafo[esteNodo][i].n;
      if((distancias[esteNodo]+grafo[esteNodo][i].w)<distancias[aquelNodo]){
        distancias[aquelNodo] = distancias[esteNodo]+grafo[esteNodo][i].w;
        previo[aquelNodo] = esteNodo;
        push(&stack,aquelNodo);
      }
    }
  }
  struct LlNode* camino = makeStack(nodoLLegada);
  for(int i=previo[nodoLLegada]; i != nodoSalida; i=previo[i])push(&camino,i);
  return camino;
}
int main(int argc, char* argv[]){
  cargarGrafo();
  int a = 66; int b = 95;
  struct LlNode* camino = dijkstra(a,b);
  printf("distancia: %d\n",distancias[b]);
  while(!stackEmpty(camino)){
    printf("%d ",pop(&camino));
  }
  return 0;
}
