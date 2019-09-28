// dlg_stlimport.cpp : 实现文件
//
#include "stdafx.h"
#include "fpc_developer.h"
#include "dlg_stlimport.h"
#include "afxdialogex.h"
#include"ReadSTLFile.h"
#include "UnicodeString.h"
#include<map>
#include<list>
#include <fstream>
#include<iostream>
#include "Public_fun.h"
using namespace std;

ProErr feat_geoms_visit(ProGeomitem* p_handle, ProErr errors, ProAppData data)
{
	vector<ProGeomitem>*pls = (vector<ProGeomitem>*)data;
	pls->push_back(*p_handle);

	return PRO_TK_NO_ERROR;
}

ProError contourvisit(ProContour  p_contour,
	ProError    status,
	ProAppData  app_data
) {
	status = PRO_TK_NO_ERROR;
	vector<ProContour> *p = (vector<ProContour> *)app_data;
	p->emplace_back(p_contour);
	return status;
}
ProError  edgevisit(ProEdge p_edge,
	ProError status,
	ProAppData app_data)
{
	status = PRO_TK_NO_ERROR;
	vector<ProEdge> *p = (vector<ProEdge> *)app_data;
	p->emplace_back(p_edge);
	return status;
}
ProError surfacevisit(ProSurface surface,
	ProError status,
	ProAppData app_data)
{
	status = PRO_TK_NO_ERROR;
	vector<ProSurface> *p = (vector<ProSurface> *)app_data;
	p->emplace_back(surface);
	return status;
}
ProError quiltvisit(ProQuilt p_quilt,
	ProError status,
	ProAppData app_data)
{
	status = PRO_TK_NO_ERROR;
	vector<ProQuilt> *p = (vector<ProQuilt> *)app_data;
	p->emplace_back(p_quilt);
	return status;
}
ProError  featurevisit(ProFeature* p_feature,
	ProError status,
	ProAppData app_data) {
	status = PRO_TK_NO_ERROR;
	vector<ProFeature> *p = (vector<ProFeature> *)app_data;
	p->emplace_back(*p_feature);
	return status;
}
ProError PMCollectSolidQuilts(
	ProSolid	    p_solid,	    /* In:  The handle to the solid */
	vector<ProQuilt>&p_quilt)
{
	ProError status = PRO_TK_NO_ERROR;
	status = ProSolidQuiltVisit(p_solid, quiltvisit, NULL, &(p_quilt));
	return status;
}
ProError  PMCollectSolidFeatures(ProSolid	    p_solid,	    /* In:  The handle to the solid */
	vector<ProFeature>&feats) {
	ProError status = PRO_TK_NO_ERROR;
	status = ProSolidFeatVisit(p_solid, featurevisit, NULL, &(feats));
	return status;
}
// dlg_stlimport 对话框

IMPLEMENT_DYNAMIC(dlg_stlimport, CDialogEx)

dlg_stlimport::dlg_stlimport(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG9, pParent)
{
	pWindow = NULL;
	sel_parent = NULL;
}

dlg_stlimport::~dlg_stlimport()
{
	if (sel_parent != NULL) {
		ProSelectionFree(&sel_parent);
	}
}

void dlg_stlimport::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(dlg_stlimport, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &dlg_stlimport::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &dlg_stlimport::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &dlg_stlimport::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &dlg_stlimport::OnBnUserSelectSTL)
	ON_BN_CLICKED(IDC_BUTTON3, &dlg_stlimport::OnBnCreateNURBS)
	ON_BN_CLICKED(IDC_BUTTON8, &dlg_stlimport::OnBnClickedSelParent)
END_MESSAGE_MAP()


