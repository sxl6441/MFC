#pragma once
#include<vector>
#include"stdafx.h"
#include"type.h"
using namespace std;
namespace Contour {
	class ReadSTLFile
	{
	public:
		static bool ReadBinarySTLFile(const char *cfilename, vector<Contour::Triangle>&Triangles);
		static bool ReadASCII(const char *cfilename, vector<Contour::Triangle>&Triangles);
		static bool ReadBinary(const char *cfilename, vector<Contour::Triangle>&Triangles);

		static int cpyint(const char*& p);
		static float cpyfloat(const char*& p);
	};
}
