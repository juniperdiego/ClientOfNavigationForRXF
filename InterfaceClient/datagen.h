#ifndef DATAGEN_H
#define DATAGEN_H

class dataGen
{
public:
	dataGen(char dataHeader, char cmd, char dataLen);
	virtual ~dataGen();
	virtual void generate(char *buf, int size) =0;
	int getBufSize();
protected:
	char	m_dataHeader;
	char	m_cmd;
	char	m_dataLen;
	char	m_check;
};

class dataGenForAerocraft :public dataGen
{
public:
	dataGenForAerocraft();
	void setMode(bool isOnTrack);
	void setPos(float x, float y, float z);
	void setVelocity(float vx, float vy, float vz);
	void setAngle(float a1, float a2, float a3);
	void setPalstance(float p1, float p2, float p3);

	void generate(char *buf, int size);
private:
	bool	m_isOnTrack;
	float	m_x;
	float	m_y;
	float	m_z;
	float	m_vx;
	float	m_vy;
	float	m_vz;
	float	m_angle1;
	float	m_angle2;
	float	m_angle3;
	float	m_p1; // ½ÇËÙ¶È
	float	m_p2;
	float	m_p3;
};

class dataGenForBroadcast :public dataGen
{
public:
	dataGenForBroadcast();
	void setYMD(int y, int m, int d);
	void setHMS(int h, int m, int s, int ms);

	void generate(char *buf, int size);
private:
	int		m_year;
	int		m_month;
	int		m_day;
	int		m_hour;
	int		m_min;
	int		m_sec;
	int		m_msec;
};
#endif // DATAGEN_H