// dlg_stlimport 消息处理程序
void dlg_stlimport::usermain()
{
	//创建对话框
	int status = Create(IDD_DIALOG9, NULL);
	if (status == 0)
	{
		AfxMessageBox(_T("对话框创建失败."));
		return;
	}
	ShowWindow(SW_SHOW);
}
//选择stl文件按钮
void dlg_stlimport::OnBnClickedButton1()
{
	ProLine buff;
	ProPath  def_path;
	ProError err;
	ProPath sel_path;
	CString csSTLasmPath;
	ProAsmcomppath comppath, newSTLpath;
	ProMatrix matrix;
	//需要判断当前模型是否有关键字的STL装配
	userGetSTLasm(csSTLasmPath);
	if (csSTLasmPath.IsEmpty())
	{
		return;
	}

	ProStringToWstring(buff, (char *)"*.stl");
	ProStringToWstring(def_path, (char *)".");
	err = ProFileOpen(NULL, buff, NULL, NULL, def_path, NULL, sel_path);
	if (err != PRO_TK_NO_ERROR)
	{
		return;
	}

	CString str_path(sel_path);
	int nPos = str_path.ReverseFind('.');
	str_path = str_path.Left(nPos);
	nPos = str_path.ReverseFind('\\');
	CString str_name = str_path.Mid(nPos + 1);

	ProMdl stl_load;
	//需要判断内存中是否已经有了同名称的模型，如果有了，就不能导入成功了 
	err = ProMdlInit(str_name.GetBuffer(), PRO_MDL_PART, &stl_load);
	if (err == PRO_TK_NO_ERROR)
	{
		AfxMessageBox(_T("内存中有同名称的零件---") + str_name);
	}
	else
	{
		//err = ProIntfimportModelCreate(sel_path, PRO_INTF_IMPORT_STL, PRO_MDL_PART, str_name.GetBuffer(), NULL, NULL, &stl_load);

		ProPath TextPath; CString csFilePath;
		ProToolkitApplTextPathGet(TextPath);
		csFilePath = TextPath;
		csFilePath = csFilePath + _T("\\data\\stl_import.dip");//stl导入配置文件,可以控制单位mm
		err = ProIntfimportModelWithOptionsMdlnameCreate(sel_path, csFilePath.GetBuffer(),
			PRO_INTF_IMPORT_STL, PRO_MDL_PART, PRO_IMPORTREP_MASTER, str_name.GetBuffer(), NULL, NULL, &stl_load);
		if (err != PRO_TK_NO_ERROR)
		{
			AfxMessageBox(_T("导入模型失败！"));
			return;
		}
		else
		{//导入成功，装配到含有关键字的装配中  
			UserCstringToComppath(csSTLasmPath, comppath);
			ProUtilMatrixCopy(NULL, matrix);
			UserAssmbleModelWithMatrix(comppath, stl_load, matrix, newSTLpath);
			//写入一个参数odb路径值，导出时用的 
			ProModelitem item; CString str_path2(sel_path);
			err = ProMdlToModelitem(stl_load, &item);
			UserSetParam(item, _T("odb_path"), str_path2);

			AfxMessageBox(_T("导入模型成功！"));
		}
	}
	//删除窗口
	//DestroyWindow();
}
//获取含有关键字的STL装配组件，如果没有，不能导入
void dlg_stlimport::userGetSTLasm(CString& csSTLasmPath)
{
	int err;
	ProMdl asmmdl;
	TKAsmCompCountData comp_data;
	ProName wname;
	CString csName, csSTLAsmName, csText;
	int iHave = 0;
	CString csBodyasmpath;
	err = ProMdlCurrentGet(&asmmdl);

	std::vector<CString> defaultname;
	UserGetScrewFile(_T("default_name.cfg"), defaultname);
	for (int i = 0; i < defaultname.size(); i++)
	{
		csText = defaultname[i];
		if (csText.Find(_T("STL装配关键字")) >= 0)
		{
			csText.Replace(_T("STL装配关键字="), _T(""));
			csSTLAsmName = csText;
		}
	}

	TKAsmCompsCollectRecursiveWithCount((ProAssembly)asmmdl, &comp_data);
	for (int i = 0; i < comp_data.nComps; i++)
	{
		err = ProMdlNameGet(comp_data.comps[i].hMdl, wname);
		csName = wname;
		if (csName.Find(csSTLAsmName) >= 0)//判断是否块装配最大组件
		{
			iHave = 1;
			UserComppathToCstring(comp_data.comps[i].hPath, csSTLasmPath);
			break;
		}
	}
	if (0 == iHave)//如果没装配，自动装配一个
	{
		userAssmbleNewAsmMain(csSTLAsmName, csSTLasmPath);
		if (!csSTLasmPath.IsEmpty())//装配成功
		{
			iHave = 1;
		}
	}
	if (iHave == 1)//有装配
	{

	}
	else
	{
		AfxMessageBox(_T("没有STL装配，请创建含有STL装配的关键字----") + csSTLAsmName);
	}

}
//取消按钮
void dlg_stlimport::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
	DestroyWindow();
}


void dlg_stlimport::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//删除窗口
	DestroyWindow();
}


bool dlg_stlimport::isNameLegalToCreo(CString nameWithOutExt) {
	//
	if (nameWithOutExt.GetLength() > 32) {
		return false;
	}

	for (int i = 0; i < nameWithOutExt.GetLength(); ++i) {
		int unicode = (int)nameWithOutExt.GetAt(i);
		if (unicode <= '9'&&unicode >= '0') {
			continue;
		}
		else if (unicode <= 'z'&&unicode >= 'a') {
			continue;
		}
		else if (unicode <= 'Z'&&unicode >= 'A') {
			continue;
		}
		else if (unicode > 255) {
			continue;
		}
		else if (unicode == '_' || unicode == '-') {
			if (i == 0) {
				return false;
			}
			else {
				continue;
			}
		}
		else {//是除了_和-外的标点符号
			return false;
		}
	}
	return true;
}


bool dlg_stlimport::UserSelectFile(IN CString Filter, IN CString InitalDir, IN CString caption,
	OUT CString&fileName)  // 用户选择文件
{
	fileName = L"";

	TCHAR *lpszFilter = Filter.AllocSysString();  // 指定后缀
	CFileDialog Filedlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER, lpszFilter);

	if (!InitalDir.IsEmpty())Filedlg.m_ofn.lpstrInitialDir = InitalDir;  // 初始显示位置
	if (!caption.IsEmpty())Filedlg.m_ofn.lpstrTitle = caption;

	INT_PTR ret = Filedlg.DoModal();
	if (IDOK == ret) {
		fileName = Filedlg.GetPathName();
		return  true;
	}
	else {
		return false;
	}
}

