#include "tcpData.h"

char degree2Binary(float degree)
{
	return degree/5.625f;
	
}

tcpData::tcpData(char dataHeader, char cmd, char dataLen)
{
	m_dataHeader = dataHeader;
	m_cmd = cmd;
	m_dataLen = dataLen;
	m_dataLenOccupyBytes = 1;//default, it is ususal except compTCorrection
}

tcpData::~tcpData()
{
}

int tcpData::getDataSize()
{
	return m_dataLen + 3 + m_dataLenOccupyBytes;
}

compTCorrection::compTCorrection()
	:tcpData(0x92, 0xCC, 0x200)
{
	m_dataLenOccupyBytes = 2;//compTCorrection
}

bool compTCorrection::setDegree(vector<vector<float> > degreeMatrix)
{
	if(degreeMatrix.size() != 16 || degreeMatrix[0].size() != 16)
		return false;
	m_degreeMatrix = degreeMatrix;
	return true;
}

bool compTCorrection::setEnable(vector<vector<bool> > enableMatrix)
{
	if(enableMatrix.size() != 16 || enableMatrix[0].size() != 16)
		return false;
	m_enableMatrix = enableMatrix;
	return true;
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
	:tcpData(0x92, 0xCB, 0x6C)
{
}

bool compRCorrection::setDegree(vector<vector<float> > degreeMatrix)
{
	if(degreeMatrix.size() != 6 || degreeMatrix[0].size() != 6)
		return false;
	m_degreeMatrix = degreeMatrix;
	return true;
}

bool compRCorrection::setEnable(vector<vector<bool> > enableMatrix)
{
	if(enableMatrix.size() != 6 || enableMatrix[0].size() != 6)
		return false;
	m_enableMatrix = enableMatrix;
	return true;
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


compTTestCode::compTTestCode()
	:tcpData(0x92, 0x5A, 0x20)
{
}

bool compTTestCode::setEnable(vector<vector<bool> > enableMatrix)
{
	if(enableMatrix.size() != 16 || enableMatrix[0].size() != 16)
		return false;
	m_enableMatrix = enableMatrix;
	return true;
}

vector<int> compTTestCode::generate()
{
	vector<int> res;

	if(m_enableMatrix.size() == 0)
		return res;

	int rowSize = m_enableMatrix.size();
	int colSize = m_enableMatrix[0].size();

	if(rowSize != 16 || colSize != 16)
		return res;

	res.push_back(m_dataHeader);
	res.push_back(m_cmd);
	res.push_back(m_dataLen & 0xff);

	int data = 0;
	for(int i = 0;  i < rowSize; i++)
	{
		data = 0;
		for(int j = 0; j < colSize/2; j++)
		{
			if(m_enableMatrix[i][j])
				data = data | (1 << j);
		}
		res.push_back(data);

		data = 0;
		for(int j = colSize/2 + 1; j < colSize; j++)
		{
			if(m_enableMatrix[i][j])
				data = data | (1 << (j- colSize/2));
		}
		res.push_back(data);
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


compRTestCode::compRTestCode()
	:tcpData(0x92, 0xA5, 0x05)
{
}

bool compRTestCode::setEnable(vector<vector<bool> > enableMatrix)
{
	if(enableMatrix.size() != 6 || enableMatrix[0].size() != 6)
		return false;
	m_enableMatrix = enableMatrix;
	return true;
}

vector<int> compRTestCode::generate()
{
	vector<int> res;

	if(m_enableMatrix.size() == 0)
		return res;

	int rowSize = m_enableMatrix.size();
	int colSize = m_enableMatrix[0].size();

	if(rowSize != 6 || colSize != 6)
		return res;

	vector<bool> enableVec;

	for(int i = 0; i < rowSize; i++)
	{
		for(int j = 0; j < rowSize; j++)
		{
			enableVec.push_back(m_enableMatrix[i][j]);
		}
	}

	res.push_back(m_dataHeader);
	res.push_back(m_cmd);
	res.push_back(m_dataLen & 0xff);

	int data = 0;
	for(int i = 0;  i < enableVec.size(); i++)
	{
		if(enableVec[i])
			data = data | (1 << (i % 8));
		if( (i+1) % 8 == 0 || (i + 1) == enableVec.size() )
		{
			res.push_back(data);
			data = 0;
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
