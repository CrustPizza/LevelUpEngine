/********************************
*								*
*	PBR Builder.h				*
*								*
*	Created : 2022/08/04		*
*	Updated : 2022/08/04		*
*********************************/

#pragma once

#include "Object/PBRModel/PBRModel.h"
#include "GraphicsEngine/Factory/Factory.h"

namespace GraphicsEngineSpace
{
	class PBRBuilder
	{

	public:
		PBRBuilder();
		~PBRBuilder();

		PBRModel* CreateNoneTextureModel(const std::string& name, Factory* factory, ModelBase* model);
		PBRModel* CreateAlbedoModel(const std::string& name, Factory* factory, ModelBase* model);
		PBRModel* CreateAlbedoNormalModel(const std::string& name, Factory* factory, ModelBase* model);
		PBRModel* CreateSkinningModel(const std::string& name, Factory* factory, ModelBase* model);
		PBRModel* CreateSkinningAlbedoModel(const std::string& name, Factory* factory, ModelBase* model);
		PBRModel* CreateSkinningAlbedoNormalModel(const std::string& name, Factory* factory, ModelBase* model);
		PBRModel* CreateWithoutAOModel(const std::string& name, Factory* factory, ModelBase* model);
		PBRModel* CreateWithoutAOStaticModel(const std::string& name, Factory* factory, ModelBase* model);
		PBRModel* CreateAllTextureModel(const std::string& name, Factory* factory, ModelBase* model);
		PBRModel* CreateAllTextureStaticModel(const std::string& name, Factory* factory, ModelBase* model);

	private:
		PBRModel* SetStandard(const std::string& name, Factory* factory, ModelBase* model);

		/* Vertex Shader */
		ShaderBase* GetBasicVS(Factory* factory);
		ShaderBase* GetNormalVS(Factory* factory);
		ShaderBase* GetSkinnedVS(Factory* factory);
		ShaderBase* GetSkinnedNormalVS(Factory* factory);

		/* Pixel Shader */
		ShaderBase* GetConstValuePS(Factory* factory);
		ShaderBase* GetAlebedoMapPS(Factory* factory);
		ShaderBase* GetAlebedoNormalMapPS(Factory* factory);
		ShaderBase* GetWithoutAOPS(Factory* factory);
		ShaderBase* GetAllTexturePS(Factory* factory);

		/* Parameter Buffer */
		BufferBase* GetVSParameterCB(Factory* factory);
		BufferBase* GetPSParameterCB(Factory* factory);
		BufferBase* GetBoneMatrixCB(Factory* factory);

		/* Vertex Buffer */
		void CreateBasicVB(Factory* factory, PrefabBase* prefab);
		void CreateNormalVB(Factory* factory, PrefabBase* prefab);
		void CreateSkinnedVB(Factory* factory, PrefabBase* prefab);
		void CreateSkinnedNormalVB(Factory* factory, PrefabBase* prefab);
	};
}