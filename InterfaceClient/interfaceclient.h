#ifndef INTERFACECLIENT_H
#define INTERFACECLIENT_H

#include <QtWidgets/QMainWindow>
#include <QDateTime>
#include <QDir>
#include <QFileDialog>
#include "ui_interfaceclient.h"
#include "comm.h"
#include "pixelarray.h"
#include "serversetting.h"
#include "datagendialog.h"
#include "logmng.h"
#include "socketclient.h"

class ServerSetting;
class DataGenDialog;
class LogMng;
class InterfaceClient : public QMainWindow
{
	Q_OBJECT

public:
	InterfaceClient(QWidget *parent = 0);
	~InterfaceClient();

public:
	void addLog(LogTypeEnum type, const char* msg);
	void clearLog();
	void logInfo(const QString& info) {addLog(LOG_TYPE_INFO, qPrintable(info));}
	void logWarning(const QString& info) {addLog(LOG_TYPE_WARNNING, qPrintable(info));}
	void logError(const QString& info) {addLog(LOG_TYPE_ERROR, qPrintable(info));}

	//socket
	void connectServer(const QString &ip);
	void disconnectServer();

	//Parameter
	void setPState(const vector<float>& states);

	//Return and Into
	void setRWorkState(char avilable, bool status1, bool status2);
	char getWhichAvail();

private:
	void initPara();
	void initReturn();
	void initComT();
	void initComR();
	void initSetting();

	void initSocket();

public slots:
	//menu
	void onServerSetting();
	void onDataGen();

	//Para
	void onPModeSendClick();
	void onPResetClick();
	void onPMeasureClick();

	//Return
	void onAvailToggled(bool);
	void onRFBroClick();
	void onRFIntoClick();
	void onRGBroClick();
	void onRGIntoClick();
	void onRMIntoClick();
	void onRZMIntoClick();
	void onRXIntoClick();

	//Setting
	void onSZSendClick();
	void onSDSendClick();
	void onSRSendClick();
	void onSTSendClick();

	//T
	void rcvTState();
	void rcvRState();
	void rcvPState();
	void rcvSState();

private:
	Ui::InterfaceClientClass ui;

	PixelArray* m_rCom;
	PixelArray* m_tCom;
	PixelArray* m_srCom;
	PixelArray* m_stCom;

	LogMng*	m_logMng;
	ServerSetting*	m_serverDialog;
	DataGenDialog*	m_genDataDialog;

	QDoubleValidator*	m_angleValid;
	QDoubleValidator*	m_doubleValid;

	SocketClient*	m_socketT;
	SocketClient*	m_socketR;
	SocketClient*	m_socketP;
	SocketClient*	m_socketS;
	SocketClient*	m_socketST;
	SocketClient*	m_socketSR;

	int m_logIndex;
};

#endif // INTERFACECLIENT_H
