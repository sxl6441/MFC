#include "stdafx.h"
#include"JWG_Util_BaseMath.h"
#include "JWG_Util_PolygonsMerge.h"
#include "JWG_Util_CurvesFit.h"
#include "JWG_Util_SegmentLineApproxi.h"

bool jwg_utl::DOrientation(const DPath &poly)
{
	return DArea(poly) >= 0;
}
double jwg_utl::DArea(const DPath &poly)
{
	int size = (int)poly.size();
	if (size < 3) return 0;

	double a = 0;
	for (int i = 0, j = size - 1; i < size; ++i)
	{
		a += ((double)poly[j].x + poly[i].x) * ((double)poly[j].y - poly[i].y);
		j = i;
	}
	return -a * 0.5;
}

void jwg_utl::DReversePath(DPath & p)
{
	std::reverse(p.begin(), p.end());
}

double jwg_utl::GetLength(const PM2dPnt&p1, const PM2dPnt&p2)
{
	double a = p1.y - p2.y;
	double b = p1.x - p2.x;
	double r = sqrt(pow(a, 2) + pow(b, 2));
	return r;
}
double jwg_utl::Distance(const PM2dPnt a, const PM2dPnt b, const PM2dPnt c) {
	//根据小线段端点到拟合后线段距离公式AX+BY+C=0来判断;
	double A = 0.0, B = 0.0, C = 0.0;
	if (abs(b.x - a.x) < precision) {
		B = 0.0; A = 1; C = (-1.0)*a.x;
	}
	else if (abs(b.y - a.y) <precision) {
		A = 0.0; B = 1; C = (-1.0)*a.y;
	}
	else {
		double k = (b.y - a.y) / (b.x - a.x);
		double bb = b.y - k*b.x;
		A = k; B = -1; C = bb;
	}
	double d = 0.0, temp = 0.0;
	temp = abs(c.x*A + c.y*B + C);
	if (temp < precision) { return 0.0; }
	else { d = (temp / (sqrt(pow(A, 2) + pow(B, 2)))); }
	return d;
}
double jwg_utl::Distance(const PM2dPnt a, const PM2dPnt b) {
	if (abs(a.x - b.x)<precision) {
		return abs(b.y - a.y);
	}
	if (abs(a.y - b.y)<precision) {
		return abs(b.x - a.x);
	}
	return sqrt(pow(b.y - a.y, 2) + pow(b.x - a.x, 2));
}
bool jwg_utl::isCollinear(PM2dPnt a, PM2dPnt b, PM2dPnt c)
{
	PM2dPnt x1, x2;
	x1.x = b.x - a.x;
	x1.y = b.y - a.y;
	x2.x = c.x - a.x;
	x2.y = c.y - a.y;
	double xlJi = x1.x*x2.y - x1.y*x2.x;

	//double xlJi = (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
	if (abs(xlJi)<precision) {
		return true;
	}
	else {
		return false;
	}

}

bool jwg_utl::LinesToPoints(const vector<PM2dLinedef>& lines, vector<PM2dPnt>& pts, bool isClosed)
{
	pts.clear();
	if ((int)lines.size() < 1) {
		return false;
	}
	PM2dPnt point;
	if (isClosed == false) {
		point.x = lines[0].end1.x;
		point.y = lines[0].end1.y;
		pts.push_back(point);
	}
	for (int i = 0; i < (int)lines.size(); i++) {
		point.x = lines[i].end2.x;
		point.y = lines[i].end2.y;
		pts.push_back(point);
	}
	return true;
}

bool jwg_utl::PointsToLines(const vector<PM2dPnt>& pts, vector<PM2dLinedef>& lines, bool isClosed)
{
	lines.clear();
	if ((int)pts.size() < 2) {
		return false;
	}
	PM2dLinedef temp_line;
	for (int i = 0; i < (int)pts.size() - 1; i++) {
		temp_line.end1 = pts[i];
		temp_line.end2 = pts[i + 1];
		lines.push_back(temp_line);
	}
	if (isClosed == true) {
		temp_line.end1 = pts[(int)pts.size() - 1];
		temp_line.end2 = pts[0];
		lines.push_back(temp_line);
	}
	return true;
}
//PM2dArc的得到过程是拟合出来的，第一条线段的起始点就是start_angle，在-PI/2到3/2*PI之间
//然后沿着每条线段的方向去增加或者减去夹角，所以end_angle在start_angle的-2PI或者+2PI之间
//Pro2dArc的定义是start_angle在0-2PI之间，然后沿逆时针走0-2PI到end_angle
void jwg_utl::TransPM2dARCtoPRO2dARC(const PM2dArcdef &src, Pro2dArcdef &dest) {

	dest.type = PRO_2D_ARC;
	dest.radius = src.radius;
	dest.center[0] = src.center.x;
	dest.center[1] = src.center.y;
	double swap_angle;
	swap_angle = abs(src.start_angle - src.end_angle);
	if (src.start_angle > src.end_angle) {
		dest.start_angle = src.end_angle;
	}
	else {
		dest.start_angle = src.start_angle;
	}
	TransAngleToTWOPIRange(&dest.start_angle);
	dest.end_angle = dest.start_angle + swap_angle;

	return;
}


bool  jwg_utl::Fit3PointsToCircle(const PM2dPnt pa, const PM2dPnt pb, const PM2dPnt pc, PM2dCircledef&dest_circle) {
	if (true == isCollinear(pa, pb, pc)) {
		return false;
	}
	double x1 = pa.x, x2 = pb.x, x3 = pc.x;
	double y1 = pa.y, y2 = pb.y, y3 = pc.y;
	double a = x1 - x2;
	double b = y1 - y2;
	double c = x1 - x3;
	double d = y1 - y3;
	double e = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) / 2.0;
	double f = ((x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) / 2.0;
	double det = b * c - a * d;
	if (fabs(det) < 1e-12)
	{
		return false;
	}

	double x0 = -(d * e - b * f) / det;
	double y0 = -(a * f - c * e) / det;
	dest_circle.radius = hypot(x1 - x0, y1 - y0);//hypot为平方和的平方根，即为斜边长
	dest_circle.center.x = x0;
	dest_circle.center.y = y0;
	if (dest_circle.radius > 100 || dest_circle.radius < 0.001) {
		return false;
	}
	return true;
}
double jwg_utl::GetLength(const PM2dLinedef&line)
{
	double a = line.end2.y - line.end1.y;
	double b = line.end2.x - line.end1.x;
	double r = sqrt(pow(a, 2) + pow(b, 2));
	return r;
}
bool jwg_utl::CalcConvexHull(const DPath& src, DPath& result) {
	if (src.size() <= 2) {
		return false;
	}
	result.clear();
	PM2dPnt PMpt;
	geos::geom::GeometryFactory::unique_ptr factor;
	Coordinate pt;
	CoordinateArraySequence fromCoords;
	for (int i = 0; i < (int)src.size(); i++) {
		pt.x = src[i].x;
		pt.y = src[i].y;
		fromCoords.add(pt);
	}
	pt.x = src[0].x;
	pt.y = src[0].y;
	fromCoords.add(pt);
	LinearRing* multpnts = factor->createLinearRing(fromCoords);
	Geometry* p1 = factor->createPolygon(multpnts, NULL);
	Geometry* hull_ptr = p1->convexHull();
	CoordinateSequence* hull_pnts = hull_ptr->getCoordinates();
	for (int i = 0; i < (int)(*hull_pnts).size(); i++) {
		PMpt.x = (*hull_pnts)[i].x;
		PMpt.y = (*hull_pnts)[i].y;
		result.push_back(PMpt);
	}
	if (*result.begin() == result.back()) {//如果凸包第一个点与最后一个点相同，则弹出最后一点
		result.pop_back();
	}
	/*delete multpnts;
	delete hull_ptr;
	delete hull_pnts;
	delete p1;*/
	return true;
}
bool jwg_utl::CalcArcEndPoints(const ProArcdata& arc, Pro3dPnt endpoint) {
	//想法是求出此圆与xoy平面的变换矩阵
	//在xoy平面上求出终止点后再转换回来
	ProMatrix Matrix, InverseMatrix;
	Pro3dPnt global_pt;
	ProVector n;//法向
	VectorCross(arc.vector1, arc.vector2, n);
	ProVector v1, v2; Pro3dPnt origin;
	memcpy(v1, arc.vector1, sizeof(double[3]));
	memcpy(v2, arc.vector2, sizeof(double[3]));
	memcpy(origin, arc.origin, sizeof(double[3]));
	ProMatrixInit(v1, v2, n, origin, Matrix);//计算出圆弧坐标系与世界坐标系的矩阵转换
	global_pt[0] = arc.radius*cos(arc.end_angle);
	global_pt[1] = arc.radius*sin(arc.end_angle);
	global_pt[2] = 0.0;
	ProUtilMatrixInvert(Matrix, InverseMatrix);
	ProPntTrfEval(global_pt, InverseMatrix, endpoint);
	return true;
	//CalcRotationMatrix(Y_axis, arc.vector1, Matrix);
}


