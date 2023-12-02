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
  struct Stack stack = makeStack(nodoSalida);
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
        pushStack(&stack,aquelNodo);
      }
    }
  }
  struct Stack camino = makeStack(nodoLLegada);
  for(int i=previo[nodoLLegada]; i != nodoSalida; i=previo[i])pushStack(&camino,i);
  return camino;
}
int main(int argc, char* argv[]){
  struct Queue queue = makeQueue(2);
  pushQ(&queue,3);
  pushQ(&queue,5);
  pushQ(&queue,7);
  pushQ(&queue,11);
  while(!queueEmpty(queue)){
    printf("%d\n",popQ(&queue));
  }
  /*
  cargarGrafo();
  int a = 66; int b = 95;
  struct Stack camino = dijkstra(a,b);
  printf("calculando desde nodo %d a nodo %d\n",a,b);
  printf("distancia: %d\n",distancias[b]);
  while(!stackEmpty(camino)){
    printf("%d ",pop(&camino));
  }
  */
  return 0;
}
