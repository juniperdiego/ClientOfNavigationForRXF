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
#include "datagen.h"
#include "logmng.h"

class ServerSetting;
class DataGen;
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

	//Return and Into
	void setRWorkState(bool state);

private:
	void initPara();
	void initReturn();
	void initComT();
	void initComR();
	void initSetting();

public slots:
	//menu
	void onServerSetting();
	void onDataGen();

	//Para
	void onPModeSendClick();
	void onPResetClick();
	void onPMeasureClick();

	//Return
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


private:
	Ui::InterfaceClientClass ui;

	PixelArray* m_rCom;
	PixelArray* m_tCom;
	PixelArray* m_srCom;
	PixelArray* m_stCom;

	LogMng*	m_logMng;
	ServerSetting*	m_serverDialog;
	DataGen*		m_genDataDialog;

	QDoubleValidator*	m_angleValid;
	QDoubleValidator*	m_doubleValid;

	int m_logIndex;
};

#endif // INTERFACECLIENT_H
