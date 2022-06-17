/********************************
*								*
*	Scene Manager.cpp			*
*								*
*	Created : 2022/06/16		*
*	Updated : 2022/06/16		*
*********************************/

#include "SceneManager.h"

namespace GameEngineSpace
{
	SceneManager::SceneManager()
		: currentScene(nullptr)
	{

	}

	SceneManager::~SceneManager()
	{

	}

	void SceneManager::AddScene(std::string sceneName, Scene* scene)
	{

	}

	bool SceneManager::SceneChange(std::string sceneName)
	{
		return false;
	}

	Scene* SceneManager::GetCurrentScene()
	{
		return nullptr;
	}

	void SceneManager::Init()
	{
		if (currentScene == nullptr)
			return;

		currentScene->Init();
	}

	void SceneManager::Update()
	{
		if (currentScene == nullptr)
			return;

		currentScene->Update();
	}

	void SceneManager::Render()
	{
		if (currentScene == nullptr)
			return;

		currentScene->Render();
	}

	void SceneManager::Release()
	{
		if (currentScene == nullptr)
			return;

		currentScene->Release();
	}
}