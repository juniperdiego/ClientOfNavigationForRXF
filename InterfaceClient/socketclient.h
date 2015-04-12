#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <QTcpSocket>

class InterfaceClient;
class SocketClient : public QTcpSocket
{
	Q_OBJECT

public:
	SocketClient(QObject *parent);
	~SocketClient();

	void start(const QString& host, int port);
	void restart();

private slots:
	void logConnection();
	void logDisconnection();
	void logError(QAbstractSocket::SocketError socketError);

private:
	InterfaceClient* m_parent;
	QString m_host;
	int m_port;
};

#endif // SOCKETCLIENT_H
