/*
*   La classe Leds est un widget qui affiche les 8 leds de l'interface
*   graphique.
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 févr. 2018) $
*   $Revision: 108 $
*   $Id: leds.h 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2013 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/
#ifndef LED_H
#define LED_H

#include<QWidget>
#include<QLabel>
#include<QPixmap>

class Leds : public QWidget
{
public:
   Leds(QWidget *parent, int numLeds, int height, int width);
   virtual ~Leds() {}
   void set(const int state);
   int get() { return state; }
protected:
   const int nbLeds;
   const int ledPad;
   const int ledWidth;
   const int ledHeight;
private:
   int state;
   QLabel **leds;
   QPixmap on, off;
};

#endif // LED_H
