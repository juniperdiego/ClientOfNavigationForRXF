#include "tcpSendFrame.h"

tcpSendFrame::tcpSendFrame()
	:m_frameStartTag(TCP_FRAME_START_TAG),
	m_reserveInt(0),
	m_frameEndTag(TCP_FRAME_END_TAG)
{
}

tcpSendFrame::~tcpSendFrame()
{
}

vector<int> tcpSendFrame::generateFrame()
{
	return vector<int> ();
}



remoteParamSendFrame::remoteParamSendFrame()
{
	m_frameLen = 0; //mark it is invalid 
}

void remoteParamSendFrame::setMode(bool mode)
{
	m_mode = mode;

	if(mode == false)
		m_frameLen = 4 * 6;
	else
		m_frameLen = 4 * 5;
}

void remoteParamSendFrame::setAntennaPattern(bool pattern)
{
	m_antennaPatern = pattern;
}

vector<int> remoteParamSendFrame::generateFrame()
{
	vector<int>  res;

	res.push_back(m_frameStartTag);
	res.push_back(m_frameLen);
	res.push_back(m_reserveInt);
	if(m_mode == false)
	{
		res.push_back(0);
		if(m_antennaPatern == false)
			res.push_back(0);
		else
			res.push_back(1);
	}
	else
		res.push_back(1);
	res.push_back(m_frameEndTag);

	return res;
}

vector<int> aerocraftSendFrame::generateFrame(char* buf, int len)
{
	m_frameEndTag = (len + 5) * 4;

	vector<int>  res;

	res.push_back(m_frameStartTag);
	res.push_back(m_frameLen);
	res.push_back(m_reserveInt);

	res.push_back(0);// mode = 0;

	for(int i = 0; i < len; i++)
		res.push_back(static_cast<int> ( buf[i] ) );
	res.push_back(m_frameEndTag);

	return res;
}

vector<int> broadcastSendFrame::generateFrame(char* buf, int len)
{
	m_frameEndTag = (len + 5) * 4;

	vector<int>  res;

	res.push_back(m_frameStartTag);
	res.push_back(m_frameLen);
	res.push_back(m_reserveInt);

	res.push_back(2);// mode = 2;

	for(int i = 0; i < len; i++)
		res.push_back(static_cast<int> ( buf[i] ) );
	res.push_back(m_frameEndTag);

	return res;
}


void groundInjectParamSendFrame::setYMD(int y, int m, int d)
{
	m_year = y;
	m_month = m;
	m_day =d;
}

void groundInjectParamSendFrame::setHMS(int h, int m, int s, int ms)
{
	m_hour = h;
	m_min = m;
	m_sec = s;
	m_msec = ms;
}

void groundInjectParamSendFrame::setSatelliteParam(float p1, float p2, float p3, 
			float p4, float p5, float p6)
{
	m_satelliteParam1 = p1;
	m_satelliteParam2 = p2;
	m_satelliteParam3 = p3;
	m_satelliteParam4 = p4;
	m_satelliteParam5 = p5;
	m_satelliteParam6 = p6;
}

void groundInjectParamSendFrame::setGroundParam(float p1, float p2, float p3) 
{
	m_groundParam1 = p1;
	m_groundParam2 = p2;
	m_groundParam3 = p3;
}
vector<int> groundInjectParamSendFrame::generateSatelliteInfo()
{
	vector<int>  res;
	unsigned int *p;
 
	p = (unsigned int *)&m_satelliteParam1;
	res.push_back( ((*p)>>24) & 0xff);
	res.push_back( ((*p)>>16) & 0xff);
	res.push_back( ((*p)>>8) & 0xff);
	res.push_back( ((*p)>>0) & 0xff);
 
	p = (unsigned int *)&m_satelliteParam2;
	res.push_back( ((*p)>>24) & 0xff);
	res.push_back( ((*p)>>16) & 0xff);
	res.push_back( ((*p)>>8) & 0xff);
	res.push_back( ((*p)>>0) & 0xff);

 	p = (unsigned int *)&m_satelliteParam3;
	res.push_back( ((*p)>>24) & 0xff);
	res.push_back( ((*p)>>16) & 0xff);
	res.push_back( ((*p)>>8) & 0xff);
	res.push_back( ((*p)>>0) & 0xff);

 	p = (unsigned int *)&m_satelliteParam4;
	res.push_back( ((*p)>>24) & 0xff);
	res.push_back( ((*p)>>16) & 0xff);
	res.push_back( ((*p)>>8) & 0xff);
	res.push_back( ((*p)>>0) & 0xff);

 	p = (unsigned int *)&m_satelliteParam5;
	res.push_back( ((*p)>>24) & 0xff);
	res.push_back( ((*p)>>16) & 0xff);
	res.push_back( ((*p)>>8) & 0xff);
	res.push_back( ((*p)>>0) & 0xff);

 	p = (unsigned int *)&m_satelliteParam6;
	res.push_back( ((*p)>>24) & 0xff);
	res.push_back( ((*p)>>16) & 0xff);
	res.push_back( ((*p)>>8) & 0xff);
	res.push_back( ((*p)>>0) & 0xff);
 
	return res;
}