void dlg_stlimport::OnBnUserSelectSTL()
{
	// TODO: 在此添加控件通知处理程序代码
	// 1.选择STL文件
	// 2.读入三角形--数据源 triangles
	// 3.设置combo为空
	// 4.求出点云与内外轮廓
	CString file_path;
	UserSelectFile(L"stl文件 (*.stl)|*.stl||", L"", L"请选择一个STL文件", file_path);

	CString old_stl;
	GetDlgItem(IDC_EDIT_FILE)->GetWindowText(old_stl);
	if (old_stl.Compare(file_path) == 0) { return; }//和之前文件路径相同则直接返回


	stl_info.Clear();
	GetDlgItem(IDC_EDIT_FILE)->SetWindowText(_T(""));
	((CComboBox*)GetDlgItem(IDC_COMBO_PAR))->ResetContent();


	CWaitCursor waitcursor;
	//转为char*并读取stl文件为三角形
	CUnicodeString trans_file_name(file_path.GetBuffer());
	file_path.ReleaseBuffer();

	const char * file_name = trans_file_name.ToMultiByte();
	bool ret = ReadSTLFile::ReadBinarySTLFile(file_name, stl_info.triangles);
	if (ret == false || stl_info.triangles.size() == 0) {
		AfxMessageBox(_T("文件读取失败"));
		return;
	}
	GetDlgItem(IDC_EDIT_FILE)->SetWindowText(file_path);

	int nPos = file_path.ReverseFind(L'\\');
	file_path.Delete(0, nPos + 1);
	nPos = file_path.Find(L'.');
	CString part_name = file_path.Left(nPos);
	GetDlgItem(IDC_EDIT_PART_NAME)->SetWindowText(part_name);

	ret = TransSTLToPointCloud(stl_info.triangles, stl_info.cloud);//转为点云
	ret = FindSTLBoundary(stl_info.triangles, stl_info.outer_boundary, stl_info.inner_boundary);//求内外边界

	return;
}

ProError dlg_stlimport::CreateFpcPart(OUT ProMdl&new_mdl)
{
	//计算界面选择的方案参数并保存IGES文件
	ProError status = PRO_TK_NO_ERROR;

	FitSurface::CalcResult cur_solution;//当前选择

	CComboBox* combo = (CComboBox*)(GetDlgItem(IDC_COMBO_PAR));
	if (combo->GetCount() > 0) {//说明之前计算过参数集
		int sel_index = combo->GetCurSel();
		if (sel_index != CB_ERR&&sel_index < fit_result.size()) {
			cur_solution = fit_result[sel_index];
		}
		else {
			return PRO_TK_E_NOT_FOUND;
		}
	}
	else {//说明之前未计算过参数集
		  //转为点云
		double expand_value = 3;//扩张一定的大小,如果面不够大，可以增大此项

		FitSurface fit_surafce;
		fit_surafce.set_range(0, 100);
		fit_surafce.attach(this);
		bool ret = fit_surafce.FindOptimalParameter(stl_info.cloud, expand_value, fit_result);

		if (fit_result.size() == 0) { return PRO_TK_GENERAL_ERROR; }

		std::sort(fit_result.begin(), fit_result.end());//根据公差排序
		for (int i = 0; i < (int)fit_result.size(); i++) {
			CString str;
			str.Format(_T("opt%d--%.5lfmm"), i + 1, fit_result[i].tol);//opt1--0.02376mm
			combo->AddString(str);//插入COMBOBOX
		}
		combo->SetCurSel(0);
		cur_solution = fit_result[0];
	}
	vector<vector<Point3>> All_boundary = stl_info.inner_boundary;//全部轮廓
	All_boundary.push_back(stl_info.outer_boundary);

	ProPath text_path;
	status = ProToolkitApplTextPathGet(text_path);
	if (status != PRO_TK_NO_ERROR) { return status; }
	CString iges_pos;
	iges_pos.Format(L"%s\\data\\fpc_reconstruct\\%s", text_path, _T("fpc_reconstruct.iges"));
	bool ret_ = FitSurface::WriteToIges(cur_solution.nurbs, All_boundary, iges_pos);//写入3dm文件中
	if (!ret_) { return PRO_TK_GENERAL_ERROR; }


	SetProgPos(100, L"");
	
	//总--导入iges文件并显示或者装配
	//// 导入iges

	ProMdlName w_name;//零件的名称
	{
		CString name_str;
		GetDlgItem(IDC_EDIT_PART_NAME)->GetWindowText(name_str);
		ProWstringCopy(name_str.GetBuffer(), w_name, PRO_VALUE_UNUSED);
		name_str.ReleaseBuffer();
	}
	new_mdl = NULL;
	status = ProIntfimportModelWithOptionsMdlnameCreate(iges_pos.AllocSysString(),
		NULL, PRO_INTF_IMPORT_IGES, PRO_MDL_PART, PRO_IMPORTREP_MASTER, w_name, NULL, NULL, &new_mdl);
	if (new_mdl == NULL || status != PRO_TK_NO_ERROR) { return status; }
	// 备份模型
	ProMdldata mdl_data;
	status = ProMdlDataGet(new_mdl, &mdl_data);
	if (status != PRO_TK_NO_ERROR) { return status; }
	ProPath direct_path;
	status = ProDirectoryCurrentGet(direct_path);
	if (status != PRO_TK_NO_ERROR) { return status; }
	ProWstringCopy(direct_path, mdl_data.path, PRO_VALUE_UNUSED);
	status = ProMdlBackup(new_mdl, &mdl_data);
	if (status != PRO_TK_NO_ERROR) {
		AfxMessageBox(L"模型备份失败");
		return status;
	}
	status = ProjectionAndClip_Intf(&new_mdl);
	if (status != PRO_TK_NO_ERROR) { return status; }
	return status;
}



