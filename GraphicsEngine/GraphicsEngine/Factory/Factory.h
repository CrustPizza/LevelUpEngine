/********************************
*								*
*	Factory.h					*
*								*
*	Created : 2022/07/01		*
*	Updated : 2022/08/11		*
*********************************/

#pragma once

#include "Bases/FactoryBase.h"
#include "ResourceManager/ResourceManager.h"

namespace GraphicsEngineSpace
{
	class PBRBuilder;

	class Factory : public FactoryBase
	{
		FactoryBase* graphicsFactory;
		ResourceManager* resourceManager;

	public:
		Factory();
		~Factory() override;

		virtual ModelBase* CreateModelFromASEFile(const std::string& name, const std::string& path, const std::string& animationKey = "");
		virtual ModelBase* CreateAnimationFromASEFile(const std::string& name, const std::string& path, const std::string& animationKey);

		TextureBase* CreateTexture(const std::string& name, const std::string& path) override;
		LayoutBase* CreateLayout(const std::string& name) override;

		ShaderBase* CreateVertexShader(const std::string& name, const std::string& path, const char* entryName, const char* shaderModel, LayoutBase* layout) override;
		ShaderBase* CreatePixelShader(const std::string& name, const std::string& path, const char* entryName, const char* shaderModel) override;

		BufferBase* CreateVertexBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize, void* dataPtr, UINT size) override;
		BufferBase* CreateIndexBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize, void* dataPtr, UINT size) override;
		BufferBase* CreateConstantBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize) override;

		SamplerBase* CreateSampler(const std::string& name, FilterOption filter) override;
		FontBase* CreateFontObject(const std::string& name, const std::string& path) override;

		virtual PrefabBase* CreatePrefab(const std::string& name, ModelBase* model, BufferBase* matrixBuffer, UINT slot);
		virtual SkyBoxBase* CreateSkyBox(const std::string& name);

		virtual PBRModel* CreateNoneTextureModel(const std::string& name, ModelBase* model);
		virtual PBRModel* CreateAlbedoModel(const std::string& name, ModelBase* model);
		virtual PBRModel* CreateAlbedoNormalModel(const std::string& name, ModelBase* model);
		virtual PBRModel* CreateSkinningModel(const std::string& name, ModelBase* model);
		virtual PBRModel* CreateSkinningAlbedoModel(const std::string& name, ModelBase* model);
		virtual PBRModel* CreateSkinningAlbedoNormalModel(const std::string& name, ModelBase* model);
		virtual PBRModel* CreateWithoutAOModel(const std::string& name, ModelBase* model);
		virtual PBRModel* CreateWithoutAOStaticModel(const std::string& name, ModelBase* model);
		virtual PBRModel* CreateAllTextureModel(const std::string& name, ModelBase* model);
		virtual PBRModel* CreateAllTextureStaticModel(const std::string& name, ModelBase* model);

		virtual IBLTexture* CreateIBLTexture(const std::string& name, const std::string& radiancePath, const std::string& irradiancePath);

		virtual DirectionalLight* CreateDirectionalLight(const std::string& name);
		virtual PointLight* CreatePointLight(const std::string& name);

		virtual Canvas* CreateCanvas(const std::string& name, float width, float height);

		virtual SpriteAnimation* CreateSpriteAnimation(const std::string& name);

	private:
		bool InitFactory(FactoryBase* factory, ResourceManager* resourceManager);
		void InitDefaultData();

		friend GraphicsEngine;
		friend PBRBuilder;
	};
}