#include <iostream>
using namespace std;
template <typename T>

class Vecteur
{
protected:
	int size; 								//nombre d'items dans le vecteur
	int capacity; 							//nombre max d'items que le vecteur peut contenir
	T* ptrs;
	int position;
public:
	Vecteur();
	~Vecteur();
	int sizeOf();
	int capacityOf();
	int getPos();
	void setPos(int pos);
	void doubleCapacity();
	bool addItemFile(T contenu); 			//contenu a ajouter a la fin du vecteur
											//Reussi: Vrai   Echec: Faux
	bool addItemPile(T contenu);
	
	bool isVectorFull();					//Retourne vrai si le vecteur est plein. Sinon, retourne faux.
	void showVector(ostream & s);
	T eraseItem(int index); 			//index de l'item a enlever du vecteur


	T obtainItem(int index);			//index de l'item a obtenir

	void clear();

	bool isEmpty();

	T operator[] (int index)
	{
		return ptrs[index];
	};

	void operator++ ()
	{
		if (position == size)
			position = 1;
		else {
			position++;
		}
	};
	
	void operator-- ()
	{
		if (position == 1)
			position = size;
		else {
			position--;
		}
	};

	void operator+= (T contenu)
	{
		//mode file seulement
		this->addItemFile(contenu);
	};

};

template <typename T>
Vecteur<T>::Vecteur()
{
	capacity = 1;
	position = 1;
	size = 0;
	ptrs = new T[capacity]; //instanciation d'un nouveau vecteur

}

template <typename T>
Vecteur<T>::~Vecteur()
{
	clear();
}

template <typename T>
int Vecteur<T>::sizeOf()
{
	return size;
}

template <typename T>
int Vecteur<T>::capacityOf()
{
	return capacity;
}

template <typename T>
int Vecteur<T>::getPos()
{
	return position;
}

template <typename T>
void Vecteur<T>::setPos(int pos)
{
	position=pos;
}

template <typename T>
bool Vecteur<T>::addItemFile(T contenu)
{
	if (isVectorFull() == true)			//Verifie si le vecteur est plein
	{
		doubleCapacity();
		ptrs[size] = contenu;			//Ajoute le pointeur de la nouvelle forme au tableau
		size++;

	}
	else
	{
		ptrs[size] = contenu;
		size++;
	}
	return true;
}

template <typename T>
bool Vecteur<T>::addItemPile(T contenu)
{
	if (isVectorFull() == true)			//Verifie si le vecteur est plein
	{
		doubleCapacity();
		for (int i = size; i > 0 ; i--) {
			ptrs[i] = ptrs[i-1];
		}
		ptrs[0] = contenu;			//Ajoute le pointeur de la nouvelle forme au tableau
		size++;

	}
	else
	{
		for (int i = size; i > 0; i--) {
			ptrs[i] = ptrs[i - 1];
		}
		ptrs[0] = contenu;
		size++;
	}
	return true;
}
template <typename T>
void Vecteur<T>::doubleCapacity()
{
	T *temp = ptrs;     		//Pointeur temporaire vers le tableau plein
	capacity *= 2;
	ptrs = new T[capacity];		//creation d'un tableau de pointeurs avec le double de capacity

	for (int i = 0; i < size; i++)
	{
		ptrs[i] = temp[i];		//Recopie les valeurs du tableau plein dans le nouveau gros tableau
	}
	delete[] temp;
}

template <typename T>
bool Vecteur<T>::isVectorFull()
{
	if (size == capacity)
	{
		return true;
	}
	return false;
}

template <typename T>
void Vecteur<T>::showVector(ostream & s)
{
	if (isEmpty() == true)
	{
		s << "Size:" << sizeOf() << ", Capacity: " << capacityOf() << endl;
		s << "Le vecteur est vide." << endl;
	}
	else
	{
		s << "Size:" << sizeOf() << ", Capacity: " << capacityOf() << endl;
		for (int i = 0; i < size; i++)
		{
			ptrs[i]->afficher(s);
		}
	}
	s << endl;

}

template <typename T>
T Vecteur<T>::eraseItem(int index)
{
	if (index<0 || index > size)		//index doit etre valide
	{
		T ptr = NULL;
		return ptr;
	}

	else
	{
		T p_address = ptrs[index];
		for (int i = index; i < size - 1; i++)
		{
			ptrs[i] = ptrs[i + 1];		//copie toutes les valeurs du vecteur vers l'index precedent (decalage)
		}
		T ptr = NULL;			//Dernier element du tableau est en double (a cause du decalage)
		ptrs[size] = ptr;			//Assigne un pointeur nul a l'ancienne position du dernier pointeur
		size--;
		return p_address;
	}

}

template <typename T>
T Vecteur<T>::obtainItem(int index)
{
	if (index<0 || index > size)		//index doit etre valide
	{
		T ptr = NULL;
		return ptr;
	}
	else
	{
		T valeur = ptrs[index];
		return valeur;
	}
}

template <typename T>
void Vecteur<T>::clear()
{
	T* temp = ptrs;
	capacity = 1;
	ptrs = new T[capacity];
	delete[] temp;				//Efface la memoire allouee dynamiquement au pointeur
	size = 0;
	position = 1;
}

template <typename T>
bool Vecteur<T>::isEmpty()
{
	if (size == 0)
		return true;
	else
		return false;
}