////求旋转变换矩阵
//void jwg_utl::CalcRotationMatrix(const ProVector vectorBefore, const ProVector vectorAfter,ProMatrix matrix)
//{
//	ProVector rotationAxis;
//	double rotationAngle;
//	//ProMatrix rotationMatrix;
//	VectorCross(vectorBefore, vectorAfter,rotationAxis);
//
//	rotationAngle = acos(VectorDotProduct(vectorBefore, vectorAfter) / VectorLength(vectorBefore) / VectorLength(vectorAfter));
//	RotationMatrix(rotationAngle, rotationAxis, matrix);
//}
//
////求旋转变换矩阵用
//void RotationMatrix(double angle, ProVector u, ProMatrix rotatinMatrix)
//{
//	double norm = jwg_utl::VectorLength(u);
//
//	u[0] = u[0] / norm;
//	u[1] = u[1] / norm;
//	u[2] = u[2] / norm;
//
//	rotatinMatrix[0][0] = cos(angle) + u[0] * u[0] * (1 - cos(angle));
//	rotatinMatrix[0][1] = u[0] * u[1] * (1 - cos(angle) - u[2] * sin(angle));
//	rotatinMatrix[0][2] = u[1] * sin(angle) + u[0] * u[2] * (1 - cos(angle));
//
//	rotatinMatrix[1][0] = u[2] * sin(angle) + u[0] * u[1] * (1 - cos(angle));
//	rotatinMatrix[1][1] = cos(angle) + u[1] * u[1] * (1 - cos(angle));
//	rotatinMatrix[1][2] = -u[0] * sin(angle) + u[1] * u[2] * (1 - cos(angle));
//
//	rotatinMatrix[2][0] = -u[1] * sin(angle) + u[0] * u[2] * (1 - cos(angle));
//	rotatinMatrix[2][1] = u[0] * sin(angle) + u[1] * u[2] * (1 - cos(angle));
//	rotatinMatrix[2][2] = cos(angle) + u[2] * u[2] * (1 - cos(angle));
//
//
//	rotatinMatrix[0][3] = rotatinMatrix[1][3] = rotatinMatrix[2][3] = rotatinMatrix[3][3] = 0;
//	rotatinMatrix[3][0] = rotatinMatrix[3][1] = rotatinMatrix[3][2] = 0;
//
//	return ;
//}
bool jwg_utl::intersect(const PM2dPnt aa, const PM2dPnt bb, const PM2dPnt cc, const PM2dPnt dd)
{
	if (max(aa.x, bb.x)<min(cc.x, dd.x)) {
		return false;
	}
	if (max(aa.y, bb.y)<min(cc.y, dd.y)) {
		return false;
	}
	if (max(cc.x, dd.x)<min(aa.x, bb.x)) {
		return false;
	}
	if (max(cc.y, dd.y)<min(aa.y, bb.y)) {
		return false;
	}
	if (mult(cc, bb, aa)*mult(bb, dd, aa)<0) {
		return false;
	}
	if (mult(aa, dd, cc)*mult(dd, bb, cc)<0) {
		return false;
	}
	return true;
}
bool jwg_utl::intersect(const PM2dLinedef aa, const PM2dLinedef bb) {
	return intersect(aa.end1, aa.end2, bb.end1, bb.end2);
}
double jwg_utl::mult(const PM2dPnt a, const PM2dPnt b, const  PM2dPnt c) {
	return (a.x - c.x)*(b.y - c.y) - (b.x - c.x)*(a.y - c.y);
}
bool jwg_utl::TransPM2dPntToProGeomdata_(const DPath& src, vector<ProGeomitemdata_> &result, bool isClosed) {
	result.clear();
	vector<PM2dLinedef> vec_lines;

	bool success = PointsToLines(src, vec_lines, isClosed);
	if (success == false) {
		return false;
	}
	ProGeomitemdata_ temp_geom;
	temp_geom.type = PRO_2D_LINE;
	temp_geom.data.p_line_data.type = PRO_2D_LINE;
	for (int i = 0; i < (int)vec_lines.size(); i++) {
		temp_geom.data.p_line_data.end1[0] = vec_lines[i].end1.x;
		temp_geom.data.p_line_data.end1[1] = vec_lines[i].end1.y;
		temp_geom.data.p_line_data.end2[0] = vec_lines[i].end2.x;
		temp_geom.data.p_line_data.end2[1] = vec_lines[i].end2.y;
		result.push_back(temp_geom);
	}
	return true;
}
//求圆弧的长度
double jwg_utl::GetLength(const PM2dArcdef&p1) {
	double angle = abs(p1.end_angle - p1.start_angle);//是绝对小于2PI的
	TransAngleToTWOPIRange(&angle);
	return angle*p1.radius;
}
//求圆弧的两个顶点，有顺序
bool jwg_utl::GetArcTwoVertex(const PM2dArcdef&p1, PM2dPnt &end1, PM2dPnt& end2) {
	end1.x = p1.center.x + p1.radius*cos(p1.start_angle);
	end1.y = p1.center.y + p1.radius*sin(p1.start_angle);
	end2.x = p1.center.x + p1.radius*cos(p1.end_angle);
	end2.y = p1.center.y + p1.radius*sin(p1.end_angle);
	return true;
}
void jwg_utl::RemoveCollinearPts(IN OUT list<PM2dLinedef>&list_lines)
{
#if 1
	typedef list<PM2dLinedef>::iterator IT;
	IT iter1, iter2;

	PM2dPnt temp_pt;
	for (iter1 = list_lines.begin(); iter1 != list_lines.end();) {
		iter2 = iter1; iter2++;
		if (iter2 == list_lines.end())iter2 = list_lines.begin();
		if (true == isCollinear(iter1->end1, iter1->end2, iter2->end2)) {//可以合并
			if ((int)list_lines.size() == 1)break;//否则有可能陷入无限循环
			temp_pt = iter2->end2;
			list_lines.erase(iter2);
			iter1->end2 = temp_pt;
		}
		else {
			++iter1;
		}
	}
#endif
}

bool jwg_utl::isPtInPolygon(const PM2dPnt& pt, const DPath&polygon) {
	if (0 == (int)polygon.size()) {
		return false;
	}
	double scale = 1e6;
	Path Mypolygons;
	IntPoint temppt;
	for (int i = 0; i < (int)polygon.size(); i++) {
		temppt.X = (signed long long)(polygon[i].x*scale);
		temppt.Y = (signed long long)(polygon[i].y*scale);
		Mypolygons.push_back(temppt);
	}
	temppt.X = (signed long long)(pt.x*scale);
	temppt.Y = (signed long long)(pt.y*scale);
	//===================================
	return PointInPolygon(temppt, Mypolygons) != 0;
	//===================================

}

