/********************************
*								*
*	Factory.h					*
*								*
*	Created : 2022/06/20		*
*	Updated : 2022/06/30		*
*********************************/

#pragma once

#include <string>
#include <type_traits>
#include "Manager/Scene/Scene.h"
#include "Manager/Input/Input.h"

namespace GameEngineSpace
{
	class GameEngine;

	class Factory
	{
		SceneManager*	sceneManager;
		Input*			inputManager;

	public:
		Factory() : sceneManager(nullptr), inputManager(nullptr) {}

		template<typename T>
		T* CreateScene(const std::string& name);

		friend GameEngine;
	};

	template<typename T>
	inline T* Factory::CreateScene(const std::string& name)
	{
		static_assert(std::is_base_of<Scene, T>::value == true, "This function can only create Scene.\n");

		T* newScene = new T;

		if (newScene == nullptr)
			return nullptr;

		if (sceneManager->AddScene(name, newScene) == true)
		{
			newScene->sceneManager = sceneManager;
			newScene->inputManager = inputManager;

			return newScene;
		}

		newScene->Release();
		delete newScene;

		return nullptr;
	}
}