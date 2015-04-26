#include "pixelarray.h"


PixelArray::PixelArray(int row, int col, int mode, bool showHeader, QWidget *parent)
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
		QLabel* label = new QLabel(toString("单位(°)"));
		hLayout->addWidget(label);
		Pixel* valid = new Pixel(toString("有效"), true, -1, large ? cDefLSize : cDefSSize);
		hLayout->addWidget(valid);
		Pixel* invalid = new Pixel(toString("无效"), false, -1, large ? cDefLSize : cDefSSize);
		hLayout->addWidget(invalid);
		mLayout->addLayout(hLayout);
	}

	QGridLayout* gLayout = new QGridLayout;
	gLayout->setMargin(0);
	gLayout->setSpacing(2);
	
	for(int i = 0; i < row+1; ++i)
	{
		vector<Pixel*> rowList;
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
				int r = qrand()%32;
				Pixel* pixel = new Pixel(QString::number(r*5.625), true, mode, large ? cDefLSize : cDefSSize);
				gLayout->addWidget(pixel, i, j);
				rowList.push_back(pixel);
			}
		}
		m_pixels.push_back(rowList);
	}

	mLayout->addLayout(gLayout);

	setLayout(mLayout);

	QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	setSizePolicy(sizePolicy);
}

PixelArray::~PixelArray()
{

}

void PixelArray::setAngleAndStates(const vector<vector<float>>& angles, const vector<vector<bool>>& states)
{
	int aSize = angles.size();
	int sSize = states.size();
	if (aSize != sSize) return;

	if (aSize * aSize != m_pixels.size() * m_pixels.size())	
		return;

	for(int i=0; i<m_pixels.size(); i++) 
    { 
		for(int j=0; j < m_pixels.size(); j++)
		{
			m_pixels[i][j]->setAngleAndState(angles[i][j], states[i][j]); 
		}
    }
}

void PixelArray::getAngleAndStates(vector<vector<float>>& angles, vector<vector<bool>>& states)
{
	for(int i=0; i<m_pixels.size(); i++) 
    { 
		vector<float> angle;
		vector<bool> state;
		for(int j=0; j < m_pixels.size(); j++)
		{
			angle.push_back(m_pixels[i][j]->getAngle()); 
			state.push_back(m_pixels[i][j]->getState()); 
		}
		angles.push_back(angle);
		states.push_back(state);
    }
}
