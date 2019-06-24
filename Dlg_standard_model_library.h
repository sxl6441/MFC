#pragma once
#include "afxcmn.h"
#include "stdafx.h"
#include "pviewctrl1.h"
#include "ListCtrlEx.h"

#include "JWG_Util_model_library.h"

#include <map>
#include <algorithm>
#include <iterator>
#include <iostream>  // pair要使用的头文件

// gdiplus要用的文件
#include <afxdtctl.h>
#include "gdiplus.h"
#include "afxwin.h"
#include "PngButton.h"
#include "afxwin.h"

// using namespace Gdiplus;
// Dlg_standard_model_library 对话框

class Dlg_standard_model_library : public ClxDialog {
    DECLARE_DYNAMIC(Dlg_standard_model_library)

public:
    Dlg_standard_model_library(CWnd *pParent = NULL);  // 标准构造函数
    virtual ~Dlg_standard_model_library();

    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DIALOG_sml_main };
#endif

protected:
    virtual void DoDataExchange(CDataExchange *pDX);  // DDX/DDV 支持
    virtual BOOL OnInitDialog();  // 初始化
private:
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg BOOL OnEraseBkgnd(CDC *pDC);
    afx_msg LRESULT OnNcHitTest(CPoint point);  // 拖动窗口
    afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
    afx_msg void OnNMKillfocusList1(NMHDR *pNMHDR, LRESULT *pResult);  // PicList
    afx_msg void OnNMSetfocusList1(NMHDR *pNMHDR, LRESULT *pResult);  // PicList
    afx_msg void OnNMKillfocusTree1(NMHDR *pNMHDR, LRESULT *pResult);  // TreeCtrl
    afx_msg void OnNMSetfocusTree1(NMHDR *pNMHDR, LRESULT *pResult);  // TreeCtrl

    afx_msg LRESULT OnRedraw(WPARAM wParam, LPARAM lParam);  // listctrl 列表控件重画
    afx_msg LRESULT OnEditClick(WPARAM wParam, LPARAM lParam);  // listctrl edit编辑完成后相应消息
    afx_msg LRESULT OnResClick(WPARAM wParam, LPARAM lParam);  // listctrl edit单击相应消息

    afx_msg void OnRclickTree1(NMHDR *pNMHDR, LRESULT *pResult);  // 右键树控件响应函数
    afx_msg void OnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);  // 树控件选择项改变响应函数
    afx_msg void OnClickPicList1(NMHDR *pNMHDR, LRESULT *pResult);  // 图片控件点击响应消息
    afx_msg void OnCbnSelchangeCombo1();  // 切换显示方式响应消息

    afx_msg void OnMenuDeleteNode();  // 删除节点--菜单
    afx_msg void OnMenuAddContent();  // 新增子类--菜单
    afx_msg void OnMenuAddModel();  // 新增标准件--菜单
    afx_msg void OnMenuSetAttris();  // 设置属性--菜单
    afx_msg void On32779();  // 修改目录名称--菜单
    afx_msg void OnShow3DView();  // 目前为不显示3D图，设置为显示3D图-菜单
    afx_msg void OnHide3DView();  // 目前为显示3D图，设置为不显示3D图-菜单
    afx_msg void OnModelCut();  // 剪切菜单
    afx_msg void OnModelPaste();  // 粘贴菜单

    afx_msg void OnBnClickedButton2();  // 最小化按钮
    afx_msg void OnBnClickedButton18();  // 关闭按钮
    afx_msg void OnBnClickedButton4();  // 折叠按钮
    afx_msg void OnBnClickedButton1();  // 装配按钮
    afx_msg void OnBnClickedButton7();  // 打开模型按钮
    afx_msg void OnBnClickedButton3();  // 搜索按钮
    afx_msg void OnBnClickedButton5();  // 导出excel
    afx_msg void OnBnClickedButton6();  // 管理员登录

    DECLARE_MESSAGE_MAP()
