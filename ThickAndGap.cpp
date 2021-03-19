#include "StdAfx.h"
#include "ThickAndGap.h"
#include "TMath.h"
#include<algorithm>
#define micro_precision 0.00001

vector<WitSrfData> CThickAndGap::partSrfs;
vector<pair<WitSrfData, WitSrfData>> CThickAndGap::thickSrfs;
vector<pair<double, double>> CThickAndGap::thickVals;
set<string> CThickAndGap::strConnectArr;
CWnd* CThickAndGap::pWindow = NULL;
int CThickAndGap::curProgPos = 0;

CThickAndGap::CThickAndGap(void)
{
}

CThickAndGap::~CThickAndGap(void)
{
}

//启动进程条
bool CThickAndGap::Startprog()
{
	curProgPos = 0;
	pWindow = NULL;
	TCHAR szPath[MAX_PATH] = { 0 };
	if (!GetModuleFileName(NULL, szPath, MAX_PATH))
		return false;
	CString strDir(szPath);
	strDir.Replace(L"Secretary.exe", L"ackDlgProg.exe");
	ShellExecuteW(NULL, L"open", strDir, NULL, NULL, SW_SHOWNORMAL); 
	//iCount = 1;//2018-09-26计数器初始化
	clock_t startTime, endTime;
	startTime = clock();
	while (1)
	{
		pWindow = CWnd::FindWindow(NULL, L"Autocheck progress");
		if (pWindow)
		{
			return true;
		}
		endTime = clock();
		if (((double)(endTime - startTime) / CLOCKS_PER_SEC) > 2)//如果2秒后没有找到，也要返回
		{
			break;
		}
	}
	return false;
}

void CThickAndGap::SendMsgToProg(msg_type type, int pos, CString str)
{
	send_data* sData = new send_data;
	sData->pos = pos;
	sData->type = type;
	_tcscpy(sData->msg, str.GetBuffer(str.GetLength()));
	str.ReleaseBuffer();

	COPYDATASTRUCT copyData;
	copyData.cbData = sizeof(send_data);   // Unicode-TCHAR  
	copyData.lpData = (void*)sData;
	if (pWindow)
	{
		::SendMessage(pWindow->m_hWnd, WM_COPYDATA, NULL, (LPARAM)&copyData);
	}
}

//结束进程条
void CThickAndGap::EndProg()
{
	Sleep(500);
	SendMsgToProg(MSG_END, 0, L"");
}

bool CThickAndGap::IsSurfGap(WitSrfData srf_1,WitSrfData srf_2)
{
	//if (srf_1.srfId == 43 && srf_2.srfId == 89)
	//	int kk = 0;
	//double cos_angle = cos(150 / 180 * M3D_PI);
	double centerPnt1[3] = { (srf_1.xyz_min[0] + srf_1.xyz_max[0])/2,(srf_1.xyz_min[1] + srf_1.xyz_max[1])/2,(srf_1.xyz_min[2] + srf_1.xyz_max[2])/2 };
	double centerPnt2[3] = { (srf_2.xyz_min[0] + srf_2.xyz_max[0])/2,(srf_2.xyz_min[1] + srf_2.xyz_max[1])/2,(srf_2.xyz_min[2] + srf_2.xyz_max[2])/2 };
	double dir[3] = {centerPnt2[0] - centerPnt1[0],centerPnt2[1] - centerPnt1[1],centerPnt2[2] - centerPnt1[2]};
	//double angle = CHT::TMath::VectCos(srf_1.dir, dir);
	//if (angle > cos_angle)
	//	int mmm = 0;
	if (CHT::TMath::VectCos(srf_1.dir, dir) > -micro_precision || CHT::TMath::VectCos(srf_2.dir, dir) < micro_precision)
		return true;
	return false;
}

