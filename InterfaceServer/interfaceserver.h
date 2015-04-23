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
	void newConnect8000();
	void newConnect8002();
	void newConnect9000();
	void newConnect9001();

	void readMessage8000();
	void readMessage8002();
	void readMessage9000();
	void readMessage9001();

	void startTcpserver();
	void sendMessage();

	void testPState();

private:
	Ui::InterfaceServerClass ui;

	QTcpServer* m_tcpServer8000;//���Բ������� T���
	QTcpServer* m_tcpServer8002;//���Բ������� R���
	QTcpServer* m_tcpServer9000;//ϵͳң��ң�ز���
	QTcpServer* m_tcpServer9001;//��ز���ע�뼰����


	QTcpSocket* m_tcpSocket8000;
	QTcpSocket* m_tcpSocket8002;
	QTcpSocket* m_tcpSocket9000;
	QTcpSocket* m_tcpSocket9001;
};

#endif // INTERFACESERVER_H
