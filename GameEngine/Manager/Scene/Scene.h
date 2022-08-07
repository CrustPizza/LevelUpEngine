/********************************
*								*
*	Scene.h						*
*								*
*	Created : 2022/06/17		*
*	Updated : 2022/06/17		*
*********************************/

#pragma once
#include <string>
#include <vector>
#include "Manager/Scene/SceneManager.h"
#include "Manager/Input/Input.h"=

namespace GameEngineSpace
{
	class Factory;

	class Scene
	{
		//std::vector<ObjectBase*> objectList;

	protected:
		SceneManager*	sceneManager;
		Input*			inputManager;

	protected:
		Scene()
			: sceneManager(nullptr)
			, inputManager(nullptr) {}
		Scene(const Scene& other) = delete;
		Scene& operator =(const Scene& other) = delete;

	public:
		virtual ~Scene() = default;

		virtual void Init() abstract;
		virtual void Update() abstract;
		virtual void Render() abstract;
		virtual void Release() abstract;

		template<typename T, typename ...Types>
		T* CreateObject(Types ...args)
		{
			T* newObj = new T(args...);

			return newObj;
		}

	private:
		void PrepareUpdate();

		friend Factory;
		friend SceneManager;
	};
}