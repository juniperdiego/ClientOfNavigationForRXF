#ifndef PIXELARRAY_H
#define PIXELARRAY_H

#include <QWidget>
#include <QGridLayout>
#include "comm.h"
#include "pixel.h"

class PixelArray : public QWidget
{
	Q_OBJECT

public:
	PixelArray(int row, int col, int mode, bool showHeader = true, QWidget *parent = NULL);
	~PixelArray();

	void setAngleAndStates(const vector<float>& angles, const vector<bool>& states);
	void getAngleAndStates(vector<float>& angles, vector<bool>& states);

private:
	//QList<QList<Pixel*>>	m_pixels;
	QList<Pixel*>	m_pixels;
};

#endif // PIXELARRAY_H
