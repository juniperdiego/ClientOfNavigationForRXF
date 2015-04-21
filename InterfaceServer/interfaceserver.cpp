#include "interfaceserver.h"

InterfaceServer::InterfaceServer(QWidget *parent)
	: QMainWindow(parent)
	, m_tcpServer(NULL)
	, m_tcpSocket(NULL)
{
	ui.setupUi(this);

	connect(ui.pushButton_start,SIGNAL(clicked()),this,SLOT(startTcpserver()));   
    connect(ui.pushButton_send,SIGNAL(clicked()),this,SLOT(sendMessage()));   

    connect(ui.pushButton_testP,SIGNAL(clicked()),this,SLOT(testPState()));   

	ui.pushButton_start->setVisible(false);

	startTcpserver();
}

InterfaceServer::~InterfaceServer()
{

}

void InterfaceServer::startTcpserver()   
{   
    m_tcpServer = new QTcpServer(this);   
       
    m_tcpServer->listen(QHostAddress::Any, 9000); //�����κ�����9000�˿ڵ�ip   
       
	//�������źŴ���������newConnect()�ۺ�����������źź���һ������ʵ��������ȡ��   
    connect(m_tcpServer,SIGNAL(newConnection()),this,SLOT(newConnect())); 
} 
void InterfaceServer::newConnect()   
{   
        m_tcpSocket = m_tcpServer->nextPendingConnection(); //�õ�ÿ����������socket   
        connect(m_tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage())); //�пɶ�����Ϣ�������������� 
}  
void InterfaceServer::readMessage() //��ȡ��Ϣ   
{  
	if (m_tcpSocket == NULL) return;

    QByteArray qba= m_tcpSocket->readAll(); //��ȡ   
    qDebug()<<qba;   
    QString ss=QVariant(qba).toString();   
    ui.textEdit_rec->setText(ss);   
       
} 
void InterfaceServer::sendMessage() //������Ϣ   
{   
	if (m_tcpSocket == NULL) return;

    QString strMesg= ui.lineEdit_sendmessage->text();   
	if (!strMesg.isEmpty())
	{
		qDebug()<<strMesg;   
		m_tcpSocket->write(strMesg.toStdString().c_str(),strlen(strMesg.toStdString().c_str())); //����   
	}
}   

void InterfaceServer::testPState() //����״̬����
{   
	if (m_tcpSocket == NULL) return;

	QByteArray sendBytes;
	QDataStream out(&sendBytes, QIODevice::WriteOnly);
	out<<TCP_FRAME_START_TAG;
	out<<0;
	out<<56;
	out<<float(3.5);
	out<<float(4.1);
	out<<float(4.2);
	out<<float(4.3);
	out<<float(4.4);
	out<<float(4.5);
	out<<float(5.1);
	out<<float(5.2);
	out<<float(5.3);
	out<<float(5.4);
	out<<TCP_FRAME_END_TAG;

	m_tcpSocket->write(sendBytes);
}   
  