void dlg_stlimport::OnBnCreateNURBS()
{
	// TODO: 在此添加控件通知处理程序代码
	//
	//	方案1：
	//	1.将triangles转为点云
	//  2.求出最佳参数，存入fit_result
	//	3.将triangles转为有序边界
	//	4.通过点云生成大块NURBS曲面，存入iges中===
	//	5.PCL程序中顺便将有序边界转为Polyline存入3dm中
	//	导入外部模型成新mdl===
	//	进行投影===
	//	进行裁剪====
	//	保存该零件===


	ProError status = PRO_TK_NO_ERROR;
	status = ProMdlEraseNotDisplayed();//擦除未显示的
	if (status != PRO_TK_NO_ERROR) { return; }

	ProMdlName w_name;//零件的名称
	{
		//检测是否本地或模型树中存在该名称零件
		CString name_str;
		GetDlgItem(IDC_EDIT_PART_NAME)->GetWindowText(name_str);
		ProWstringCopy(name_str.GetBuffer(), w_name, PRO_VALUE_UNUSED);
		name_str.ReleaseBuffer();
		ProMdl test_mdl;
		status = ProMdlRetrieve(w_name, PRO_MDL_PART, &test_mdl);
		if (status == PRO_TK_NO_ERROR) {
			AfxMessageBox(L"已存在该名称的零件，请重新输入");
			return;
		}
	}

	CWaitCursor wait;//等待光标

	Startprog();
	SetProgRange(0, 120);
	SetProgPos(0, L"");

	//导出当前选择项对应的iges
	ProMdl new_mdl=NULL;
	CreateFpcPart(new_mdl);
	SetProgPos(120, L"");
	EndProg();


	status = ProSelectionVerify(sel_parent);
	if (status == PRO_TK_NO_ERROR) {
		status = AsmNewMdl(sel_parent, new_mdl);
	}
	else {
		status = ShowMdlInWindow(w_name, new_mdl);
	}

	return;
}


ProError dlg_stlimport::DeleteFeature(ProFeature &feature)
{
	ProError status = PRO_TK_NO_ERROR;
	int *pFeaID = NULL;
	status = ProArrayAlloc(1, sizeof(int), 1, (ProArray*)&pFeaID);
	if (status != PRO_TK_NO_ERROR) { return status; }
	pFeaID[0] = feature.id;

	ProFeatureDeleteOptions *featDeleteOptions;
	status = ProArrayAlloc(1, sizeof(ProFeatureDeleteOptions), 1, (ProArray*)&featDeleteOptions);
	if (status != PRO_TK_NO_ERROR) { return status; }
	featDeleteOptions[0] = PRO_FEAT_DELETE_NO_OPTS;

	status = ProFeatureWithoptionsDelete((ProSolid)feature.owner, pFeaID, featDeleteOptions, PRO_REGEN_NO_FLAGS);
	if (status != PRO_TK_NO_ERROR) { return status; }
	ProArrayFree((ProArray*)&pFeaID);
	ProArrayFree((ProArray*)&featDeleteOptions);
	return status;
}

ProError dlg_stlimport::CreateProjectionUDF(ProMdl *p_mdl, ProjectionLineRingToQuilt& ref_info, ProGroup &udf_group) {

	ProError status = PRO_TK_NO_ERROR;
	ProUdfdata pData;
	status = ProUdfdataAlloc(&pData);
	if (status != PRO_TK_NO_ERROR) { return status; }
	status = ProUdfdataPathSet(pData, ref_info.gph_pos);
	if (status != PRO_TK_NO_ERROR) { return status; }
	// UDF参考
	ProUdfreference udfRef = NULL;

	status = ProUdfreferenceAlloc(_T("投影到的面组"), *(ref_info.quilt_sel), PRO_B_FALSE, &udfRef);
	if (status != PRO_TK_NO_ERROR) { return status; }
	status = ProUdfdataReferenceAdd(pData, udfRef);
	if (status != PRO_TK_NO_ERROR) { return status; }
	status = ProUdfreferenceAlloc(_T("曲线链1"), *(ref_info.curve_1), PRO_B_FALSE, &udfRef);
	if (status != PRO_TK_NO_ERROR) { return status; }
	status = ProUdfdataReferenceAdd(pData, udfRef);
	if (status != PRO_TK_NO_ERROR) { return status; }

	//PRO_QUILT

	ProUdfCreateOption options[] = { PROUDFOPT_FIX_MODEL_UI_OFF };
	status = ProUdfCreate((ProSolid)*p_mdl, pData, NULL, options, 1, &udf_group);
	if (status != PRO_TK_NO_ERROR) { return status; }

	status = ProUdfdataFree(pData);
	if (status != PRO_TK_NO_ERROR) { return status; }
	return status;
}

ProError dlg_stlimport::CreateClipUDF(ProMdl *p_mdl, ClipQuiltByLineRing& ref_info, ProGroup &udf_group) {

	ProError status = PRO_TK_NO_ERROR;
	ProUdfdata pData = NULL;
	status = ProUdfdataAlloc(&pData);
	if (status != PRO_TK_NO_ERROR) { return status; }
	status = ProUdfdataPathSet(pData, ref_info.gph_pos);
	if (status != PRO_TK_NO_ERROR) { return status; }
	// UDF参考
	ProUdfreference udfRef = NULL;

	status = ProUdfreferenceAlloc(_T("要修剪的面组"), *(ref_info.quilt_sel), PRO_B_FALSE, &udfRef);
	if (status != PRO_TK_NO_ERROR) { return status; }
	status = ProUdfdataReferenceAdd(pData, udfRef);
	if (status != PRO_TK_NO_ERROR) { return status; }
	status = ProUdfreferenceAlloc(_T("复合曲线"), *(ref_info.curve_1), PRO_B_FALSE, &udfRef);
	if (status != PRO_TK_NO_ERROR) { return status; }
	status = ProUdfdataReferenceAdd(pData, udfRef);
	if (status != PRO_TK_NO_ERROR) { return status; }

	ProUdfCreateOption options[] = { PROUDFOPT_FIX_MODEL_UI_OFF };
	status = ProUdfCreate((ProSolid)*p_mdl, pData, NULL, options, 1, &udf_group);
	if (status != PRO_TK_NO_ERROR) { return status; }

	status = ProUdfdataFree(pData);
	if (status != PRO_TK_NO_ERROR) { return status; }
	return status;
}

