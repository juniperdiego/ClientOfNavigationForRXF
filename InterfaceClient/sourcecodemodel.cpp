#include "sourcecodemodel.h"

SourceCodeModel::SourceCodeModel(int len, int col, bool htol, QObject *parent)
	: QAbstractTableModel(parent)
{
	m_len=len;
	m_col=col;
	m_data=NULL;
	m_htol=htol;
	if(m_len>0)
	{
		m_data=new char[m_len];
		memset(m_data,0,m_len);
	}
}

SourceCodeModel::~SourceCodeModel()
{
	if(m_data!=NULL)
		delete[] m_data;
}

int SourceCodeModel::rowCount(const QModelIndex & parent) const
{
	int m=m_len/m_col;
	int n=m_len%m_col;
	if(n>0) m++;

	return m;
}

int SourceCodeModel::columnCount(const QModelIndex & parent) const
{
	return m_col;
}

QVariant SourceCodeModel::data(const QModelIndex & index, int role) const
{
	if(!index.isValid()) return QVariant();
	int col=index.column();
	int row=index.row();

	if(role==Qt::DisplayRole)
	{
		int i=row*m_col+col;
		if(i>=m_len || i<0)
		{
			return QString("");
		}
		else
		{
			QString val = QString("%1").arg((int)m_data[i] & 0xFF,0,16).toUpper();
			if( val.length() == 1 ) val.prepend('0');
			return val;
		}
	}
	else if(role==Qt::TextAlignmentRole)
	{
		return int(Qt::AlignCenter | Qt::AlignVCenter);
	}
	return QVariant();
}

void SourceCodeModel::setNewPackage(char *pdata)
{
	if(!m_htol)
	{
		memcpy(m_data, pdata, m_len);
	}
	else
	{
		for(int i=0;i<m_len;)
		{
			m_data[i] = pdata[i+1];
			m_data[i+1] = pdata[i];
			i=i+2;
		}
	}
}
