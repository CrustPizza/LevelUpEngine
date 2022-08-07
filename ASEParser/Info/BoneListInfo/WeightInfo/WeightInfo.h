/********************************
*								*
*	Weight Info.h				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include <vector>
#include "Token/TokenList.h"

using std::vector;

struct WeightData
{
	unsigned int index;
	float weight;
};

/// <summary>
/// Weight Á¤º¸
/// 
/// 2022. 05. 01
/// </summary>
struct WeightInfo
{
	vector<WeightData> weights;

	void SetData(std::ifstream& data);
};