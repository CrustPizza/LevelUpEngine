/********************************
*								*
*	ASE Pareser.h				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#pragma once

#include "Info/FileInfo/FileInfo.h"
#include "Info/SceneInfo/SceneInfo.h"
#include "Info/GeometryInfo/GeometryInfo.h"
#include "Info/MaterialListInfo/MaterialListInfo.h"
#include "Info/HelperInfo/HelperInfo.h"
#include "Info/ShapeInfo/ShapeInfo.h"
#include <fstream>

#ifdef ASEParser_Export
#define ASEParserDeclSpec __declspec( dllexport )
#else
#define ASEParserDeclSpec __declspec( dllimport )
#endif

/// <summary>
/// ASE Parser
/// 
/// 2022. 04. 06
/// </summary>
class ASEParserDeclSpec ASEParser
{
private:
	std::ifstream			file;

	FileInfo				fileInfo;
	SceneInfo				sceneInfo;
	MaterialListInfo		materialListInfo;
	vector<GeometryInfo>	geometryList;
	vector<HelperInfo>		helperList;
	vector<ShapeInfo>		shapeList;

public:
	ASEParser();
	virtual ~ASEParser();

	virtual bool LoadASEFile(const std::string& fileName);
	
	virtual const SceneInfo& GetSceneInfo();
	virtual const map<int, MaterialInfo>& GetMaterials();
	virtual const vector<GeometryInfo>& GetGeoMetries();
	virtual const vector<HelperInfo>& GetHelpers();
	virtual const vector<ShapeInfo>& GetShapes();
	

private:
	void GetDataFromFile();
	void SplitVertex();
};

extern "C"
{
	ASEParserDeclSpec ASEParser* CreateASEParser();
	using ASEParserConstructor = ASEParser*(*)();
}