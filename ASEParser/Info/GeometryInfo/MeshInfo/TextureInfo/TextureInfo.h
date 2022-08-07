/********************************
*								*
*	Texture Info.h				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include <vector>
#include "Token/TokenList.h"

using std::vector;

union TVertex
{
	struct
	{
		float x;
		float y;
		float z;
	};

	float r[3];
};

/// <summary>
/// Texture의 정보들
/// 
/// 2022. 04. 11
/// </summary>
struct TextureInfo
{
	vector<TVertex>	tVertex;

	void SetData(std::ifstream& data);
};