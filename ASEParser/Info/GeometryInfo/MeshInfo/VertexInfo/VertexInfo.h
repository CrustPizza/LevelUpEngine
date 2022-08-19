/********************************
*								*
*	Vertex Info.h				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include <vector>
#include "Token/TokenList.h"

using std::vector;

struct Vertex
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		float r[4];
	};

	int				next;
	float			normal[4];
	int				textureIndex;
	unsigned int	weightIndex[16];
	float			weights[16];
	unsigned int	materialID;
};

/// <summary>
/// Vertex의 정보들
/// 
/// 2022. 04. 07
/// </summary>
struct VertexInfo
{
	vector<Vertex> vertices;
	unsigned int verticesSize;

	void SetData(std::ifstream& data);
};