bool jwg_utl::CalcLineOffset(IN const jwg_utl::DPaths& dp_boxs,
	IN const jwg_utl::DPaths& dp_coutour,
	IN double out_distance, IN double in_distance,
	OUT vector<vector<ProGeomitemdata_>>&result_geoms, EndType et)
{
	result_geoms.resize(0);
	//首先，将ProGeomitemdata_转为DPath
	if ((int)dp_boxs.size() != 0)
	{
		for (int i = 0; i < (int)dp_coutour.size(); i++) {
			for (int j = 0; j < (int)dp_boxs.size(); j++) {
				jwg_utl::DPaths temp_contour, temp_box;
				temp_contour.push_back(dp_coutour[i]);
				temp_box.push_back(dp_boxs[j]);
				bool isAllin = true;
				for (int z = 0; z < (int)dp_coutour[i].size(); z++) {
					if (!isPtInPolygon(dp_coutour[i][z], dp_boxs[j])) {
						isAllin = false;
						break;
					}
				}
				jwg_utl::DPaths temp_result;//最终未拟合结果

				if (isAllin == false) {
					//并未全部选中
					//1.切出选中（线段1）
					jwg_utl::DPaths selected_lines;
					jwg_utl::PolygonsMerge::LinesCut(temp_contour, temp_box, selected_lines);
					if ((int)selected_lines.size() == 0) {//没切中
						continue;
					}
					//2.将选中线段偏移最大值 得几何1(多边形)
					jwg_utl::DPaths selected_lines_buffer_max;
					jwg_utl::PolygonsMerge::PolygonsOffset(selected_lines, selected_lines_buffer_max,
						max(out_distance, in_distance), jtMiter, etOpenButt);
					//3.原始形状偏距得几何2(多边形)
					jwg_utl::DPaths origin_shape_offset;
					jwg_utl::PolygonsMerge::PolygonsOffset(temp_contour, origin_shape_offset,
						(out_distance - in_distance) / 2.0, jtMiter, etClosedPolygon);
					////4.用几何1去切几何2,得选中线段偏移(out_distance-in_distance)/2.0的位置（线段2）
					jwg_utl::DPaths selected_lines_offset_center;
					jwg_utl::PolygonsMerge::LinesCut(origin_shape_offset, selected_lines_buffer_max,
						selected_lines_offset_center);
					//5.将线段2进行偏置得到几何3（多边形）
					//jwg_utl::DPaths temp_result;
					jwg_utl::PolygonsMerge::PolygonsOffset(selected_lines_offset_center, temp_result,
						(out_distance + in_distance) / 2.0, jtMiter, et);

				}
				else {//全部选中
					  //1.原始形状偏距(out_distance-in_distance)/2.0的位置（线段1）
					jwg_utl::DPaths selected_lines_offset_center;
					jwg_utl::PolygonsMerge::PolygonsOffset(temp_contour, selected_lines_offset_center,
						(out_distance - in_distance) / 2.0, jtMiter, etClosedPolygon);
					//2.将线段1进行缓冲，得到多边形	jwg_utl::DPaths temp_result;

					jwg_utl::PolygonsMerge::PolygonsOffset(selected_lines_offset_center, temp_result,
						(out_distance + in_distance) / 2.0, jtMiter, etClosedLine);
				}
				//A.将点进行拟合
				vector<vector<ProGeomitemdata_>>  vec_temp_geom;
				for (int i = 0; i < (int)temp_result.size(); i++) {
					vector<ProGeomitemdata_> temp_geom;
					jwg_utl::CurvesFit cur_fit(0.02, 0.05);
					cur_fit.AddPaths(temp_result[i]);
					cur_fit.Execute(temp_geom);
					vec_temp_geom.push_back(temp_geom);
				}
				//B.存入最终结果
				result_geoms.insert(result_geoms.end(), vec_temp_geom.begin(), vec_temp_geom.end());
			}
		}
	}
	else
	{
		for (int i = 0; i < (int)dp_coutour.size(); i++) {
			jwg_utl::DPaths temp_contour;
			temp_contour.push_back(dp_coutour[i]);

			jwg_utl::DPaths temp_result;//最终未拟合结果

										//1.原始形状偏距(out_distance-in_distance)/2.0的位置（线段1）
			jwg_utl::DPaths selected_lines_offset_center;
			jwg_utl::PolygonsMerge::PolygonsOffset(temp_contour, selected_lines_offset_center,
				(out_distance - in_distance) / 2.0, jtMiter, etClosedPolygon);
			//2.将线段1进行缓冲，得到多边形	jwg_utl::DPaths temp_result;

			jwg_utl::PolygonsMerge::PolygonsOffset(selected_lines_offset_center, temp_result,
				(out_distance + in_distance) / 2.0, jtMiter, etClosedLine);
			//A.将点进行拟合
			vector<vector<ProGeomitemdata_>>  vec_temp_geom;
			for (int i = 0; i < (int)temp_result.size(); i++) {
				vector<ProGeomitemdata_> temp_geom;
				jwg_utl::CurvesFit cur_fit(0.05, 0.05);
				cur_fit.AddPaths(temp_result[i]);
				cur_fit.Execute(temp_geom);
				vec_temp_geom.push_back(temp_geom);
			}
			//B.存入最终结果
			result_geoms.insert(result_geoms.end(), vec_temp_geom.begin(), vec_temp_geom.end());
		}
	}
	return true;
}
void jwg_utl::TransGeomitemdataToDPaths(IN const vector<vector<ProGeomitemdata_> >& originCoutours, OUT jwg_utl::DPaths&result)
{
	for (int i = 0; i<(int)originCoutours.size(); i++)
	{
		vector<jwg_utl::PM2dLinedef>linesl;
		jwg_utl::SegmentLineApproxi SegmentLineApproxi_inst(0.03);
		SegmentLineApproxi_inst.ClacGeoms(originCoutours[i]);
		SegmentLineApproxi_inst.GetResult(linesl);
		jwg_utl::DPath temp;
		LinesToPoints(linesl, temp, true);
		result.push_back(temp);
	}
	return;
}
void jwg_utl::SortEdges(vector<PM2dLinedef>& lines) {
	int size = (int)lines.size();
	int max_nums = size*size;
	vector<PM2dLinedef> temp_lines;
	temp_lines.push_back(lines[0]);
	PM2dPnt  temp1 = lines[0].end2;
	lines.erase(lines.begin());
	int num(0);
	while ((int)lines.size() != 0) {
		//限制最大排序次数,如果超过最大排序次数还未找到封闭起始点，在开放轮廓中首点尾点加一条线来封闭
		num++;
		if (num > max_nums)
		{
			PM2dLinedef line_temp;
			line_temp.type = PM_2D_LINE;
			memcpy(&line_temp.end1, &temp_lines.back().end2, sizeof(PM2dPnt));
			memcpy(&line_temp.end2, &temp_lines.front().end1, sizeof(PM2dPnt));
			temp_lines.push_back(line_temp);
			lines = temp_lines;
			return;
		}
		for (int j = 0; j < (int)lines.size(); j++) {
			if (PntEqualsPnt(temp1, lines[j].end1) == true) {
				temp1 = lines[j].end2;
				temp_lines.push_back(lines[j]);
				lines.erase(lines.begin() + j);
				if (j > 0)j--;
			}
			else if (PntEqualsPnt(temp1, lines[j].end2) == true) {
				SwapLines(lines[j]);//交换线段的两端点点坐标
				temp1 = lines[j].end2;
				temp_lines.push_back(lines[j]);
				lines.erase(lines.begin() + j);
				if (j > 0)j--;
			}
		}
	}
	lines = temp_lines;
}
bool jwg_utl::PntEqualsPnt(const PM2dPnt& p1, const PM2dPnt &p2) {
	if (abs(p1.x - p2.x)<1e-3&&abs(p1.y - p2.y)<1e-3) {
		return true;
	}
	return false;
}
void jwg_utl::SwapLines(IN OUT PM2dLinedef &data) {
	PM2dPnt temp1;
	temp1 = data.end1;
	data.end1 = data.end2;
	data.end2 = temp1;
	return;
}
//几何是否自交
bool jwg_utl::isSelfIntersect(const DPath& polygon) {
	DPaths outpoly;
	bool success = PolygonsMerge::PolygonSimplify(polygon, outpoly);
	if (success == false || (int)outpoly.size() != 1) {
		return true;
	}
	return false;
}
bool jwg_utl::isSelfIntersect(const vector<ProGeomitemdata_> & Coutour, double Tol) {
	vector<PM2dLinedef> lines;
	DPath pts;

	SegmentLineApproxi gToPath(Tol);
	gToPath.ClacGeoms(Coutour);
	gToPath.GetResult(lines);//得到结果线段
	LinesToPoints(lines, pts, true);
	return isSelfIntersect(pts);
}
bool jwg_utl::ArcFit(
	vector<PM2dPnt>& vec_points,
	PM2dArcdef& dest_arc, int start, int end) {
	//先把线段转为序列点，改进后的想法是将线段按照一定长度切开，分成更多线段（点）
	//这样可以弥补长线段和短线段的区别，使结果更精确，这部分待修正

	int m_nNum = end - start + 1;
	if (m_nNum<3 || end>(int)vec_points.size() - 1) {
		return false;
	}
	vector<PM2dPnt> more_points;
	more_points.assign(vec_points.begin() + start, vec_points.begin() + end + 1);

	if (3 == (int)more_points.size()) {
		double x1 = more_points[0].x, x2 = more_points[1].x, x3 = more_points[2].x;
		double y1 = more_points[0].y, y2 = more_points[1].y, y3 = more_points[2].y;
		double a = x1 - x2;
		double b = y1 - y2;
		double c = x1 - x3;
		double d = y1 - y3;
		double e = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) / 2.0;
		double f = ((x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) / 2.0;
		double det = b * c - a * d;
		if (fabs(det) < 1e-4)
		{
			return false;
		}

		double x0 = -(d * e - b * f) / det;
		double y0 = -(a * f - c * e) / det;
		dest_arc.radius = hypot(x1 - x0, y1 - y0);//hypot为平方和的平方根，即为斜边长
		dest_arc.center.x = x0;
		dest_arc.center.y = y0;
	}
	else {
#if 1
		double x0 = more_points[0].x;
		double y0 = more_points[0].y;
		double xn = more_points[more_points.size() - 1].x;
		double yn = more_points[more_points.size() - 1].y;

		//当最后一个点和第一个点的y值是相同的话，会产生无穷大的情况
		//这是为了避免下面求值时产生的无穷大的情况 
		if (abs(yn - y0) < 1e-6)
		{
			yn = y0 + 1e-6;
		}
		double D = ((pow(x0, 2) - pow(xn, 2)) + (pow(y0, 2) - pow(yn, 2))) / (yn - y0);
		double E = (x0 - xn) / (yn - y0);
		double F = (yn*pow(x0, 2) - y0*pow(xn, 2) + yn*pow(y0, 2) - y0*pow(yn, 2)) / (y0 - yn);
		double G = (x0*yn - xn*y0) / (y0 - yn);

		double J = 0;
		double temp = 0;
		for (int i = 0; i < more_points.size(); i++) {
			double Hi = more_points[i].x + E*more_points[i].y + G;
			J += (pow(more_points[i].x, 2) + pow(more_points[i].y, 2) + D*more_points[i].y + F)*Hi;
			temp += pow(Hi, 2);
		}
		double a = -J / temp;
		double b = D + a*E;
		double c = F + a*G;
		double A = a / (-2.0);
		double B = b / (-2.0);
		double temp1 = a*a + b*b - 4.0 * c;
		if (temp1 < 0)return false;
		double R = sqrt(temp1) / 2.0;
#endif
		dest_arc.center.x = A;
		dest_arc.center.y = B;
		dest_arc.radius = R;
		dest_arc.type = PM_2D_ARC;
	}

	//dest_arc.start_angle = 0.0;

#if 1
	//以下是对角度的处理,这部分非常重要,经历多次改动，决定使用如下策略：
	//首先求出起始角度，3/2*PI到-PI/2
	//划过的角度为每一小线段对应的圆心角之和
	double A = dest_arc.center.x;
	double B = dest_arc.center.y;
	if (abs(vec_points[start].x - A) > precision) {
		dest_arc.start_angle = atan((vec_points[start].y - B) / (vec_points[start].x - A));//atan范围(-PI/2,PI/2)
		if (vec_points[start].x - A < 0)dest_arc.start_angle += PI;
	}
	else {
		if (vec_points[start].y - B > 0)dest_arc.start_angle = PI / 2;
		else { dest_arc.start_angle = -PI / 2; }
	}

	dest_arc.end_angle = dest_arc.start_angle;
	//接下来求对应的圆心角，利用向量的叉积
	PM2dPnt vector1;//向量1
	PM2dPnt vector2;//向量2
	double seg_angle = 0.0;//圆心角
						   //double real_end_angel = 0.0;//用于修正每次角度
	PM2dPnt csys; csys.x = 0.0; csys.y = 0.0;

	//以下是分每一小线段进行计算，会有累积误差
	//此时，小线段对应的圆心角不会大于180度，
	//原点到线段起始点的向量1和原点到线段终止点的向量2之间的夹角范围为(-PI,PI];
	for (int i = start; i < end; i++) {
		vector1.x = vec_points[i].x - dest_arc.center.x;
		vector1.y = vec_points[i].y - dest_arc.center.y;
		vector2.x = vec_points[i + 1].x - dest_arc.center.x;
		vector2.y = vec_points[i + 1].y - dest_arc.center.y;
		//首先判断扫描角的正负，利用向量叉积的正负，即z的正负
		//再加上cos判断出真实的角度值
		double  XlJi = vector1.x*vector2.y - vector1.y*vector2.x;
		double dianJi = 0.0;
		if (abs(XlJi - 0)<precision) {//共线  
			if (vector1.x / vector2.x > 0) {//同向
				seg_angle = 0.0;
			}
			else {
				seg_angle = PI;//反向
			}
		}
		else if (XlJi > 0) {//范围在（0,PI）之间
			double dianJi = vector1.x*vector2.x + vector1.y*vector2.y;
			seg_angle = acos(dianJi / (Distance(vector1, csys)*Distance(vector2, csys)));
		}
		else {//(XlJi < 0)范围在（-PI,0）之间
			double dianJi = vector1.x*vector2.x + vector1.y*vector2.y;
			seg_angle = -acos(dianJi / (Distance(vector1, csys)*Distance(vector2, csys)));
		}
		dest_arc.end_angle += seg_angle;

		//如何解决累计误差
		double temp;//真实的最后的角度
		if (abs(vec_points[i + 1].x - A) > precision) {
			temp = atan((vec_points[i + 1].y - B) / (vec_points[i + 1].x - A));//atan范围(-PI/2,PI/2)
			if (vec_points[i + 1].x - A < 0)temp += PI;
		}
		else {
			if (vec_points[i + 1].y - B > 0)temp = PI / 2;
			else { temp = -PI / 2; }
		}


		if (abs((temp - 2 * PI) - dest_arc.end_angle) < 1e-6) {
			dest_arc.end_angle = temp - 2 * PI;
		}
		if (abs((temp + 2 * PI) - dest_arc.end_angle) < 1e-6) {
			dest_arc.end_angle = temp + 2 * PI;
		}
		if (abs((temp)-dest_arc.end_angle) < 1e-6) {
			dest_arc.end_angle = temp;
		}
	}
#endif
	return true;
}
double jwg_utl::AngleBetweenTwo2dVector(const PM2dPnt &p1, const PM2dPnt &p2) {
	double lengthA = sqrt(pow(p1.x, 2) + pow(p1.y, 2));
	double lengthB = sqrt(pow(p2.x, 2) + pow(p2.y, 2));
	if (lengthA < 1e-6 || lengthB < 1e-6) {
		return 0;
	}
	double Dot = p1.x*p2.x + p1.y*p2.y;
	return acos(Dot / (lengthA*lengthB));
}
bool jwg_utl::ClacPerpendicular(IN const PM2dPnt& src_end1, IN const PM2dPnt& src_end2, IN const PM2dPnt& GivenPt,
	OUT PM2dLinedef& result) {

	bool err;
	double A = 0.0, B = 0.0, C = 0.0;
	//直线方程Ax + By + C = 0
	err = CalcLineGeneralDef(src_end1, src_end2, A, B, C);
	if (err = false) { return false; }
	if (abs(A) < 1e-6) {//结果直线方程为x-m=0;
		result.end1 = GivenPt;
		result.end2.x = GivenPt.x;
		result.end2.y = GivenPt.y + 1.0;
		return true;
	}
	else if (abs(B) < 1e-6) {//结果直线方程为y-m=0;
		result.end1 = GivenPt;
		result.end2.x = GivenPt.x + 1;
		result.end2.y = GivenPt.y;
		return true;
	}
	else {//与直线方程Ax + By + C = 0(A≠0，B≠0)垂直的直线方程是Bx - Ay + m = 0, (m是参变量)的原理求出垂线方程的m值
		  //结果直线斜率为A/B;
		result.end1 = GivenPt;
		result.end2.x = GivenPt.x + 1;
		result.end2.y = GivenPt.y + (B / A*1.0);
		return true;
	}
}
bool jwg_utl::CalcLineGeneralDef(IN const PM2dPnt& src_end1, IN const PM2dPnt& src_end2,
	OUT double&A, OUT double&B, OUT double&C) {
	if (abs(src_end2.x - src_end1.x) < precision&&abs(src_end2.y - src_end1.y) < precision) {
		return false;
	}

	if (abs(src_end2.x - src_end1.x) < precision) {
		B = 0.0; A = 1; C = (-1.0)*src_end1.x;
	}
	else if (abs(src_end2.y - src_end1.y) <precision) {
		A = 0.0; B = 1; C = (-1.0)*src_end1.y;
	}
	else {
		double k = (src_end2.y - src_end1.y) / (src_end2.x - src_end1.x);
		double bb = src_end2.y - k*src_end2.x;
		A = k; B = -1; C = bb;
	}
	return true;
}
bool jwg_utl::TransPro2dGeomToPM2dGeom(const ProGeomitemdata_ &src, PM2dGeom &dest) {
	//memset(&dest, 0, sizeof(PM2dGeom));
	if (src.type == PRO_2D_LINE || src.data.p_line_data.type == PRO_2D_LINE) {
		dest.type = PM_2D_LINE;
		dest.geom.line.type = PM_2D_LINE;
		dest.geom.line.end1.x = src.data.p_line_data.end1[0];
		dest.geom.line.end1.y = src.data.p_line_data.end1[1];
		dest.geom.line.end2.x = src.data.p_line_data.end2[0];
		dest.geom.line.end2.y = src.data.p_line_data.end2[1];
	}
	else if (src.type == PRO_2D_ARC || src.data.p_line_data.type == PRO_2D_ARC) {
		dest.type = PM_2D_ARC;
		dest.geom.arc.type = PM_2D_ARC;
		dest.geom.arc.radius = src.data.p_arc_data.radius;
		dest.geom.arc.start_angle = src.data.p_arc_data.start_angle;
		dest.geom.arc.end_angle = src.data.p_arc_data.end_angle;
		dest.geom.arc.center.x = src.data.p_arc_data.center[0];
		dest.geom.arc.center.y = src.data.p_arc_data.center[1];
	}
	else if (src.type == PRO_2D_CIRCLE || src.data.p_line_data.type == PRO_2D_CIRCLE) {
		dest.type = PM_2D_CIRCLE;
		dest.geom.circle.type = PM_2D_CIRCLE;
		dest.geom.circle.radius = src.data.p_circle_data.radius;
		dest.geom.circle.center.x = src.data.p_circle_data.center[0];
		dest.geom.circle.center.y = src.data.p_circle_data.center[1];
	}
	return true;
}
bool jwg_utl::TransPM2dGeomToPro2dGeom(const PM2dGeom &src, ProGeomitemdata_ &geomdata) {
	//memset(&geomdata, 0, sizeof(ProGeomitemdata_));
	if (src.type == PM_2D_LINE) {
		geomdata.type = PRO_2D_LINE;
		geomdata.data.p_line_data.type = PRO_2D_LINE;
		geomdata.data.p_line_data.end1[0] = src.geom.line.end1.x;
		geomdata.data.p_line_data.end1[1] = src.geom.line.end1.y;
		geomdata.data.p_line_data.end2[0] = src.geom.line.end2.x;
		geomdata.data.p_line_data.end2[1] = src.geom.line.end2.y;
	}
	else if (src.type == PM_2D_ARC) {
		geomdata.type = PRO_2D_ARC;
		Pro2dArcdef temp_arc;
		TransPM2dARCtoPRO2dARC(src.geom.arc, temp_arc);
		geomdata.data.p_arc_data.type = PRO_2D_ARC;
		geomdata.data.p_arc_data.center[0] = temp_arc.center[0];
		geomdata.data.p_arc_data.center[1] = temp_arc.center[1];
		geomdata.data.p_arc_data.radius = temp_arc.radius;
		geomdata.data.p_arc_data.start_angle = temp_arc.start_angle;
		geomdata.data.p_arc_data.end_angle = temp_arc.end_angle;
	}
	else if (src.type == PM_2D_CIRCLE) {
		geomdata.type = PRO_2D_CIRCLE;
		geomdata.data.p_circle_data.type = PRO_2D_CIRCLE;
		geomdata.data.p_circle_data.center[0] = src.geom.circle.center.x;
		geomdata.data.p_circle_data.center[1] = src.geom.circle.center.y;
		geomdata.data.p_circle_data.radius = src.geom.circle.radius;
	}
	return true;
}
bool jwg_utl::CounterClockwiseVecPM2dGeom(vector<PM2dGeom>& src, vector<PM2dGeom>& result) {
	//想法是先离散，再考虑
}
bool jwg_utl::GetSpecPts(const ProGeomitemdata_& before, const ProGeomitemdata_ &after, PM2dPnt&CommonPt, PM2dPnt&BeforeAnother, PM2dPnt&AfterAnother) {
	//原始点
	PM2dPnt Before1, Before2;
	PM2dPnt After1, After2;


	//首先找到两几何的端点
	if (before.type == PRO_2D_ARC) {
		Before1.x = before.data.p_arc_data.center[0] + before.data.p_arc_data.radius*cos(before.data.p_arc_data.start_angle);
		Before1.y = before.data.p_arc_data.center[1] + before.data.p_arc_data.radius*sin(before.data.p_arc_data.start_angle);

		Before2.x = before.data.p_arc_data.center[0] + before.data.p_arc_data.radius*cos(before.data.p_arc_data.end_angle);
		Before2.y = before.data.p_arc_data.center[1] + before.data.p_arc_data.radius*sin(before.data.p_arc_data.end_angle);
	}
	else if (before.type == PRO_2D_LINE) {
		Before1.x = before.data.p_line_data.end1[0];
		Before1.y = before.data.p_line_data.end1[1];

		Before2.x = before.data.p_line_data.end2[0];
		Before2.y = before.data.p_line_data.end2[1];
	}

	if (after.type == PRO_2D_ARC) {
		After1.x = after.data.p_arc_data.center[0] + after.data.p_arc_data.radius*cos(after.data.p_arc_data.start_angle);
		After1.y = after.data.p_arc_data.center[1] + after.data.p_arc_data.radius*sin(after.data.p_arc_data.start_angle);

		After2.x = after.data.p_arc_data.center[0] + after.data.p_arc_data.radius*cos(after.data.p_arc_data.end_angle);
		After2.y = after.data.p_arc_data.center[1] + after.data.p_arc_data.radius*sin(after.data.p_arc_data.end_angle);
	}
	else if (after.type == PRO_2D_LINE) {
		After1.x = after.data.p_line_data.end1[0];
		After1.y = after.data.p_line_data.end1[1];

		After2.x = after.data.p_line_data.end2[0];
		After2.y = after.data.p_line_data.end2[1];
	}
	//找到两几何的公共点
	if (Before1 == After1) {
		CommonPt = Before1;
		BeforeAnother = Before2;
		AfterAnother = After2;
	}
	else if (Before1 == After2) {
		CommonPt = Before1;
		BeforeAnother = Before2;
		AfterAnother = After1;
	}
	else if (Before2 == After1) {
		CommonPt = Before2;
		BeforeAnother = Before1;
		AfterAnother = After2;
	}
	else if (Before2 == After2) {
		CommonPt = Before2;
		BeforeAnother = Before1;
		AfterAnother = After1;
	}
	else {
		return false;
	}
}
//这是得到屏蔽框的函数
bool jwg_utl::CoverOfShieldFrame(vector<vector<ProGeomitemdata_> > &shieldCoutour, DPath&result) {
	result.clear();
	vector<MarkEnds> AllMarkEnds;//得到所有的端部区域结构

	vector<pair<int, int> > ArcNeedToLine_index;//端点圆弧需要转换为直线的位置对应i,j
	for (int i = 0; i < (int)shieldCoutour.size(); i++) {
		double max_shoulder = 0;
		for (int j = 0; j < (int)shieldCoutour[i].size(); j++) {
			int after = j == (int)shieldCoutour[i].size() - 1 ? 0 : j + 1;
			int before = j == 0 ? (int)shieldCoutour[i].size() - 1 : j - 1;
			if (shieldCoutour[i][before].type == PRO_2D_LINE&&shieldCoutour[i][after].type == PRO_2D_LINE) {
				Pro2dPnt before_end1, before_end2, after_end1, after_end2;
				memcpy(before_end1, shieldCoutour[i][before].data.p_line_data.end1, sizeof(double[2]));
				memcpy(before_end2, shieldCoutour[i][before].data.p_line_data.end2, sizeof(double[2]));
				memcpy(after_end1, shieldCoutour[i][after].data.p_line_data.end1, sizeof(double[2]));
				memcpy(after_end2, shieldCoutour[i][after].data.p_line_data.end2, sizeof(double[2]));

				Pro2dPnt before_vector, after_vector;
				wit::TMath2D::d2Cut(before_end2, before_end1, before_vector);
				wit::TMath2D::d2Cut(after_end2, after_end1, after_vector);
				double AngleCrossValue = wit::TMath2D::VectCos(before_vector, after_vector);//两向量夹角
				if (abs(AngleCrossValue - (-1)) < 1e-6) {//说明这两个向量反向
														 //存入AllMarkEnds
					PM2dPnt temppt1, temppt2;
					temppt1.x = before_end2[0]; temppt1.y = before_end2[1];
					temppt2.x = after_end1[0]; temppt2.y = after_end1[1];
					if (shieldCoutour[i][j].type == PRO_2D_ARC) {
						MarkEnds temp_end(i, true, temppt1, temppt2);
						AllMarkEnds.push_back(temp_end);
						ArcNeedToLine_index.push_back(pair<int, int>(i, j));
					}
					else {
						MarkEnds temp_end(i, false, temppt1, temppt2);
						AllMarkEnds.push_back(temp_end);
					}
				}
			}
			else if (shieldCoutour[i][before].type == PRO_2D_ARC&&shieldCoutour[i][after].type == PRO_2D_ARC) {
				PM2dPnt end1, end2;
				PM2dPnt  before_pt, after_pt;
				double angle1 = shieldCoutour[i][before].data.p_arc_data.end_angle - shieldCoutour[i][before].data.p_arc_data.start_angle;
				double angle2 = shieldCoutour[i][after].data.p_arc_data.end_angle - shieldCoutour[i][after].data.p_arc_data.start_angle;
				TransAngleToTWOPIRange(&angle1);
				TransAngleToTWOPIRange(&angle2);
				//前一个弧或者后一个弧是个半圆
				if (abs(angle1 - PI) < 1e-5 || abs(angle2 - PI) < 1e-5) {
					continue;
				}
				//得到两端点
				GetSpecPts(shieldCoutour[i][before], shieldCoutour[i][j], end1, before_pt, end2);
				GetSpecPts(shieldCoutour[i][j], shieldCoutour[i][after], end2, end1, after_pt);
				if (abs(GetLength(end1, end2) - GetLength(before_pt, after_pt))>1e-4) {//是否宽度一致
					continue;
				}
				bool isInTwoSide = intersect(end1, end2, before_pt, after_pt);//两个圆弧是否在两侧
				if (isInTwoSide == false) {
					//存入AllMarkEnds
					if (shieldCoutour[i][j].type == PRO_2D_ARC) {
						MarkEnds temp_end(i, true, end1, end2);
						AllMarkEnds.push_back(temp_end);
						ArcNeedToLine_index.push_back(pair<int, int>(i, j));
					}
					else {
						MarkEnds temp_end(i, false, end1, end2);
						AllMarkEnds.push_back(temp_end);
					}

				}
			}
		}
	}
	//将端点圆弧转换为线段，直接抹平，因为后续加方块替代
	for (int z = 0; z < (int)ArcNeedToLine_index.size(); ++z) {
		int i = ArcNeedToLine_index[z].first;
		int j = ArcNeedToLine_index[z].second;
		int before = j == 0 ? (int)shieldCoutour[i].size() - 1 : j - 1;
		PM2dPnt end1, end2, before_pt;
		//得到两端点
		GetSpecPts(shieldCoutour[i][before], shieldCoutour[i][j], end1, before_pt, end2);

		shieldCoutour[i][j].type = PRO_2D_LINE;
		shieldCoutour[i][j].data.p_line_data.type = PRO_2D_LINE;
		shieldCoutour[i][j].data.p_line_data.end1[0] = end1.x;
		shieldCoutour[i][j].data.p_line_data.end1[1] = end1.y;
		shieldCoutour[i][j].data.p_line_data.end2[0] = end2.x;
		shieldCoutour[i][j].data.p_line_data.end2[1] = end2.y;
	}
	vector<PM2dLinedef> AllLines;//所有的线段
	DPaths SrcPolygons;//所有多边形
	for (int i = 0; i < (int)shieldCoutour.size(); i++) {
		vector<PM2dLinedef> lines;
		jwg_utl::SegmentLineApproxi SegmentLineApproxi_inst(0.03);
		SegmentLineApproxi_inst.ClacGeoms(shieldCoutour[i]);
		SegmentLineApproxi_inst.GetResult(lines);
		AllLines.insert(AllLines.end(), lines.begin(), lines.end());
		DPath temppts;
		LinesToPoints(lines, temppts, true);
		SrcPolygons.push_back(temppts);
	}

	map<double, pair<MarkEnds, MarkEnds> > map_EndDis;//找到最近的
	for (int i = 0; i < (int)AllMarkEnds.size(); i++) {
		for (int j = i + 1; j < (int)AllMarkEnds.size(); j++) {
			double distance = GetLength(AllMarkEnds[i].Middle, AllMarkEnds[j].Middle);
			map_EndDis.insert(pair< double, pair<MarkEnds, MarkEnds>>(distance, pair<MarkEnds, MarkEnds>(AllMarkEnds[i], AllMarkEnds[j])));
		}
	}


	//连接最近的两个
	//结果存入RectangleAdd
	DPaths RectangleAdd;
	typedef map<double, pair<MarkEnds, MarkEnds> >::iterator IT_double_pair_markends;

	while ((int)map_EndDis.size() != 0) {
		IT_double_pair_markends it_sortdis = map_EndDis.begin();
		PM2dLinedef oldline1, oldline2;
		oldline1.type = PM_2D_LINE;
		oldline2.type = PM_2D_LINE;
		oldline1.end1 = it_sortdis->second.first.p1;
		oldline1.end2 = it_sortdis->second.first.p2;
		oldline2.end1 = it_sortdis->second.second.p1;
		oldline2.end2 = it_sortdis->second.second.p2;
		if (abs(it_sortdis->first)<1e-4) {//说明重合

			vector<PM2dLinedef>::iterator it_vec_lines;
			it_vec_lines = find_if(AllLines.begin(), AllLines.end(), FindEdge(oldline1));
			if (it_vec_lines != AllLines.end()) { AllLines.erase(it_vec_lines); }
			SwapLines(oldline1);
			it_vec_lines = find_if(AllLines.begin(), AllLines.end(), FindEdge(oldline1));
			if (it_vec_lines != AllLines.end()) { AllLines.erase(it_vec_lines); }

			//从map_EndDis删除含有两end的数据
			for (IT_double_pair_markends it_temp = map_EndDis.begin(); it_temp != map_EndDis.end(); ) {
				if (it_temp->second.first == it_sortdis->second.first || it_temp->second.second == it_sortdis->second.first
					|| it_temp->second.first == it_sortdis->second.second || it_temp->second.second == it_sortdis->second.second) {
					//说明含
					it_temp = map_EndDis.erase(it_temp);
				}
				else {//不含
					++it_temp;
				}
			}
			continue;//继续
		}
		//如果有相同的点，则删除自己
		if (isTwoLineNeighboring(oldline1, oldline2)) {
			map_EndDis.erase(it_sortdis);
			continue;
		}
		if (it_sortdis->second.first.isCircle != it_sortdis->second.second.isCircle) {
			map_EndDis.erase(it_sortdis);
			continue;
		}
		//判断是连接p1p1还是p1p2
		PM2dLinedef newline1, newline2;
		newline1.type = PM_2D_LINE;
		newline2.type = PM_2D_LINE;


		if (intersect(it_sortdis->second.first.p1, it_sortdis->second.second.p1,
			it_sortdis->second.first.p2, it_sortdis->second.second.p2)) {//p1p2相交
			newline1.end1 = it_sortdis->second.first.p1;
			newline1.end2 = it_sortdis->second.second.p2;
			newline2.end1 = it_sortdis->second.first.p2;
			newline2.end2 = it_sortdis->second.second.p1;
		}
		else {
			newline1.end1 = it_sortdis->second.first.p1;
			newline1.end2 = it_sortdis->second.second.p1;
			newline2.end1 = it_sortdis->second.first.p2;
			newline2.end2 = it_sortdis->second.second.p2;

		}
		//判断连接后的两条线段与其他线段是否相交
		int intersect_index = 0;
		for (; intersect_index < (int)AllLines.size(); ++intersect_index) {
			if (intersect(newline1, AllLines[intersect_index])) {//说明与别的线段相交
				if (isTwoLineNeighboring(newline1, AllLines[intersect_index])) {//如果是相邻线段，则不能重合
					PM2dPnt CommonPt, line1_pt, line2_pt;
					GetTwoLineCommonPt(newline1, AllLines[intersect_index], CommonPt, line1_pt, line2_pt);
					PM2dPnt t1, t2;
					d2Cut(CommonPt, line1_pt, t1);
					d2Cut(CommonPt, line2_pt, t2);
					double anglecos = VectCos(t1, t2);
					//起点终点的向量

					if (abs(anglecos - 1)>1e-4) {//除了端点都不重合
						continue;
					}
				}
				break;
			}
			if (intersect(newline2, AllLines[intersect_index])) {//说明与别的线段相交
				if (isTwoLineNeighboring(newline2, AllLines[intersect_index])) {//如果是相邻线段，则不能重合
					PM2dPnt CommonPt, line1_pt, line2_pt;
					GetTwoLineCommonPt(newline2, AllLines[intersect_index], CommonPt, line1_pt, line2_pt);
					PM2dPnt t1, t2;
					d2Cut(CommonPt, line1_pt, t1);
					d2Cut(CommonPt, line2_pt, t2);
					double anglecos = VectCos(t1, t2);
					//起点终点的向量

					if (abs(anglecos - 1)>1e-4) {//除了端点都不重合
						continue;
					}
				}
				break;
			}
		}
		if (intersect_index == (int)AllLines.size()) {//说明满足条件
													  //新的线段中加入四条
			DPath temp;
			temp.push_back(newline1.end1);
			temp.push_back(newline1.end2);
			temp.push_back(newline2.end2);
			temp.push_back(newline2.end1);
			RectangleAdd.push_back(temp);
			//从map_EndDis删除含有两end的数据
			for (IT_double_pair_markends it_temp = map_EndDis.begin(); it_temp != map_EndDis.end(); ) {
				if (it_temp->second.first == it_sortdis->second.first || it_temp->second.second == it_sortdis->second.first
					|| it_temp->second.first == it_sortdis->second.second || it_temp->second.second == it_sortdis->second.second) {
					//说明含
					it_temp = map_EndDis.erase(it_temp);
				}
				else {//不含
					++it_temp;
				}
			}
		}
		else {
			map_EndDis.erase(it_sortdis);
		}
	}
	//此处应该加入很多端部的小圆
	for (int i = 0; i < (int)AllMarkEnds.size(); i++) {
		if (AllMarkEnds[i].isCircle == true) {
			ProGeomitemdata_ end_circle;
			end_circle.type = PRO_2D_CIRCLE;
			end_circle.data.p_circle_data.type = PRO_2D_CIRCLE;
			end_circle.data.p_circle_data.radius = GetLength(AllMarkEnds[i].p1, AllMarkEnds[i].p2) / 2.0;
			//end_circle.data.p_circle_data.radius = 0.25;
			end_circle.data.p_circle_data.center[0] = AllMarkEnds[i].Middle.x;
			end_circle.data.p_circle_data.center[1] = AllMarkEnds[i].Middle.y;
			vector<ProGeomitemdata_> vec_circle;
			vec_circle.push_back(end_circle);

			vector<PM2dLinedef> lines;
			jwg_utl::SegmentLineApproxi SegmentLineApproxi_inst(0.03);
			SegmentLineApproxi_inst.ClacGeoms(vec_circle);
			SegmentLineApproxi_inst.GetResult(lines);
			DPath pts;
			LinesToPoints(lines, pts, true);
			RectangleAdd.push_back(pts);
		}
	}

	DPaths  result_coutour1, result_coutour2;
	PolygonsMerge::PolygonsOffset(RectangleAdd, result_coutour1, 1e-6, jtMiter, etClosedPolygon);
	result_coutour1.insert(result_coutour1.end(), SrcPolygons.begin(), SrcPolygons.end());
	PolygonsMerge::PolygonsUnion(result_coutour1, result_coutour2);
	//可能结果有好几种可能
	if ((int)result_coutour2.size() == 1) {
		result = result_coutour2[0];
	}
	else if ((int)result_coutour2.size()>1) {
		int max_area_index = 0;
		double max_area = abs(DArea(result_coutour2[0]));
		for (int i = 1; i < (int)result_coutour2.size(); i++) {
			double area = abs(DArea(result_coutour2[i]));
			if (max_area < area) {
				max_area_index = i;
				max_area = area;
			}
		}
		result = result_coutour2[max_area_index];
	}
	else {
		return false;
	}
	return true;
}
//判断两个线段是否有公共端点
bool jwg_utl::isTwoLineNeighboring(const PM2dLinedef aa, const PM2dLinedef bb) {
	return aa.end1 == bb.end1 || aa.end1 == bb.end2 || aa.end2 == bb.end1 || aa.end2 == bb.end2;
}
bool jwg_utl::SortEdges(IN vector<PM2dLinedef>& lines, OUT DPaths &geoms2d) {
	class TCoordinate {
	public:
		TCoordinate(Coordinate& a_pt) :pt(a_pt) {}
		bool operator()(const Coordinate& a_pt)const {
			if (abs(a_pt.x - pt.x) < 1e-3&&abs(a_pt.y - pt.y) < 1e-3) {
				return true;
			}
			return false;
		}
		Coordinate pt;
	};
	fac factory;
	//转换原始数据
	CoordinateArraySequence cs;
	Coordinate pt;
	geos::operation::linemerge::LineSequencer lineOrder;
	vector<geos::geom::Geometry*> CollectPolygons;
	for (int i = 0; i < (int)lines.size(); i++) {
		cs.clear();
		pt.x = lines[i].end1.x;
		pt.y = lines[i].end1.y;
		cs.add(pt);
		pt.x = lines[i].end2.x;
		pt.y = lines[i].end2.y;
		cs.add(pt);
		geos::geom::LineString *lineString = factory->createLineString(cs);
		CollectPolygons.push_back(lineString);
	}
	lineOrder.add(CollectPolygons);
	geos::geom::Geometry* res = lineOrder.getSequencedLineStrings();
	//转换回去
	geos::geom::CoordinateSequence *ResultPts = res->getCoordinates();
	if (ResultPts->size() < 3) {
		return false;
	}
	const std::vector<Coordinate>* vec_coor = ResultPts->toVector();
	//得到的vec_coor中，两两点构成线段，所以会多一倍点
	std::list<Coordinate> UniqueCoor(vec_coor->begin(), vec_coor->end());
	typedef std::list<Coordinate>::iterator IT_LIST;

	for (IT_LIST it = UniqueCoor.begin(); it != UniqueCoor.end(); ++it) {
		IT_LIST after = it;
		after++;
		if (after != UniqueCoor.end()) {
			if (it->equals2D(*after)) {
				it = UniqueCoor.erase(it);
			}
		}
	}
	std::vector<Coordinate> vec_tt(UniqueCoor.begin(), UniqueCoor.end());

	vector<Coordinate> OneGeom;
	vector<vector<Coordinate> > AllGeoms;
	Coordinate start_pt = vec_tt[0];
	typedef std::vector<Coordinate>::iterator IT;
	IT iter_st = vec_tt.begin();
	while (iter_st != vec_tt.end()) {
		start_pt = *iter_st;
		IT iter_end = find_if(iter_st + 1, vec_tt.end(), TCoordinate(start_pt));
		if (iter_end == vec_tt.end()) {
			return false;
		}
		vector<Coordinate> temp(iter_st, iter_end);
		AllGeoms.push_back(temp);
		iter_st = iter_end + 1;
	}
	jwg_utl::PM2dPnt temp;
	vector<jwg_utl::PM2dPnt> vec_geoms;
	for (int i = 0; i < (int)AllGeoms.size(); i++) {
		vec_geoms.clear();
		for (int j = 0; j < (int)AllGeoms[i].size(); j++) {
			temp.x = AllGeoms[i][j].x;
			temp.y = AllGeoms[i][j].y;
			vec_geoms.push_back(temp);
		}
		geoms2d.push_back(vec_geoms);
	}
}
double jwg_utl::VectCos(const PM2dPnt a, const PM2dPnt b) {
	double temp = a.x*b.x + a.y*b.y;
	double alen = sqrt(a.x*a.x + a.y + a.y);
	double blen = sqrt(b.x*b.x + b.y*b.y);
	if (abs(alen) < 1e-6 || abs(blen) < 1e-6) {
		return 0;
	}
	return temp / (alen*blen);
}
bool jwg_utl::GetTwoLineCommonPt(const PM2dLinedef&line1, const PM2dLinedef&line2, PM2dPnt& CommonPt, PM2dPnt&BeforeAnother, PM2dPnt&AfterAnother) {
	//原始点
	PM2dPnt Before1 = line1.end1;
	PM2dPnt Before2 = line1.end2;
	PM2dPnt After1 = line2.end1;
	PM2dPnt After2 = line2.end2;

	//找到两几何的公共点
	if (Before1 == After1) {
		CommonPt = Before1;
		BeforeAnother = Before2;
		AfterAnother = After2;
	}
	else if (Before1 == After2) {
		CommonPt = Before1;
		BeforeAnother = Before2;
		AfterAnother = After1;
	}
	else if (Before2 == After1) {
		CommonPt = Before2;
		BeforeAnother = Before1;
		AfterAnother = After2;
	}
	else if (Before2 == After2) {
		CommonPt = Before2;
		BeforeAnother = Before1;
		AfterAnother = After1;
	}
	else {
		return false;
	}
}
bool jwg_utl::d2Cut(const PM2dPnt start_pt, const PM2dPnt end_pt, PM2dPnt&result) {
	result.x = end_pt.x - start_pt.x;
	result.y = end_pt.y - start_pt.y;
	return true;
}
bool jwg_utl::FindLineOrientation(jwg_utl::DPath& lines,
	jwg_utl::DPath&OriginGeom, bool&isCounterClockwise) {
	//1.判断每两个点和几何

	vector<PM2dLinedef> vec_lines;
	PointsToLines(lines, vec_lines, false);
	//list<PM2dLinedef> list_lines;
	//list_lines.assign(vec_lines.begin(), vec_lines.end());
	//RemoveCollinearPts(list_lines);//去除共线点
	//vec_lines.assign(list_lines.begin(), list_lines.end());

	vector<bool> vec_Ori;//方向
	for (int i = 0; i < (int)vec_lines.size(); i++) {
		bool isCounterClockwise;
		bool success = FindLineOrientation(vec_lines[i].end1, vec_lines[i].end2, OriginGeom, isCounterClockwise);
		if (success == false) {
			return false;
		}
		vec_Ori.push_back(isCounterClockwise);
	}
	//如果vec_Ori全部是true或者全是false,则返回true;
	int count_true = std::count(vec_Ori.begin(), vec_Ori.end(), true);
	int count_false = std::count(vec_Ori.begin(), vec_Ori.end(), false);
	if (vec_Ori.size() == count_true) {
		isCounterClockwise = true;
		return true;
	}
	else if (vec_Ori.size() == count_false) {
		isCounterClockwise = false;
		return true;
	}
	else {
		return false;
	}

}
bool jwg_utl::FindLineOrientation(const jwg_utl::PM2dPnt pStart, const jwg_utl::PM2dPnt pEnd,
	jwg_utl::DPath&OriginGeom, bool&isCounterClockwise) {
	//判断点在几何中的位置
	if (PntEqualsPnt(pStart, pEnd)) {
		return false;
	}
	DPath TempContour = OriginGeom;
	if (!DOrientation(TempContour)) {
		std::reverse(TempContour.begin(), TempContour.end());
	}
	vector<PM2dLinedef> vec_lines;
	PointsToLines(TempContour, vec_lines, true);
	//list<PM2dLinedef> list_lines;
	//list_lines.assign(vec_lines.begin(), vec_lines.end());	
	//RemoveCollinearPts(list_lines);//去除共线点
	//vec_lines.assign(list_lines.begin(), list_lines.end());
	double StartIndex = -1;//在几何中的位置，0-size
	double EndIndex = -1;

	for (int i = 0; i < (int)vec_lines.size(); i++) {
		if (isPtOnLine(pStart, vec_lines[i])&isPtOnLine(pEnd, vec_lines[i])) {//都在这个线段上
			if (PntEqualsPnt(pStart, vec_lines[i].end1)) {
				StartIndex = i;
			}
			else if (PntEqualsPnt(pStart, vec_lines[i].end2)) {
				StartIndex = i + 1;
			}
			else {
				StartIndex = i + (Distance(pStart, vec_lines[i].end1) / Distance(vec_lines[i].end1, vec_lines[i].end2));
			}
			if (PntEqualsPnt(pEnd, vec_lines[i].end1)) {
				EndIndex = i;
			}
			else if (PntEqualsPnt(pEnd, vec_lines[i].end2)) {
				EndIndex = i + 1;
			}
			else {
				EndIndex = i + (Distance(pEnd, vec_lines[i].end1) / Distance(vec_lines[i].end1, vec_lines[i].end2));
			}
			break;
		}
	}

	//现在可以判断
	if (EndIndex == -1 || StartIndex == -1) {
		return false;
	}
	if (EndIndex > StartIndex) {
		isCounterClockwise = true;
		return true;
	}
	else {
		isCounterClockwise = false;
		return true;
	}


}
bool jwg_utl::isPtOnLine(const PM2dPnt& pt, const PM2dLinedef&line)//判断点是否在线段上
{
	double d1 = Distance(pt, line.end1);
	double d2 = Distance(pt, line.end2);
	double d3 = Distance(line.end1, line.end2);
	if (fabs(d3 - d1 - d2) < 1e-3) {
		return true;
	}
	else {
		return false;
	}
}
bool jwg_utl::isTwoPolygonsIntersect(const DPath&ply1, const DPath&ply2) {
	DPaths src, results;
	src.push_back(ply1);
	src.push_back(ply2);
	PolygonsMerge::PolygonsUnion(src, results);
	if ((int)results.size() == 1) {
		return true;
	}
	else {
		return false;
	}
}
