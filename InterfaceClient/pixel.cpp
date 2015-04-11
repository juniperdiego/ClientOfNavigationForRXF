#include "pixel.h"
#include "comm.h"

const QString cValidStyle = "background-color: green";
const QString cInvalidStyle = "background-color: lightGray";

Pixel::Pixel(const QString& value, bool valid, int mode, const QSize& size, QWidget *parent)
	: QFrame(parent)
	, m_valid(valid)
	, m_mode(mode)
	, m_label(NULL)
	, m_edit(NULL)
{
	setFrameShape(QFrame::Box);
	setFrameShadow(QFrame::Plain);

	QHBoxLayout* layout = new QHBoxLayout;
	layout->setMargin(0);
	layout->setSpacing(0);

	m_label = new QLabel(value);
	m_label->setAlignment(Qt::AlignCenter);
	layout->addWidget(m_label);

	m_edit = new QLineEdit;
	m_edit->setFrame(false);
	m_edit->setVisible(false);
	layout->addWidget(m_edit);

	QDoubleValidator* validator = new QDoubleValidator(0, 360, 3, this);
	m_edit->setValidator(validator);

	setLayout(layout);

	setFixedSize(size);

	m_label->installEventFilter(this);

	setValid(m_valid);

	connect(m_edit, SIGNAL(editingFinished()), this, SLOT(onEditingFinished()));
	connect(m_edit, SIGNAL(returnPressed()), this, SLOT(onEditingFinished()));

}

Pixel::~Pixel()
{

}

bool Pixel::eventFilter(QObject* o, QEvent* e)
{
	if (o == m_label && e->type() == QEvent::MouseButtonRelease)
	{
		QMouseEvent* event = dynamic_cast<QMouseEvent*>(e);
		if (m_mode == 1 && event->button() == Qt::LeftButton)
		{
			m_label->setVisible(false);
			m_edit->setText(m_label->text());
			m_edit->setVisible(true);
			m_edit->setFocus();
		}
		else if (o == m_label && m_mode != -1 && event->button() == Qt::RightButton)
		{
			setValid(!m_valid);
		}
	}

	return QFrame::eventFilter(o, e);
}

void Pixel::onEditingFinished()
{
	m_label->setText(m_edit->text());
	m_edit->setVisible(false);
	m_label->setVisible(true);
}

void Pixel::setValid(bool valid)
{
	m_valid = valid;
	setStyleSheet(m_valid ? cValidStyle : cInvalidStyle);
}

QString Pixel::getAngleStr()
{
	if (m_edit->isVisible())
		return m_edit->text();

	return m_label->text();
}


