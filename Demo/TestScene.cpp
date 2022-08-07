#include "TestScene.h"
#include <Windows.h>
#include <tchar.h>

TestScene::TestScene()
{

}

TestScene::~TestScene()
{

}

void TestScene::Init()
{

}

void TestScene::Update()
{
	//OutputDebugString(_T("TestScene Update\n"));

	if (inputManager->GetInputState('2', GameEngineSpace::KeyState::DOWN) == true)
	{
		sceneManager->ChangeScene("Test2");
	}
}

void TestScene::Render()
{
	//OutputDebugString(_T("TestScene Render\n"));
}

void TestScene::Release()
{

}