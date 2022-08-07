/********************************
*								*
*	Object Base.h				*
*								*
*	Created : 2022/06/20		*
*	Updated : 2022/07/19		*
*********************************/

#pragma once

#include <vector>
#include <string>
#include "Bases/ResourceBase.h"
#include "Transform/Transform.h"

namespace GraphicsEngineSpace
{
	class ObjectBase : public ResourceBase<ObjectBase>
	{
		std::string name;
		std::string parentName;

		Transform transform;

		ObjectBase* parent;
		std::vector<ObjectBase*> child;

	public:
		ObjectBase()
			: transform(this)
			, parent(nullptr) {}
		virtual ~ObjectBase() = default;

		const std::string& GetName() { return name; }
		const std::string& GetParentName() { return parentName; }
		ObjectBase* GetParent() { return parent; }
		std::vector<ObjectBase*>& GetChild() { return child; }
		Transform& GetTransform() { return transform; }

		void SetName(const std::string& name) { this->name = name; }
		void SetParentName(const std::string& name) { this->parentName = name; }

		void SetupAttachment(ObjectBase* parent)
		{
			if (parent == nullptr)
			{
				Detachment();

				return;
			}

			if (parent == this->parent)
				return;

			Matrix worldTrnasform = this->transform.GetWorldTransform();

			this->transform.UpdateWorldTransform();
			parent->transform.UpdateWorldTransform();

			if (this->parent != nullptr)
			{
				this->parent->UnsetAttachment(this);
			}

			this->parent = parent;
			parent->child.push_back(this);

			worldTrnasform = this->transform.GetWorldTransform();

			this->transform.DecomposeWorldTransform(this->transform.GetWorldTransform());

			Matrix& thisWorld = this->transform.GetWorldTransform();

			thisWorld = worldTrnasform;
		}

		void UnsetAttachment(ObjectBase* child)
		{
			for (auto iter = this->child.begin(); iter != this->child.end(); iter++)
			{
				if (*iter == child)
				{
					this->child.erase(iter);

					return;
				}
			}
		}

		void Detachment()
		{
			if (this->parent == nullptr)
				return;

			this->parent->UnsetAttachment(this);

			this->transform.UpdateWorldTransform();
			this->transform.DecomposeWorldTransform(this->transform.GetWorldTransform());
			this->parent = nullptr;
		}

		void PrepareRender()
		{
			transform.UpdateWorldTransform();

			for (auto* iter : child)
				iter->PrepareRender();
		}
	};
}