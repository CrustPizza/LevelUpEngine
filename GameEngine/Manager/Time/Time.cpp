/********************************
*								*
*	Time.h						*
*								*
*	Created : 2022/08/06		*
*	Updated : 2022/08/06		*
*********************************/

#include "Time.h"

namespace GameEngineSpace
{
	Time Time::instance;

	Time::Time()
		: FPS(0)
		, FrameCount(0)
		, FrameTime(0.0f)
		, playTime(0.0f)
		, curTime{}
		, prevTime{}
		, frequency{}
		, deltaTime(0.0f)
	{
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&prevTime);
	}

	Time::~Time()
	{

	}

	void Time::Update()
	{
		if (QueryPerformanceCounter(&curTime) == 0)
			throw "Error : QueryPerformanceCounter is Failed";

		deltaTime = ((float)(curTime.QuadPart - prevTime.QuadPart) / (float)frequency.QuadPart);
		prevTime = curTime;
		playTime += deltaTime;
		FrameTime += deltaTime;
		FrameCount++;

		if (FrameTime >= 1.0f)
		{
			FPS = FrameCount;
			FrameCount = 0;
			FrameTime -= 1.0f;
		}
	}
}