bool CThickAndGap::IsSurfThick(WitSrfData srf_1, WitSrfData srf_2)
{
	if(CHT::TMath::VectCos(srf_2.dir, srf_1.dir)>-micro_precision)
		return false;
	double centerPnt1[3] = { (srf_1.xyz_min[0] + srf_1.xyz_max[0]) / 2,(srf_1.xyz_min[1] + srf_1.xyz_max[1]) / 2,(srf_1.xyz_min[2] + srf_1.xyz_max[2]) / 2 };
	double centerPnt2[3] = { (srf_2.xyz_min[0] + srf_2.xyz_max[0]) / 2,(srf_2.xyz_min[1] + srf_2.xyz_max[1]) / 2,(srf_2.xyz_min[2] + srf_2.xyz_max[2]) / 2 };
	double dir[3] = { centerPnt2[0] - centerPnt1[0],centerPnt2[1] - centerPnt1[1],centerPnt2[2] - centerPnt1[2] };
	if (CHT::TMath::VectCos(srf_1.dir, dir) > -micro_precision || CHT::TMath::VectCos(srf_2.dir, dir) < micro_precision)
		return false;
	return true;
}

void CThickAndGap::GetVerticalVector(double triEnd1[3],double triEnd2[3],double triDir[3],double es[3][3])
{
	CHT::TMath::d3Cut(triEnd1,triEnd2,es[0]);
	m3dNormalizeVector(es[0]);
	memcpy_s(es[2],3*sizeof(double),triDir,3*sizeof(double));
	m3dCrossProduct(es[1], es[2], es[0]);
	m3dNormalizeVector(es[1]);
}

void GetCenter(double pnts[3][3] ,double center[3])
{
	static double flag = 1.0 / 3.0;
	memset(center, 0, sizeof(double[3]));
	CHT::TMath::d3Plus(pnts[0], pnts[1], center);
	CHT::TMath::d3Plus(center, pnts[2], center);
	CHT::TMath::d3MultiNum(center, flag, center);
}

