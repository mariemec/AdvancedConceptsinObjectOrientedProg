/*
*   Voir fichier d'entête pour informations.
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 févr. 2018) $
*   $Revision: 108 $
*   $Id: MonInterface.cpp 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2013 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/
#include <QStyleFactory>
#include "MonInterface.h"
#include <iostream>
#include <fstream>
using namespace std;

enum Registre { SW = 8, BTN = 9, LD = 10, AN0 = 11, AN1 = 12, AN2 = 13, AN3 = 14 };

MonInterface::MonInterface(const char * theName) : VisiTest(theName)
{
	testnbr = 0;
	isFile = true;
	isStart = false;

	donnee.typeTest = 1;
	donnee.registreSW = SW;
	donnee.retourSW = 1;

	donnee.registreLD = LD;
	donnee.valeurLD = 1;

	donnee.etatLD = 1;
	donnee.etatSW = 1;

	resetTest();
	resetArchive();
}

void MonInterface::testSuivant()
{
	
		testnbr++;

		if (testnbr == 1) {
			int valeur;
			fpga.lireRegistre(SW, valeur);
			fpga.ecrireRegistre(LD, valeur);

			donnee.etatSW = valeur;
			donnee.retourSW = valeur;
			donnee.etatLD = valeur;
			donnee.valeurLD = valeur;

			donnee.typeTest = 1;
			setTest(donnee);

			if (isStart)
				ajouter(donnee);

		}

		if (testnbr == 2) {
			int nbrSwAllum = 0;
			int valeur;
			int i = 1;

			fpga.lireRegistre(SW, valeur);

			while (i < 129) {
				if ((valeur&i) == i)
					nbrSwAllum++;
				i *= 2;
			}

			if ((nbrSwAllum % 2) == 0) {
				fpga.ecrireRegistre(LD, 255);
				donnee.etatSW = valeur;
				donnee.retourSW = valeur;
				donnee.etatLD = 255;
				donnee.valeurLD = 255;
			}
			else {
				fpga.ecrireRegistre(LD, 0);
				donnee.etatSW = valeur;
				donnee.retourSW = valeur;
				donnee.etatLD = 0;
				donnee.valeurLD = 0;
			}
			donnee.typeTest = 2;
			setTest(donnee);
			if (isStart)
				ajouter(donnee);
		}

		if (testnbr == 3) {
			int valeur;
			int nbrLdAllum;

			fpga.lireRegistre(SW, valeur);
			donnee.etatSW = valeur;
			donnee.retourSW = valeur;

			nbrLdAllum = log2(valeur + 1);

			int valeurLed = 0;
			if (nbrLdAllum != 0) {
				for (int i = 0; i < nbrLdAllum; i++) {
					valeurLed += pow(2, i);
				}
				donnee.etatLD = valeurLed;
				donnee.valeurLD = valeurLed;
			}
			else {
				valeurLed = 0;
				donnee.etatLD = 0;
				donnee.valeurLD = 0;
			}

			fpga.ecrireRegistre(LD, valeurLed);

			donnee.typeTest = 3;
			setTest(donnee);
			if (isStart)
				ajouter(donnee);

			testnbr = 0;
		}
}

void MonInterface::ajouter(DonneesTest donneeT) {	//methode qui ajoute une donnee selon le mode actif fil ou pile
	if (isFile)
	{
		enMemoire += donneeT;		//operator += est redefini pour ajouter un element a la fin du vecteur
		++enMemoire;
	}
	else {
		enMemoire.addItemPile(donneeT);	//une methode addItemPile() a ete ajoutee a la classe vecteur pour ajouter un element au debut du vecteur
	}
	message("Test ajouter aux archives.");
}

void MonInterface::demarrer() {
	message("La sauvegarde des tests est demarree.");
	isStart = true;
}
void MonInterface::arreter() {
	message("La sauvegarde des tests est terminee.");
	isStart = false;
}

void MonInterface::sauvegarder(char *nomFichier) {

	if (isStart == true) {
		fstream myFile;
		myFile.open(nomFichier, ios_base::out);
		if (myFile.is_open())
		{
			cout << "Fichier ouvert avec succes" << endl;

			for (int i = 0; i < enMemoire.sizeOf(); i++) {

				myFile << enMemoire[i];
			}
			myFile.close();
		}

	}
	else
		message("Sauvegarde echouee. Veuillez Demarrer SVP.");
}

void MonInterface::vider() {
	enMemoire.clear();
	resetArchive();
	message("Archives vides.");
}

void MonInterface::modeFile() {
	if (enMemoire.isEmpty())
	{
		isFile = true;
		message("Mode File activer.");
	}
	else{
		message("SVP vider avant de changer de mode");
	}
}

void MonInterface::modePile() {
	if (enMemoire.isEmpty())
	{
		isFile = false;
		message("Mode Pile activer.");
	}
	else
		message("SVP vider avant de changer de mode");
}

void MonInterface::premier() {
		setArchive(enMemoire[0]);
		setArchive(1, enMemoire.sizeOf());
		enMemoire.setPos(1);
}

void MonInterface::dernier() {
		setArchive(enMemoire[enMemoire.sizeOf()-1]);
		setArchive(enMemoire.sizeOf(), enMemoire.sizeOf());
		enMemoire.setPos(enMemoire.sizeOf());
}

void MonInterface::precedent() {
	--enMemoire;

		setArchive(enMemoire[enMemoire.getPos() - 1]);
		setArchive(enMemoire.getPos(), enMemoire.sizeOf());
}

void MonInterface::suivant() {
	++enMemoire;

		setArchive(enMemoire[enMemoire.getPos() - 1]);
		setArchive(enMemoire.getPos(), enMemoire.sizeOf());

}

ostream& operator<<(ostream &os, const DonneesTest& aAfficher) {

	os << "Type test: " << aAfficher.typeTest << endl;
	os << "Adresse Switch: " << aAfficher.registreSW << endl;
	os << "Retour Switch: " << aAfficher.retourSW << endl;
	os << "Etat Switch: " << aAfficher.etatSW << endl;
	os << "Adresse LED: " << aAfficher.registreLD << endl;
	os << "Valeur LED: " << aAfficher.valeurLD << endl;
	os << "Etat LED: " << aAfficher.etatLD << endl;
	os << "------------------------------------------------" << endl;
	return os;
}