#include "socketclient.h"
#include "interfaceclient.h"
#include <QTextCodec>

SocketClient::SocketClient(QObject *parent)
	: QTcpSocket(parent)
{
	m_parent=qobject_cast<InterfaceClient*>(parent);

	connect(this, SIGNAL(connected()), this, SLOT(logConnection()));
	connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(logError(QAbstractSocket::SocketError)));
	connect(this, SIGNAL(disconnected()), this, SLOT(logDisconnection()));
}

SocketClient::~SocketClient()
{

}

void SocketClient::start(const QString& host, int port)
{
	m_host=host;
	m_port=port;
	this->connectToHost(host, port);
}

void SocketClient::restart()
{
	this->abort();
	this->connectToHost(m_host, m_port);
}

void SocketClient::logConnection()
{
	m_parent->logInfo(toString("Socket连接成功 HOST：%1 PORT：%2").arg(m_host).arg(m_port));
}

void SocketClient::logError(QAbstractSocket::SocketError socketError)
{
	m_parent->logError(toString("Socket错误代码-%1 HOST：%2 PORT：%3").arg(socketError).arg(m_host).arg(m_port));
}

void SocketClient::logDisconnection()
{

	m_parent->logWarning(toString("Socket失去连接 HOST：%1 PORT：%2").arg(m_host).arg(m_port));

}