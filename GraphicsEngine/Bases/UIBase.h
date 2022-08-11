/********************************
*								*
*	UI Base.h					*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/10		*
*********************************/

#pragma once

#include <vector>
#include "Bases/ResourceBase.h"
#include "Bases/GraphicsEngineBase.h"

namespace GraphicsEngineSpace
{
	enum class HorizontalLocation
	{
		LEFT,
		CENTER,
		RIGHT,
		STRETCH
	};

	enum class VerticalLocation
	{
		TOP,
		MIDDLE,
		BOTTOM,
		STRETCH
	};

	class UIBase : public ResourceBase<UIBase>
	{
		struct Location
		{
			HorizontalLocation hLocation;
			VerticalLocation vLocation;
		};

	protected:
		Location anchor;
		Location pivot;

		float width;
		float height;

		bool isEnable;

		UIBase* parent;
		std::vector<UIBase*> child;
		Vector position;
		Vector rotation;
		Vector scale;

	private:
		Vector screenPosition;

	protected:
		UIBase()
			: anchor{ HorizontalLocation::LEFT, VerticalLocation::TOP }
			, pivot{ HorizontalLocation::LEFT, VerticalLocation::TOP }
			, width(0.0f)
			, height(0.0f)
			, parent(nullptr)
			, position(Vector::Zero)
			, rotation(Vector::Zero)
			, scale(Vector::One)
			, isEnable(true)
			, screenPosition(Vector::Zero) {}

	public:
		virtual ~UIBase() = default;

		virtual void Render(GraphicsEngineBase* engine) abstract;

		void SetAnchor(Location anchor)
		{
			if (parent == nullptr)
				return;

			SetHorizontalAnchor(anchor.hLocation);
			SetVerticalAnchor(anchor.vLocation);
		}

		void SetHorizontalAnchor(HorizontalLocation hLocation)
		{
			if (parent == nullptr)
				return;

			if (hLocation == HorizontalLocation::STRETCH)
				this->width = parent->width;

			anchor.hLocation = hLocation;
		}

		void SetVerticalAnchor(VerticalLocation vLocation)
		{
			if (parent == nullptr)
				return;

			if (vLocation == VerticalLocation::STRETCH)
				this->height = parent->height;

			anchor.vLocation = vLocation;
		}

		void SetPivot(Location pivot)
		{
			this->pivot = pivot;
		}

		void SetPosition(const Vector& position) { this->position = position; }
		void SetRotation(const Vector& rotation) { this->rotation = rotation; }
		void SetScale(const Vector& scale) { this->scale = scale; }
		void SetWidth(float width) { this->width = width; }
		void SetHeight(float height) { this->height = height; }
		void SetEnable(bool enable) { this->isEnable = enable; }
		void SetParent(UIBase* parent)
		{
			if (parent == nullptr)
				return;

			if (this->parent != nullptr)
				this->parent->PopChild(this);

			this->parent = parent;
			parent->SetChild(this);
		}

		const Vector& GetPosition() { return position; }
		const Vector& GetRotation() { return rotation; }
		const Vector& GetScale() { return scale; }
		float GetWidth() { return width; }
		float GetHeight() { return height; }
		bool  GetEnable() { return isEnable; }
		Rect  GetUIRect()
		{
			auto screenPosition = GetScreenPosition();

			return Rect
			{
				static_cast<long>(screenPosition.x),
				static_cast<long>(screenPosition.y),
				static_cast<long>(screenPosition.x + width),
				static_cast<long>(screenPosition.y + height)
			};
		}

		Vector GetScreenPosition()
		{
			auto screenPosition = Vector::Zero;

			if (parent != nullptr)
			{
				screenPosition = parent->GetScreenPosition();

				switch (anchor.hLocation)
				{

				case HorizontalLocation::CENTER:
				{
					screenPosition.x += parent->width / 2;

					break;
				}

				case HorizontalLocation::RIGHT:
				{
					screenPosition.x += parent->width;

					break;
				}

				}

				switch (anchor.vLocation)
				{

				case VerticalLocation::MIDDLE:
				{
					screenPosition.y += parent->height / 2;

					break;
				}

				case VerticalLocation::BOTTOM:
				{
					screenPosition.y += parent->height;

					break;
				}

				}
			}

			switch (pivot.hLocation)
			{

			case HorizontalLocation::CENTER:
			{
				screenPosition.x -= width / 2 * scale.x;

				break;
			}

			case HorizontalLocation::RIGHT:
			{
				screenPosition.x -= width * scale.x;

				break;
			}

			}

			switch (pivot.vLocation)
			{

			case VerticalLocation::MIDDLE:
			{
				screenPosition.y -= height / 2 * scale.y;

				break;
			}

			case VerticalLocation::BOTTOM:
			{
				screenPosition.y -= height * scale.y;

				break;
			}

			}

			return position + screenPosition;
		}

	private:
		void SetChild(UIBase* child)
		{
			for (int i = 0; i < this->child.size(); i++)
			{
				if (this->child[i] == child)
					return;
			}

			this->child.push_back(child);
		}

		void PopChild(UIBase* child)
		{
			for (int i = 0; i < this->child.size(); i++)
			{
				if (this->child[i] == child)
				{
					this->child.erase(this->child.begin() + i);

					return;
				}
			}
		}
	};
}