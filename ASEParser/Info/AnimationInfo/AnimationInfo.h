/********************************
*								*
*	Animation Info.h			*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include "Info/AnimationInfo/ControlInfo/ControlInfo.h"

/// <summary>
/// Animation Á¤º¸
/// 
/// 2022. 04. 18
/// </summary>
struct AnimationInfo
{
	ControlInfo controlInfo;

	void SetData(std::ifstream& data);
};