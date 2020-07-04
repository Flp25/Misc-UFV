#include<iostream>
#include<string>
#include "banco.h"

using namespace std;

//void mensagens(int opt);
//void inicio();

int main(){

   double cash = 600;
   string nome = "Felipe Dias Macedo";
   banco x(cash, nome);
   x.iniciar();
   x.saldo(nome);
   x.saque(474);
   return 0;

}
