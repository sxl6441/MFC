#pragma once
#include"stdafx.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include"ReadSTLFile.h"
#include <sstream>    
using namespace std;
namespace Contour {

	bool ReadSTLFile::ReadBinarySTLFile(const char *cfilename, vector<Contour::Triangle>&Triangles)
	{
		FILE * pFile=NULL;
		long lSize;
		char* buffer;
		size_t result;

		/* 若要一个byte不漏地读入整个文件，只能采用二进制方式打开 */
		fopen_s(&pFile, cfilename, "rb");
		if (pFile == NULL)
		{
			fputs("File error", stderr);
			return false;
		}

		/* 获取文件大小 */
		fseek(pFile, 0, SEEK_END);
		lSize = ftell(pFile);
		rewind(pFile);

		/* 分配内存存储整个文件 */
		buffer = (char*)malloc(sizeof(char)*lSize);
		if (buffer == NULL)
		{
			fputs("Memory error", stderr);
			return false;
		}

		/* 将文件拷贝到buffer中 */
		result = fread(buffer, 1, lSize, pFile);
		if (result != lSize)
		{
			fputs("Reading error", stderr);
			return false;
		}


		/* 结束演示，关闭文件并释放内存 */

		fclose(pFile);
		ios::sync_with_stdio(false);
		ReadASCII(buffer, Triangles);
		if ((int)Triangles.size() < 1) {
			ReadBinary(buffer, Triangles);
		}
		//if (buffer[79] != '\0')//判断格式
		//{
		//	ReadASCII(buffer, Triangles);
		//}
		//else
		//{
		//	ReadBinary(buffer, Triangles);
		//}
		ios::sync_with_stdio(true);

		free(buffer);
		return true;
	}

	bool ReadSTLFile::ReadASCII(const char *buffer, vector<Contour::Triangle>&Triangles)
	{
		string name, useless;
		stringstream ss(buffer);
		ss >> name >> name;
		ss.get();
		do {
			ss >> useless;
			if (useless != "facet")
				break;
			ProVector normal;
			ss >> useless >> normal[0] >> normal[1] >> normal[2];
			getline(ss, useless);
			getline(ss, useless);
			Pro3dPnt vertex[3];
			//读取三个顶点
			for (int i = 0; i < 3; i++)
			{
				Pro3dPnt pnt;
				ss >> useless >> pnt[0] >> pnt[1] >> pnt[2];
				//ss >> useless >> x >> y >> z;
				//pointList.push_back(STLPoint3f(x, y, z));
				for (int x = 0; x < 3; x++) {
					vertex[i][x] = (double)pnt[x];
				}
			}
			Contour::Triangle TempTriangle(vertex[0], vertex[1], vertex[2], normal);
			Triangles.push_back(TempTriangle);
			getline(ss, useless);
			getline(ss, useless);
			getline(ss, useless);
		} while (1);
		return true;
	}

	bool ReadSTLFile::ReadBinary(const char *buffer, vector<Contour::Triangle>&Triangles)
	{
		const char* p = buffer;
		char name[80];
		memcpy(name, p, 80);
		p += 80;
		unsigned int unTriangles = cpyint(p);
		Triangles.resize(0);
		Triangles.reserve(unTriangles + 10);
		for (int i = 0; i < (int)unTriangles; i++)
		{
			//p += 12;//跳过头部法向量
			ProVector normal;
			for (int j = 0; j < 3; j++) {
				normal[j] = (double)cpyfloat(p);
			}
			//ProVectorTrfEval(normal, matrix, normal);//转向量
			Pro3dPnt vertex[3];
			for (int j = 0; j < 3; j++)//读取三顶点
			{
				for (int x = 0; x < 3; x++) {
					vertex[j][x] = (double)cpyfloat(p);
				}
				//ProPntTrfEval(vertex[j], matrix, vertex[j]);//转坐标
			}

			p += 2;//跳过尾部标志

			Contour::Triangle TempTriangle(vertex[0], vertex[1], vertex[2], normal);
			Triangles.push_back(TempTriangle);
		}
		return true;
	}
	int ReadSTLFile::cpyint(const char*& p)
	{
		int cpy;
		char *memwriter = (char*)&cpy;
		memcpy(memwriter, p, 4);
		p += 4;
		return cpy;
	}
	float ReadSTLFile::cpyfloat(const char*& p)
	{
		float cpy;
		char * memwriter = (char*)&cpy;
		memcpy(memwriter, p, 4);
		p += 4;
		return cpy;
	}
}
