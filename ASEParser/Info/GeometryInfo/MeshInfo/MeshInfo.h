/********************************
*								*
*	Mesh Info.h					*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include "Info/GeometryInfo/MeshInfo/FaceInfo/FaceInfo.h"
#include "Info/GeometryInfo/MeshInfo/VertexInfo/VertexInfo.h"
#include "Info/GeometryInfo/MeshInfo/NormalInfo/NormalInfo.h"
#include "Info/GeometryInfo/MeshInfo/TextureInfo/TextureInfo.h"
#include "Info/GeometryInfo/MeshInfo/ColorInfo/ColorInfo.h"

/// <summary>
/// °´Ã¼ÀÇ Mesh Á¤º¸
/// Vertex, Texture coordinate, Index, Normal
/// 
/// 2022. 04. 07
/// </summary>
struct MeshInfo
{
	float			timeValue;

	VertexInfo		vertexInfo;

	FaceInfo		faceInfo;

	TextureInfo		textureInfo;

	NormalInfo		normalInfo;

	ColorInfo		colorInfo;

	void SetData(std::ifstream& data);
};