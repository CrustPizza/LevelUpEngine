/********************************
*								*
*	Scene Manager.h				*
*								*
*	Created : 2022/06/16		*
*	Updated : 2022/06/16		*
*********************************/

#pragma once
#include <map>
#include "Scene.h"

class SceneManager
{
	std::map<std::string, Scene*> sceneList;

	Scene* currentScene;

private:
	SceneManager(); 
	~SceneManager();

public:
	void AddScene(std::string sceneName, Scene* scene);
	bool SceneChange(std::string sceneName);

	Scene* GetCurrentScene();

	void Init();
	void Update();
	void Render();
	void Release();
};