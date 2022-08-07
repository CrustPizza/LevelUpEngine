/********************************
*								*
*	Normal Info.h				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include <vector>
#include "Token/TokenList.h"

using std::string;
using std::vector;

struct Normal
{
	float	faceNormal[4];
	float	vertexNormal[3][4];
};

/// <summary>
/// Face와 Vertex의 Normal vector 정보들
/// 
/// 2022. 04. 07
/// </summary>
struct NormalInfo
{
	vector<Normal> normals;
	unsigned int normalSize;

	void SetData(std::ifstream& data);
};