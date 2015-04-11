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
	PixelArray(int row, int col, bool isEdit, bool showHeader = true, QWidget *parent = NULL);
	~PixelArray();

private:
	QList<QList<Pixel*>>	m_pixels;
	
};

#endif // PIXELARRAY_H
