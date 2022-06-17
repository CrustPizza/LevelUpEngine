/********************************
*								*
*	Scene.h						*
*								*
*	Created : 2022/06/17		*
*	Updated : 2022/06/17		*
*********************************/

#pragma once
#include <string>
#include <vector>

namespace GameEngineSpace
{
	class Scene
	{
		std::string name;
		//std::vector<ObjectBase*> objectList;

	public:
		Scene(std::string name) : name(name) {}
		Scene(const Scene& other) = delete;
		Scene& operator =(const Scene& other) = delete;

		virtual void Init() abstract;
		virtual void Update() abstract;
		virtual void Render() abstract;
		virtual void Release() abstract;
	};
}