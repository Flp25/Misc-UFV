#pragma once
#include <iostream>
#include <string>

using namespace std;

class banco{

   private:
      string dono;
      double cash;

   public:
      banco();
      banco(double c, string d);
      ~banco();

      void iniciar();
      void mensagens(int opt);

      void saldo(string d);
      void deposito(double c);
      double saque(double c);

};
