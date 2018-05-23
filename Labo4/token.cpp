/////////////////////////////////////////////////////////////////////
//
// Laboratorio 3: calcolo di semplici espressioni numeriche 
//                mediante pile e code
//
// vengono accettati dall'esterno solo numeri positivi.
// Per trattare anche numeri negativi occorre modificare
// l'analizzatore lessicale.
//
///////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "token.h"

using std::cout;
using std::cin;
using std::string;
using std::istringstream;
using std::ostringstream;

/////////////////////////////////////////////////////////////////////
// Funzioni ausiliarie su tipi di dato semplici
/////////////////////////////////////////////////////////////////////

// da stringa a numero
int str2int(const string &s) {
  int n;
  istringstream iss(s);
  iss >> n; 
  return n;
}

// da numero a stringa
string int2str(int n) {
  ostringstream oss;
  oss << n;
  string s = oss.str();
  return s;
}

// ritorna false se e solo se token di tipo sconosciuto o se stringa vuota.
// se stringa non vuota, la stringa perde il pezzo iniziale,
// che diventa token.

bool prossimoToken(string &s, token &t) {
  if(s.empty()){
    return false;
  }else{
    token t;
    t.val = s[0];
    if((int)t.val[0] < 10){
      t.k = NUMERO;
    }else{
      switch((int)t.val[0]){
        case 40: { t.k = PARENTESI_APERTA; break; }     // '('
        case 41: { t.k = PARENTESI_CHIUSA; break; }     // ')'
        case 43: { t.k = OP_SOMMA; break; }             // '+'
        case 45: { t.k = OP_SOTTRAZIONE; break; }       // '-'
        case 42: { t.k = OP_MOLTIPLICAZIONE; break; }   // '*'
        default: { t.k = SCONOSCIUTO; }
      }
    }
    //std::cerr << "\nTOKEN VALUE: " << t.val << std::endl;
    //std::cerr << "\nTYPE: " << t.k << std::endl;
    int n = s.find(" ", 0);
    string ns = s.substr(n, (s.size() - n));
    s.erase(0, s.size());
    s = ns;
    return true;
  }
}

