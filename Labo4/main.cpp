/////////////////////////////////////////////////////////////////////
//
// Laboratorio 3: calcolo di semplici espressioni numeriche 
//                mediante pile e code
//
// vengono accettati dall'esterno solo numeri positivi.
// Per trattare anche numeri negativi occorre modificare
// l'analizzatore lessicale.
//
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "token.h"
#include "queue.h"
#include "stack.h"

using std::cout;
using std::cin;
using std::string;
using std::istringstream;
using std::ostringstream;

/////////////////////////////////////////////////////////////////////
// Funzioni principali: leggi() e calcola()
/////////////////////////////////////////////////////////////////////

// Estrae uno dopo l'altro i token dalla stringa "str", inserendoli via via nella coda "codaToken"
bool leggi(const string &str, queue::Queue &codaToken) {
  token t;
  string str1 = str;
  bool res = true;
  while(res || !(str1.empty())){
    if(prossimoToken(str1, t)){
      queue::enqueue(t, codaToken);
      res = true;
    }else{
      res = false;
    }
  }
  return res;
}

// Estrae uno dopo l'altro i token dalla coda, inserendoli via via sullo stack.
// Appena si incontra un token PARENTESI CHIUSA, quello segnala la fine
// di una sottoespressione; allora tiriamo giu' dallo stack gli ultimi cinque token inseriti.
// I token estratti dovrebbero essere esattamente, nell'ordine:
// un ")", un numero, un operatore aritmetico, un altro
// numero, e un "("; se non è così, allora si segnala
// errore sintattico e l'algoritmo termina.
// A questo punto la funzione deve convertire i token di tipo NUMERO in numeri interi, 
// eseguire l'operazione aritmetica opportuna, e trasformare il risultato da numero a
// token e inserire quest'ultimo sullo stack.
// Alla fine se non ci sono errori sintattici la funzione deve mettere nella variabile
// risultato il vaore dell'espressione
bool calcola(queue::Queue codaToken, int &risultato) {
  token t;
  stack::Stack pilaToken;
  token PC, PA, N1, N2, OP;
  while(codaToken != queue::EMPTYQUEUE){
    t = queue::dequeue(codaToken);
    if(t.k != PARENTESI_CHIUSA){
      stack::push(t, pilaToken);
    }else{
      int j = 0;
      for(int i = 0; i < 5; i++){
        t = stack::pop(pilaToken);
        j++;
      }
      switch(j){
        case 0: { PC = t; break; }
        case 1: { N1 = t; break; }
        case 2: { OP = t; break; }
        case 3: { N2 = t; break; }
        case 4: { PA = t; break; }
        default: { return false; }
      }
      int n1, n2;
      string s1 = N1.val;
      string s2 = N2.val;
      istringstream itmp1(s1);
      itmp1 >> n1;
      istringstream itmp2(s2);
      itmp2 >> n2;
      switch(OP.k){
        case 4: { risultato = (n1+n2); break; }
        case 5: { risultato = (n1-n2); break; }
        case 6: { risultato = (n1*n2); break; }
        default: { return false; }
      }
      string res;
      ostringstream otmp;
      otmp << risultato;
      res = otmp.str(); 
      t.val = res; 
      t.k = NUMERO;
      stack::push(t, pilaToken);
    }
  }
  token res = stack::pop(pilaToken);
  string resT = res.val;
  istringstream itmp(resT);
  itmp >> risultato;
  return true;
  // DA IMPLEMENTARE
  //return true;
}

/////////////////////////////////////////////////////////////////////
//                               MAIN
/////////////////////////////////////////////////////////////////////

int main() {

  string s;
  queue::Queue q;
  int r;

  cout << "Inserisci l'espressione che vuoi valutare:" << endl;
  getline(cin,s);

  if (!leggi(s,q)) {
    cout << "errore lessicale\n";
    exit(1);
  }

  if (!calcola(q,r)) {
    cout << "errore sintattico\n";
    exit(1);
  }

  cout << "risultato: " << r << "\n";
  exit(0);
}
