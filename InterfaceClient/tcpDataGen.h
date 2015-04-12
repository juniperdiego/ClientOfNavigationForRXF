#ifndef TCP_DATA_GEN
#define TCP_DATA_GEN

#include <vector>
using std::vector;

class tcpDataGen
{
public:
	tcpDataGen(char dataHeader, char cmd, char dataLen);
	~tcpDataGen();
	virtual vector<int>  generate() =0;
	int getDataSize();
protected:
	char	m_dataHeader;
	char	m_cmd;
	unsigned int	m_dataLen;
	unsigned int	m_dataLenOccupyBytes;
	char	m_check;
};

class compTCorrection : public tcpDataGen
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

class compRCorrection : public tcpDataGen
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

#endif // TCP_DATA_GEN
