/********************************
*								*
*	Face Info.h					*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include <vector>
#include "Token/TokenList.h"

using std::vector;

struct Face
{
	unsigned int	index[4];
	unsigned int	tIndex[4];
	int				smoothing;
	int				materialID;
};

/// <summary>
/// Face의 정보들
/// 
/// 2022. 04. 07
/// </summary>
struct FaceInfo
{
	vector<Face>	faces;
	unsigned int	facesSize;

	void SetData(std::ifstream& data);
};