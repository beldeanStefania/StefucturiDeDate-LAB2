#include "Tranzactie.h"
#include<iostream>
using namespace std;

Tranzactie::Tranzactie(int id, int suma, Element bancnote[], int nr_bancnote)
{
	this->idTranzactie = id;
	this->nrBanconte = nr_bancnote;
	this->suma = suma;
	this->bancnote = new Element[nr_bancnote];
	for (int i = 0; i < nr_bancnote; i++) this->bancnote[i] = bancnote[i];
}

Tranzactie::Tranzactie()
{
	this->idTranzactie = -1;
	this->suma = -1;
	this->bancnote = new Element[1];
	this->nrBanconte = -1;
}

void Tranzactie::Destructor()
{
	delete[] this->bancnote;
}

Tranzactie& Tranzactie::operator=(const Tranzactie& tranzactie)
{
	// TODO: insert return statement here
	this->idTranzactie = tranzactie.idTranzactie;
	this->suma = tranzactie.suma;
	this->nrBanconte = tranzactie.nrBanconte;
	delete[] this->bancnote;
	for (int i = 0; i < this->nrBanconte; i++) this->bancnote[i] = tranzactie.bancnote[i];
	return *this;
}

ostream& operator<<(ostream& os, Tranzactie tranzactie)
{
	// TODO: insert return statement here
	cout << "Id-ul tranzactiei este: " << tranzactie.idTranzactie << " suma de: " << tranzactie.suma << endl;
	cout << "Generare plata: ";
	for (int i = 0; i < tranzactie.nrBanconte; i++) cout << tranzactie.bancnote[i].valoare << " ~ " << tranzactie.bancnote[i].nr_aparitii<<", ";
	cout << endl;
	return os;
}