bool CThickAndGap::SurfDist(WitSrfData srf_1,WitSrfData srf_2, double &minDist, double &maxDist)
{
	double cos_angle = cos(170.0 / 180 * M3D_PI);
	if (!srf_1.IsPlane || !srf_2.IsPlane)
		cos_angle = cos(150.0 / 180 * M3D_PI);
	minDist = D_MAX;
	maxDist = 0.0;
	double maxTolDist(D_MIN);
	//for (int i = 0; i < srf_1.Vertices.size(); i++)
	//{
	//	for (int j = 0; j < srf_2.Vertices.size(); j++)
	//	{
	//		double m_dist = CHT::TMath::Twod3Dist(srf_1.Vertices[i].Vertice, srf_2.Vertices[j].Vertice);
	//		if (m_dist > minDist)
	//			continue;
	//		minDist = m_dist;
	//	}
	//}
	struct wit_srf_es
	{
		double es[3][3];
	};
	vector<wit_srf_es> srf1EsArr,srf2EsArr;
	wit_srf_es srfEs;
	for(int i=0;i<srf_1.Triangles.size();i++)
	{
		int index_0 = srf_1.Triangles[i].TriIndex[0];
		int index_1 = srf_1.Triangles[i].TriIndex[1];
		int index_2 = srf_1.Triangles[i].TriIndex[2];
		double triDir[3] = { (srf_1.Normals[index_0].Vertice[0] + srf_1.Normals[index_1].Vertice[0] + srf_1.Normals[index_2].Vertice[0]) / 3,
			(srf_1.Normals[index_0].Vertice[1] + srf_1.Normals[index_1].Vertice[1] + srf_1.Normals[index_2].Vertice[1]) / 3,
			(srf_1.Normals[index_0].Vertice[2] + srf_1.Normals[index_1].Vertice[2] + srf_1.Normals[index_2].Vertice[2]) / 3
		};
		GetVerticalVector(srf_1.Vertices[index_0].Vertice,srf_1.Vertices[index_1].Vertice,/*srf_1.Normals[index_0].Vertice*/triDir,srfEs.es);
		srf1EsArr.push_back(srfEs);
	}
	for(int i=0;i<srf_2.Triangles.size();i++)
	{
		int index_0 = srf_2.Triangles[i].TriIndex[0];
		int index_1 = srf_2.Triangles[i].TriIndex[1];
		int index_2 = srf_2.Triangles[i].TriIndex[2];
		double triDir[3] = { (srf_2.Normals[index_0].Vertice[0] + srf_2.Normals[index_1].Vertice[0] + srf_2.Normals[index_2].Vertice[0]) / 3,
			(srf_2.Normals[index_0].Vertice[1] + srf_2.Normals[index_1].Vertice[1] + srf_2.Normals[index_2].Vertice[1]) / 3,
			(srf_2.Normals[index_0].Vertice[2] + srf_2.Normals[index_1].Vertice[2] + srf_2.Normals[index_2].Vertice[2]) / 3
		};
		GetVerticalVector(srf_2.Vertices[index_0].Vertice,srf_2.Vertices[index_1].Vertice,/*srf_2.Normals[index_0].Vertice*/triDir,srfEs.es);
		srf2EsArr.push_back(srfEs);
	}
	//vector<double> _distList;
	for(int i=0;i<srf_1.Triangles.size();i++)
	{
		//double distTol(0.0);
		//vector<double> distList;
		int index_0 = srf_1.Triangles[i].TriIndex[0];
		int index_1 = srf_1.Triangles[i].TriIndex[1];
		int index_2 = srf_1.Triangles[i].TriIndex[2];
		double contour1[][3] = {{srf_1.Vertices[index_0].Vertice[0],srf_1.Vertices[index_0].Vertice[1],srf_1.Vertices[index_0].Vertice[2]},
		{srf_1.Vertices[index_1].Vertice[0],srf_1.Vertices[index_1].Vertice[1],srf_1.Vertices[index_1].Vertice[2]},
		{srf_1.Vertices[index_2].Vertice[0],srf_1.Vertices[index_2].Vertice[1],srf_1.Vertices[index_2].Vertice[2]}};
		for(int j=0;j<srf_2.Triangles.size();j++)
		{
			double angle = CHT::TMath::VectCos(srf1EsArr[i].es[2], srf2EsArr[j].es[2]);
			if (angle > cos_angle)
				continue;
			index_0 = srf_2.Triangles[j].TriIndex[0];
			index_1 = srf_2.Triangles[j].TriIndex[1];
			index_2 = srf_2.Triangles[j].TriIndex[2];
			double contour2[][3] = {{srf_2.Vertices[index_0].Vertice[0],srf_2.Vertices[index_0].Vertice[1],srf_2.Vertices[index_0].Vertice[2]},
			{srf_2.Vertices[index_1].Vertice[0],srf_2.Vertices[index_1].Vertice[1],srf_2.Vertices[index_1].Vertice[2]},
			{srf_2.Vertices[index_2].Vertice[0],srf_2.Vertices[index_2].Vertice[1],srf_2.Vertices[index_2].Vertice[2]}};
			//是否为厚度begin
			double t2_center[3], temp_pnt[3], tdir[3];
			GetCenter(contour2,t2_center);
			CHT::TMath::GetPntOnSrf(t2_center, contour1[0], srf1EsArr[i].es[2], temp_pnt);
			CHT::TMath::d3Cut(t2_center, temp_pnt, tdir);
			double dd = CHT::TMath::d3Multiple(tdir, srf2EsArr[j].es[2]);
			if (dd < PRECISION)
			{
				continue;
			}
			//是否为厚度end
			//判断是否相交begin
			if(CHT::TMath::IsTwoContourCrossEach(contour1,3, contour2, 3, srf1EsArr[i].es[2], srf2EsArr[j].es[2]))
				return false;
			//判断是否相交end
			double m_dist(D_MAX);
			if(!CHT::TMath::GetTwoContourMinDist(contour1,3,contour2,3,srf1EsArr[i].es,srf2EsArr[j].es,m_dist))
				continue;
			if(m_dist<minDist)
				minDist = m_dist;
			if (m_dist > maxDist)
				maxDist = m_dist;
			//distList.push_back(m_dist);
			//distTol += m_dist;
		}
		//if (maxTolDist >= distTol)
		//	continue;
		//maxTolDist = distTol;
		//_distList.clear();
		//_distList.assign(distList.begin(), distList.end());
	}
	//maxDist = D_MAX;
	//for (auto distElem : _distList)
	//{
	//	if (distElem < maxDist)
	//		maxDist = distElem;
	//}
	return true;
	minDist = D_MAX;
	for(int i=0;i<srf_1.Vertices.size();i++)
	{
		for(int t=0;t<srf_2.Triangles.size();t++)
		{
			double midPnt[3];
			int index_0 = srf_2.Triangles[t].TriIndex[0];
			CHT::TMath::GetPntOnSrf(srf_1.Vertices[i].Vertice,srf_2.Vertices[index_0].Vertice,srf_2.Normals[index_0].Vertice,midPnt);
			int index_1 = srf_2.Triangles[t].TriIndex[1];
			int index_2 = srf_2.Triangles[t].TriIndex[2];
			if(!CHT::TMath::IsPntInTriangle_s(midPnt,srf_2.Vertices[index_0].Vertice,srf_2.Vertices[index_1].Vertice,srf_2.Vertices[index_2].Vertice))
				continue;
			double m_dist(CHT::TMath::PtoSdist(srf_1.Vertices[i].Vertice,srf_2.Vertices[index_0].Vertice,srf_2.Normals[index_0].Vertice));
			if(m_dist<minDist)
				minDist = m_dist;
		}
	}
	for(int i=0;i<srf_2.Vertices.size();i++)
	{
		for(int t=0;t<srf_1.Triangles.size();t++)
		{
			double midPnt[3];
			int index_0 = srf_1.Triangles[t].TriIndex[0];
			CHT::TMath::GetPntOnSrf(srf_2.Vertices[i].Vertice,srf_1.Vertices[index_0].Vertice,srf_1.Normals[index_0].Vertice,midPnt);
			int index_1 = srf_1.Triangles[t].TriIndex[1];
			int index_2 = srf_1.Triangles[t].TriIndex[2];
			if(!CHT::TMath::IsPntInTriangle_s(midPnt,srf_1.Vertices[index_0].Vertice,srf_1.Vertices[index_1].Vertice,srf_1.Vertices[index_2].Vertice))
				continue;
			double m_dist(CHT::TMath::PtoSdist(srf_2.Vertices[i].Vertice,srf_1.Vertices[index_0].Vertice,srf_1.Normals[index_0].Vertice));
			if(m_dist<minDist)
				minDist = m_dist;
		}
	}
	//for(int i=0;i<srf_1.Triangles.size();i++)
	//{
	//	for(int j=0;j<srf_1.Triangles[i].size();j++)
	//	{
	//		for(int t=0;t<srf_2.Triangles.size();t++)
	//		{
	//			for(int k=0;k<srf_2.Triangles[t].size();k++)
	//			{
	//				//double m_dist(CHT::TMath::Twod3Dist(srf_1.Triangles[i][j].WitVertice,srf_2.Triangles[t][k].WitVertice));
	//				//double m_dist(CHT::TMath::PtoSdist(srf_1.Triangles[i][j].WitVertice,srf_2.Triangles[t][k].WitVertice,srf_2.));
	//				//if(m_dist<minDist)
	//				//	minDist = m_dist;
	//			}
	//		}
	//	}
	//}
	return true;
}

