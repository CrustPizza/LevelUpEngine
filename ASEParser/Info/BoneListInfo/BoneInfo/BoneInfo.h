/********************************
*								*
*	Bone Info.h					*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include "Token/TokenList.h"

/// <summary>
/// Bone Á¤º¸
/// 
/// 2022. 05. 01
/// </summary>
struct BoneInfo
{
	string boneName;

	void SetData(std::ifstream& data);
};