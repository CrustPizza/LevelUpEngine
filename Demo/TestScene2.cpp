#include "TestScene2.h"
#include <Windows.h>
#include <tchar.h>

TestScene2::TestScene2()
{

}

TestScene2::~TestScene2()
{

}

void TestScene2::Init()
{

}

void TestScene2::Update()
{
	//OutputDebugString(_T("TestScene2 Update\n"));

	int* a = CreateObject<int>(100);





	if (inputManager->GetInputState('1', GameEngineSpace::KeyState::DOWN) == true)
	{
		sceneManager->ChangeScene("Test");
	}
}

void TestScene2::Render()
{
	//OutputDebugString(_T("TestScene2 Render\n"));
}

void TestScene2::Release()
{

}