//FELIPE DIAS - 4799
//PRATICA 9 HERANCA MULTIPLA


#include"Veiculo.h"
#include"VTransporte.h"
#include"VPasseio.h"
#include"Carro.h"
#include"Moto.h"
#include"Taxi.h"
#include"Onibus.h"

#include<iostream>

using namespace std;

int main(){
    //V Passeio
    //Carro c(0," ", 2, 2017);
    Moto m;

    //V Transporte
    Onibus o;
    
    //Ambos
    Taxi t(100000,"Tesla", 2, 2017, 2, 10.99, 10.99, 100);
    // PRECO - MARCA - PASSAGEIROS - ANO - PORTAS - TAXA INI - VALOR POR KM - KMS

    //t.set_ano(2017);
     
    //o.imprime();
    //c.imprime();
    //m.imprime();

    t.imprime();

}

***************************************************************************************************************************************

#ifndef VEICULO_H
#define VEICULO_H

#include<string>
#include<iostream>
using namespace std;


class Veiculo{
    public:

        Veiculo();
        Veiculo(const double, string);
        ~Veiculo();

        void set_preco(double);
        void set_marca(string);

        double get_preco();
        string get_marca();

        virtual double IPVA()=0;
        virtual void imprime();

    private:

        double preco;
        string marca;


};


#endif // VEICULO_H



#include "Veiculo.h"
#include<iostream>

using namespace std;

Veiculo::Veiculo(){
    preco=0;
    marca=" ";
}
Veiculo:: ~Veiculo(){

}
Veiculo::Veiculo(const double a, const string b){
    cout<<"\nC.Normal - Veiculo\n";
    preco=a;
    marca=b;
}

void Veiculo::set_preco(double a){
    if(a>=0)    preco=a;
}
void Veiculo::set_marca(string b){
    marca=b;
}

double Veiculo::get_preco(){
    return this->preco;
}
string Veiculo::get_marca(){
    return marca;
}

void Veiculo::imprime(){
    cout<<"-----------------------------------------\n";
    cout<<"VEICULO\n";
    cout<<"Marca: "<<marca<<endl;
    cout<<"Preco: "<<preco<<" $\n";
}


***************************************************************************************************************************************

#ifndef VPASSEIO_H
#define VPASSEIO_H

#include<string>
#include<iostream>
#include"Veiculo.h"
using namespace std;


class VPasseio: virtual public Veiculo{
    public:

        VPasseio();
        VPasseio(const double, const string, const int);
        ~VPasseio();

        void set_ano(int);
        int get_ano();

        virtual double seguro()=0;
        virtual double IPVA()=0;

        virtual void imprime();


    private:

        int ano;


};

#endif // VPasseio_H



#include"VPasseio.h"
#include<iostream>
#include<string>

using namespace std;

VPasseio::VPasseio(){
    ano=0;
}

VPasseio::VPasseio(const double a, const string b, const int c):Veiculo(a,b){
    cout<<"\nC.Normal - VPasseio\n";
    this->ano=c;
}


VPasseio::~VPasseio(){ }


void VPasseio::set_ano(int a){
 this->ano=a;

}


int VPasseio::get_ano(){

    return ano;

}

void VPasseio::imprime(){

    Veiculo::imprime();
    cout<<"Ano: "<<get_ano()<<endl;
}


***************************************************************************************************************************************


#ifndef VTRANSPORTE_H
#define VTRANSPORTE_H

#include"Veiculo.h"
#include<string>
#include<iostream>
using namespace std;


class VTransporte : virtual public Veiculo{
    public:
        VTransporte();
        VTransporte(const double, const string, const int);
        ~VTransporte();

        void set_numPassageiros(int);
        int get_numPassageiros();

        virtual double Valor_Tarifa()=0;

        virtual void imprime();

    private:
        int numPassageiros;

};


#endif // VEICULO_H


#include "VTransporte.h"
#include<iostream>

using namespace std;

VTransporte::VTransporte(){
    numPassageiros=0;
}
VTransporte::~VTransporte(){
}
VTransporte::VTransporte(const double a, const string b, const int c): Veiculo(a,b){
    cout<<"\nC.Normal - VTransporte\n";
   numPassageiros=c;
}

void VTransporte::set_numPassageiros(int a){
    if(a>=0)    numPassageiros=a;
}


int VTransporte::get_numPassageiros(){
    return numPassageiros;
}


void VTransporte::imprime(){
    Veiculo::imprime();
    cout<<numPassageiros<<" passageiros\n";
}


***************************************************************************************************************************************

#ifndef CARRO_H
#define CARRO_H

#include<string>
#include<iostream>
#include"VPasseio.h"
using namespace std;


class Carro: virtual public VPasseio{
    public:

        Carro();
        Carro(const double, const string, const int, const int);
        ~Carro();

        void set_portas(int);
        int get_portas();

        virtual double seguro();
        virtual double IPVA();

        virtual void imprime();


    private:

        int portas;


};


#endif // Carro_H


#include<string>
#include<iostream>
#include"Carro.h"

using namespace std;

Carro::Carro(){

    portas=0;

}
Carro::Carro(const double a, const string b, const int c, const int d):VPasseio(a,b,c){
    cout<<"\nC.Normal - Carro\n";
    portas=d;    

}
Carro::~Carro(){ }

void Carro::set_portas(int a){

    if(a==2 || a==4) portas=a; 
   
}

