/********************************
*								*
*	Input.h						*
*								*
*	Created : 2022/06/20		*
*	Updated : 2022/07/20		*
*********************************/

#pragma once

#include <Windows.h>
#include <map>
#include "../HeraclesMath/HeraclesMath.h"

#pragma comment(lib, "../MathLibrary/HeraclesMath.lib")

namespace GameEngineSpace
{
	using namespace HeraclesMath;

	enum class KeyState
	{
		UP,
		DOWN,
		STAY,
		TOGGLE
	};

	class Input
	{
	private:
		// Key
		std::map<int, bool> prevKeyState;
		std::map<int, bool> currKeyState;

		// Cursor Coordinate
		Vector prevCursorXY;
		Vector currCursorXY;

	public:
		// 윈도우 활성화 관련 Input 거름망
		bool isMouseInWindow;
		bool isWindowActivated;

	private:
		Input();
		~Input();

	public:
		// Key Input
		void Update();
		void LateUpdate();
		virtual bool GetInputState(int key, KeyState state);

		// Mouse Pos
		void SetMousePos(float x, float y);
		const Vector& GetMousePos();
		Vector GetMouseMoveVector();

		static Input* GetInstance();
	};
}