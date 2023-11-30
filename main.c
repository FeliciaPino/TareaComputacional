#include <stdio.h>
#include <stdlib.h>

#define CANTIDADNODOS 111
//para guardar caminos, el nodo al que se conecta y el peso del camino
struct Par{
  int n;
  int w;
};
struct Par* grafo[CANTIDADNODOS];//los nodos a los que esta conectado el nodo i-esimo
int cantidadConexiones[CANTIDADNODOS];//la cantidad de conexiones que tiene el nodo i-esimo

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


int main(int argc, char* argv[]){
  struct Stack* stack = makeStack(3);
  printf("%d\n",pop(&stack));
  push(&stack,5);
  push(&stack,7);
  printf("%d\n",pop(&stack));
  printf("%d\n",pop(&stack));
  return 0;
}
