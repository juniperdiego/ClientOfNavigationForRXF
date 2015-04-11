#include "pixelarray.h"


PixelArray::PixelArray(int row, int col, bool isEdit, bool showHeader, QWidget *parent)
	: QWidget(parent)
{
	bool large = row < 10;

	QVBoxLayout* mLayout = new QVBoxLayout;
	mLayout->setMargin(0);
	mLayout->setSpacing(10);

	if (showHeader)
	{
		QHBoxLayout* hLayout = new QHBoxLayout;
		hLayout->setMargin(0);
		hLayout->setSpacing(6);
		hLayout->addStretch();
		QLabel* label = new QLabel(toString("��λ(��)"));
		hLayout->addWidget(label);
		Pixel* valid = new Pixel(toString("��Ч"), true, -1, large ? cDefLSize : cDefSSize);
		hLayout->addWidget(valid);
		Pixel* invalid = new Pixel(toString("��Ч"), false, -1, large ? cDefLSize : cDefSSize);
		hLayout->addWidget(invalid);
		mLayout->addLayout(hLayout);
	}

	QGridLayout* gLayout = new QGridLayout;
	gLayout->setMargin(0);
	gLayout->setSpacing(2);
	
	for(int i = 0; i < row+1; ++i)
	{
		QList<Pixel*> rowList;
		for(int j = 0; j < col+1; ++j)
		{
			if (i == 0 && j > 0)
			{
				QLabel* label = new QLabel(QString::number(j));
				label->setAlignment(Qt::AlignCenter);
				label->setFixedSize(large ? cDefLSize : cDefSSize);
				gLayout->addWidget(label, i, j);
			}
			else if (i > 0 && j == 0)
			{
				QLabel* label = new QLabel(QString::number(i));
				label->setAlignment(Qt::AlignCenter);
				label->setFixedSize(40, 20);
				gLayout->addWidget(label, i, j);
			}
			else if (i > 0 && j > 0)
			{
				Pixel* pixel = new Pixel(QString("%1.%2").arg(i).arg(j), true, isEdit, large ? cDefLSize : cDefSSize);
				gLayout->addWidget(pixel, i, j);
				rowList.append(pixel);
			}
		}
		m_pixels.append(rowList);
	}

	mLayout->addLayout(gLayout);

	setLayout(mLayout);

	QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	setSizePolicy(sizePolicy);
}

PixelArray::~PixelArray()
{

}
