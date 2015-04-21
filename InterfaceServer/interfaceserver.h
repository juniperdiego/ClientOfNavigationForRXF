#ifndef INTERFACESERVER_H
#define INTERFACESERVER_H

#include <QtWidgets/QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include "ui_interfaceserver.h"

const int TCP_FRAME_START_TAG = 1234567890;
const int TCP_FRAME_END_TAG = -1234567890;

class InterfaceServer : public QMainWindow
{
	Q_OBJECT

public:
	InterfaceServer(QWidget *parent = 0);
	~InterfaceServer();


public slots:
	void newConnect();
	void startTcpserver();
	void sendMessage();
	void readMessage();

	void testPState();

private:
	Ui::InterfaceServerClass ui;

	QTcpServer* m_tcpServer;
	QTcpSocket* m_tcpSocket;
};

#endif // INTERFACESERVER_H
