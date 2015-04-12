#ifndef DATAGEN_H
#define DATAGEN_H

#include <QDialog>
#include <QDoubleValidator>
#include <QDir>
#include <QFileDialog>
#include "ui_datagen.h"
#include "comm.h"

class DataGen : public QDialog
{
	Q_OBJECT

public:
	DataGen(QWidget *parent = 0);
	~DataGen();

private slots:
	void onFGenFileClick();
	void onGGenFileClick();

private:
	Ui::DataGen ui;
};

#endif // DATAGEN_H
