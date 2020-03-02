#include <iostream>
#include "Vecteur.h"
using namespace std;

Vecteur::Vecteur()
{
	capacity = 1;
	size = 0;
	formes = new Forme*[capacity]; //instanciation d'un nouveau vecteur

	for (int i=0; i<capacity;i++) //Remplissage du vecteur avec des NULL
	{
		formes[i]=NULL;
	}
}
Vecteur::~Vecteur()
{
	clear();
}

int Vecteur::sizeOf()
{
	return size;	
}


int Vecteur::capacityOf()
{
	return capacity;
}

bool Vecteur::addItem(Forme* ptrForme)
{
	if (isVectorFull()==true)			//Verifie si le vecteur est plein
	{
		doubleCapacity();	
		formes[size]=ptrForme;			//Ajoute le pointeur de la nouvelle forme au tableau
		size++;

	}
	else
	{
		formes[size]=ptrForme;
		size++;		
	}
	return true;
}

void Vecteur::doubleCapacity()
{
	Forme **temp = formes;     		//Pointeur temporaire vers le tableau plein
	capacity*=2;
	formes = new Forme*[capacity];		//creation d'un tableau de pointeurs avec le double de capacity

	for (int i=0;i<size;i++)
	{
		formes[i]=temp[i];		//Recopie les valeurs du tableau plein dans le nouveau gros tableau
	}
	delete[] temp;
}

bool Vecteur::isVectorFull()
{
	if (size == capacity)
	{
		return true;	
	}
	return false;
}

void Vecteur::showVector(ostream & s)
{
	if (isEmpty()==true)
	{
		s << "Size:"<< sizeOf()<<", Capacity: "<<capacityOf()<<endl;
		s<<"Le vecteur est vide."<<endl;
	}
	else
	{
		s << "Size:"<< sizeOf()<<", Capacity: "<<capacityOf()<<endl;	
		for (int i=0;i<size;i++)
		{
			formes[i]->afficher(s);
		}
	}
	s<<endl;
	
}

Forme* Vecteur::eraseItem(int index)
{
	if (index<0 || index > size)		//index doit etre valide
	{
		Forme* ptr = NULL;
		return ptr;
	}

	else
	{
		Forme* p_address = formes[index];
		for (int i=index;i<size-1;i++)
		{
			formes[i]=formes[i+1];		//copie toutes les valeurs du vecteur vers l'index precedent (decalage)
		}
		Forme* ptr = NULL;			//Dernier element du tableau est en double (a cause du decalage)
		formes[size]=ptr;			//Assigne un pointeur nul a l'ancienne position du dernier pointeur
		size--;
		return p_address;		
	}

}

Forme* Vecteur::obtainItem(int index)
{
	if (index<0 || index > size)		//index doit etre valide
	{
		Forme* ptr = NULL;
		return ptr;
	}
	else
	{
		Forme *p_address = formes[index];
		return p_address;
	}
}

void Vecteur::clear()
{
	for (int i=0;i<size;i++)
	{
		delete formes[i];			//Efface la memoire allouee dynamiquement aux Formes pointees dans le vecteur
	}
	delete[] formes;				//Efface la memoire allouee dynamiquement au pointeur
	size = 0;
}

bool Vecteur::isEmpty()
{
	if (size ==0)
		return true;
	else
		return false;
}

