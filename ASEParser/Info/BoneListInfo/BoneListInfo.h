/********************************
*								*
*	Bone List Info.h			*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include "Info/BoneListInfo/BoneInfo/BoneInfo.h"
#include "Info/BoneListInfo/WeightInfo/WeightInfo.h"

/// <summary>
/// Bone°ú Weight Vertex Á¤º¸
/// 
/// 2022. 05. 01
/// </summary>
struct BoneListInfo
{
	vector<BoneInfo>	boneList;
	vector<WeightInfo>	weightList;

	void SetData(std::ifstream& data);
};