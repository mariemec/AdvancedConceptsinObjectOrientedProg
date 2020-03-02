TEMPLATE     = vcapp
TARGET       = TestCarte
CONFIG      += warn_on qt debug_and_release windows console
HEADERS     += ./VisiTest/MonInterface.h ./VisiTest/centralwidget.h ./VisiTest/leds.h ./VisiTest/switches.h ./VisiTest/VisiTest.h ./CommunicationFPGA/CommunicationFPGA.h ./Vecteur/Vecteur.h
SOURCES     += ./VisiTest/MonInterface.cpp TestCarte.cpp
INCLUDEPATH += ./VisiTest ./CommunicationFPGA ./Vecteur
LIBS	      += ./VisiTest/VisiTest.lib ./CommunicationFPGA/CommunicationFPGA.lib
QT += widgets
