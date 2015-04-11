#ifndef INTERFACECLIENT_H
#define INTERFACECLIENT_H

#include <QtWidgets/QMainWindow>
#include "ui_interfaceclient.h"
#include "pixelarray.h"

class InterfaceClient : public QMainWindow
{
	Q_OBJECT

public:
	InterfaceClient(QWidget *parent = 0);
	~InterfaceClient();

private:
	void initComT();
	void initComR();
	void initSetting();

private:
	Ui::InterfaceClientClass ui;

	PixelArray* rCom;
	PixelArray* tCom;
	PixelArray* srCom;
	PixelArray* stCom;

};

#endif // INTERFACECLIENT_H
