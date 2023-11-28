#include <stdio.h>
//esta estructura en realidad representa cada nodo de una linkedlist que representa el stack, al final el stack en si va a ser un puntero que apunta al primero de estos
struct Stack{
  int valor;
  struct Stack* siguiente;
};
//se le pasa un puntero al puntero que apunta a la cima del stack, crea un nuevo nodo apuntando a la cima y modifica el puntero para que ahora apunte a este nuevo creado
void push(struct Stack** pstack, int valor){
  struct Stack* newTop = (struct Stack*)malloc(sizeof(struct Stack));
  newTop->valor = valor;
  newTop->siguiente = (*pstack)->siguiente;
  *pstack = newTop;
}
int pop(struct Stack** pstack){
  int ret = (*ṕstack)->valor;
  (*pstack) = (*pstack)->siguiente;
  return ret;
}
int main(int argc, char* argv[]){
  printf("hello world");
  return 0;
}
