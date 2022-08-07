/********************************
*								*
*	Helper Info.h				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include <map>
#include "Info/GeometryInfo/NodeInfo/NodeInfo.h"
#include "Info/AnimationInfo/AnimationInfo.h"

using std::map;

/// <summary>
/// Helper Á¤º¸
/// 
/// 2022. 04. 15
/// </summary>
struct HelperInfo
{
	map<string, NodeInfo> nodeList;

	string currentNode;
	string parentNode;
	string helperName;

	float boundingBoxMin[4];
	float boundingBoxMax[4];

	AnimationInfo animationInfo;

	void SetData(std::ifstream& data);
};