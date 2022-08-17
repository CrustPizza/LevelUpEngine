/********************************
*								*
*	Resource Manager.cpp		*
*								*
*	Created : 2022/06/24		*
*	Updated : 2022/08/05		*
*********************************/

#include "ResourceManager.h"

namespace GraphicsEngineSpace
{
	ResourceManager::ResourceManager()
	{

	}

	ResourceManager::~ResourceManager()
	{
		RELEASE_MAP(textureList);
		RELEASE_MAP(shaderList);
		RELEASE_MAP(layoutList);
		RELEASE_MAP(bufferList);
		RELEASE_MAP(modelList);
		RELEASE_MAP(prefabList);
		RELEASE_MAP(samplerList);
		RELEASE_MAP(skyBoxList);
		RELEASE_MAP(fontList);
		RELEASE_MAP(PBRModelList);
		RELEASE_MAP(IBLTextureList);
		RELEASE_MAP(lightList);
		RELEASE_MAP(canvasList);
		RELEASE_MAP(spriteAnimationList);
	}

	bool ResourceManager::AddTexture(const std::string& name, TextureBase* textureObject)
	{
		auto result = FindGraphicsResource(textureList, name);

		if (result != nullptr)
			return false;

		textureList[name] = textureObject;

		return true;
	}

	bool ResourceManager::AddShader(const std::string& name, ShaderBase* shader)
	{
		auto result = FindGraphicsResource(shaderList, name);

		if (result != nullptr)
			return false;

		shaderList[name] = shader;

		return true;
	}

	bool ResourceManager::AddLayout(const std::string& name, LayoutBase* layout)
	{
		auto result = FindGraphicsResource(layoutList, name);

		if (result != nullptr)
			return false;

		layoutList[name] = layout;

		return true;
	}

	bool ResourceManager::AddBuffer(const std::string& name, BufferBase* buffer)
	{
		auto result = FindGraphicsResource(bufferList, name);

		if (result != nullptr)
			return false;

		bufferList[name] = buffer;

		return true;
	}

	bool ResourceManager::AddModel(const std::string& name, ModelBase* model)
	{
		auto result = FindGraphicsResource(modelList, name);

		if (result != nullptr)
			return false;

		modelList[name] = model;

		return true;
	}

	bool ResourceManager::AddPrefab(const std::string& name, PrefabBase* prefab)
	{
		auto result = FindGraphicsResource(prefabList, name);

		if (result != nullptr)
			return false;

		prefabList[name] = prefab;

		return true;
	}

	bool ResourceManager::AddSampler(const std::string& name, SamplerBase* sampler)
	{
		auto result = FindGraphicsResource(samplerList, name);

		if (result != nullptr)
			return false;

		samplerList[name] = sampler;

		return true;
	}

	bool ResourceManager::AddSkyBox(const std::string& name, SkyBoxBase* skyBox)
	{
		auto result = FindGraphicsResource(skyBoxList, name);

		if (result != nullptr)
			return false;

		skyBoxList[name] = skyBox;

		return true;
	}

	bool ResourceManager::AddFont(const std::string& name, FontBase* font)
	{
		auto result = FindGraphicsResource(fontList, name);

		if (result != nullptr)
			return false;

		fontList[name] = font;

		return true;
	}

	bool ResourceManager::AddPBRModel(const std::string& name, PBRModel* PBRModel)
	{
		auto result = FindGraphicsResource(PBRModelList, name);

		if (result != nullptr)
			return false;

		PBRModelList[name] = PBRModel;

		return true;
	}

	bool ResourceManager::AddIBLTexture(const std::string& name, IBLTexture* IBLTexture)
	{
		auto result = FindGraphicsResource(IBLTextureList, name);

		if (result != nullptr)
			return false;

		IBLTextureList[name] = IBLTexture;

		return true;
	}

	bool ResourceManager::AddLight(const std::string& name, LightBase* light)
	{
		auto result = FindGraphicsResource(lightList, name);

		if (result != nullptr)
			return false;

		lightList[name] = light;

		return true;
	}

	bool ResourceManager::AddCanvas(const std::string& name, Canvas* canvas)
	{
		auto result = FindGraphicsResource(canvasList, name);

		if (result != nullptr)
			return false;

		canvasList[name] = canvas;

		return true;
	}

	bool ResourceManager::AddSpriteAnimation(const std::string& name, SpriteAnimation* spriteAnimation)
	{
		auto result = FindGraphicsResource(spriteAnimationList, name);

		if (result != nullptr)
			return false;

		spriteAnimationList[name] = spriteAnimation;

		return true;
	}

