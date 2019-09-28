#pragma once
#include "TKInclude.h"
#include "Public_fun.h"
#include "resource.h"
#include"type.h"
#include"list"
#include"vector"
#include"FitSurface.h"
#include"FPCBaseMath.h"
using namespace std;
using namespace Contour;

//投影环到面组的UDF创建结构
struct ProjectionLineRingToQuilt {
	ProPath gph_pos;
	ProSelection*quilt_sel;//面组
	ProSelection *curve_1;//环上一条曲线
};

//用环修剪面组,保留内部的的UDF创建结构
struct ClipQuiltByLineRing {
	ProPath gph_pos;
	ProSelection*quilt_sel;//面组
	ProSelection *curve_1;//环的sel，类型为复合曲线
};

struct STLInfo{
	vector<Triangle> triangles;//STL文件读出的三角形 <<input
	vector<Point3> cloud;//点云   >>output
	vector<Point3> normals;//法向集    >>output
	vector<Point3>outer_boundary;//外轮廓    >>output
	vector<vector<Point3>> inner_boundary;//内轮廓   >>output

	void Clear() {
		triangles.clear();
		cloud.clear();
		normals.clear();
		outer_boundary.clear();
		inner_boundary.clear();
	}
};
//定时器2001传递的结构
struct ONTIME_2001 {
	ProSelection parent_sel;//选择的父装配
	ProMdl mdl;//SetTimer时传递的mdl句柄
	int new_windowid;//new_mdl的窗口id
	int old_windowid;//之前窗口的id
	CString pos_3dm;//3dm存储的位置
};

// dlg_stlimport 对话框

class dlg_stlimport : public CDialogEx,public FitSurfaceObserver
{
	DECLARE_DYNAMIC(dlg_stlimport)

public:
	dlg_stlimport(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~dlg_stlimport();

	void dlg_stlimport::usermain();
	//获取含有关键字的STL装配组件，如果没有，不能导入 
	void dlg_stlimport::userGetSTLasm(CString& csSTLasmPath);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG9 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	bool isNameLegalToCreo(CString nameWithOutExt);
	bool UserSelectFile(IN CString Filter, IN CString InitalDir, IN CString caption, OUT CString & fileName);
	void OnBnUserSelectSTL();


	ProError CreateFpcPart(OUT ProMdl&new_mdl);//总--


	afx_msg void OnBnCreateNURBS();

	ProError DeleteFeature(ProFeature & feature);

	ProError CreateProjectionUDF(ProMdl * p_mdl, ProjectionLineRingToQuilt & ref_info, ProGroup & udf_group);

	ProError CreateClipUDF(ProMdl * p_mdl, ClipQuiltByLineRing & ref_info, ProGroup & udf_group);

	ProErr GetQuiltContour(IN ProQuilt & quilt, OUT vector<int>& vec_ids);

	ProErr ProjectionAndClip_Intf(ProMdl * p_mdl);//对导入的特征进行投影和裁剪

	ProError RetriveCompCurveFromProjGroup(ProMdl & mdl, ProGroup & group, OUT ProSelection & comp_curve);

	ProError AsmNewMdl(ProSelection& parent, ProMdl & mdl);
	ProError ShowMdlInWindow(wchar_t* w_name, ProMdl & mdl);
private:
	vector<FitSurface::CalcResult> fit_result;//最终拟合结果

	void updateFitSurfaceProcess(int value);
private:
	STLInfo stl_info;
	ProSelection sel_parent;//选择的父装配
private: //用来显示进度条的
	enum msg_type { MSG_RANGE, MSG_POS, MSG_STRING, MSG_BOTH, MSG_END };
	//type 1:range 2:pos 3:msg 4:pos&&msg 5:end
	struct send_data
	{
		msg_type type;
		TCHAR msg[100];
		int pos;
	};
	//进度条窗口
	CWnd* pWindow;
	void SetProgRange(int low, int top);
	void SetProgPos(int pos, CString strMsg);
	void SendMsgToProg(msg_type type, int pos, CString str);
	bool Startprog();
	void EndProg();
public:
	afx_msg void OnBnClickedSelParent();
	virtual void OnOK();
};