bool CThickAndGap::SurfMaxDist(WitSrfData srf_1, WitSrfData srf_2, double &maxDist)
{
	maxDist = -1;
	double srf1CenterPnt[3] = { srf_1.xyz_min[0] / 2 + srf_1.xyz_max[0] / 2,srf_1.xyz_min[1] / 2 + srf_1.xyz_max[1] / 2, srf_1.xyz_min[2] / 2 + srf_1.xyz_max[2] / 2 }, srf2CenterPnt[3] = { srf_2.xyz_min[0] / 2 + srf_2.xyz_max[0] / 2,srf_2.xyz_min[1] / 2 + srf_2.xyz_max[1] / 2, srf_2.xyz_min[2] / 2 + srf_2.xyz_max[2] / 2 };
	for (int i = 0; i < int(srf_1.Vertices.size()); i++)
	{
		double midPnt[3];
		CHT::TMath::GetPntOnSrf(srf_1.Vertices[i].Vertice, srf2CenterPnt, srf_2.dir, midPnt);
		for (int j = 0; j < srf_2.Triangles.size(); j++)
		{
			int index_0 = srf_2.Triangles[j].TriIndex[0];
			int index_1 = srf_2.Triangles[j].TriIndex[1];
			int index_2 = srf_2.Triangles[j].TriIndex[2];
			if(!CHT::TMath::IsPntInTriangle_s(midPnt, srf_2.Vertices[index_0].Vertice, srf_2.Vertices[index_1].Vertice, srf_2.Vertices[index_2].Vertice))
				continue;
			double rDist = CHT::TMath::Twod3Dist(srf_1.Vertices[i].Vertice, midPnt);
			if (maxDist < rDist)
				maxDist = rDist;
			break;
		}
	}

	for (int i = 0; i < int(srf_2.Vertices.size()); i++)
	{
		double midPnt[3];
		CHT::TMath::GetPntOnSrf(srf_2.Vertices[i].Vertice, srf1CenterPnt, srf_1.dir, midPnt);
		for (int j = 0; j < srf_1.Triangles.size(); j++)
		{
			int index_0 = srf_1.Triangles[j].TriIndex[0];
			int index_1 = srf_1.Triangles[j].TriIndex[1];
			int index_2 = srf_1.Triangles[j].TriIndex[2];
			if (!CHT::TMath::IsPntInTriangle_s(midPnt, srf_1.Vertices[index_0].Vertice, srf_1.Vertices[index_1].Vertice, srf_1.Vertices[index_2].Vertice))
				continue;
			double rDist = CHT::TMath::Twod3Dist(srf_2.Vertices[i].Vertice, midPnt);
			if (maxDist < rDist)
				maxDist = rDist;
			break;
		}
	}

	if (maxDist < 0)
		return false;
	return true;
}