	bool ResourceManager::SubLayout(const std::string& name)
	{
		for (auto iter = layoutList.begin(); iter != layoutList.end(); iter++)
		{
			if (iter->first == name)
			{
				delete iter->second;
				layoutList.erase(iter);

				return true;
			}
		}

		return false;
	}

	TextureBase* const ResourceManager::GetTexture(const std::string& name)
	{
		auto result = FindGraphicsResource(textureList, name);

		if (result == nullptr)
			return nullptr;

		result->GetRefCount()++;

		return dynamic_cast<TextureBase*>(result);
	}

	ShaderBase* const ResourceManager::GetShader(const std::string& name)
	{
		auto result = FindGraphicsResource(shaderList, name);

		if (result == nullptr)
			return nullptr;

		result->GetRefCount()++;

		return dynamic_cast<ShaderBase*>(result);
	}

	LayoutBase* const ResourceManager::GetLayout(const std::string& name)
	{
		auto result = FindGraphicsResource(layoutList, name);

		if (result == nullptr)
			return nullptr;

		result->GetRefCount()++;

		return dynamic_cast<LayoutBase*>(result);
	}

	BufferBase* const ResourceManager::GetBuffer(const std::string& name)
	{
		auto result = FindGraphicsResource(bufferList, name);

		if (result == nullptr)
			return nullptr;

		result->GetRefCount()++;

		return dynamic_cast<BufferBase*>(result);
	}

	ModelBase* const ResourceManager::GetModel(const std::string& name)
	{
		auto result = FindGraphicsResource(modelList, name);

		if (result == nullptr)
			return nullptr;

		result->GetRefCount()++;

		return dynamic_cast<ModelBase*>(result);
	}

	PrefabBase* const ResourceManager::GetPrefab(const std::string& name)
	{
		auto result = FindGraphicsResource(prefabList, name);

		if (result == nullptr)
			return nullptr;

		result->GetRefCount()++;

		return dynamic_cast<PrefabBase*>(result);
	}

	SamplerBase* const ResourceManager::GetSampler(const std::string& name)
	{
		auto result = FindGraphicsResource(samplerList, name);

		if (result == nullptr)
			return nullptr;

		result->GetRefCount()++;

		return dynamic_cast<SamplerBase*>(result);
	}

	SkyBoxBase* const ResourceManager::GetSkyBox(const std::string& name)
	{
		auto result = FindGraphicsResource(skyBoxList, name);

		if (result == nullptr)
			return nullptr;

		result->GetRefCount()++;

		return dynamic_cast<SkyBoxBase*>(result);
	}

	FontBase* const ResourceManager::GetFont(const std::string& name)
	{
		auto result = FindGraphicsResource(fontList, name);

		if (result == nullptr)
			return nullptr;

		result->GetRefCount()++;

		return dynamic_cast<FontBase*>(result);
	}

	PBRModel* const ResourceManager::GetPBRModel(const std::string& name)
	{
		auto result = FindGraphicsResource(PBRModelList, name);

		if (result == nullptr)
			return nullptr;

		result->GetRefCount()++;

		return dynamic_cast<PBRModel*>(result);
	}

	IBLTexture* const ResourceManager::GetIBLTexture(const std::string& name)
	{
		auto result = FindGraphicsResource(IBLTextureList, name);

		if (result == nullptr)
			return nullptr;

		result->GetRefCount()++;

		return dynamic_cast<IBLTexture*>(result);
	}

	LightBase* const ResourceManager::GetLight(const std::string& name)
	{
		auto result = FindGraphicsResource(lightList, name);

		if (result == nullptr)
			return nullptr;

		result->GetRefCount()++;

		return dynamic_cast<LightBase*>(result);
	}

	Canvas* const ResourceManager::GetCanvas(const std::string& name)
	{
		auto result = FindGraphicsResource(canvasList, name);

		if (result == nullptr)
			return nullptr;

		result->GetRefCount()++;

		return dynamic_cast<Canvas*>(result);
	}

	SpriteAnimation* const ResourceManager::GetSpriteAnimation(const std::string& name)
	{
		auto result = FindGraphicsResource(spriteAnimationList, name);

		if (result == nullptr)
			return nullptr;

		result->GetRefCount()++;

		return dynamic_cast<SpriteAnimation*>(result);
	}

	DirectionalLight* const ResourceManager::GetDirectionalLight()
	{
		for (auto& iter : lightList)
		{
			if (iter.second == nullptr)
				continue;

			DirectionalLight* dLight = dynamic_cast<DirectionalLight*>(iter.second);

			if (dLight != nullptr)
				return dLight;
		}

		return nullptr;
	}
}