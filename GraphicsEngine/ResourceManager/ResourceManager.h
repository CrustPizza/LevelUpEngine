/********************************
*								*
*	Resource Manager.h			*
*								*
*	Created : 2022/06/24		*
*	Updated : 2022/08/05		*
*********************************/

#pragma once

#include <map>
#include <string>
#include "Bases/ResourceBase.h"
#include "Bases/TextureBase.h"
#include "Bases/ShaderBase.h"
#include "Bases/LayoutBase.h"
#include "Bases/BufferBase.h"
#include "Bases/ModelBase.h"
#include "Bases/PrefabBase.h"
#include "Bases/SamplerBase.h"
#include "Bases/SkyBoxBase.h"
#include "Bases/FontBase.h"

#include "Object/PBRModel/PBRModel.h"
#include "Object/IBLTexture/IBLTexture.h"
#include "Object/PointLight/PointLight.h"
#include "Object/DirectionalLight/DirectionalLight.h"
#include "Object/Canvas/Canvas.h"
#include "Object/SpriteAnimation/SpriteAnimation.h"

namespace GraphicsEngineSpace
{
#ifdef GraphicsEngine_Export
#define GraphicsEngineDeclSpec __declspec( dllexport )
#else
#define GraphicsEngineDeclSpec __declspec( dllimport )
#endif

	typedef unsigned int UINT;

	class Factory;

	/// <summary>
	/// 생성된 객체를 관리하는 클래스
	/// 
	/// 2022. 06. 30
	/// </summary>
	class GraphicsEngineDeclSpec ResourceManager
	{
		std::map<std::string, TextureBase*> textureList;
		std::map<std::string, ShaderBase*>	shaderList;
		std::map<std::string, LayoutBase*>	layoutList;
		std::map<std::string, BufferBase*>	bufferList;
		std::map<std::string, ModelBase*>	modelList;
		std::map<std::string, PrefabBase*>	prefabList;
		std::map<std::string, SamplerBase*>	samplerList;
		std::map<std::string, SkyBoxBase*>	skyBoxList;
		std::map<std::string, FontBase*>	fontList;

		std::map<std::string, PBRModel*>	PBRModelList;
		std::map<std::string, IBLTexture*>	IBLTextureList;
		std::map<std::string, LightBase*>	lightList;
		std::map<std::string, UIBase*>		canvasList;
		std::map<std::string, SpriteAnimation*> spriteAnimationList;

	public:
		ResourceManager();
		~ResourceManager();

	private:
		bool AddTexture(const std::string& name, TextureBase* textureObject);
		bool AddShader(const std::string& name, ShaderBase* shader);
		bool AddLayout(const std::string& name, LayoutBase* layout);
		bool AddBuffer(const std::string& name, BufferBase* buffer);
		bool AddModel(const std::string& name, ModelBase* model);
		bool AddPrefab(const std::string& name, PrefabBase* prefab);
		bool AddSampler(const std::string& name, SamplerBase* sampler);
		bool AddSkyBox(const std::string& name, SkyBoxBase* skyBox);
		bool AddFont(const std::string& name, FontBase* font);
		bool AddPBRModel(const std::string& name, PBRModel* PBRModel);
		bool AddIBLTexture(const std::string& name, IBLTexture* IBLTexture);
		bool AddLight(const std::string& name, LightBase* light);
		bool AddCanvas(const std::string& name, Canvas* canvas);
		bool AddSpriteAnimation(const std::string& name, SpriteAnimation* spriteAnimation);

		bool SubLayout(const std::string& name);

	public:
		virtual TextureBase* const GetTexture(const std::string& name);
		virtual ShaderBase* const GetShader(const std::string& name);
		virtual LayoutBase* const GetLayout(const std::string& name);
		virtual BufferBase* const GetBuffer(const std::string& name);
		virtual ModelBase* const GetModel(const std::string& name);
		virtual PrefabBase* const GetPrefab(const std::string& name);
		virtual SamplerBase* const GetSampler(const std::string& name);
		virtual SkyBoxBase* const GetSkyBox(const std::string& name);
		virtual FontBase* const GetFont(const std::string& name);
		virtual PBRModel* const GetPBRModel(const std::string& name);
		virtual IBLTexture* const GetIBLTexture(const std::string& name);
		virtual LightBase* const GetLight(const std::string& name);
		virtual Canvas* const GetCanvas(const std::string& name);
		virtual SpriteAnimation* const GetSpriteAnimation(const std::string& name);

		virtual DirectionalLight* const GetDirectionalLight();

	private:
		template<typename T>
		ResourceBase<T>* FindGraphicsResource(const std::map<std::string, T*>& list, const std::string& name);

		friend Factory;
	};

	template<typename T>
	inline ResourceBase<T>* ResourceManager::FindGraphicsResource(const std::map<std::string, T*>& list, const std::string& name)
	{
		auto finder = list.find(name);

		if (finder == list.end())
			return nullptr;

		return finder->second;
	}
}