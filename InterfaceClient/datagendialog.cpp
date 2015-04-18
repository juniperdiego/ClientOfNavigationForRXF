#include "datagendialog.h"
#include "dataGen.h"


DataGenDialog::DataGenDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	QDoubleValidator* coordV = new QDoubleValidator(-8000, 8000, 3, this);
	coordV->setNotation(QDoubleValidator::StandardNotation);
	ui.zxLE->setValidator(coordV);
	ui.zyLE->setValidator(coordV);
	ui.zzLE->setValidator(coordV);

	QDoubleValidator* coordSV = new QDoubleValidator(-12000, 12000, 4, this);
	coordSV->setNotation(QDoubleValidator::StandardNotation);
	ui.zxsLE->setValidator(coordSV);
	ui.zysLE->setValidator(coordSV);
	ui.zzsLE->setValidator(coordSV);

	m_angleV = new QDoubleValidator(this);
	m_angleV->setNotation(QDoubleValidator::StandardNotation);
	ui.gjLE->setValidator(m_angleV);
	ui.fjLE->setValidator(m_angleV);
	ui.pjLE->setValidator(m_angleV);

	m_angleSV = new QDoubleValidator(this);
	m_angleSV->setNotation(QDoubleValidator::StandardNotation);
	ui.gjsLE->setValidator(m_angleSV);
	ui.fjsLE->setValidator(m_angleSV);
	ui.pjsLE->setValidator(m_angleSV);

	m_craftModel = new SourceCodeModel(LEN_DATA, 16, false, this); 
	ui.ffTableView->setModel(m_craftModel);
	ui.ffTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	connect(ui.fgenfilePB, SIGNAL(clicked()), this, SLOT(onFGenFileClick()));
	connect(ui.ggenfilePB, SIGNAL(clicked()), this, SLOT(onGGenFileClick()));

	resize(900, 500);
}

DataGenDialog::~DataGenDialog()
{

}

void DataGenDialog::setIsOnTrack(bool isOnTrack) 
{ 
	if (isOnTrack)
	{
		ui.fdzRB->setChecked(true);
		m_angleV->setBottom(-180);
		m_angleV->setTop(180);
		m_angleV->setDecimals(4);
		m_angleSV->setBottom(-10);
		m_angleSV->setTop(10);
		m_angleSV->setDecimals(5);
	}
	else
	{
		ui.fdrRB->setChecked(true);
		m_angleV->setBottom(-180);
		m_angleV->setTop(180);
		m_angleV->setDecimals(3);
		m_angleSV->setBottom(-100);
		m_angleSV->setTop(100);
		m_angleSV->setDecimals(4);
	}
}

bool DataGenDialog::checkInputValue(QLineEdit* inputLE, float bottom, float top, int prec, float lsb)
{
	if (inputLE->text().isEmpty())
	{
		//QMessageBox::warning(this, windowTitle(), 
		//	toString("请输入参数"));
		//inputLE->setFocus();
		//return false;
		inputLE->setText(QString::number(0));
	}

	float value = inputLE->text().toFloat();
	
	if (value < bottom || value > top)
	{
		QMessageBox::warning(this, windowTitle(), 
			toString("参数超出范围[%1, %2]").arg(bottom).arg(top));
		inputLE->setFocus();
		return false;
	}

	float tmp = fmod(value, lsb);
	if (!isZero(tmp))
	{
		int ratio = qRound(value/lsb);
		inputLE->setText(QString::number(lsb*ratio, 'f', prec));
	}

	return true;
}

bool DataGenDialog::checkCraftParameter()
{
	if (!checkInputValue(ui.zxLE, -8000, 8000, 3, 0.001) ||
		!checkInputValue(ui.zyLE, -8000, 8000, 3, 0.001) ||
		!checkInputValue(ui.zzLE, -8000, 8000, 3, 0.001) ||
		!checkInputValue(ui.zxsLE, -12000, 12000, 4, 0.0015) ||
		!checkInputValue(ui.zysLE, -12000, 12000, 4, 0.0015) ||
		!checkInputValue(ui.zzsLE, -12000, 12000, 4, 0.0015) ||
		!checkInputValue(ui.gjLE, -180, 180, isOnTrack() ? 4 : 3, isOnTrack() ? 0.0256 : 0.006) ||
		!checkInputValue(ui.fjLE, -180, 180, isOnTrack() ? 4 : 3, isOnTrack() ? 0.0256 : 0.006) ||
		!checkInputValue(ui.pjLE, -180, 180, isOnTrack() ? 4 : 3, isOnTrack() ? 0.0256 : 0.006) ||
		!checkInputValue(ui.gjsLE, isOnTrack() ? -10 : -100, isOnTrack() ? 10 : 100, isOnTrack() ? 5 : 4, isOnTrack() ? 0.00512 : 0.0035) ||
		!checkInputValue(ui.fjsLE, isOnTrack() ? -10 : -100, isOnTrack() ? 10 : 100, isOnTrack() ? 5 : 4, isOnTrack() ? 0.00512 : 0.0035) ||
		!checkInputValue(ui.pjsLE, isOnTrack() ? -10 : -100, isOnTrack() ? 10 : 100, isOnTrack() ? 5 : 4, isOnTrack() ? 0.00512 : 0.0035)
		)
	{
		return false;
	}



	return true;
}

void DataGenDialog::onFGenFileClick()
{
	if (!checkCraftParameter()) return;

	dataGenForAerocraft craft;
	craft.setMode(ui.fdzRB->isChecked());
	craft.setPos(ui.zxLE->text().toFloat(), ui.zyLE->text().toFloat(), ui.zzLE->text().toFloat());
	craft.setVelocity(ui.zxsLE->text().toFloat(), ui.zysLE->text().toFloat(), ui.zzsLE->text().toFloat());
	craft.setAngle(ui.gjLE->text().toFloat(), ui.fjLE->text().toFloat(), ui.pjLE->text().toFloat());
	craft.setPalstance(ui.gjsLE->text().toFloat(), ui.fjsLE->text().toFloat(), ui.pjsLE->text().toFloat());	

	int size = craft.getBufSize();
	char* buf = new char[LEN_DATA];
	memset(buf, 0, LEN_DATA);
	craft.generate(buf, size);
	m_craftModel->setNewPackage(buf, size);

	QByteArray byteArr(buf, size);
	//qDebug()<<byteArr.toHex();

	QDir curPath;
	curPath.mkdir("DATA");
	curPath.cd("DATA");
    QString fileName = QFileDialog::getSaveFileName(this, toString("保存数据文件"),
                           curPath.absolutePath(), tr("DAT (*.dat)"));
	if (!fileName.endsWith(".dat", Qt::CaseInsensitive)) return;

	QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(byteArr);
    file.close();
}

void DataGenDialog::onGGenFileClick()
{
	QDir curPath;
	curPath.mkdir("DATA");
	curPath.cd("DATA");
    QString fileName = QFileDialog::getSaveFileName(this, toString("保存数据文件"),
                           curPath.absolutePath(), tr("DAT (*.dat)"));
	if (!fileName.endsWith(".dat", Qt::CaseInsensitive)) return;
    
	qDebug()<<fileName;
}