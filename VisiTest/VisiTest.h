/*
*   La classe VisiTest offre une interface graphique (sous forme de librairie)
*   afin de tester certaines fonctionnalités de la carte FPGA utilisée en S2.
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 févr. 2018) $
*   $Revision: 108 $
*   $Id: VisiTest.h 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2016 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/
#ifndef VISITEST_H
#define VISITEST_H

#include <QMainwindow>

using namespace std;
struct DonneesTest
{
	int typeTest;

	int registreSW;
	int retourSW;
	int etatSW;

	int registreLD;
	int valeurLD;
	int etatLD;

	friend ostream& operator<<(ostream &os, const DonneesTest& aAfficher);
};

class VisiTest: public QMainWindow
{
	Q_OBJECT
public:
	VisiTest(const char *titre = 0);
	virtual ~VisiTest();

	void setArchive(const DonneesTest & data);
	void setArchive(const int num, const int total);
	void resetArchive();

	virtual void sauvegarder(char *nomFichier);

	void setTest(const DonneesTest & data);
	void resetTest();

	void message(const char *msg);

public slots:	
	virtual void testSuivant();
	virtual void demarrer();
	virtual void arreter();
	virtual void vider();
	virtual void modeFile();
	virtual void modePile();

	virtual void premier();
	virtual void dernier();
	virtual void precedent();
	virtual void suivant();

	void sauvegarder();
	void quitter();
private:
	QWidget *widget;
};

#endif //VISITEST_H
