/********************************
*								*
*	Material List Info.h		*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include "Info/MaterialListInfo/MaterialInfo/MaterialInfo.h"

/// <summary>
/// ASE 파일 Material List 정보
/// 
/// 2022. 04. 11
/// </summary>
struct MaterialListInfo
{
	map<int, MaterialInfo> materials;

	void SetData(std::ifstream& data);
};