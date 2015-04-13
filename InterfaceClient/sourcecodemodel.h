#ifndef SOURCECODEMODEL_H
#define SOURCECODEMODEL_H

#include <QAbstractTableModel>

class SourceCodeModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	SourceCodeModel(int len, int col=16, bool htol=false, QObject *parent=0);
	~SourceCodeModel();

	int rowCount(const QModelIndex & parent = QModelIndex()) const;
	int columnCount(const QModelIndex & parent = QModelIndex()) const;
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

	void setNewPackage(char *pdata);


private:
	char* m_data;
	int m_len;
	int m_col;
	bool m_htol; //是否反转字节序，默认否
};

#endif // SOURCECODEMODEL_H