ProErr dlg_stlimport::GetQuiltContour(IN ProQuilt&quilt, OUT vector<int>&vec_ids)
{
	ProErr status = PRO_TK_NO_ERROR;
	vec_ids.resize(0);
	vector<ProSurface> vec_surfaces;
	status = ProQuiltSurfaceVisit(quilt, surfacevisit, NULL, &vec_surfaces);
	if (status != PRO_TK_NO_ERROR) { return status; }
	map<ProSurface, vector<ProContour>> vec_contours;
	for (int i = 0; i < (int)vec_surfaces.size(); i++) {
		vector<ProContour> vec_temp;
		status = ProSurfaceContourVisit(vec_surfaces[i], contourvisit, NULL, &vec_temp);
		if (status != PRO_TK_NO_ERROR) { continue; }
		vec_contours.insert(make_pair(vec_surfaces[i], vec_temp));
	}
	vector<ProEdge> vec_edges;

	for (map<ProSurface, vector<ProContour>>::iterator iter = vec_contours.begin();
		iter != vec_contours.end(); ++iter) {
		for (int i = 0; i < (int)iter->second.size(); ++i) {
			status = ProContourEdgeVisit(iter->first, iter->second[i], edgevisit, NULL, &vec_edges);
			if (status != PRO_TK_NO_ERROR) { continue; }
		}
	}
	for (int i = 0; i < (int)vec_edges.size(); i++) {
		ProEdge p1, p2;
		ProSurface s1, s2;
		status = ProEdgeNeighborsGet(vec_edges[i], &p1, &p2, &s1, &s2);
		if (s1 == NULL || s2 == NULL) {
			int id;
			status = ProEdgeIdGet(vec_edges[i], &id);
			if (status != PRO_TK_NO_ERROR) { continue; }
			vec_ids.push_back(id);
		}
	}
	return status;
}

