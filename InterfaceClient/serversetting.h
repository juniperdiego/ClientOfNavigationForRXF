#ifndef SERVERSETTING_H
#define SERVERSETTING_H

#include <QDialog>
#include "ui_serversetting.h"
#include "interfaceclient.h"

class InterfaceClient;
class ServerSetting : public QDialog
{
	Q_OBJECT

public:
	ServerSetting(bool flag, QWidget *parent = 0);
	~ServerSetting();

private slots:
	void switchConnection();

private:
	void connectServer();
	void disconnectServer();

private:
	Ui::ServerSettingClass ui;

	InterfaceClient*	m_wnd;
	bool m_flag;
	QString m_ipAddress;
};

#endif // SERVERSETTING_H
