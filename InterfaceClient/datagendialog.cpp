#include "datagendialog.h"
#include "dataGen.h"


DataGenDialog::DataGenDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	QDoubleValidator* dValidator = new QDoubleValidator(this);
	dValidator->setBottom(0);
	ui.zxLE->setValidator(dValidator);
	ui.zyLE->setValidator(dValidator);
	ui.zzLE->setValidator(dValidator);
	ui.zxsLE->setValidator(dValidator);
	ui.zysLE->setValidator(dValidator);
	ui.zzsLE->setValidator(dValidator);

	ui.gjLE->setValidator(dValidator);
	ui.fjLE->setValidator(dValidator);
	ui.pjLE->setValidator(dValidator);
	ui.gjsLE->setValidator(dValidator);
	ui.fjsLE->setValidator(dValidator);
	ui.pjsLE->setValidator(dValidator);

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
	isOnTrack ? ui.fdzRB->setChecked(true) : ui.fdrRB->setChecked(true);
}

bool DataGenDialog::checkCraftParameter()
{
	if (ui.zxLE->text().isEmpty() ||
		ui.zyLE->text().isEmpty() ||
		ui.zzLE->text().isEmpty() ||
		ui.zxsLE->text().isEmpty() ||
		ui.zysLE->text().isEmpty() ||
		ui.zzsLE->text().isEmpty() ||
		ui.gjLE->text().isEmpty() ||
		ui.fjLE->text().isEmpty() ||
		ui.pjLE->text().isEmpty() ||
		ui.gjsLE->text().isEmpty() ||
		ui.fjLE->text().isEmpty() ||
		ui.pjsLE->text().isEmpty()
		)
	{
		QMessageBox::warning(this, windowTitle(), 
			toString("请输入飞行器自身参数"));
		return false;
	}

	return true;
}

void DataGenDialog::onFGenFileClick()
{
	if (!checkCraftParameter()) return;

	dataGenForAerocraft craft;
	craft.setMode(ui.fdzRB->isChecked());
	craft.setPos(ui.zxLE->text().toDouble(), ui.zyLE->text().toDouble(), ui.zzLE->text().toDouble());
	craft.setVelocity(ui.zxsLE->text().toDouble(), ui.zysLE->text().toDouble(), ui.zzsLE->text().toDouble());
	craft.setAngle(ui.gjLE->text().toDouble(), ui.fjLE->text().toDouble(), ui.pjLE->text().toDouble());
	craft.setPalstance(ui.gjsLE->text().toDouble(), ui.fjsLE->text().toDouble(), ui.pjsLE->text().toDouble());	

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