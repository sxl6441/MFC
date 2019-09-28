#pragma once
#include"type.h"
#include <fitting_surface_tdm.h>
#include<Eigen/StdVector>
#include<opennurbs_polyline.h>
#include<nurbs_data.h>
#include"opencascade.h"
using namespace pcl::on_nurbs;
using namespace Contour;
class FitSurfaceObserver
{
public:
	FitSurfaceObserver() {};
	~FitSurfaceObserver() {};
	virtual void updateFitSurfaceProcess(int value) = 0;
};
class FitSurface
{
public:
	FitSurface() :m_state(0) ,m_min(0),m_max(100){}
	//拟合的参数设置
	typedef struct _fit_parameter {
		unsigned order; //阶数
		unsigned refinement;//细化次数
		unsigned iterations;//迭代次数

		double interior_smoothness;//表面内部的光滑度。
		double interior_weight;//为表面内部优化的权重

		double boundary_smoothness;//曲面边界的平滑度。
		double boundary_weight;//曲面边界优化的权重。

		double expand_value;//初始化样条曲面时要扩张的大小
		_fit_parameter(){
			order = 3;
			refinement = 5;
			iterations = 10;

			interior_smoothness = 0.3;
			interior_weight = 1.0;
			boundary_smoothness = 0.3;
			boundary_weight = 1.0;

			expand_value = 3.0;
		}
	}fit_parameter;

	//计算结构存储
	struct CalcResult {
		fit_parameter par;
		ON_NurbsSurface nurbs;
		double tol;
		bool operator<(const CalcResult&another)const{
			return tol < another.tol;
		}
	};
public:
	//该函数实为static ，为了观察者模式，改为非static
	//@vec_pts 点云
	//@expand_value 面扩张大小
	//@result 拟合参数推算结果存储
	 bool FindOptimalParameter(IN const vector<Point3>& vec_pts, IN double expand_value,
		OUT vector<CalcResult> &result);

	//@nurbs nurbs曲面
	//@lines 多条闭合环
	//@file_save_pos 3dm文件存储的位置--存有样条曲面和多条闭合环
	static bool WriteTo3dm(IN const ON_NurbsSurface& nurbs, IN const vector<vector<Point3>>& lines,
		IN CString file_save_pos);
	//@nurbs nurbs曲面
	//@lines 多条闭合环
	//@file_save_pos 3dm文件存储的位置--存有样条曲面和多条闭合环
	static bool WriteToIges(IN const ON_NurbsSurface& nurbs, IN const vector<vector<Point3>>& lines,
		IN CString file_save_pos);
	//保存为iges文件
	static Standard_Boolean SaveIGES(const Standard_CString & aFileName, const Handle(TopTools_HSequenceOfShape)& aHSequenceOfShape);
//
public:
	void set_range(int min, int max);
	void attach(FitSurfaceObserver* observer);
	void detach(FitSurfaceObserver* observer);
	void notify();
	void set_state(int state);
private:
	std::list<FitSurfaceObserver*> m_list;
	int m_state;
	int m_min;
	int m_max;
private:
	//
	
	//@
	static bool Find4Corners(IN const vector_vec3d &m_data, IN double expand_value,
		OUT ON_3dPoint&ll, OUT ON_3dPoint&lr, OUT ON_3dPoint&ur, OUT ON_3dPoint&ul);
	//@vec_3d点云
	//@lines 多条闭合环
	//@fit_par 拟合参数
	//@file_save_pos 3dm文件存储的位置--存有样条曲面和多条闭合环
	static bool FitSurfaceByPar(IN const vector<Point3>& vec_pts, IN const vector<vector<Point3>>& lines,
		IN const fit_parameter & fit_par, IN CString file_save_pos);
	/**
	* @breif Convert OpenNURBS NURBS surface to OpenCASCADE Geom_BSplineSurface.
	* @param [in] theSurface opennurbs nurbs surface;
	* @param [in] aBSplineSurface opencascade nurbs surfacesurface;
	* @note pay attention to the knots of opennurbs nurbs curve/surface.
	*/
	static bool ConvertSurface(const ON_NurbsSurface& theSurface, Handle_Geom_BSplineSurface&aBSplineSurface);
};

