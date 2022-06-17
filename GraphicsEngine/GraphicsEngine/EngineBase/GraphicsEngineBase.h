/********************************
*								*
*	Graphics Engine Base.h		*
*								*
*	Created : 2022/06/13		*
*	Updated : 2022/06/15		*
*********************************/

#pragma once

#include <Windows.h>

#ifdef GraphicsEngine_Export
#define GraphicsEngineDeclSpec __declspec( dllexport )
#else
#define GraphicsEngineDeclSpec __declspec( dllimport )
#endif

class GraphicsEngineBase
{
public:
	GraphicsEngineBase() = default;
	virtual ~GraphicsEngineBase() = default;

	virtual bool OnResize(UINT width, UINT height) abstract;

	virtual void BeginRender() abstract;
	virtual void Render() abstract;
	virtual void PostProcess() abstract;
	virtual void EndRender() abstract;
	virtual void Release() abstract;
};