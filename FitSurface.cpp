#include "stdafx.h"
#include "FitSurface.h"
#include "UtilMatrix.h"

bool FitSurface::FitSurfaceByPar(IN const vector<Point3>& vec_pts, IN const vector<vector<Point3>>& lines,
	IN const fit_parameter & fit_par, IN CString file_save_pos)
{

	if (vec_pts.size() == 0 || file_save_pos.IsEmpty()) {
		return false;
	}
	pcl::on_nurbs::NurbsDataSurface data;

	for (unsigned i = 0; i < vec_pts.size(); i++)
	{
		const Point3 &p = vec_pts[i];
		if (!_isnan(p.x()) && !_isnan(p.y()) && !_isnan(p.z()))
			data.interior.push_back(Eigen::Vector3d(p.x(), p.y(), p.z()));//这是将所有点云xyz数据转为vector_vec3d格式的内部点
	}

	// fit B-spline surface
	// parameters
	unsigned order = fit_par.order;
	unsigned refinement = fit_par.refinement;
	unsigned iterations = fit_par.iterations;

	pcl::on_nurbs::FittingSurface::Parameter params;
	params.interior_smoothness = fit_par.interior_smoothness;//表面内部的光滑度。0.2
	params.interior_weight = fit_par.interior_weight;//为表面内部优化的权重1.0

	params.boundary_smoothness = fit_par.boundary_smoothness;//曲面边界的平滑度。0.2
	params.boundary_weight = fit_par.boundary_weight;//表面边界优化的权重。1.0

	ON_3dPoint ll, lr, ur, ul;
	Find4Corners(data.interior, fit_par.expand_value, ll, lr, ur, ul);

	ON_NurbsSurface nurbs = pcl::on_nurbs::FittingSurface::initNurbs4Corners(order, ll, lr, ur, ul);

	/*表面拟合类pcl :: on_nurbs :: FittingSurface用点数据和初始B样条初始化。*/
	pcl::on_nurbs::FittingSurface fit(&data, nurbs);

	fit.setQuiet(true); // enable/disable debug output

	// surface refinement
	for (unsigned i = 0; i < refinement; i++)
	{
		fit.refine(0);
		fit.refine(1);
		fit.assemble(params);
		fit.solve();
	}


	// surface fitting with final refinement level
	for (unsigned i = 0; i < iterations; i++)
	{
		fit.assemble(params);
		fit.solve();
	}
	double max_dis = 0;
	for (int i = 0; i < (int)data.interior_error.size(); i++) {
		max_dis = max(max_dis, data.interior_error[i]);
	}
	//return false;
	if (fit.m_nurbs.IsValid())
	{
		int layer_index = 1;


		ONX_Model model;
		ONX_Model_Object& surf = model.m_object_table.AppendNew();
		surf.m_object = new ON_NurbsSurface(fit.m_nurbs);
		//surf.m_bDeleteObject = true;
		surf.m_attributes.m_layer_index = layer_index;
		surf.m_attributes.m_name = _T("surface");

		for (int i = 0; i < (int)lines.size(); i++) {
			int _size = (int)lines[i].size();
			if (_size < 3) { continue; }

			ON_3dPointArray *pt_arr = new ON_3dPointArray(_size + 1);
			for (int j = 0; j < _size; j++) {
				const Point3&temp = lines[i][j];
				pt_arr->Append(ON_3dPoint(temp.x(), temp.y(), temp.z()));
			}
			pt_arr->Append(ON_3dPoint(lines[i][0].x(), lines[i][0].y(), lines[i][0].z()));
			ON_PolylineCurve*temp = new ON_PolylineCurve(*pt_arr);
			if (temp->IsValid()) {
				ONX_Model_Object&line = model.m_object_table.AppendNew();
				line.m_object = new ON_PolylineCurve(*pt_arr);
				//line.m_bDeleteObject = true;
				line.m_attributes.m_layer_index = ++layer_index;//=====
				line.m_attributes.m_name = _T("polyline");
			}

		}
		model.Polish(); // fill in defaults as needed.

		if (!model.IsValid())
		{
			// try to repair the model
			model.Audit(true, NULL, NULL, NULL);
		}
		if (model.IsValid())
		{
			bool ret = model.Write(file_save_pos.AllocSysString());
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	return true;
}

bool FitSurface::ConvertSurface(const ON_NurbsSurface & theSurface, Handle_Geom_BSplineSurface & aBSplineSurface)
{
	TColgp_Array2OfPnt aPoles(1, theSurface.CVCount(0), 1, theSurface.CVCount(1));
	TColStd_Array2OfReal aWeights(1, theSurface.CVCount(0), 1, theSurface.CVCount(1));

	TColStd_Array1OfReal aUKnotSequence(1, theSurface.KnotCount(0) + 2);
	TColStd_Array1OfReal aVKnotSequence(1, theSurface.KnotCount(1) + 2);

	bool IsRational = theSurface.IsRational();
	bool IsUPeriodic = (theSurface.IsPeriodic(0)) ? true : false;
	bool IsVPeriodic = (theSurface.IsPeriodic(1)) ? true : false;

	// control point and its weight.
	for (int i = 0; i < theSurface.CVCount(0); ++i)
	{
		for (int j = 0; j < theSurface.CVCount(1); ++j)
		{
			if (IsRational)
			{
				ON_4dPoint aPole;

				theSurface.GetCV(i, j, aPole);

				aPoles.SetValue(i + 1, j + 1, gp_Pnt(aPole.x / aPole.w, aPole.y / aPole.w, aPole.z / aPole.w));
				aWeights.SetValue(i + 1, j + 1, aPole.w);
			}
			else
			{
				ON_3dPoint aPole;

				theSurface.GetCV(i, j, aPole);

				aPoles.SetValue(i + 1, j + 1, gp_Pnt(aPole.x, aPole.y, aPole.z));
				aWeights.SetValue(i + 1, j + 1, 1);
			}

		}
	}

	// Knot vector and its multiplicity.
	for (int i = 0; i < theSurface.KnotCount(0); ++i)
	{
		aUKnotSequence.SetValue(i + 2, theSurface.Knot(0, i));
	}

	aUKnotSequence.SetValue(aUKnotSequence.Lower(), theSurface.Knot(0, 0));
	aUKnotSequence.SetValue(aUKnotSequence.Upper(), theSurface.Knot(0, theSurface.KnotCount(0) - 1));

	TColStd_Array1OfReal aUKnots(1, BSplCLib::KnotsLength(aUKnotSequence, IsUPeriodic));
	TColStd_Array1OfInteger aUMults(1, aUKnots.Upper());

	BSplCLib::Knots(aUKnotSequence, aUKnots, aUMults);

	for (int j = 0; j < theSurface.KnotCount(1); ++j)
	{
		aVKnotSequence.SetValue(j + 2, theSurface.Knot(1, j));
	}

	aVKnotSequence.SetValue(aVKnotSequence.Lower(), theSurface.Knot(1, 0));
	aVKnotSequence.SetValue(aVKnotSequence.Upper(), theSurface.Knot(1, theSurface.KnotCount(1) - 1));

	TColStd_Array1OfReal aVKnots(1, BSplCLib::KnotsLength(aVKnotSequence, IsVPeriodic));
	TColStd_Array1OfInteger aVMults(1, aVKnots.Upper());

	BSplCLib::Knots(aVKnotSequence, aVKnots, aVMults);

	//数据转换完成，开始构造opencascade的面
	try {
		aBSplineSurface = new Geom_BSplineSurface(aPoles,
			aWeights, aUKnots, aVKnots, aUMults, aVMults,
			theSurface.Degree(0), theSurface.Degree(1),
			IsUPeriodic, IsVPeriodic);
	}
	catch (Standard_ConstructionError& e) {
		cout << e.GetMessageString() << endl;
		return false;
	}
	return true;
}



bool FitSurface::FindOptimalParameter(IN const vector<Point3>& vec_pts, IN double expand_value,
	OUT vector<CalcResult> &result)
{
	if (vec_pts.size() == 0) {
		return false;
	}
	set_state(0);
	notify();
	result.resize(0);
	pcl::on_nurbs::NurbsDataSurface data;
	for (unsigned i = 0; i < vec_pts.size(); i++)
	{
		const Point3 &p = vec_pts[i];
		if (!_isnan(p.x()) && !_isnan(p.y()) && !_isnan(p.z()))
			data.interior.push_back(Eigen::Vector3d(p.x(), p.y(), p.z()));//这是将所有点云xyz数据转为vector_vec3d格式的内部点
	}
	ON_3dPoint ll, lr, ur, ul;
	Find4Corners(data.interior, expand_value, ll, lr, ur, ul);//就算自动计算还是需要扩张大小的

	vector<fit_parameter> vec_par;//计算参数集

	fit_parameter temp;
	temp.boundary_weight = 1.0;
	temp.interior_weight = 1.0;
#if 1  //最佳结果为order =3,refinement=7.iterations为9--11均可
	//这样只需计算两次即可
	for (double interior_smoothness = 0.2; interior_smoothness <= 0.2; interior_smoothness += 0.1) {
		temp.interior_smoothness = interior_smoothness;
		for (double boundary_smoothness = 0.2; boundary_smoothness <= 0.2; boundary_smoothness += 0.1) {
			temp.boundary_smoothness = boundary_smoothness;
			for (int order = 3; order < 4; order++) {//阶数为3 若生不成，可以order>=4  *1
				temp.order = order;
				for (unsigned refinement = 7; refinement >5; refinement--) {//*2
					temp.refinement = refinement;
					for (unsigned iterations = 9; iterations < 10; iterations++) {//*1
						temp.iterations = iterations;
						vec_par.emplace_back(temp);
					}
				}
			}
		}
	}
#endif

#if 0
	for (unsigned int ss = 5; ss < 6; ss++) {
		temp.interior_smoothness = 0.2;
		temp.boundary_smoothness = 0.2;
		temp.order = 3;
		temp.refinement = 7;
		temp.iterations = 9;
		vec_par.emplace_back(temp);
	}
#endif
	// fit B-spline surface
	for (int i = 0; i < (int)vec_par.size(); i++) {
		ON_NurbsSurface nurbs = pcl::on_nurbs::FittingSurface::initNurbs4Corners(vec_par[i].order, ll, lr, ur, ul);

		/*表面拟合类pcl :: on_nurbs :: FittingSurface用点数据和初始B样条初始化。*/
		pcl::on_nurbs::FittingSurface fit(&data, nurbs);
		fit.setQuiet(true); // enable/disable debug output
		// parameters
		pcl::on_nurbs::FittingSurface::Parameter params;
		params.interior_smoothness = vec_par[i].interior_smoothness;//表面内部的光滑度
		params.interior_weight = vec_par[i].interior_weight;//为表面内部优化的权重
		params.boundary_smoothness = vec_par[i].boundary_smoothness;//曲面边界的平滑度
		params.boundary_weight = vec_par[i].boundary_weight;//表面边界优化的权重

															// surface refinement
		for (unsigned j = 0; j < vec_par[i].refinement; j++)
		{
			fit.refine(0);
			fit.refine(1);
			fit.assemble(params);
			fit.solve();
		}
		// surface fitting with final refinement level
		for (unsigned j = 0; j < vec_par[i].iterations; j++)
		{
			fit.assemble(params);
			fit.solve();
		}
		if (fit.m_nurbs.IsValid()) {
			double max_dis = 0;
			for (int j = 0; j < (int)data.interior_error.size(); j++) {
				max_dis = max(max_dis, data.interior_error[j]);
			}
			CalcResult temp;
			temp.par = vec_par[i];
			temp.nurbs = fit.m_nurbs;
			temp.tol = max_dis;
			result.push_back(temp);//存入结果
#if 1 //当差距小于0.01时，不再计算
			if (max_dis < 0.01) {
				break;
			}
#endif
		}
		int pos = (i*1.0 / vec_par.size())* (m_max - m_min) + m_min;
		set_state(pos);
		notify();
	}
	set_state(m_max);
	notify();
	return true;
}

bool FitSurface::WriteTo3dm(IN const ON_NurbsSurface & nurbs, IN const vector<vector<Point3>>& lines, IN CString file_save_pos)
{
	if (!nurbs.IsValid()) {
		return false;
	}

	int layer_index = 1;
	ONX_Model model;
	ONX_Model_Object& surf = model.m_object_table.AppendNew();
	surf.m_object = new ON_NurbsSurface(nurbs);
	//surf.m_bDeleteObject = true;
	surf.m_attributes.m_layer_index = layer_index;
	surf.m_attributes.m_name = _T("surface");

	for (int i = 0; i < (int)lines.size(); i++) {
		int _size = (int)lines[i].size();
		if (_size < 3) { continue; }

		ON_3dPointArray *pt_arr = new ON_3dPointArray(_size + 1);
		for (int j = 0; j < _size; j++) {
			const Point3&temp = lines[i][j];
			pt_arr->Append(ON_3dPoint(temp.x(), temp.y(), temp.z()));
		}
		pt_arr->Append(ON_3dPoint(lines[i][0].x(), lines[i][0].y(), lines[i][0].z()));
		ON_PolylineCurve*temp = new ON_PolylineCurve(*pt_arr);
		if (temp->IsValid()) {
			ONX_Model_Object&line = model.m_object_table.AppendNew();
			line.m_object = new ON_PolylineCurve(*pt_arr);
			//line.m_bDeleteObject = true;
			line.m_attributes.m_layer_index = ++layer_index;//=====
			line.m_attributes.m_name = _T("polyline");
		}

	}
	model.Polish(); // fill in defaults as needed.

	if (!model.IsValid())
	{
		// try to repair the model
		model.Audit(true, NULL, NULL, NULL);
	}
	if (model.IsValid())
	{
		bool ret = model.Write(file_save_pos.AllocSysString());
	}
	else {
		return false;
	}
	return true;
}

bool FitSurface::WriteToIges(IN const ON_NurbsSurface & nurbs, IN const vector<vector<Point3>>& lines, IN CString file_save_pos)
{
	Handle_Geom_BSplineSurface  aBSplineSurface = NULL;
	bool ret = ConvertSurface(nurbs, aBSplineSurface);
	if (false == ret) {
		return false;
	}

	TopoDS_Face aFace = BRepBuilderAPI_MakeFace(aBSplineSurface, Precision::Confusion());


	if (!BRepAlgo::IsValid(aFace)) {
		cout << "曲面无效" << endl;
		return false;
	}

	Handle(TopTools_HSequenceOfShape) aHSequenceOfShape = new TopTools_HSequenceOfShape;
	aHSequenceOfShape->Append(aFace);


	//gp_Pnt p1(1, 1, 1);
	//gp_Pnt p2(50, 50, 50);
	//TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(p1, p2);
	//aHSequenceOfShape->Append(aEdge);


	for (int i = 0; i < (int)lines.size(); i++) {
		int nsize = (int)lines[i].size();
		if (nsize < 3) { continue; }
		for (int j = 0; j < lines[i].size(); j++) {
			int after = (j + 1) % nsize;
			gp_Pnt p1(lines[i][j].x(), lines[i][j].y(), lines[i][j].z());
			gp_Pnt p2(lines[i][after].x(), lines[i][after].y(), lines[i][after].z());
			TopoDS_Edge aEdge = BRepBuilderAPI_MakeEdge(p1, p2);
			aHSequenceOfShape->Append(aEdge);
		}
	}

	TCollection_AsciiString aFileName(file_save_pos.GetBuffer());
	file_save_pos.ReleaseBuffer();
	SaveIGES(aFileName.ToCString(), aHSequenceOfShape);

	return true;
}
Standard_Boolean FitSurface::SaveIGES(const Standard_CString& aFileName,
	const Handle(TopTools_HSequenceOfShape)& aHSequenceOfShape)
{

	IGESControl_Controller::Init();
	IGESControl_Writer ICW(Interface_Static::CVal("XSTEP.iges.unit"),
		Interface_Static::IVal("XSTEP.iges.writebrep.mode"));

	for (Standard_Integer i = 1; i <= aHSequenceOfShape->Length(); i++)
		ICW.AddShape(aHSequenceOfShape->Value(i));

	ICW.ComputeModel();
	Standard_Boolean result = ICW.Write(aFileName);
	return result;
}
void FitSurface::set_range(int min, int max)
{
	m_min = min;
	m_max = max;
}
void FitSurface::attach(FitSurfaceObserver * observer)
{
	m_list.push_back(observer);
}

void FitSurface::detach(FitSurfaceObserver * observer)
{
	m_list.remove(observer);
}

void FitSurface::notify()
{
	std::list<FitSurfaceObserver*>::iterator it = m_list.begin();
	for (; it != m_list.end(); it++)
	{
		(*it)->updateFitSurfaceProcess(m_state);
	}
}

void FitSurface::set_state(int state)
{
	m_state = state;
}


bool FitSurface::Find4Corners(IN const vector_vec3d &m_data, IN double expand_value,
	OUT ON_3dPoint&ll, OUT ON_3dPoint&lr, OUT ON_3dPoint&ur, OUT ON_3dPoint&ul) {
	//计算出点的平均值点P 和xyz三个向量的值，init所生成的面在xPy面上,
	//所以所有点投影在xPy面上，可以求出2d点云的包围盒，四个方向的角即为四个角，ll、lr、ur、ul为左上，右上，右下，左下
	Eigen::Vector3d mean;
	Eigen::Matrix3d eigenvectors;
	Eigen::Vector3d eigenvalues;

	NurbsTools::pca(m_data, mean, eigenvectors, eigenvalues);

	//投影
	Pro3dPnt origin{ mean(0),mean(1),mean(2) };
	ProVector x_dir{ eigenvectors(0,0),eigenvectors(1,0),eigenvectors(2,0) };
	ProVector y_dir{ eigenvectors(0,1),eigenvectors(1,1) ,eigenvectors(2,1) };
	ProVector z_dir{ eigenvectors(0,2),eigenvectors(1,2),eigenvectors(2,2) };

	ProMatrix matrix_boTop;
	ProMatrixInit(x_dir, y_dir, z_dir, origin, matrix_boTop);
	ProMatrix matrixTopbo;
	ProUtilMatrixInvert(matrix_boTop, matrixTopbo);
#if 1
	//找四个角
	double xmin(0), xmax(0), ymin(0), ymax(0);

	Pro3dPnt st_pt{ m_data[0](0),m_data[0](1) ,m_data[0](2) };
	Pro3dPnt st_pj;
	ProPntTrfEval(st_pt, matrixTopbo, st_pj);
	xmin = xmax = st_pj[0];
	ymin = ymax = st_pj[1];

	for (int i = 0; i < (int)m_data.size(); i++) {
		Pro3dPnt src{ m_data[i](0),m_data[i](1) ,m_data[i](2) };
		Pro3dPnt pj;
		ProPntTrfEval(src, matrixTopbo, pj);
		xmin = min(pj[0], xmin);
		xmax = max(pj[0], xmax);
		ymin = min(pj[1], ymin);
		ymax = max(pj[1], ymax);
	}
	double expend = expand_value;//扩展多少
	Pro3dPnt e_ll{ xmin - expend, ymax + expend, 0 };
	Pro3dPnt e_lr{ xmax + expend, ymax + expend, 0 };
	Pro3dPnt e_ur{ xmax + expend, ymin - expend, 0 };
	Pro3dPnt e_ul{ xmin - expend, ymin - expend, 0 };


	ProPntTrfEval(e_ll, matrix_boTop, e_ll);
	ProPntTrfEval(e_lr, matrix_boTop, e_lr);
	ProPntTrfEval(e_ur, matrix_boTop, e_ur);
	ProPntTrfEval(e_ul, matrix_boTop, e_ul);

	for (int i = 0; i < 3; i++) {
		ll[i] = e_ll[i];
		lr[i] = e_lr[i];
		ur[i] = e_ur[i];
		ul[i] = e_ul[i];
	}
#endif
	return true;
}
