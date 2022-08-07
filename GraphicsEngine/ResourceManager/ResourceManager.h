/********************************
*								*
*	Resource Manager.h			*
*								*
*	Created : 2022/06/24		*
*	Updated : 2022/08/07		*
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

#include "Object/PBRModel/PBRModel.h"
#include "Object/IBLTexture/IBLTexture.h"

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
	/// ������ ��ü�� �����ϴ� Ŭ����
	/// 
	/// 2022. 06. 30
	/// </summary>
	class GraphicsEngineDeclSpec ResourceManager
	{
		class ResourceContainer
		{
			std::map<std::string, ResourceBase*> resourceList;

		public:
			bool AddResource(const std::string& name, ResourceBase* resource);
			ResourceBase* GetResource(const std::string& name);
		};

		std::map<unsigned int, ResourceContainer> resourceContainers;

		std::map<std::string, TextureBase*> textureList;
		std::map<std::string, ShaderBase*>	shaderList;
		std::map<std::string, LayoutBase*>	layoutList;
		std::map<std::string, BufferBase*>	bufferList;
		std::map<std::string, ModelBase*>	modelList;
		std::map<std::string, PrefabBase*>	prefabList;
		std::map<std::string, SamplerBase*>	samplerList;
		std::map<std::string, SkyBoxBase*>	skyBoxList;
		std::map<std::string, PBRModel*>	PBRModelList;
		std::map<std::string, IBLTexture*>	IBLTextureList;

	public:
		ResourceManager();
		~ResourceManager();

	private:
		//bool AddTexture(const std::string& name, TextureBase* textureObject);
		//bool AddShader(const std::string& name, ShaderBase* shader);
		//bool AddLayout(const std::string& name, LayoutBase* layout);
		//bool AddBuffer(const std::string& name, BufferBase* buffer);
		//bool AddModel(const std::string& name, ModelBase* model);
		//bool AddPrefab(const std::string& name, PrefabBase* prefab);
		//bool AddSampler(const std::string& name, SamplerBase* sampler);
		//bool AddSkyBox(const std::string& name, SkyBoxBase* skyBox);
		//bool AddPBRModel(const std::string& name, PBRModel* PBRModel);
		//bool AddIBLTexture(const std::string& name, IBLTexture* IBLTexture);

		template <class T>
		bool AddResource(const std::string& name, T* resource);

		//bool SubLayout(const std::string& name);

	public:
		//virtual TextureBase* const GetTexture(const std::string& name);
		//virtual ShaderBase* const GetShader(const std::string& name);
		//virtual LayoutBase* const GetLayout(const std::string& name);
		//virtual BufferBase* const GetBuffer(const std::string& name);
		//virtual ModelBase* const GetModel(const std::string& name);
		//virtual PrefabBase* const GetPrefab(const std::string& name);
		//virtual SamplerBase* const GetSampler(const std::string& name);
		//virtual SkyBoxBase* const GetSkyBox(const std::string& name);
		//virtual PBRModel* const GetPBRModel(const std::string& name);
		//virtual IBLTexture* const GetIBLTexture(const std::string& name);

		template <class T>
		T* GetResource(const std::string& name);

	private:
		//template<typename T>
		//ResourceBase* FindGraphicsResource(const std::map<std::string, T*>& list, const std::string& name);

		template<typename T>
		unsigned int GetUniqueKey();

		friend Factory;
	};

	template<class T>
	inline bool ResourceManager::AddResource(const std::string& name, T* resource)
	{
		return resourceContainers[GetUniqueKey<T>()].AddResource(name, resource);
	}

	template<class T>
	inline T* ResourceManager::GetResource(const std::string& name)
	{
		return resourceContainers[GetUniqueKey<T>()].GetResource(name);
	}

	template<typename T>
	inline unsigned int ResourceManager::GetUniqueKey()
	{
		static T* key = nullptr;

		return reinterpret_cast<unsigned int>(&key);
	}

	//template<typename T>
	//inline ResourceBase* ResourceManager::FindGraphicsResource(const std::map<std::string, T*>& list, const std::string& name)
	//{
	//	auto finder = list.find(name);

	//	if (finder == list.end())
	//		return nullptr;

	//	return finder->second;
	//}
}