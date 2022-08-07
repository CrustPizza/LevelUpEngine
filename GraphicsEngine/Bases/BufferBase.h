/********************************
*								*
*	Buffer Base.h				*
*								*
*	Created : 2022/07/01		*
*	Updated : 2022/07/01		*
*********************************/

#pragma once

#include "Bases/ResourceBase.h"
#include "Bases/ShaderBase.h"
#include "Define/GraphicsUsage.h"

namespace GraphicsEngineSpace
{
	enum class BufferType
	{
		NONE,
		CONSTANT,
		VERTEX,
		INDEX
	};

	class BufferBase : public ResourceBase<BufferBase>
	{
		BufferType type;

	public:
		BufferBase(BufferType type)
			: type(type) {}
		virtual ~BufferBase() = default;

		virtual bool SetUpBuffer(unsigned int slot, void* data, ShaderType targetType) abstract;
	};
}