private:  // 控件变量
    CTreeCtrl m_treectrl;  // 树控件变量
    CListCtrl m_piclist;  // 图片显示控件
    ListCtrlEx::CListCtrlEx m_listctrl;  // 单个标准件显示控件
    CPviewctrl1 m_Creoview;  // creoview显示控件
    CString m_searchEdit;  // 搜索框的变量
    CString m_SearchEdit2;  // 第二个搜索框
    CPngButton m_BtnMin;  // 最小化按钮
    CPngButton m_BtnClosed;  // 关闭按钮
    CComboBox m_ComboBox;  // 显示方式ComboBox控件变量
    CComboBox m_AndOrCombo;  // 搜索与或ComboBox
    // m_adminInfo;				//edit（readonly）显示权限信息
private:
    enum PicOrList {
        SML_PIC_60 = 1,  // 显示的是图片60*60
        SML_PIC_90 = 2,  // 显示的是图片90*90
        SML_LIST = 3  // 显示的是list
    };
    CWitCheckDataBase SqlDataOp;  // 数据库操作对象
    int max_primary_key;  // 目前的模型数据库中primary key的最大值

    HTREEITEM SelectedNode;  // 树控件中被选中的目录或者被选中的零件（为了piclist进行高亮）
    HTREEITEM SelectedContent;  // 树控件中被选中的目录或者被选中的零件的父目录。(为了piclist的显示)

    CString CutPasteContent;  // 存储着被剪切的标准件的路径信息

    vector<HTREEITEM> PicCorrTree;  // piclist控件上显示的图像对应的树节点,下标为row
    std::map<HTREEITEM, jwg_utl::ordered_stand_model> map_htree_model;  // key为树节点HTREEITEM,value为ordered_stand_model结构体

    // 图片相关
    CImageList m_Imagelist;  // 图片控件的显示列表
    CImageList m_imagelist1;  // 树控件节点图片
    CImage m_ImgBK;
    HICON m_hIcon;
    CBitmap BlankBitmap60;  // 空的Bitmap
	CBitmap BlankBitmap90;  // 空的Bitmap
private:
    void FillTree(vector<jwg_utl::ordered_stand_model> &OrderModelInfo);  // 填充树控件
    void OrderTreeLastLevelByAlphabet();  // 将树控件最后一级按照字母排序
    void OrderContent(HTREEITEM hTree);  // 将该节点下的节点进行排序
    void ListShowPic(int GivenWidth);  // 将piclist显示为图片样式
    void ListShowReport();  // 将piclist显示为列表样式
    void PerformSearch(IN vector<HTREEITEM> &vec_item, IN CString SearchText,
                       OUT vector<HTREEITEM> &result);  // 寻找符合要求的树节点
    void UserSelectFiles(IN CString Filter, IN CString InitalDir, IN CString caption,
                         OUT vector<CString> &AllSelectedFilePath);  // 用户选择文件
    CString SelFilePath(CString caption);  // 用户选择文件夹，返回文件夹路径
private:
    ULONG_PTR m_pGdiToken;  // GdiPlus变量
    virtual void OnOK();

private:
    int m_PicSelectedItemIndex;  // 用来一直显示PicList选中状态的
    HTREEITEM m_TreeSelectedItemIndex;  // 用来一直显示TreeList选中状态的

    // 根据树节点对应的数据和目前的登录状态，判断是否有操作权限。
    bool JudgePermission(enum Category perm, HTREEITEM item);
    void UpdateLoginInfo();  // 更新登录信息
    void TempFillInfo();
	void CreateBlankBitmap(CBitmap & bm, int width);
	bool VerifyNodeIsExist(HTREEITEM nowNode);  // 检查nowNode节点是否在数据库和map中存在，是否可以在其下增加子类或者标准件

    HTREEITEM PreContent;  // 前一个SelectedContent,避免PicList重画
    PicOrList PreShow;  // PicList前一个显示的是List还是Picture60,Picture90,避免PicList重画
public:
};
