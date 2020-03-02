/*
*   La classe MonInterface teste l'interface usager VisiTest (librairie).
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 févr. 2018) $
*   $Revision: 108 $
*   $Id: MonInterface.h 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2016 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/
#ifndef MONINTERFACE_H
#define MONINTERFACE_H

#include "VisiTest.h"
#include "CommunicationFPGA.h"
#include "Vecteur.h"

class MonInterface : public VisiTest
{
public:

	MonInterface(const char *theName);
public slots:
	virtual	void testSuivant();

	void demarrer();
	void arreter();
	void sauvegarder(char *nomFichier);
	void vider();
	void modeFile();
	void modePile();
	void premier();
	void dernier();
	void precedent();
	void suivant();

	void ajouter(DonneesTest donneeT);

private:
	DonneesTest donnee;
	CommunicationFPGA fpga;
	Vecteur<DonneesTest> enMemoire;
	bool isStart; //etat Demarrer ou Arreter
	bool isFile;  //mode file ou mode pile

	int testnbr;	//index du test a effectuer

};

#endif // MONINTERFACE_H