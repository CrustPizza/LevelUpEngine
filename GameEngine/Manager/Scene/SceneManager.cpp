/********************************
*								*
*	Scene Manager.cpp			*
*								*
*	Created : 2022/06/16		*
*	Updated : 2022/06/16		*
*********************************/

#include "SceneManager.h"
#include "Scene.h"

namespace GameEngineSpace
{
	SceneManager::SceneManager()
		: currentScene(nullptr)
	{

	}

	SceneManager::~SceneManager()
	{
		for (auto iter = sceneList.begin(); iter != sceneList.end(); iter++)
		{
			if (iter->second != nullptr)
			{
				iter->second->Release();
				delete iter->second;
			}
		}
	}

	bool SceneManager::AddScene(std::string sceneName, Scene* scene)
	{
		Scene* result = FindScene(sceneName);

		// �̹� ��ϵ� Scene�� �ִ�.
		if (result != nullptr)
			return false;

		sceneList[sceneName] = scene;

		if (currentScene == nullptr)
			currentScene = scene;

		return true;
	}

	Scene* SceneManager::FindScene(std::string sceneName)
	{
		auto result = sceneList.find(sceneName);

		// Scene�� ���ٸ� nullptr
		if (result == sceneList.end())
			return nullptr;

		return result->second;
	}

	bool SceneManager::ChangeScene(std::string sceneName)
	{
		Scene* result = FindScene(sceneName);

		// Scene�� ���ٸ� false
		if (result == nullptr)
			return false;

		// ���� Scene�̶��
		if (result == currentScene)
			return false;

		currentScene = result;
		currentScene->Init();

		return true;
	}

	Scene* SceneManager::GetCurrentScene()
	{
		return currentScene;
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

		currentScene->PrepareUpdate();
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

	SceneManager* SceneManager::GetInstance()
	{
		static SceneManager instance;

		return &instance;
	}
}