/********************************
*								*
*	Map Info.h					*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include "Token/TokenList.h"

enum class MapType
{
	NONE,
	DIFFUSE,
	SPECULAR,
	NORMAL,
	SHINE
};

/// <summary>
/// ASE 파일 Map 정보
/// 
/// 2022. 04. 11
/// </summary>
struct MapInfo
{
	string	mapName;
	string	className;
	MapType	type;

	int		subNumber;
	float	amount;

	string	bitmap;
	string	mapType;
	string	bitmapFilter;

	float	uOffset;
	float	vOffset;
	float	uTiling;
	float	vTiling;

	float	angle;
	float	blur;
	float	blufOffset;

	float	noUseAmt; // Amount?
	
	float	noiseSize;
	int		noiseLevel;
	float	noisePhase;

	MapInfo* genericMap;

	MapInfo() : mapName{}, className{}, mapType{}, genericMap(nullptr) {}

	void SetData(std::ifstream& data);
};