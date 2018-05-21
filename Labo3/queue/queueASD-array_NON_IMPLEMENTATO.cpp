#include "queueASD-array.h"

using namespace queue;


/****************************************************************/
/* 			FUNZIONI SULLE CODE 			*/
/****************************************************************/

void extend(Queue& q){
    Queue aux;
    int size = q.maxsize;
    aux.queue = new Elem[size+BLOCKDIM];
    for(int i = 0; i < q.size; i++){
        aux.queue[i] = q.queue[i];
    }
    delete [] q.queue;
    q.queue = aux.queue;
    q.maxsize = (BLOCKDIM + size);
}

void shiftLeft(Queue& q){
    Queue aux;
    int j = 0;
    aux.queue = new Elem[q.maxsize];
    for(int i = 1; i<q.size; i++){
        aux.queue[j] = q.queue[i];
        j++;
    }
    q.queue = aux.queue;
    q.size = (q.size - 1);
}

/****************************************************************/
Queue queue::createEmpty()
{
    Queue q;
    q.queue = new Elem[BLOCKDIM];
    q.size = 0;
    q.maxsize = BLOCKDIM;
    return q;
}

/****************************************************************/
void queue::enqueue(Elem e, Queue& l) // aggiunge e in coda
{
    if(isEmpty(l)){
        l.queue[l.size] = e;
        l.size++;
        return;
    }else if(l.size == l.maxsize){
        extend(l);
        l.queue[l.size+1] = e;
        l.size++;
        return;
    }else{
        l.queue[l.size+1] = e;
        l.size++;
        return;
    }
}


/****************************************************************/
Elem queue::dequeue(Queue& l) // rimuove il primo elemento e lo restituisce
{
    if(isEmpty(l)){
        return EMPTYELEM;
    }else{
        Elem t = l.queue[0];
        shiftLeft(l);
        return t;
    }
}


/****************************************************************/
Elem queue::first(Queue& l) // restituisce il primo elemento
{
    if(isEmpty(l)){
        return EMPTYELEM;
    }else{
        Elem t = l.queue[0];
        return t;
    }
}


/****************************************************************/
bool queue::isEmpty(const Queue& l)
{
   return (l.size == 0);
}



/****************************************************************/
Queue readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    return readFromStream(ifs);
}


/****************************************************************/
Queue readFromStdin()
{
    cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " << FINEINPUT << " per terminare\n";
    return readFromStream((std::cin));
}


/****************************************************************/
Queue readFromStream(istream& str)
{
    Queue l = createEmpty();        
    int dato;
    str>>dato;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    while (dato!= FINEINPUT)  // assumiamo che il segnale di fine input nel file sia  FINEINPUT
        {     
        enqueue(dato, l);   // aggiunge l'elemento alla fine della coda
        str>>dato;
        if (!str) throw runtime_error("Errore inserimento dati\n");
        }
return l;
}

/****************************************************************/
void print(const Queue& l)
{
cout << endl;
for (int i=0; i<l.size; ++i)
   cout << l.queue[i] << "; "; 
cout << endl;
}
