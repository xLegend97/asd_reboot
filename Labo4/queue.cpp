#include "queue.h"

using namespace queue;


/****************************************************************/
/* 			FUNZIONI SULLE CODE 			*/
/****************************************************************/

/****************************************************************/
void queue::enqueue(Elem e, Queue& l) // aggiunge e in coda
{
  cell* aux = new cell;
  Queue cur = l;
  while(cur != EMPTYQUEUE){
    cur = cur->next;
  }
  aux->info = e;
  aux->next = EMPTYQUEUE;
  cur->next = aux;
}


/****************************************************************/
Elem queue::dequeue(Queue& l) // rimuove il primo elemento e lo restituisce
{
  if(isEmpty(l)){
    throw ("The Stack is Empty!");
  }else{
    Elem t;
    t = l->info;
    Queue tmp = l;
    l = l->next;
    delete tmp;
    return t;
  }
}

/****************************************************************/
bool queue::isEmpty(const Queue& l)
{
  return (l == EMPTYQUEUE);
}

/****************************************************************/