ProErr dlg_stlimport::ProjectionAndClip_Intf(ProMdl *p_mdl)
{
	// TODO: 在此添加控件通知处理程序代码
	ProError status = PRO_TK_NO_ERROR;
	ProSelection quilt_sel = NULL;//面组sel
	vector<ProQuilt>p_quilts;//面组
	{
		status = PMCollectSolidQuilts((ProSolid)*p_mdl, p_quilts);
		if (status != PRO_TK_NO_ERROR) { return status; }
		if (p_quilts.size() != 1) { return status; }
		ProGeomitem	  geom_item;
		/* Get the quilt sel */
		status = ProQuiltToGeomitem((ProSolid)*p_mdl, p_quilts[0], &geom_item);
		if (status != PRO_TK_NO_ERROR) { return status; }
		status = ProSelectionAlloc(NULL, &geom_item, &quilt_sel);
		if (status != PRO_TK_NO_ERROR) { return status; }
	}

	ProSelection outer_sel = NULL;//外轮廓的一条边
	vector<ProSelection> inner_sels;//内轮廓的一条边
	{
		//思路：3dm导入时，会把一些线段转化为spline线，所以判断
		map<UniqueLine, ProGeomitem> map_line_geom;

		vector<ProGeomitem> curve_geoms;
		//1.首先进行遍历，结果存入map_line_geom
		vector<ProFeature>feat_arr;
		status = PMCollectSolidFeatures((ProSolid)*p_mdl, feat_arr);
		if (status != PRO_TK_NO_ERROR) { return status; }
		for (int i = 0; i < feat_arr.size(); i++) {
			status = ProFeatureGeomitemVisit(&(feat_arr[i]), PRO_CURVE, feat_geoms_visit, NULL, &curve_geoms);
			if (status != PRO_TK_NO_ERROR) { continue; }
		}
		ProArrayFree((ProArray*)(&feat_arr));
		for (int i = 0; i < (int)curve_geoms.size(); i++) {
			ProGeomitemdata *g_itemdata = NULL;
			status = ProGeomitemdataGet(&curve_geoms[i], &g_itemdata);
			if (status != PRO_TK_NO_ERROR ||
				g_itemdata->data.p_curve_data->line.type != PRO_ENT_LINE) {
				continue;
			}
			ProLinedata & ldata = g_itemdata->data.p_curve_data->line;

			UniqueLine u_line(UniquePt(ldata.end1[0], ldata.end1[1], ldata.end1[2]),
				UniquePt(ldata.end2[0], ldata.end2[1], ldata.end2[2]));
			map_line_geom.insert(make_pair(u_line, curve_geoms[i]));//存入map
			ProGeomitemdataFree(&g_itemdata);
		}


		//2.得到外轮廓的一条边
		for (int i = 0; i < (int)stl_info.outer_boundary.size(); i++) {
			UniqueLine line(stl_info.outer_boundary[i], stl_info.outer_boundary[(i + 1) % (int)stl_info.outer_boundary.size()]);
			map<UniqueLine, ProGeomitem>::iterator iter = map_line_geom.find(line);
			if (iter != map_line_geom.end()) {
				status = ProSelectionAlloc(NULL, &(iter->second), &outer_sel);
				if (status == PRO_TK_NO_ERROR) {
					break;
				}
			}
		}
		if (outer_sel == NULL) {
			return status;
		}
		for (int i = 0; i < (int)stl_info.inner_boundary.size(); i++) {
			ProSelection inner_sel = NULL;
			for (int j = 0; j < (int)stl_info.inner_boundary[i].size(); j++) {
				UniqueLine line(stl_info.inner_boundary[i][j],
					stl_info.inner_boundary[i][(j + 1) % (int)stl_info.inner_boundary[i].size()]);
				map<UniqueLine, ProGeomitem>::iterator iter = map_line_geom.find(line);
				if (iter != map_line_geom.end()) {
					status = ProSelectionAlloc(NULL, &(iter->second), &inner_sel);
					if (status == PRO_TK_NO_ERROR) {
						break;
					}
				}
			}
			if (inner_sel != NULL) {
				inner_sels.push_back(inner_sel);
			}
		}
	}

	ProPath proj_path, clip_path, clip2_pos;//3个udf路径
	{
		CString proj_udf_pos, clip_udf_pos, clip2_udf_pos;
		ProPath text_path;
		status = ProToolkitApplTextPathGet(text_path);
		if (status != PRO_TK_NO_ERROR) { return status; }
		proj_udf_pos.Format(L"%s\\data\\fpc_reconstruct\\udf\\%s", text_path, _T("fpc_projection.gph"));
		clip_udf_pos.Format(L"%s\\data\\fpc_reconstruct\\udf\\%s", text_path, _T("fpc_clip.gph"));
		clip2_udf_pos.Format(L"%s\\data\\fpc_reconstruct\\udf\\%s", text_path, _T("fpc_clip_outer.gph"));

		status = ProWstringCopy(proj_udf_pos.AllocSysString(), proj_path, PRO_VALUE_UNUSED);
		if (status != PRO_TK_NO_ERROR) { return status; }
		status = ProWstringCopy(clip_udf_pos.AllocSysString(), clip_path, PRO_VALUE_UNUSED);
		if (status != PRO_TK_NO_ERROR) { return status; }
		status = ProWstringCopy(clip2_udf_pos.AllocSysString(), clip2_pos, PRO_VALUE_UNUSED);
		if (status != PRO_TK_NO_ERROR) { return status; }
	}

	ProGroup outer_group;//外轮廓投影结果组
	vector<ProGroup> inner_groups;//内轮廓的投影结果组


								  //轮廓投影
	ProjectionLineRingToQuilt proj_info;
	proj_info.quilt_sel = &quilt_sel;
	status = ProWstringCopy(proj_path, proj_info.gph_pos, PRO_VALUE_UNUSED);
	if (status != PRO_TK_NO_ERROR) { return status; }
	{
		{ //外轮廓投影group
			proj_info.curve_1 = &outer_sel;
			status = CreateProjectionUDF(p_mdl, proj_info, outer_group);
			if (status != PRO_TK_NO_ERROR) { return status; }
		}
		{ //内轮廓投影
			for (int i = 0; i < (int)inner_sels.size(); i++)
			{
				proj_info.curve_1 = &(inner_sels[i]);
				ProGroup temp;
				status = CreateProjectionUDF(p_mdl, proj_info, temp);
				if (status != PRO_TK_NO_ERROR) { continue; }
				inner_groups.push_back(temp);
			}
		}
	}
	ProSelection outer_compcrv = NULL;//外轮廓投影得到的复合曲线
	vector<ProSelection> inner_compcrvs;//内轮廓投影得到的复合曲线s
	{
		status = RetriveCompCurveFromProjGroup(*p_mdl, outer_group, outer_compcrv);
		if (status != PRO_TK_NO_ERROR) { return status; }
		for (int i = 0; i < (int)inner_groups.size(); i++)
		{
			ProSelection temp = NULL;
			status = RetriveCompCurveFromProjGroup(*p_mdl, inner_groups[i], temp);
			if (status != PRO_TK_NO_ERROR) { continue; }
			inner_compcrvs.push_back(temp);
		}
	}

	//轮廓投影进行修剪,
	//因为修剪方向的不确定性，所以采取如下规则判断
	//初始面组是vector<id> ,先修剪内轮廓，这时，要保证初始面组均在
	//修剪外轮廓时，要保证初始面组均不在

	vector<int> initial_contour;//初始大轮廓
	status = GetQuiltContour(p_quilts[0], initial_contour);//拿到初始轮廓id
	if (status != PRO_TK_NO_ERROR) { return status; }



	for (int i = 0; i < (int)inner_compcrvs.size(); ++i)
	{
		ClipQuiltByLineRing clip_info;
		clip_info.quilt_sel = &quilt_sel;
		status = ProWstringCopy(clip_path, clip_info.gph_pos, PRO_VALUE_UNUSED);
		if (status != PRO_TK_NO_ERROR) { return status; }

		clip_info.curve_1 = &(inner_compcrvs[i]);
		ProGroup clip_group;
		status = CreateClipUDF(p_mdl, clip_info, clip_group);//修剪内轮廓
		if (status != PRO_TK_NO_ERROR) { return status; }

		vector<int> post_contour;//修剪过后的轮廓
		status = GetQuiltContour(p_quilts[0], post_contour);
		if (status != PRO_TK_NO_ERROR) { return status; }

		bool is_all_exist = true;
		for (int j = 0; j < (int)initial_contour.size(); ++j) {
			vector<int>::iterator iter = std::find(post_contour.begin(), post_contour.end(), initial_contour[i]);
			if (iter == post_contour.end()) {
				is_all_exist = false;
				break;
			}
		}
		if (false == is_all_exist) {//说明外面的轮廓有一个不在了
			ProFeature *feat_arr = NULL;
			status = ProGroupFeaturesCollect(&clip_group, &feat_arr);
			if (status != PRO_TK_NO_ERROR) { return status; }
			int feat_cnt = 0;
			status = ProArraySizeGet((ProArray)feat_arr, &feat_cnt);
			if (status != PRO_TK_NO_ERROR) { return status; }
			for (int k = 0; k < feat_cnt; k++)
			{
				DeleteFeature(feat_arr[k]);
			}
			ProArrayFree((ProArray*)&feat_arr);
			status = ProWstringCopy(clip2_pos, clip_info.gph_pos, PRO_VALUE_UNUSED);
			if (status != PRO_TK_NO_ERROR) { return status; }
			status = CreateClipUDF(p_mdl, clip_info, clip_group);//修剪内轮廓
			if (status != PRO_TK_NO_ERROR) { return status; }
		}
	}

	{
		ClipQuiltByLineRing clip_info;
		clip_info.quilt_sel = &quilt_sel;
		status = ProWstringCopy(clip_path, clip_info.gph_pos, PRO_VALUE_UNUSED);
		if (status != PRO_TK_NO_ERROR) { return status; }

		clip_info.curve_1 = &outer_compcrv;
		ProGroup clip_group;
		status = CreateClipUDF(p_mdl, clip_info, clip_group);//修剪外轮廓
		if (status != PRO_TK_NO_ERROR) { return status; }

		vector<int> post_contour;//修剪过后的轮廓
		status = GetQuiltContour(p_quilts[0], post_contour);
		if (status != PRO_TK_NO_ERROR) { return status; }

		bool is_one_exist = false;
		for (int j = 0; j < (int)initial_contour.size(); ++j) {
			vector<int>::iterator iter = std::find(post_contour.begin(), post_contour.end(), initial_contour[j]);
			if (iter != post_contour.end()) {
				is_one_exist = true;
				break;
			}
		}
		if (true == is_one_exist) {//说明外面的轮廓还有一个存在
			ProFeature *feat_arr = NULL;
			status = ProGroupFeaturesCollect(&clip_group, &feat_arr);
			if (status != PRO_TK_NO_ERROR) { return status; }
			int feat_cnt = 0;
			status = ProArraySizeGet((ProArray)feat_arr, &feat_cnt);
			if (status != PRO_TK_NO_ERROR) { return status; }
			for (int k = 0; k < feat_cnt; k++)
			{
				DeleteFeature(feat_arr[k]);
			}
			status = ProWstringCopy(clip2_pos, clip_info.gph_pos, PRO_VALUE_UNUSED);
			if (status != PRO_TK_NO_ERROR) { return status; }
			status = CreateClipUDF(p_mdl, clip_info, clip_group);//修剪外轮廓
			if (status != PRO_TK_NO_ERROR) { return status; }
		}
	}
	if (status != PRO_TK_NO_ERROR) { return status; }
	status = ProMdlSave(*p_mdl);
	if (status != PRO_TK_NO_ERROR) { return status; }

	status = ProWindowRepaint(-1);
	return status;
}