int Carro::get_portas(){

    return portas;

}

double Carro::seguro(){

    double seg;

    seg=(this->get_preco()*0.02)*(1+(0.02*(2017-get_ano())));

    if(this->get_portas()==4) seg=seg-(seg*0.05);

    return seg;

}
double Carro::IPVA(){

    return this->get_preco()*0.04;

}

void Carro::imprime(){

    VPasseio::imprime();
    cout<<"Seguro: "<<seguro()<<" $\n";
    cout<<"IPVA: "<<IPVA()<<" $\n";
    cout<<portas<<" Portas\n";
    cout<<"-----------------------------------------\n";

}


***************************************************************************************************************************************

#ifndef MOTO_H
#define MOTO_H

#include<string>
#include<iostream>
#include"VPasseio.h"
using namespace std;


class Moto: public VPasseio{
    public:

        Moto();
        Moto(const double, const string, const int, const int);
        ~Moto();

        void set_cilindradas(int);
        int get_cilindradas();

        virtual double seguro();
        virtual double IPVA();

        virtual void imprime();


    private:

        int cilindradas;


};


#endif // Moto_H


#include<string>
#include<iostream>
#include"Moto.h"
using namespace std;

Moto::Moto(){

    cilindradas=0;

}
Moto::Moto(const double a, const string b, const int c, const int d):VPasseio(a,b,c){

    cilindradas=d;

}
Moto::~Moto(){ }

void Moto::set_cilindradas(int a){

    if(a>0) cilindradas=a;

}
int Moto::get_cilindradas(){

    return cilindradas;

}

double Moto::seguro(){

    double seg;
    seg=(this->get_preco()*0.03)*(1+(0.02*(2017-this->get_ano())));

    if(this->get_cilindradas()>500) seg=seg+(seg*0.1);

    return seg;

}
double Moto::IPVA(){

    return this->get_preco()*0.02;

}

void Moto::imprime(){

    VPasseio::imprime();
    cout<<"Seguro: "<<seguro()<<" $\n";
    cout<<"IPVA: "<<IPVA()<<" $\n";
    cout<<cilindradas<<" CC\n";
    cout<<"-----------------------------------------\n";


}



***************************************************************************************************************************************


#ifndef ONIBUS_H
#define ONIBUS_H

#include"VTransporte.h"

#include<string>
#include<iostream>
using namespace std;


class Onibus : public VTransporte{
    public:
        Onibus();
        ~Onibus();
        Onibus(const double, const string, const int, const double);


        void set_tarifaFixa(double);
        double get_tarifaFixa();

        virtual double Valor_Tarifa();
        virtual double IPVA();
        virtual void imprime();
    private:
        double tarifaFixa;

};


#endif // VEICULO_H



#include "Onibus.h"
#include<iostream>

using namespace std;

Onibus::Onibus(){
    tarifaFixa=0;
}
Onibus::~ Onibus(){
}
Onibus::Onibus(const double a, const string b, const int c, const double d): VTransporte(a,b,c){
   tarifaFixa=d;
}

void Onibus::set_tarifaFixa(double a){
    if(a>=0)    tarifaFixa=a;
}


double Onibus::get_tarifaFixa(){
    return tarifaFixa;
}

double Onibus:: Valor_Tarifa(){
    return tarifaFixa;

}
double Onibus::IPVA(){
    return this->get_preco()*0.01;
}

void Onibus::imprime(){
    VTransporte::imprime();
    cout<<"IPVA: "<<IPVA()<<" $\n";
    cout<<tarifaFixa<<" $ de tarifa\n";
}

**********************************************HERANCA MULTIPLA***************************************************************************

#ifndef TAXI_H_INCLUDED
#define TAXI_H_INCLUDED

#include<iostream>
#include"VTransporte.h"
#include"Carro.h"
#include<string>
using namespace std;

class Taxi:public Carro, public VTransporte{
    public:
        Taxi();                                   //Numero de portas
        Taxi(const double, const string, const int, const int, const int, const double, const double, const int);
        ~Taxi();

        virtual double Valor_Tarifa();
        virtual double IPVA();
        virtual void imprime();

    private:
        double tarifaInicial, valorKM;
        int KM;


};


#endif // TAXI_H_INCLUDED

#include "Taxi.h"
#include<string>
#include<iostream>

using namespace std;

Taxi::Taxi(){
    tarifaInicial=0;
    valorKM=0;
    KM=0;
}

Taxi::~Taxi(){  }

Taxi::Taxi(const double a, const string b, const int c, const int d, const int e, const double f, const double g, const int h): Veiculo(a,b), Carro(a,b,d,e), VTransporte(a,b,c){
   
   this->set_ano(d);
   tarifaInicial=f;
   valorKM=g;
   KM=h;
}

double Taxi:: Valor_Tarifa(){
    return (tarifaInicial+valorKM*KM);
}


double Taxi::IPVA(){
    return this->get_preco()*0.02;
}

void Taxi::imprime(){
    cout<<" -Taxi- Heranca Multipla\n";

    VTransporte::imprime();
    Carro::imprime();
    cout<<"IPVA: "<<IPVA()<<" $\n";
    cout<<tarifaInicial<<" $ de tarifa inicial\n";
    cout<<valorKM<<" $ de Valor por KM\n";
    cout<<KM<<" KM de distancia\n";
}



















