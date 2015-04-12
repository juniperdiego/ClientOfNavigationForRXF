#include "tcpDataGen.h"

char degree2Binary(float degree)
{
	return degree/5.625f;
	
}

tcpDataGen::tcpDataGen(char dataHeader, char cmd, char dataLen)
{
	m_dataHeader = dataHeader;
	m_cmd = cmd;
	m_dataLen = dataLen;
	m_dataLenOccupyBytes = 1;//default, it is ususal except compTCorrection
}

tcpDataGen::~tcpDataGen()
{
}

int tcpDataGen::getDataSize()
{
	return m_dataLen + 3 + m_dataLenOccupyBytes;
}

compTCorrection::compTCorrection()
	:tcpDataGen(0x92, 0xCC, 0x200)
{
	m_dataLenOccupyBytes = 2;//compTCorrection
}

void compTCorrection::setDegree(vector<vector<float> > degreeMatrix)
{
	m_degreeMatrix = degreeMatrix;
}

void compTCorrection::setEnable(vector<vector<bool> > enableMatrix)
{
	m_enableMatrix = enableMatrix;
}

vector<int> compTCorrection::generate()
{
	vector<int> res;

	if(m_degreeMatrix.size() == 0 || m_enableMatrix.size() == 0)
		return res;

	res.push_back(m_dataHeader);
	res.push_back(m_cmd);
	res.push_back((m_dataLen >> 8) & 0xff);
	res.push_back(m_dataLen & 0xff);

	int rowSize = m_degreeMatrix.size();
	int colSize = m_degreeMatrix[0].size();


	for(int i = 0;  i < rowSize; i++)
	{
		for(int j = 0; j < colSize; j++)
		{
			int data = 0;
			data = (i+1) >> 12 |  	// x axis
				(j+1) >> 8 |	// y axis
				m_enableMatrix[i][j] >>7 |// enable
				degree2Binary(m_degreeMatrix[i][j]) >> 1 | //degree
				0x1;

			// data occupy two bytes, so first push its high byte, then low byte
			res.push_back((data >> 8) & 0xff);
			res.push_back(data & 0xff);
		}
	}

	// calc the check
	char check = 0;
	for(int i = 2 + m_dataLenOccupyBytes; i < res.size(); i++)
	{
		check = check ^ (res[i] & 0xff);
	}
	res.push_back(check);
	return res;

}

compRCorrection::compRCorrection()
	:tcpDataGen(0x92, 0xCB, 0x6C)
{
}

void compRCorrection::setDegree(vector<vector<float> > degreeMatrix)
{
	m_degreeMatrix = degreeMatrix;
}

void compRCorrection::setEnable(vector<vector<bool> > enableMatrix)
{
	m_enableMatrix = enableMatrix;
}

vector<int> compRCorrection::generate()
{
	vector<int> res;

	if(m_degreeMatrix.size() == 0 || m_enableMatrix.size() == 0)
		return res;

	res.push_back(m_dataHeader);
	res.push_back(m_cmd);
	res.push_back(m_dataLen & 0xff);

	int rowSize = m_degreeMatrix.size();
	int colSize = m_degreeMatrix[0].size();


	for(int i = 0;  i < rowSize; i++)
	{
		for(int j = 0; j < colSize; j++)
		{
			int data = 0;
			data = (i+1) >> 20 |  	// x axis
				(j+1) >> 16 |	// y axis
			//??	m_enableMatrix[i][j] >>7 |// enable
				degree2Binary(m_degreeMatrix[i][j]) >> 0 | //degree
				0x1;

			// data occupy 3 bytes, 
			res.push_back((data >> 16) & 0xff);
			res.push_back((data >> 8) & 0xff);
			res.push_back(data & 0xff);
		}
	}

	// calc the check
	char check = 0;
	for(int i = 2 + m_dataLenOccupyBytes; i < res.size(); i++)
	{
		check = check ^ (res[i] & 0xff);
	}
	res.push_back(check);
	return res;

}

