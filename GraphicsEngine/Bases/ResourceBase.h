/********************************
*								*
*	Resource Base.h				*
*								*
*	Created : 2022/07/01		*
*	Updated : 2022/07/01		*
*********************************/

#pragma once

namespace GraphicsEngineSpace
{
	class ResourceManager;

	template <typename T>
	class ResourceBase
	{
		int refCount;

	public:
		ResourceBase()
			: refCount(0) {}
		virtual ~ResourceBase() = default;

		void Release() { refCount--; }

	private:
		int& GetRefCount() { return refCount; }

		friend ResourceManager;
	};
}