#include <iostream>
#include <stdexcept>

#include "token.h"
	
using namespace std;

// Implementa QUEUE 
namespace queue{


// Gli elementi della QUEUE sono token
typedef token Elem;       

struct cell{
    Elem info;
    cell* next;
};
typedef cell* Queue;    // Simply-linked list 
const Queue EMPTYQUEUE = NULL;

bool isEmpty(const Queue&);
void enqueue(Elem, Queue&);  /* inserisce l'elemento alla fine della lista */
Elem dequeue(Queue&);        /* cancella l'elemento in prima posizione (se esiste) e lo restituisce */
}
