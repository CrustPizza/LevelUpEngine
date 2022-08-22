/********************************
*								*
*	Graphics Engine Base.h		*
*								*
*	Created : 2022/06/13		*
*	Updated : 2022/08/08		*
*********************************/

#pragma once

#include <vector>
#include "Bases/FactoryBase.h"
#include "Bases/TextureBase.h"
#include "Bases/MeshBase.h"
#include "Define/GraphicsTopology.h"
#include "../HeraclesMath/HeraclesMath.h"

namespace GraphicsEngineSpace
{
	typedef unsigned int UINT;

	class GraphicsEngineBase
	{
	public:
		struct RenderData
		{
			Matrix worldTransform;
			float animationTime;
			PrefabBase* prefab;
		};

		struct Sprite3DData
		{
			Texture* texture;
			Vector worldPosition[3];
			Vector texCoord[3];
			Matrix worldViewProjection;
			float  depth;
		};

	protected:
		std::vector<RenderData> renderQueue;
		std::vector<Sprite3DData> sprite3DQueue;

	public:
		GraphicsEngineBase() = default;
		virtual ~GraphicsEngineBase() = default;

		virtual FactoryBase* const CreateFactory() abstract;
		virtual bool OnResize(UINT width, UINT height) abstract;

		// Texture 타입을 동적 타입으로 받고 싶다..
		virtual bool DrawSprite(Texture* texture, long posX, long posY, long width, long height, float z) abstract;
		virtual bool DrawSprite(Texture* texture, const Rect& dest, const Rect& src, float z) abstract;
		virtual bool DrawSpriteOn3D(Texture* texture, Vector worldPosition[3], const Matrix& viewProjection) abstract;
		virtual bool DrawSpriteOn3D(Texture* texture, Vector worldPosition[3], const Matrix& viewProjection, const Vector texCoord[3]) abstract;
		virtual bool DrawSpriteOn3D(Texture* texture, long width, long height, const Matrix& worldViewProjection) abstract;
		virtual bool DrawSpriteOn3D(Texture* texture, long width, long height, const Matrix& worldViewProjection, const Vector texCoord[3]) abstract;

		virtual bool DrawMesh(BufferBase* vertices, BufferBase* indices) abstract;
		virtual bool DrawTextColor(std::string& text, Vector color, Vector position, float rotation = 0.0f, Vector scale = { 1.0f, 1.0f }) abstract;
		virtual bool DrawTextColor(const std::string& fontName, std::string& text, Vector color, Vector position, float rotation = 0.0f, Vector scale = { 1.0f, 1.0f }) abstract;
		virtual bool DrawTextColor(const std::string& fontName, std::wstring& text, Vector color, Vector position, float rotation = 0.0f, Vector scale = { 1.0f, 1.0f }) abstract;
		virtual bool DrawLine(BufferBase* vertices, BufferBase* indices) abstract;

		virtual bool SetFontName(const std::string& fontName) abstract;
		virtual bool SetUpShader(ShaderBase* shader) abstract;

		virtual bool GraphicsDebugBeginEvent(const std::string& name) abstract;
		virtual bool GraphicsDebugEndEvent() abstract;

		virtual void BeginShadowRender() abstract;
		virtual void EndShadowRender() abstract;

		virtual void BeginRender() abstract;
		virtual void Render() abstract;
		virtual void PostProcess() abstract;
		virtual void EndRender() abstract;
		virtual void Release() abstract;

		virtual void DebugRender() abstract;

		virtual void AddRenderQueue(const RenderData& renderData) abstract;
	};
}