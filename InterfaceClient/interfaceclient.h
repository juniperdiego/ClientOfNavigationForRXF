#ifndef INTERFACECLIENT_H
#define INTERFACECLIENT_H

#include <QtWidgets/QMainWindow>
#include <QDateTime>
#include <QDir>
#include <QFileDialog>
#include "ui_interfaceclient.h"
#include "pixelarray.h"

class InterfaceClient : public QMainWindow
{
	Q_OBJECT

public:
	InterfaceClient(QWidget *parent = 0);
	~InterfaceClient();

public:
	void addLog(const QString& msg);
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
	//Para
	void onPModeSendClick();
	void onPResetClick();
	void onPMeasureClick();

	//Return
	void onRFGenClick();
	void onRFBroClick();
	void onRFIntoClick();
	void onRGGenClick();
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

	int m_logIndex;
};

#endif // INTERFACECLIENT_H
