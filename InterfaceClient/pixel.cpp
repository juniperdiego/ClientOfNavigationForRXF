#include "pixel.h"
#include "comm.h"
#include "interfaceclient.h"

const QString cValidStyle = "Pixel {background-color: green}";
const QString cInvalidStyle = "Pixel {background-color: lightGray}";

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

	QDoubleValidator* validator = new QDoubleValidator(0, 180, 3, this);
	m_edit->setValidator(validator);

	setLayout(layout);

	setFixedSize(size);

	m_label->installEventFilter(this);

	setState(m_valid);

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
		if (m_mode > 0 && event->button() == Qt::LeftButton)
		{
			m_label->setVisible(false);
			m_edit->setText(m_label->text());
			m_edit->setVisible(true);
			m_edit->setFocus();
		}
		else if (o == m_label && (m_mode == 2 || m_mode == 0) && event->button() == Qt::RightButton)
		{
			setState(!m_valid);
		}
	}

	return QFrame::eventFilter(o, e);
}

void Pixel::onEditingFinished()
{
	if (checkInputValue(InterfaceClient::s_wnd, m_edit, 0, 180, 3, 5.625))
		m_label->setText(m_edit->text());

	m_edit->setVisible(false);
	m_label->setVisible(true);
}

void Pixel::setState(bool valid)
{
	m_valid = valid;
	setStyleSheet(m_valid ? cValidStyle : cInvalidStyle);
}

float Pixel::getAngle()
{
	if (m_edit->isVisible())
		return m_edit->text().toFloat();

	return m_label->text().toFloat();
}


void Pixel::setAngleAndState(float angle, bool state)
{
	m_label->setText(QString::number(angle, 'f'));
	setState(state);
}


