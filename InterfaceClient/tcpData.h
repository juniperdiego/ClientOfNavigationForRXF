#ifndef TCP_DATA_H
#define TCP_DATA_H


#include "comm.h"

class tcpData
{
public:
	tcpData(char dataHeader, char cmd, char dataLen);
	~tcpData();
	virtual vector<int>  generate() =0;
	int getDataSize();
protected:
	char	m_dataHeader;
	char	m_cmd;
	unsigned int	m_dataLen;
	unsigned int	m_dataLenOccupyBytes;
	char	m_check;
};

class compTCorrection : public tcpData
{
public:
	compTCorrection();
	vector<int> generate();
	void setDegree(vector<vector<float> > degreeMatrix);
	void setEnable(vector<vector<bool> > enableMatrix);
private:
	vector<vector<float> > m_degreeMatrix;
	vector<vector<bool> > m_enableMatrix;
};

class compRCorrection : public tcpData
{
public:
	compRCorrection();
	vector<int> generate();
	void setDegree(vector<vector<float> > degreeMatrix);
	void setEnable(vector<vector<bool> > enableMatrix);
private:
	vector<vector<float> > m_degreeMatrix;
	vector<vector<bool> > m_enableMatrix;
};

class compTTestCode: public tcpData
{
public:
	compTTestCode();
	vector<int> generate();
	void setEnable(vector<vector<bool> > enableMatrix);
private:
	vector<vector<bool> > m_enableMatrix;
};

class compRTestCode: public tcpData
{
public:
	compRTestCode();
	vector<int> generate();
	void setEnable(vector<vector<bool> > enableMatrix);
private:
	vector<vector<bool> > m_enableMatrix;
};
#endif // TCP_DATA_GEN
