/********************************
*								*
*	Geometry Info.h				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include <map>
#include "Info/GeometryInfo/NodeInfo/NodeInfo.h"
#include "Info/GeometryInfo//MeshInfo/MeshInfo.h"
#include "Info/AnimationInfo/AnimationInfo.h"
#include "Info/BoneListInfo/BoneListInfo.h"

using std::map;

/// <summary>
/// °´Ã¼ÀÇ Transform, Mesh Á¤º¸
/// 
/// 2022. 04. 07
/// </summary>
struct GeometryInfo
{
	map<string, NodeInfo>	nodeList;
	MeshInfo				meshInfo;

	AnimationInfo animationInfo;

	string currentNode;
	string parentNode;

	unsigned int	motionBlur;
	unsigned int	castShadow;
	unsigned int	recvShadow;
	unsigned int	materialRef;
	float			wireframeColor[4];

	BoneListInfo	boneInfo;

	bool	isSkin;

	void SetData(std::ifstream& data);
};