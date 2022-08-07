/********************************
*								*
*	Scene Info.h				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include "Token/TokenList.h"

/// <summary>
/// ASE 파일 Scene 정보
/// 
/// 2022. 04. 06
/// </summary>
struct SceneInfo
{
	string	sceneName;
	int		firstFrame;
	int		LastFrame;
	int		frameSpeed;
	int		tick;
	float	bgStatic[4];
	float	ambientStatic[4];

	void SetData(std::ifstream& data);
};