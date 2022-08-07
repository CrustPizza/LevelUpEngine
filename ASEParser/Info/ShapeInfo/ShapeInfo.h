/********************************
*								*
*	Shape Info.h				*
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
/// Shape Á¤º¸
/// 
/// 2022. 04. 27
/// </summary>
struct ShapeInfo
{
	map<string, NodeInfo> nodeList;

	string currentNode;
	string parentNode;
	string helperName;

	AnimationInfo animationInfo;

	void SetData(std::ifstream& data);
};