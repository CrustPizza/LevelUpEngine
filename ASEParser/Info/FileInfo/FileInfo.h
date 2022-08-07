/********************************
*								*
*	File Info.h					*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include "Token/TokenList.h"

/// <summary>
/// ASE 파일 정보
/// 
/// 2022. 04. 06
/// </summary>
struct FileInfo
{
	int exportVer;
	string comment;

	void SetData(std::ifstream& data, AseToken type);
};