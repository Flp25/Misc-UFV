#include<iostream>
int horas = 24;
int minutos = 60;

using namespace std;

int saida(int a, int b){

   cout << "O JOGO DUROU "<< a <<" HORA(S) E " << b << " MINUTO(S)\n";
   return 0;

}

int main(){

   int h_ini, h_fim;
   int m_ini, m_fim;
   int h_dif, m_dif;

   h_dif = m_dif = 0;

   cin >> h_ini >> m_ini >> h_fim >> m_fim;

   m_dif = m_fim - m_ini;
   h_dif = h_fim - h_ini;

   if(h_ini == h_fim && m_ini == m_fim)
      return saida(horas, m_dif);

   if((h_fim - h_ini) < 0){

      h_dif = horas + (h_fim - h_ini);

   }

   if((m_fim - m_ini) < 0){

      m_dif = minutos + (m_fim - m_ini);
      h_dif --;

      if(h_dif < 0)
         h_dif = horas - 1;

   }

   return saida(h_dif, m_dif);

}
