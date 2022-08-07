/********************************
*								*
*	Scene Manager.h				*
*								*
*	Created : 2022/06/16		*
*	Updated : 2022/06/16		*
*********************************/

#pragma once

#include <map>
#include <string>

namespace GameEngineSpace
{
#ifdef GameEngine_Export
#define GameEngineDeclSpec __declspec( dllexport )
#else
#define GameEngineDeclSpec __declspec( dllimport )
#endif

	class Scene;

	class GameEngineDeclSpec SceneManager
	{
		std::map<std::string, Scene*> sceneList;

		Scene* currentScene;

	private:
		SceneManager();
		SceneManager(const SceneManager& other) = delete;
		SceneManager& operator =(const SceneManager& other) = delete;
		~SceneManager();

	public:
		virtual bool AddScene(std::string sceneName, Scene* scene);
		virtual Scene* FindScene(std::string sceneName);
		virtual bool ChangeScene(std::string sceneName);

		Scene* GetCurrentScene();

		void Init();
		void Update();
		void Render();
		void Release();

		static SceneManager* GetInstance();
	};
}