#ifndef PIXEL_H
#define PIXEL_H

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QEvent>
#include <QMouseEvent>
#include <QDoubleValidator>

const QSize cDefSSize = QSize(40, 20);
const QSize cDefLSize = QSize(80, 40);

//mode 0:change 1:edit 2:edit/change -1:sample

class Pixel : public QFrame
{
	Q_OBJECT

public:
	Pixel(const QString& value, bool valid, int mode, const QSize& size = cDefSSize, QWidget *parent = NULL);
	~Pixel();

	void setState(bool valid);
	bool getState() {return m_valid;}
	float getAngle();
	void setAngleAndState(float angle, bool state);

protected:
	bool eventFilter(QObject* o, QEvent* e);

private slots:
	void onEditingFinished();

private:
	bool	m_valid;
	int		m_mode;
	
	QLabel*	m_label;
	QLineEdit*	m_edit;
};

#endif // PIXEL_H
