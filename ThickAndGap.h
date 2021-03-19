#pragma once
#include "set"

enum msg_type { MSG_RANGE, MSG_POS, MSG_STRING, MSG_BOTH, MSG_END };
//type 1:range 2:pos 3:msg 4:pos&&msg 5:end
struct send_data
{
	msg_type type;
	TCHAR msg[6000];
	int pos;
};

class CThickAndGap
{
public:
	CThickAndGap(void);
public:
	~CThickAndGap(void);
public:
	static vector<WitSrfData> partSrfs;
	static vector<pair<WitSrfData, WitSrfData>> thickSrfs;
	static vector<pair<double,double>> thickVals;
	static set<string> strConnectArr;
public://进度条
	static int curProgPos;
	static CWnd* pWindow; //进程条窗口
	static void SendMsgToProg(msg_type type, int pos, CString str);
	//启动进程条
	static bool Startprog();
	//结束进程条
	static void EndProg();
public:
	static void GetVerticalVector(double triEnd1[3],double triEnd2[3],double triDir[3],double es[3][3]);
	static bool IsSurfGap(WitSrfData srf_1,WitSrfData srf_2);
	static bool IsSurfThick(WitSrfData srf_1, WitSrfData srf_2);
	static bool SurfDist(WitSrfData srf_1,WitSrfData srf_2, double &minDist, double &maxDist);
	static bool SurfMaxDist(WitSrfData srf_1, WitSrfData srf_2, double &maxDist);
public:
	void PartSurfSet(vector<WitSrfData> part_surfaces);
	void AddSurf(WitSrfData srf_data);
	void Check();
	static DWORD WINAPI  ThreadCheckFun(LPVOID p);
	static DWORD WINAPI  TotalThreadCheckFun(LPVOID p);
	void GetResult(vector<pair<WitSrfData, WitSrfData>> &m_thickSrfs, vector<pair<double,double>> &m_thickVals);
};
