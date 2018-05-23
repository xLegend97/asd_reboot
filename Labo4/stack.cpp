#include "stack.h"

using namespace stack;

/****************************************************************/
bool stack::isEmpty(const Stack& s)
{
    return (s == EMPTYSTACK);
}

/****************************************************************/
void stack::push(const Elem x, Stack& s) 
{
    cell* aux = new cell;
    aux->info = x;
    if(isEmpty(s)){ aux->next = EMPTYSTACK; 
    } else { aux->next = s; }
    s = aux;
}

/****************************************************************/
Elem stack::pop(Stack& s)
{
    if(isEmpty(s)){
        throw ("The Stack is Empty!");
    }else{
        Elem e = s->info;
        Stack tmp = s;
        s = s->next;
        delete tmp;
        return e;    
    }
}

/****************************************************************/

