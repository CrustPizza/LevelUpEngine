/********************************
*								*
*	Input.cpp					*
*								*
*	Created : 2022/06/20		*
*	Updated : 2022/07/20		*
*********************************/

#include "Input.h"

namespace GameEngineSpace
{
	Input::Input()
		: prevCursorXY{}
		, currCursorXY{}
	{
		isMouseInWindow = false;
		isWindowActivated = true;
	}

	Input::~Input()
	{

	}

	/// <summary>
	/// 키 입력을 확인하는 함수
	/// </summary>
	void Input::Update()
	{
		// 사용하는 키 목록 전체를 갱신한다.
		// 첫 프레임에는 비어있어서 동작하지 않는다.
		for (auto& iter : currKeyState)
		{
			if ((GetAsyncKeyState(iter.first) & 0x8000) != 0)
				currKeyState[iter.first] = true;
			else
				currKeyState[iter.first] = false;
		}
	}

	void Input::LateUpdate()
	{
		// 키 상태 복사
		for (auto& iter : currKeyState)
			prevKeyState[iter.first] = iter.second;

		prevCursorXY = currCursorXY;
	}

	/// <summary>
	/// 현재 프레임에서 키의 상태를 반환
	/// </summary>
	bool Input::GetInputState(int key, KeyState state)
	{
		if (isWindowActivated != true)
			return false;

		switch (state)
		{

		case KeyState::UP:
		{
			// 키를 눌렀다가 때는 타이밍에 True를 반환한다.
			return currKeyState[key] ? false : (prevKeyState[key] ? true : false);
		}

		case KeyState::DOWN:
		{
			// 키를 누르는 타이밍에 True를 반환한다.
			return prevKeyState[key] ? false : (currKeyState[key] ? true : false);
		}

		case KeyState::STAY:
		{
			// 키를 누르고 있으면 True를 반환한다.
			return currKeyState[key];
		}

		case KeyState::TOGGLE:
		{
			// 키를 누를 때마다 On/Off 된다.
			return GetKeyState(key) & 0x0001;
		}

		}

		return false;
	}

	/// <summary>
	/// 마우스 좌표 설정하는 함수
	/// </summary>
	void Input::SetMousePos(float x, float y)
	{
		currCursorXY[0] = x;
		currCursorXY[1] = y;
	}

	const Vector& Input::GetMousePos()
	{
		return currCursorXY;
	}

	Vector Input::GetMouseMoveVector()
	{
		return Vector
		{
			currCursorXY[0] - prevCursorXY[0],
			currCursorXY[1] - prevCursorXY[1],
			0.0f,
			0.0f
		};
	}

	Input* Input::GetInstance()
	{
		static Input instance;

		return &instance;
	}
}