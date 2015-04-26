#include "interfaceclient.h"
#include <QBrush>

InterfaceClient* InterfaceClient::s_wnd = NULL;

InterfaceClient::InterfaceClient(QWidget *parent)
	: QMainWindow(parent)
	, m_serverDialog(NULL)
	, m_genDataDialog(NULL)
	, m_logIndex(1)
{
	ui.setupUi(this);

	//init log tw
	QStringList headers;
    headers << toString("序号") << toString("时间") << toString("动作");
	ui.logTW->setColumnCount(3);
	ui.logTW->setHorizontalHeaderLabels(headers);
	ui.logTW->setColumnWidth(0, 40);
	ui.logTW->setColumnWidth(1, 140);
	ui.logTW->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	//init validator
	m_angleValid = new QDoubleValidator(-180, 180, 3, this);
	m_doubleValid = new QDoubleValidator(this);
	m_doubleValid->setBottom(0);
		
	//init Parameter
	initPara();

	//init Return
	initReturn();

	//init component T
	initComT();

	//init component R
	initComR();

	//init Setting
	initSetting();

	//init menu
	connect(ui.actionNetSet, SIGNAL(triggered()), this, SLOT(onServerSetting()));
	connect(ui.actionGenData, SIGNAL(triggered()), this, SLOT(onDataGen()));

	//init log 
	m_logMng = new LogMng("Client");

	//init socket
	initSocket();

	//test
}

InterfaceClient::~InterfaceClient()
{
	delete m_logMng;
}

void InterfaceClient::onServerSetting()
{
	bool flag = false;
	if( m_socketT->state()==QAbstractSocket::ConnectedState ||
		m_socketR->state()==QAbstractSocket::ConnectedState ||
		m_socketP->state()==QAbstractSocket::ConnectedState ||
		m_socketS->state()==QAbstractSocket::ConnectedState ||
		m_socketST->state()==QAbstractSocket::ConnectedState ||
		m_socketSR->state()==QAbstractSocket::ConnectedState
		)
	{
		flag = true;
	}
	if (m_serverDialog == NULL)
		m_serverDialog = new ServerSetting(false, this);
	m_serverDialog->setFlag(flag);
	m_serverDialog->exec();
}

void InterfaceClient::onDataGen()
{
	if (m_genDataDialog == NULL)
		m_genDataDialog = new DataGenDialog(this);
	m_genDataDialog->setIsOnTrack(ui.rf1RB->isChecked());
	m_genDataDialog->show();
	m_genDataDialog->raise();
}

void InterfaceClient::addLog(LogTypeEnum type, const char* msg)
{
	int row = ui.logTW->rowCount();
	if (row >= MAX_LOG_LINE)
		ui.logTW->removeRow(0);

	row = ui.logTW->rowCount();
	ui.logTW->insertRow(row);

	QTableWidgetItem* item0 = new QTableWidgetItem(QString::number(m_logIndex));
	if (type != LOG_TYPE_INFO) item0->setForeground(type == LOG_TYPE_ERROR ? QBrush(Qt::red) : QBrush(Qt::blue));
	item0->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.logTW->setItem(row, 0, item0);

	QTableWidgetItem* item1 = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
	if (type != LOG_TYPE_INFO) item1->setForeground(type == LOG_TYPE_ERROR ? QBrush(Qt::red) : QBrush(Qt::blue));
	item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.logTW->setItem(row, 1, item1);

	QTableWidgetItem* item2 = new QTableWidgetItem(toString(msg));
	if (type != LOG_TYPE_INFO) item2->setForeground(type == LOG_TYPE_ERROR ? QBrush(Qt::red) : QBrush(Qt::blue));
	ui.logTW->setItem(row, 2, item2);

	ui.logTW->setCurrentItem(NULL);
	ui.logTW->scrollToBottom();
	
	++m_logIndex;

	if (ui.logCB->isChecked())
	{
		QString logStr = item0->text() + " \t" + item1->text() + " \t" + item2->text() + "\n";
		m_logMng->log(type, logStr);
	}
}

void InterfaceClient::clearLog()
{
	ui.logTW->clearContents();
	ui.logTW->setRowCount(0);
	m_logIndex = 0;
}

void InterfaceClient::initSocket()
{
	m_socketT = new SocketClient(this);
	connect(m_socketT, SIGNAL(readyRead()), this, SLOT(rcvTState()));
	m_socketR = new SocketClient(this);
	connect(m_socketR, SIGNAL(readyRead()), this, SLOT(rcvRState()));
	m_socketP = new SocketClient(this);
	connect(m_socketP, SIGNAL(readyRead()), this, SLOT(rcvPState()));
	m_socketS = new SocketClient(this);
	connect(m_socketS, SIGNAL(readyRead()), this, SLOT(rcvSState()));
	m_socketST = new SocketClient(this);
	m_socketSR = new SocketClient(this);

}

void InterfaceClient::connectServer(const QString &ip)
{
	if (m_socketT->state() == QAbstractSocket::UnconnectedState)
		m_socketT->start(ip, T_PORT);
	if (m_socketR->state() == QAbstractSocket::UnconnectedState)
		m_socketR->start(ip, R_PORT);
	if (m_socketP->state() == QAbstractSocket::UnconnectedState)
		m_socketP->start(ip, P_PORT);
	if (m_socketS->state() == QAbstractSocket::UnconnectedState)
		m_socketS->start(ip, S_PORT);
	if (m_socketST->state() == QAbstractSocket::UnconnectedState)
		m_socketST->start(ip, ST_PORT);
	if (m_socketSR->state() == QAbstractSocket::UnconnectedState)
		m_socketSR->start(ip, SR_PORT);

	if (m_serverDialog)
	{
		m_serverDialog->reject();
	}

}

void InterfaceClient::disconnectServer()
{
	m_socketT->disconnectFromHost();
	m_socketR->disconnectFromHost();
	m_socketP->disconnectFromHost();
	m_socketS->disconnectFromHost();
	m_socketST->disconnectFromHost();
	m_socketSR->disconnectFromHost();

}

