#include "queue.h"

using namespace queue;


/****************************************************************/
/* 			FUNZIONI SULLE CODE 			*/
/****************************************************************/

/****************************************************************/
void queue::enqueue(Elem e, Queue& l) // aggiunge e in coda
{
  cell* aux = new cell;
  aux->info = e;
  aux->prev = l->prev;
  aux->next = l;
  l->prev = aux;
}


/****************************************************************/
Elem queue::dequeue(Queue& l) // rimuove il primo elemento e lo restituisce
{
  Elem t;
  t = l->next->info;
  Queue tmp = l->next;
  l->next = l->next->next;
  l->next->next->prev = l;
  delete tmp;
  return t;
}

/****************************************************************/
bool queue::isEmpty(const Queue& l)
{
  return (l->next == l);
}

/****************************************************************/
