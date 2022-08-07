/********************************
*								*
*	Object Base.cpp				*
*								*
*	Created : 2022/07/26		*
*	Updated : 2022/07/26		*
*********************************/

#include "ObjectBase.h"

namespace GameEngineSpace
{
	Transform& ObjectBase::GetTransform()
	{
		return transform;
	}

	ObjectBase* ObjectBase::GetParent()
	{
		return parent;
	}

	std::vector<ObjectBase*>& ObjectBase::GetChild()
	{
		return child;
	}

	void ObjectBase::SetupAttachment(ObjectBase* parent)
	{
		if (parent == nullptr)
		{
			Detachment();

			return;
		}

		if (parent == this->parent)
			return;

		this->transform.UpdateWorldTransform();
		parent->transform.UpdateWorldTransform();

		this->Detachment();

		this->parent = parent;
		parent->child.push_back(this);

		this->transform.UpdateWorldTransform(parent->transform.GetWorldTransform());
		this->transform.DecomposeWorldTransform(this->transform.GetWorldTransform());
	}

	void ObjectBase::UnsetAttachment(ObjectBase* child)
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

	void ObjectBase::Detachment()
	{
		if (this->parent == nullptr)
			return;

		this->parent->UnsetAttachment(this);

		this->transform.UpdateWorldTransform(this->parent->transform.GetWorldTransform());
		this->transform.DecomposeWorldTransform(this->transform.GetWorldTransform());
		this->parent = nullptr;
	}
}