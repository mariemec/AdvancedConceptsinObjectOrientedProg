/*
*   La classe CentralWidget sert de widget central pour l'inteface
*   graphique VisiTest. Elle gère les évènements et les redirige
*   dans les onglets appropriés: onglet de test (géré par la
*   classe TestWidget) et l'onglet d'archive (géré par la classe
*   ArchiveWidget). La classe DonneeWidget est utilisée par les 2
*   onglets afin d'afficher les données.
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 févr. 2018) $
*   $Revision: 108 $
*   $Id: centralwidget.h 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2016 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/
#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include<QPushButton>
#include<QTabWidget>
#include<QTextEdit>

#include "visitest.h"
#include "leds.h"
#include "switches.h"

class DonneeWidget : public QWidget
{
	Q_OBJECT
public:
	DonneeWidget(QWidget *parent=0);
	~DonneeWidget();
	void set(const DonneesTest & data);
	void reset();
private:
	QLabel *type;
	QLabel *addSwitches, *retSwitches;
	QLabel *addLeds, *valLeds;
	Leds *leds;
	Switches *switches;
};

class TestWidget : public QWidget
{
	Q_OBJECT
public:
	TestWidget(QWidget *parent=0);
	~TestWidget();
    void set(const DonneesTest & data);
    void reset();
signals:
	void testButtonClicked();
private slots:
	void testClicked();
private:
	DonneeWidget *donneeWidget;
	QPushButton *button;
};

class ArchiveWidget : public QWidget
{
	Q_OBJECT
public:
	ArchiveWidget(QWidget *parent=0);
	~ArchiveWidget();
    void set(const DonneesTest & data);
    void reset();
signals:
	void firstArchiveClicked();
	void lastArchiveClicked();
	void previousArchiveClicked();
	void nextArchiveClicked();
private slots:
	void firstClicked();
	void lastClicked();
	void previousClicked();
	void nextClicked();
private:
	DonneeWidget *donneeWidget;
	QPushButton *first;
	QPushButton *last;
	QPushButton *previous;
	QPushButton *next;
};

class CentralWidget : public QWidget
{
	Q_OBJECT
public:
	CentralWidget(QWidget *parent=0);
	virtual ~CentralWidget();
    void setArchive(const DonneesTest & data);
    void setArchive(const int num, const int total);
    void resetArchive();
    void setTest(const DonneesTest & data);
    void resetTest();
signals:
	void firstArchiveClicked();
	void lastArchiveClicked();
	void previousArchiveClicked();
	void nextArchiveClicked();
	void testButtonClicked();
private slots:
	void firstClicked();
	void lastClicked();
	void previousClicked();
	void nextClicked();
	void testClicked();
private:
	QTabWidget *tabs;
	TestWidget *test;
	ArchiveWidget *archive;
};

#endif // CENTRALWIDGET_H