ProError dlg_stlimport::RetriveCompCurveFromProjGroup(ProMdl &mdl, ProGroup&group, OUT ProSelection&comp_curve)
{
	ProError status = PRO_TK_NO_ERROR;
	comp_curve = NULL;

	ProFeature *feat_arr = NULL;
	status = ProGroupFeaturesCollect(&group, &feat_arr);
	if (status != PRO_TK_NO_ERROR) { return status; }
	int feat_cnt = 0;
	status = ProArraySizeGet((ProArray)feat_arr, &feat_cnt);
	if (status != PRO_TK_NO_ERROR) { return status; }
	for (int i = 0; i < feat_cnt; i++) {
		vector<ProGeomitem> curve_geoms;
		status = ProFeatureGeomitemVisit(&(feat_arr[i]), PRO_CURVE, feat_geoms_visit, NULL, &curve_geoms);
		if (status != PRO_TK_NO_ERROR) { continue; }
		for (int j = 0; j < (int)curve_geoms.size(); j++) {
			ProCurve p_curve;//所选曲线
			status = ProCurveInit((ProSolid)mdl, curve_geoms[j].id, &p_curve);
			if (status != PRO_TK_NO_ERROR) { continue; }
			ProEnttype type;
			status = ProCurveTypeGet(p_curve, &type);
			if (status != PRO_TK_NO_ERROR) { continue; }
			if (PRO_ENT_CMP_CRV == type) {//是复合曲线
				status = ProSelectionAlloc(NULL, &curve_geoms[j], &comp_curve);
				if (status != PRO_TK_NO_ERROR) { continue; }
				break;
			}
		}
		if (comp_curve != NULL) {
			break;
		}
	}
	if (comp_curve == NULL) {
		return PRO_TK_E_NOT_FOUND;
	}
	return status;
}

