#ifndef INTERFACECLIENT_H
#define INTERFACECLIENT_H

#include <QtWidgets/QMainWindow>
#include <QTextCodec>
#include "ui_interfaceclient.h"

class InterfaceClient : public QMainWindow
{
	Q_OBJECT

public:
	InterfaceClient(QWidget *parent = 0);
	~InterfaceClient();

private:
	Ui::InterfaceClientClass ui;

	QTextCodec*	codec;
};

#endif // INTERFACECLIENT_H
