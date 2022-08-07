/********************************
*								*
*	Time.h						*
*								*
*	Created : 2022/08/06		*
*	Updated : 2022/08/06		*
*********************************/

#pragma once

#include <Windows.h>

namespace GameEngineSpace
{
	class Time
	{
		int		FPS;
		int		FrameCount;
		float	FrameTime;
		float	playTime;

		LARGE_INTEGER curTime;
		LARGE_INTEGER prevTime;
		LARGE_INTEGER frequency;

	public:
		float deltaTime;

	public:
		void Update();
		int GetFPS() { return FPS; }

	public:
		static Time instance;

	private:
		Time();
		~Time();
	};
}