ProError dlg_stlimport::AsmNewMdl(ProSelection& parent, ProMdl & mdl)
{

	// 这里是装配相关代码
	ProError status = PRO_TK_NO_ERROR;
	ProMdl assem_mdl;  // 要装配的组件句柄

	// AfxMessageBox(L"注意:模型单位采用mmgs\n接下来请选择 要装配的标准件 所在的组件.ASM");

	// --- 获取要装配的装配体下
	ProAsmcomppath p_cmp_path;
	status = ProSelectionAsmcomppathGet(parent, &p_cmp_path);
	if (status != PRO_TK_NO_ERROR) { return status; }
	ProMdl asm_mdl;
	status = ProMdlCurrentGet(&asm_mdl);
	if (status != PRO_TK_NO_ERROR) { return status; }
	ProAsmcomppath assem_path;  // 要装配的组件 路径
	status = ProAsmcomppathInit((ProSolid)asm_mdl, p_cmp_path.comp_id_table, p_cmp_path.table_num, &assem_path);
	if (status != PRO_TK_NO_ERROR) { return status; }
	status = ProAsmcomppathMdlGet(&assem_path, &assem_mdl);
	if (status != PRO_TK_NO_ERROR) { return status; }


	ProMatrix identity_matrix = { { 1.0, 0.0, 0.0, 0.0 },
	{ 0.0, 1.0,0.0,0.0 },
	{ 0.0, 0.0,1.0,0.0 },
	{ 0.0, 0.0,0.0,1.0 }
	};

	ProAsmcomp asmcomp;  // 保存添加入组件中的元件

	// --- 将零件添加到组件的初始位置
	status = ProAsmcompAssemble(ProAssembly(assem_mdl), (ProSolid)mdl, identity_matrix, &asmcomp);
	if (status != PRO_TK_NO_ERROR) { return status; }
	status = ProAsmcompConstrRedefUI(&asmcomp);
	if (status != PRO_TK_NO_ERROR) { return status; }
	return status;
}

ProError dlg_stlimport::ShowMdlInWindow(wchar_t* w_name, ProMdl & mdl)
{
	ProError status = PRO_TK_NO_ERROR;
#if 1  // 显示出来
	int windowid;
	status = ProObjectwindowMdlnameCreate(w_name, PRO_PART, &windowid);
	if (status != PRO_TK_NO_ERROR) { return status; }
	status = ProMdlDisplay(mdl);
	if (status != PRO_TK_NO_ERROR) { return status; }
	status = ProWindowCurrentSet(windowid);
	if (status != PRO_TK_NO_ERROR) { return status; }
	status = ProWindowActivate(windowid);
	if (status != PRO_TK_NO_ERROR) { return status; }
#endif
	return status;
}


void dlg_stlimport::updateFitSurfaceProcess(int value)
{
	SetProgPos(value, L"");
	return;
}
void dlg_stlimport::SetProgRange(int low, int top)
{
	SendMsgToProg(MSG_RANGE, top, L"");
}

void dlg_stlimport::SetProgPos(int pos, CString strMsg)
{
	SendMsgToProg(MSG_POS, pos, strMsg);
}

void dlg_stlimport::SendMsgToProg(msg_type type, int pos, CString str)
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
	if (sData != NULL) {
		delete(sData);
	}
}

//启动进程条
bool dlg_stlimport::Startprog()
{
	ProError status;
	ProPath text_path;
	status = ProToolkitApplTextPathGet(text_path);
	if (status != PRO_TK_NO_ERROR) { return false; }
	CString exeDir;
	exeDir.Format(L"%s\\data\\fpc_reconstruct\\FitSurfaceProgress.exe", text_path);

	ShellExecuteW(NULL, L"open", exeDir, NULL, NULL, SW_SHOWNORMAL);
	Sleep(2000);
	pWindow = CWnd::FindWindow(NULL, L"逆向造型最优参数计算中");
	if (pWindow)
	{
		return true;
	}
	return false;
}

//结束进程条
void dlg_stlimport::EndProg()
{
	Sleep(500);
	SendMsgToProg(MSG_END, 0, L"");
}


void dlg_stlimport::OnBnClickedSelParent()
{
	// TODO: 在此添加控件通知处理程序代码
	ProError status = PRO_TK_NO_ERROR;
	GetDlgItem(IDC_EDIT_PARENT_NAME)->SetWindowText(L"");//设置EDIT
	ProMode mode;
	status = ProModeCurrentGet(&mode);
	if (mode != PRO_MODE_ASSEMBLY) {
		return;
	}
	int n_sel;
	ProSelection *sel = NULL;
	status = ProSelect((char *)"prt_or_asm", 1, NULL, NULL, NULL, NULL, &sel, &n_sel);
	if (status != PRO_TK_NO_ERROR || n_sel != 1) {
		return;
	}
	ProModelitem item;
	status = ProSelectionModelitemGet(sel[0], &item);
	if (status != PRO_TK_NO_ERROR || item.type != PRO_ASSEMBLY) { return; }
	status = ProSelectionCopy(sel[0], &sel_parent);
	if (status != PRO_TK_NO_ERROR) { return; }

	ProName mdlname;
	status = ProMdlNameGet(item.owner, mdlname);
	if (status != PRO_TK_NO_ERROR) { return; }

	GetDlgItem(IDC_EDIT_PARENT_NAME)->SetWindowText((CString)mdlname);//设置EDIT
}


void dlg_stlimport::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	return;
	__super::OnOK();
}
