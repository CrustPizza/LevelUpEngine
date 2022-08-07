/********************************
*								*
*	Material Info.h				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include <map>
#include <vector>
#include "Info/MaterialListInfo/MaterialInfo/MapInfo/MapInfo.h"

using std::vector;
using std::map;

/// <summary>
/// ASE 파일 Material 정보
/// 
/// 2022. 04. 11
/// </summary>
struct MaterialInfo
{
	string	materialName;
	string	className;

	float	ambient[4];
	float	diffuse[4];
	float	specular[4];

	float	shine;
	float	shineStrength;
	float	transparency;
	float	wireSize;

	string	shading;

	string	fallOff;
	float	xpFallOff;
	string	xpType;
	float	selfIllumination;

	vector<MapInfo> maps;
	map<int, MaterialInfo> subMaterial;

	void SetData(std::ifstream& data);
};