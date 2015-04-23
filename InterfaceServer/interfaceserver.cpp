#include "interfaceserver.h"
//#include <windows.h>
//#pragma comment(lib, "Winmm.lib")
#include <Winsock2.h>
#pragma comment(lib,"ws2_32.lib")

void ntohlArray(int *p, int size)
{
	if(p == NULL)
		return;
	for(int i = 0; i < size; i ++)
	{
		p[i] = ntohl(p[i]);
	}
}

void htonlArray(int *p, int size)
{
	for(int i = 0; i < size; i++)
	{
		p[i] = htonl(p[i]);
	}
}

InterfaceServer::InterfaceServer(QWidget *parent)
	: QMainWindow(parent)
	, m_tcpServer8000(NULL)
	, m_tcpServer8002(NULL)
	, m_tcpServer9000(NULL)
	, m_tcpServer9001(NULL)
	, m_tcpSocket8000(NULL)
	, m_tcpSocket8002(NULL)
	, m_tcpSocket9000(NULL)
	, m_tcpSocket9001(NULL)
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
	m_tcpServer8000 = new QTcpServer(this);   
	m_tcpServer8002 = new QTcpServer(this);   
	m_tcpServer9000 = new QTcpServer(this);   
    m_tcpServer9001 = new QTcpServer(this);   
       
	m_tcpServer8000->listen(QHostAddress::Any, 8000); //�����κ�����8000�˿ڵ�ip 
	m_tcpServer8002->listen(QHostAddress::Any, 8002); //�����κ�����8002�˿ڵ�ip 
	m_tcpServer9000->listen(QHostAddress::Any, 9000); //�����κ�����9000�˿ڵ�ip 
    m_tcpServer9001->listen(QHostAddress::Any, 9001); //�����κ�����9001�˿ڵ�ip   
       
	//�������źŴ���������newConnect()�ۺ�����������źź���һ������ʵ��������ȡ��   
    connect(m_tcpServer8000,SIGNAL(newConnection()),this,SLOT(newConnect8000()));
	connect(m_tcpServer8002,SIGNAL(newConnection()),this,SLOT(newConnect8002())); 
	connect(m_tcpServer9000,SIGNAL(newConnection()),this,SLOT(newConnect9000())); 
	connect(m_tcpServer9001,SIGNAL(newConnection()),this,SLOT(newConnect9001())); 
} 
void InterfaceServer::newConnect8000()   
{   
        m_tcpSocket8000 = m_tcpServer8000->nextPendingConnection(); //�õ�ÿ����������socket   
        connect(m_tcpSocket8000,SIGNAL(readyRead()),this,SLOT(readMessage8000())); //�пɶ�����Ϣ�������������� 
}  
void InterfaceServer::newConnect8002()   
{   
        m_tcpSocket8002 = m_tcpServer8002->nextPendingConnection(); //�õ�ÿ����������socket   
        connect(m_tcpSocket8002,SIGNAL(readyRead()),this,SLOT(readMessage8001())); //�пɶ�����Ϣ�������������� 
}  
void InterfaceServer::newConnect9000()   
{   
        m_tcpSocket9000 = m_tcpServer9000->nextPendingConnection(); //�õ�ÿ����������socket   
        connect(m_tcpSocket9000,SIGNAL(readyRead()),this,SLOT(readMessage9000())); //�пɶ�����Ϣ�������������� 
}  
void InterfaceServer::newConnect9001()   
{   
        m_tcpSocket9001 = m_tcpServer9001->nextPendingConnection(); //�õ�ÿ����������socket   
        connect(m_tcpSocket9001,SIGNAL(readyRead()),this,SLOT(readMessage9001())); //�пɶ�����Ϣ�������������� 
}  
void InterfaceServer::readMessage8000() //��ȡ��Ϣ   
{  
	if (m_tcpSocket8000 == NULL) return;

    QByteArray qba= m_tcpSocket8000->readAll(); //��ȡ   
    qDebug()<<qba;   
    QString ss=QVariant(qba).toString();   
    ui.textEdit_rec->setText(ss);   
} 
void InterfaceServer::readMessage8002() //��ȡ��Ϣ   
{  
	if (m_tcpSocket8002 == NULL) return;

    QByteArray qba= m_tcpSocket8002->readAll(); //��ȡ   
    qDebug()<<qba;   
    QString ss=QVariant(qba).toString();   
    ui.textEdit_rec->setText(ss);   
} 
void InterfaceServer::readMessage9000() //��ȡ��Ϣ   
{  
	if (m_tcpSocket9000 == NULL) return;

	const int maxBufSize = 500;
	int* buf = new int[maxBufSize/sizeof(int)];
   	int bufSize = m_tcpSocket9000->read((char*)buf, maxBufSize); 
	ntohlArray(buf, bufSize/sizeof(int) );

	for(int i = 0; i < bufSize/sizeof(int); i ++)
	{
		qDebug()  << buf[i] ;
	}
	
#if 0
    QByteArray qba= m_tcpSocket9000->readAll(); //��ȡ   
    qDebug()<<qba;   
    QString ss=QVariant(qba).toString();   
    ui.textEdit_rec->setText(ss);   
#endif
} 
void InterfaceServer::readMessage9001() //��ȡ��Ϣ   
{  
	if (m_tcpSocket9001 == NULL) return;

	const int maxBufSize = 500;
	int* buf = new int[maxBufSize/sizeof(int)];
   	int bufSize = m_tcpSocket9001->read((char*)buf, maxBufSize); 
	ntohlArray(buf, bufSize/sizeof(int) );

	for(int i = 0; i < bufSize/sizeof(int); i ++)
	{
		qDebug()  << buf[i] ;
	}  
} 
void InterfaceServer::sendMessage() //������Ϣ   
{   
	QTcpSocket *tcpSocket = NULL;
	tcpSocket = m_tcpSocket9000;
	if (tcpSocket == NULL) return;

    QString strMesg= ui.lineEdit_sendmessage->text();   
	if (!strMesg.isEmpty())
	{
		qDebug()<<strMesg;   
		tcpSocket->write(strMesg.toStdString().c_str(),strlen(strMesg.toStdString().c_str())); //����   
	}
}   

void InterfaceServer::testPState() //����״̬����
{   
	QTcpSocket *tcpSocket = NULL;
	tcpSocket = m_tcpSocket9000;
	if (tcpSocket == NULL) return;

	static bool c = true;
	
	QByteArray sendBytes;
	QDataStream out(&sendBytes, QIODevice::WriteOnly);
	out.setFloatingPointPrecision(QDataStream::SinglePrecision);
	out<<TCP_FRAME_START_TAG;
	out<<56;
	out<<0;

	c = ! c;

	if(c)
		out<<float(3.5);
	else
		out << 3.8f;
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

	tcpSocket->write(sendBytes);
	



}   
  
