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

	void setAngleAndStates(const vector<vector<float>>& angles, const vector<vector<bool>>& states);
	void getAngleAndStates(vector<vector<float>>& angles, vector<vector<bool>>& states);

private:
	vector<vector<Pixel*>>	m_pixels;
};

#endif // PIXELARRAY_H
