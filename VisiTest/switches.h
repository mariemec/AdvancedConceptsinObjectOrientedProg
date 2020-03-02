/*
*   La classe Switches est un widget qui affiche les 8 dipswitches de l'interface
*   graphique.
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 févr. 2018) $
*   $Revision: 108 $
*   $Id: switches.h 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2013 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/
#ifndef SWITCHES_H
#define SWITCHES_H

#include<QWidget>
#include<QSlider>

class Switches : public QWidget
{
public:
   Switches(QWidget *parent, int numSwitches, int height, int width);
   ~Switches();

   void set(const int state);
   int get() const;
private:
   const int nbSwitches, height, width;
   QSlider **switches;
   int state;
};

#endif // SWITCHES_H