void CThickAndGap::PartSurfSet(vector<WitSrfData> part_surfaces)
{
	partSrfs.assign(part_surfaces.begin(),part_surfaces.end());
}

void CThickAndGap::AddSurf(WitSrfData srf_data)
{
	partSrfs.push_back(srf_data);
}

struct threadSrfData
{
	//int iSeq;
	vector<WitSrfData> partSrfs_temp;
	vector<pair<WitSrfData, WitSrfData>> thickSrfs;
	vector<pair<double, double>> thickVals;
};



typedef BOOL(WINAPI *LPFN_GLPI)(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, PDWORD);

DWORD CountSetBits(ULONG_PTR bitMask)
{
	DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
	DWORD bitSetCount = 0;
	ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
	DWORD i;

	for (i = 0; i <= LSHIFT; ++i)
	{
		bitSetCount += ((bitMask & bitTest) ? 1 : 0);
		bitTest /= 2;
	}
	return bitSetCount;
}
void GetCoreNumber(DWORD &logicalProcessorCount,DWORD &processorCoreCount)
{
	logicalProcessorCount = 0;
	processorCoreCount = 0;
	LPFN_GLPI glpi;
	glpi = (LPFN_GLPI)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "GetLogicalProcessorInformation");
	if (NULL == glpi)
	{
		printf("GetLogicalProcessorInformation is not supported.\n");
	}
	BOOL done = FALSE;
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = NULL;
	DWORD returnLength = 0;
	while (!done)
	{
		DWORD rc = glpi(buffer, &returnLength);
		if (FALSE == rc)
		{
			if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				if (buffer)
					free(buffer);
				buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(returnLength);
				if (NULL == buffer)
				{
					printf("Error: Allocation failure\n");
					return ;
				}
			}
			else
			{
				printf("Error %d\n", GetLastError());
				return ;
			}
		}
		else
		{
			done = TRUE;
		}
	}
	ptr = buffer;
	DWORD byteOffset = 0;
	while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength)
	{
		switch (ptr->Relationship)
		{
		case RelationProcessorCore:
			processorCoreCount++;
			logicalProcessorCount += CountSetBits(ptr->ProcessorMask);
			break;
		}
		byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
		ptr++;
	}
}

