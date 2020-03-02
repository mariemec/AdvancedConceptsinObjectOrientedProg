/*
*   Ce programme teste l'interface usager VisiTest (librairie)
*   avec l'aide de la classe MonInterface.
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 févr. 2018) $
*   $Revision: 108 $
*   $Id: TestVisiTest.cpp 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2013 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/
#include <QApplication>
#include "MonInterface.h"

int main( int argc, char ** argv )
{
	QApplication app(argc, argv);
 
	MonInterface gui("TestCarte V1");

   app.exec();
}
