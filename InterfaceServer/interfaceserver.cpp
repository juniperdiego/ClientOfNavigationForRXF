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
       
	m_tcpServer8000->listen(QHostAddress::Any, 8000); //监听任何连上8000端口的ip 
	m_tcpServer8002->listen(QHostAddress::Any, 8002); //监听任何连上8002端口的ip 
	m_tcpServer9000->listen(QHostAddress::Any, 9000); //监听任何连上9000端口的ip 
    m_tcpServer9001->listen(QHostAddress::Any, 9001); //监听任何连上9001端口的ip   
       
	//新连接信号触发，调用newConnect()槽函数，这个跟信号函数一样，其实你可以随便取。   
    connect(m_tcpServer8000,SIGNAL(newConnection()),this,SLOT(newConnect8000()));
	connect(m_tcpServer8002,SIGNAL(newConnection()),this,SLOT(newConnect8002())); 
	connect(m_tcpServer9000,SIGNAL(newConnection()),this,SLOT(newConnect9000())); 
	connect(m_tcpServer9001,SIGNAL(newConnection()),this,SLOT(newConnect9001())); 
} 
void InterfaceServer::newConnect8000()   
{   
        m_tcpSocket8000 = m_tcpServer8000->nextPendingConnection(); //得到每个连进来的socket   
        connect(m_tcpSocket8000,SIGNAL(readyRead()),this,SLOT(readMessage8000())); //有可读的信息，触发读函数槽 
}  
void InterfaceServer::newConnect8002()   
{   
        m_tcpSocket8002 = m_tcpServer8002->nextPendingConnection(); //得到每个连进来的socket   
        connect(m_tcpSocket8002,SIGNAL(readyRead()),this,SLOT(readMessage8001())); //有可读的信息，触发读函数槽 
}  
void InterfaceServer::newConnect9000()   
{   
        m_tcpSocket9000 = m_tcpServer9000->nextPendingConnection(); //得到每个连进来的socket   
        connect(m_tcpSocket9000,SIGNAL(readyRead()),this,SLOT(readMessage9000())); //有可读的信息，触发读函数槽 
}  
void InterfaceServer::newConnect9001()   
{   
        m_tcpSocket9001 = m_tcpServer9001->nextPendingConnection(); //得到每个连进来的socket   
        connect(m_tcpSocket9001,SIGNAL(readyRead()),this,SLOT(readMessage9001())); //有可读的信息，触发读函数槽 
}  
void InterfaceServer::readMessage8000() //读取信息   
{  
	if (m_tcpSocket8000 == NULL) return;

    QByteArray qba= m_tcpSocket8000->readAll(); //读取   
    qDebug()<<qba;   
    QString ss=QVariant(qba).toString();   
    ui.textEdit_rec->setText(ss);   
} 
void InterfaceServer::readMessage8002() //读取信息   
{  
	if (m_tcpSocket8002 == NULL) return;

    QByteArray qba= m_tcpSocket8002->readAll(); //读取   
    qDebug()<<qba;   
    QString ss=QVariant(qba).toString();   
    ui.textEdit_rec->setText(ss);   
} 
void InterfaceServer::readMessage9000() //读取信息   
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
    QByteArray qba= m_tcpSocket9000->readAll(); //读取   
    qDebug()<<qba;   
    QString ss=QVariant(qba).toString();   
    ui.textEdit_rec->setText(ss);   
#endif
} 
void InterfaceServer::readMessage9001() //读取信息   
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
void InterfaceServer::sendMessage() //发送信息   
{   
	QTcpSocket *tcpSocket = NULL;
	tcpSocket = m_tcpSocket9000;
	if (tcpSocket == NULL) return;

    QString strMesg= ui.lineEdit_sendmessage->text();   
	if (!strMesg.isEmpty())
	{
		qDebug()<<strMesg;   
		tcpSocket->write(strMesg.toStdString().c_str(),strlen(strMesg.toStdString().c_str())); //发送   
	}
}   

void InterfaceServer::testPState() //测试状态参数
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
  
