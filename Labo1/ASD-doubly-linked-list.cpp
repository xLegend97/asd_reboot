// Implementa le funzioni sulle liste realizzate con strutture doppiamente collegate, circolari, con sentinella, senza ordinamento

#include "ASD-doubly-linked-list.h"


using namespace list;

struct list::node {  // descrivo qui, fuori dal namespace, come e' fatta la struttura node: i dettagli interni non saranno visibili dal main
Elem info;
node *prev;
node *next;
};

/*************************************************/
/* Implementazione delle operazioni di utilita'� */
/*************************************************/

void readFromStream(istream& str, List& l)
{
    createEmpty(l);
    Elem e;
    str>>e;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    while (e != FINEINPUT)  // assumiamo che il segnale di fine input nel file sia  FINEINPUT
        {     
        addRear(e, l);   // aggiunge l'elemento alla fine della lista
        str>>e;
        if (!str) throw runtime_error("Errore inserimento dati\n");
        }
}

void readFromFile(string nome_file, List& l)  /* legge il contenuto di una lista da file */
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    readFromStream(ifs, l);
}



void readFromStdin(List& l)         /* legge il contenuto di una lista da standard input */
{
   cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " << FINEINPUT << " per terminare\n";
   readFromStream((std::cin), l);
}


void print(const List& l)           /* stampa la lista */
{
   List q = l->next;  // q "salta la sentinella" e va alla testa della lista
   while (q != l)     // avanza finche' non finisce la lista
     {
      cout << q->info << "; ";
      q = q->next; 
      }
}

/**************************************************/
/* Implementazione delle operazioni nel namespace */
/**************************************************/

void list::clear(const List& l)                 /* "smantella" la lista svuotandola */
{
    node* cur = l->next;
    node* aux;
    while(cur != l){
        aux = cur;
        cur = cur->next;
        delete aux;
    }
    l->next = l;
    l->prev = l;
}


Elem list::get(int pos, const List& l)        /* restituisce l'elemento in posizione pos se presente; restituisce un elemento che per convenzione si decide che rappresenta l'elemento vuoto altrimenti*/
{
    if(pos > size(l)){
        return EMPTYELEM;
    }else{
        int n = 0;
        node* cur = l->next;
        while((cur != l) && (n != pos)){
            n++;
            cur = cur->next;
        }
        return cur->info;
    }
}


void list::set(int pos, Elem e, const List& l)        /* modifica l'elemento in posizione pos, se la posizione e' ammissibile */
{
    if(pos > size(l)){
        return;
    }else{
        int n = 0;
        node* cur = l->next;
        while((cur != l) && (n != pos)){
            n++;
            cur = cur->next;
        }
        cur->info = e;
    }
}


void list::add(int pos, Elem e, const List& l)        /* inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
{              
    if(pos > size(l)){
        return;
    }if(pos == 0){
        addFront(e, l);
    }if(pos == size(l)){
        addRear(e, l);
    }else{
        int n = 0;
        node* aux = new node;
        node* cur = l->next;
        aux->info = e;
        while((cur != l) && (n != pos)){
            n++;
            cur = cur->next;
        }
        aux->next = cur;
        aux->prev = cur->prev->next;
        cur->prev->next = aux;
        cur->prev = aux;
    }
}


void list::addRear(Elem e,  const List& l)        /* inserisce l'elemento alla fine della lista */
{
    node* aux = new node;
    aux->info = e;
    if(isEmpty(l)){
        aux->next = l;
        aux->prev = l;
        l->next = aux;
        l->prev = aux;
    }else{
        aux->next = l;
        aux->prev = l->prev;
        l->prev->next = aux;
        l->prev = aux;
    }
}


void list::addFront(Elem e, const List& l)        /* inserisce l'elemento all'inizio della lista */
{
    node* aux = new node;
    aux->info = e;
    if(isEmpty(l)){
        aux->next = l;
        aux->prev = l;
        l->prev = aux;
        l->next = aux;
    }else{
        aux->prev = l;
        aux->next = l->next->next;
        l->next->prev = aux;
        l->next = aux;
    }
}


void list::removePos(int pos, const List& l)      /* cancella l'elemento in posizione pos dalla lista */
{
    if(pos > size(l)){
        return;
    }else{
        int n = 0;
        node* cur = l->next;
        while((cur != l) && (n != pos)){
            n++;
            cur = cur->next;
        }
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        delete cur;
    }
}


void list::removeEl(Elem e, const List& l)        /* cancella tutte le occorrenze dell'elemento elem, se presenti, dalla lista */
{
    node *cur = l->next;
    while(cur != l){
        if(cur->info == e){
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            delete cur;
            return;
        }else{
            cur = cur->next;
        }
    }
}


bool list::isEmpty(const List& l)         /* restituisce true se la lista e' vuota (ed e' vuota se il next di l, e' l stessa */
{
    return (l->next == l);
}


int list::size(const List& l)           /* restituisce la dimensione della lista */
{
    int s = 0;
    node * cur = l->next;
    while(cur != l){
        s++;
        cur = cur->next;
    }
    return s;
}


void list::createEmpty(List& l)           /* crea la lista vuota */
{
    l = new node;
    l->next = l;
    l->prev = l;
}
