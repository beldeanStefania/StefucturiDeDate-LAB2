#include "ATM.h"
#include"Collection.h"
#include<iostream>
using namespace std;

void ATM::afisareColectie(Element bancnote[], int lungime, int k)
{
	cout << k << ")";
	k++;
	for (int i = 0; i < lungime; i++)
		cout << bancnote[i].valoare << " -> " << bancnote[i].nr_aparitii << " ";
	cout << endl;
}

ATM::ATM(const Collection& colectie, Tranzactie tranzactie[], int nrTranzactii)
{
	this->colectieBancnote = colectie;
	this->tranzactii = new Tranzactie[nrTranzactii];
	this->nrTranzactii = nrTranzactii;
	for (int i = 0; i < nrTranzactii; i++)
		this->tranzactii[i] = tranzactie[i];

}

void ATM::retragereNumerar(int id, int suma, int lungime, Element bancnote[])
{
	int ok = 1;
	for (int i = 0; i < lungime; i++)
		if (bancnote[i].nr_aparitii > this->colectieBancnote.nroccurrences(bancnote[i].valoare)) ok = 0;
	if (ok == 0) cout << "Momentan ATM-ul nu are suficiente bancnote pt a efectua tranzactia" << endl;
	else
	{
		cout << "Tranzactie efectuata cu succes" << endl;
		for (int i = 0; i < lungime; i++)
		{
			Element element;
			element.valoare = bancnote[i].valoare;
			element.nr_aparitii = this->colectieBancnote.nroccurrences(element.valoare) - bancnote[i].nr_aparitii;
			this->colectieBancnote.setNumarBancnote(element);
		}
		this->tranzactii[this->nrTranzactii] = Tranzactie(id, suma, bancnote, lungime);
		this->nrTranzactii++;
	}
}

void ATM::addBancnota(TElem valoare)
{
	this->colectieBancnote.add(valoare);
}

void ATM::elimBancnota(TElem valoare)
{
	this->colectieBancnote.remove(valoare);
}

void ATM::getTranzactia(int& poz_stop, int suma, Element bancnote[], int lungime, int poz)
{
	if (suma == 0)
	{
		poz_stop--;
		bancnote[lungime].valoare = -1;
	}
	else {
		for (int i = poz; i < this->colectieBancnote.getLungime() && poz_stop; i++) {
			if (poz_stop == 0) break;
			int k = 0;
			TElem bancnota = this->colectieBancnote.getVal(i);
			while (suma >= 0) {
				suma = suma - bancnota;
				k++;
				bancnote[lungime].valoare = bancnota;
				bancnote[lungime].nr_aparitii = k;
				getTranzactia(poz_stop, suma, bancnote, lungime + 1, i + 1);
				if (poz_stop == 0) break;
			}
			if (suma < 0) {
				suma = suma + bancnota;
				k--;
				bancnote[lungime].nr_aparitii = k;
			}
			suma = suma + k * bancnota;
		}
	}
}

void ATM::generareTranzactii(int& indice, int suma, Element bancnote[], int lungime, int poz)//backtracking
{
	if (suma == 0)
		afisareColectie(bancnote, lungime, indice);
	else {
		for (int i = poz; i < this->colectieBancnote.getLungime(); i++) {
			int k = 0;
			TElem bancnota = this->colectieBancnote.getVal(i);
			while (suma >= 0) {
				suma = suma - bancnota;
				k++;
				bancnote[lungime].valoare = bancnota;
				bancnote[lungime].nr_aparitii = k;
				if (suma == 0) indice++;
				generareTranzactii(indice, suma, bancnote, lungime + 1, i + 1);
			}
			if (suma < 0) {
				suma = suma + bancnota;
				k--;
				bancnote[lungime].nr_aparitii = k;
			}
			suma = suma + k * bancnota;
		}
	}
}

ostream& operator<<(ostream& os, ATM atm)
{
	// TODO: insert return statement here
	cout << "BANCNOTE DISPONIBILE:" << endl;
	for (int i = 0; i < atm.colectieBancnote.getLungime(); i++)
		cout << "val: " << atm.colectieBancnote.getVal(i) << ", numar: " << atm.colectieBancnote.getAt(i) << endl;
	cout << endl << "TRANZACTII EFECTUATE: " << endl;
	for (int i = 0; i < atm.nrTranzactii; i++) {
		cout << atm.tranzactii[i];
		cout << endl;
	}
	return os;
}
