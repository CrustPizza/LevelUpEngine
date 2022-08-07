/********************************
*								*
*	Control Info.h				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include <vector>
#include "Token/TokenList.h"

using std::vector;

struct ControlCoord
{
	float tick;

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
};

/// <summary>
/// Control Á¤º¸
/// 
/// 2022. 04. 27
/// </summary>
struct ControlInfo
{
	vector<ControlCoord> posSample;
	vector<ControlCoord> rotSample;

	void SetData(std::ifstream& data);
};