DWORD WINAPI  CThickAndGap::ThreadCheckFun(LPVOID p)
{
	//CString str;
	////mm++;
	////str.Format(L"%d", mm);
	////AfxMessageBox(str);

	////cs.Lock();
	//int nSeq = *((int*)p);
	threadSrfData *tSrfData = (threadSrfData*)p;
	//int srf_num = int(partSrfs.size());
	////int nSeq = tSrfData->iSeq;
	//////str.Format(L"%d",nSeq);
	//////AfxMessageBox(str);
	////////cs.Unlock();
	//////return -1;
	////int srf_num = int(partSrfs.size());
	////int verNum = srf_num / threadNum;
	////int iStart = nSeq*verNum, iEnd(0);
	////if (threadNum == nSeq + 1)
	////	iEnd = srf_num;
	////else
	////	iEnd = (nSeq + 1)*verNum;
	/*for (int i = srf_num - 1; i >= 0; i--)*/
	for (int i = 0; i < (int)tSrfData->partSrfs_temp.size(); i++)
	{
		double min_dist(D_MAX), max_dist(D_MIN);
		int minKey(-1);
		/*for (int j = 0; j<srf_num; j++)*/
		for (int j = 1; j < int(partSrfs.size()); j++)
		{

			//if (i == j)
			//	continue;
			if (tSrfData->partSrfs_temp[i].srfId == partSrfs[j].srfId) {
				continue;
			}
			//过滤重复ij和ji相反值begin
			string strConnect = "|" + to_string(j) + "-" + to_string(i) + " | ";
			if (!strConnectArr.empty() && strConnectArr.find(strConnect) != strConnectArr.end())
				continue;
			strConnect = "|" + to_string(i) + "-" + to_string(j) + " | ";
			strConnectArr.insert(strConnect);
			//过滤重复ij和ji相反值end
			//if ((partSrfs[i].srfId == 31843 && partSrfs[j].srfId == 30538) || (partSrfs[i].srfId == 30538 && partSrfs[j].srfId == 31843))
			//	AfxMessageBox(L"MSG");
			if (!IsSurfThick(tSrfData->partSrfs_temp[i], partSrfs[j]))
				continue;
			double m_dist(0.0),n_dist(0.0);
			if (!SurfDist(tSrfData->partSrfs_temp[i], partSrfs[j], m_dist, n_dist))
				continue;
			if (min_dist < m_dist/*||fabs(m_dist - D_MAX)<PRECISION*/)
				continue;
			min_dist = m_dist;
			max_dist = n_dist;
			minKey = j;
		}
		if (minKey < 0 || min_dist < micro_precision || fabs(min_dist - D_MAX)< micro_precision)
			continue;
		//bool IsInclude(false);
		//for (auto pt : thickSrfs)
		//{
		//	if ((partSrfs[i].srfId == pt.first.srfId&&partSrfs[minKey].srfId == pt.second.srfId)
		//		|| (partSrfs[i].srfId == pt.second.srfId&&partSrfs[minKey].srfId == pt.first.srfId))
		//	{
		//		IsInclude = true;
		//		break;
		//	}
		//}
		//if (IsInclude)
		//	continue;
		//SurfMaxDist(partSrfs[i], partSrfs[minKey], max_dist);
		//thickSrfs.push_back(make_pair(partSrfs[i], partSrfs[minKey]));
		//thickVals.push_back(make_pair(min_dist, max_dist));
		tSrfData->thickSrfs.push_back(make_pair(tSrfData->partSrfs_temp[i], partSrfs[minKey]));
		tSrfData->thickVals.push_back(make_pair(min_dist, max_dist));
		//COPYDATASTRUCT copyData;
		//copyData.dwData = i - iStart;
		//dlgProgress.PostMessage(WM_COPYDATA,NULL,(LPARAM)&copyData);
		curProgPos++;
		if (curProgPos % 10 == 0)
			SendMsgToProg(MSG_POS, curProgPos, L"");
	}
	return 0;
}
static bool sort1(const WitSrfData &WitSrfData1_, const  WitSrfData &WitSrfData2_)
{
	return((int)WitSrfData2_.Triangles.size() < (int)WitSrfData1_.Triangles.size());
}
void CThickAndGap::Check()
{
	DWORD logicalProcessorCount,processorCoreCount;
	GetCoreNumber(logicalProcessorCount, processorCoreCount);

	int threadNum(2);
	if (logicalProcessorCount > 2)
		threadNum = logicalProcessorCount;
	thickSrfs.clear();
	thickVals.clear();
	strConnectArr.clear();
	vector<threadSrfData *> tSrfDatas;
	//按三角形从多到少排序
	std::sort(partSrfs.begin(), partSrfs.end(), sort1);
	//分组
	vector<vector<WitSrfData>> group_partSrfs;
	int srf_num = int(partSrfs.size());
	int coreNum(1);//实际可分组数量
	if (srf_num <= threadNum) {
		coreNum = srf_num;
	}
	else {
		coreNum = threadNum;
	}
	int verNum = srf_num / coreNum;

	//分组
	group_partSrfs.resize(coreNum);
	for (int i = 0; i < (int)partSrfs.size(); i++) {
		int curr_index(0);
		if (i < coreNum) {
			curr_index = i;
		}
		else {
			curr_index = i % coreNum;
		}
		group_partSrfs[curr_index].push_back(partSrfs[i]);
	}
	////重新组合
	//partSrfs.clear();
	//for (int i = 0; i < (int)group_partSrfs.size(); i++) {
	//	for (int j = 0; j < (int)group_partSrfs[i].size(); j++) {
	//		partSrfs.push_back(group_partSrfs[i][j]);
	//	}
	//}
	HANDLE *hThreads=new HANDLE[threadNum];
	for (int i = 0; i < (int)group_partSrfs.size(); i++)
	{
		threadSrfData *oSrfData = new  threadSrfData;
		//oSrfData->iSeq = threadNum;
		oSrfData->partSrfs_temp = group_partSrfs[i];
		hThreads[i] = CreateThread(NULL, 0, ThreadCheckFun, (LPVOID)oSrfData, 0, NULL); // 创建线程
		tSrfDatas.push_back(oSrfData);
	}
	for (int i = 0; i < (int)group_partSrfs.size(); i++)
	{
		//MsgWaitForMultipleObjects(1, &hThreads[i], FALSE, INFINITE, QS_ALLINPUT);
		WaitForSingleObject(hThreads[i], INFINITE);	//一直等待，直到子线程返回
		//dlgProgress->SetProgressPos(40 + (i + 1) * 10);
		//Sleep(100);
	}

	for (int i = 0; i < threadNum; i++)
	{
		thickSrfs.insert(thickSrfs.end(), tSrfDatas[i]->thickSrfs.begin(), tSrfDatas[i]->thickSrfs.end());
		thickVals.insert(thickVals.end(), tSrfDatas[i]->thickVals.begin(), tSrfDatas[i]->thickVals.end());
		delete tSrfDatas[i];
	}
	delete[] hThreads;
}

void CThickAndGap::GetResult(vector<pair<WitSrfData, WitSrfData>> &m_thickSrfs, vector<pair<double, double>> &m_thickVals)
{
	m_thickSrfs.assign(thickSrfs.begin(), thickSrfs.end());
	m_thickVals.assign(thickVals.begin(), thickVals.end());
}