vector<int> groundInjectParamSendFrame::generateGroundInfo()
{
	int tmp;
	unsigned int num;
	vector<int>  res;
	float precision;
	
	// param 1
	precision	= 0.01;
   	num = abs(int(m_groundParam1/precision));
	if(m_groundParam1 < 0)
		num = num| 0x8000;
	tmp = static_cast<int> ((num>> 8) & 0xff);
	res.push_back(tmp);
	tmp = static_cast<int> ((num>> 0) & 0xff);
	res.push_back(tmp);

	// pkaram 2
	precision	= 0.01;
   	num = abs(int(m_groundParam2/precision));
	if(m_groundParam1 < 0)
		num = num| 0x8000;
	tmp = static_cast<int> ((num>> 8) & 0xff);
	res.push_back(tmp);
	tmp = static_cast<int> ((num>> 0) & 0xff);
	res.push_back(tmp);

	// param 3
	precision	= 1;
   	num = abs(int(m_groundParam3));
	if(m_groundParam1 < 0)
		num = num| 0x8000;
	tmp = static_cast<int> ((num>> 8) & 0xff);
	res.push_back(tmp);
	tmp = static_cast<int> ((num>> 0) & 0xff);
	res.push_back(tmp);

	return res;
}

vector<int> groundInjectParamSendFrame::generateFrame()
{
	m_frameEndTag = (89 + 5) * 4;

	vector<int>  res;

	res.push_back(m_frameStartTag);
	res.push_back(m_frameLen);
	res.push_back(m_reserveInt);

	res.push_back(1);// mode = 1;

#if 0
时刻中
	B47~B36：年；
	B35~B32：月；
	B31~B27：日；
	B26~B22：时；
	B21~B16：分；
	B15~B10：秒；
	B9~B0： 毫秒

	byte 5: b47 ~ b40
	byte 4: b39 ~ b32
	byte 3: b31 ~ b24
	byte 2: b23 ~ b16
	byte 1: b15 ~ b8
	byte 0: b7 ~ b0
#endif
	// 1 时间信息
	res.push_back( static_cast<int> ((m_year >> 4) & 0xff));
	res.push_back( static_cast<int> ( ((m_year & 0xf) << 4) | m_month));
	res.push_back( static_cast<int> ( ((m_day & 0x1f) << 3) | ((m_hour  & 0x1f) >> 2)));
	res.push_back( static_cast<int> ( ((m_hour& 0x3) << 6) | ((m_min  & 0x3f) )));
	res.push_back( static_cast<int> ( ((m_sec& 0x1f) << 2) | ((m_msec) >> 8 )));
	res.push_back( static_cast<int> ( m_msec & 0xff ));

	//2 卫星信息 & 地面站信息
	vector<int> satelliteInfo = generateSatelliteInfo();
	if(m_whichAvail == 0x11)
	{
		for(int i = 0; i < satelliteInfo.size(); i++)
			res.push_back(satelliteInfo[i]);
		
		//insert 24 * 2 empty info for other satellites
		for(int i = 0; i < 24*2; i++)
			res.push_back(0);

		// insert 6 empty info for ground info
		for(int i = 0; i < 6; i++)
			res.push_back(0);

	}
	else if(m_whichAvail == 0x22)
	{
		//insert 24 empty info for other satellites
		for(int i = 0; i < 24; i++)
			res.push_back(0);

		for(int i = 0; i < satelliteInfo.size(); i++)
			res.push_back(satelliteInfo[i]);
		
		//insert 24 empty info for other satellites
		for(int i = 0; i < 24; i++)
			res.push_back(0);

		// insert 6 empty info for ground info
		for(int i = 0; i < 6; i++)
			res.push_back(0);
	}
	else if(m_whichAvail == 0x33)
	{
		//insert 24 * 2 empty info for other satellites
		for(int i = 0; i < 24*2; i++)
			res.push_back(0);
		
		for(int i = 0; i < satelliteInfo.size(); i++)
			res.push_back(satelliteInfo[i]);

		// insert 6 empty info for ground info
		for(int i = 0; i < 6; i++)
			res.push_back(0);
	}
	else if(m_whichAvail == 0x44)
	{
		//insert 24 * 3 empty info for other satellites
		for(int i = 0; i < 24*3; i++)
			res.push_back(0);

		// insert 6 info for ground info
		vector<int> groundInfo = generateGroundInfo();
		for(int i = 0; i < groundInfo.size(); i++)
			res.push_back(groundInfo[i]);

	}
	else if(m_whichAvail == 0x55)
	{
		//insert 24 * 3 empty info for other satellites
		for(int i = 0; i < 24*3; i++)
			res.push_back(0);

		// insert 6 empty info for ground info
		for(int i = 0; i < 6; i++)
			res.push_back(0);

	}

	//3. 可用信息
	res.push_back(static_cast<int>(m_whichAvail));

	res.push_back(m_frameEndTag);

	return res;
}
