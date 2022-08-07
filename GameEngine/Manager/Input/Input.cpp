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
	/// Ű �Է��� Ȯ���ϴ� �Լ�
	/// </summary>
	void Input::Update()
	{
		// ����ϴ� Ű ��� ��ü�� �����Ѵ�.
		// ù �����ӿ��� ����־ �������� �ʴ´�.
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
		// Ű ���� ����
		for (auto& iter : currKeyState)
			prevKeyState[iter.first] = iter.second;

		prevCursorXY = currCursorXY;
	}

	/// <summary>
	/// ���� �����ӿ��� Ű�� ���¸� ��ȯ
	/// </summary>
	bool Input::GetInputState(int key, KeyState state)
	{
		if (isWindowActivated != true)
			return false;

		switch (state)
		{

		case KeyState::UP:
		{
			// Ű�� �����ٰ� ���� Ÿ�ֿ̹� True�� ��ȯ�Ѵ�.
			return currKeyState[key] ? false : (prevKeyState[key] ? true : false);
		}

		case KeyState::DOWN:
		{
			// Ű�� ������ Ÿ�ֿ̹� True�� ��ȯ�Ѵ�.
			return prevKeyState[key] ? false : (currKeyState[key] ? true : false);
		}

		case KeyState::STAY:
		{
			// Ű�� ������ ������ True�� ��ȯ�Ѵ�.
			return currKeyState[key];
		}

		case KeyState::TOGGLE:
		{
			// Ű�� ���� ������ On/Off �ȴ�.
			return GetKeyState(key) & 0x0001;
		}

		}

		return false;
	}

	/// <summary>
	/// ���콺 ��ǥ �����ϴ� �Լ�
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