/********************************
*								*
*	UI Base.h					*
*								*
*	Created : 2022/08/08		*
*	Updated : 2022/08/08		*
*********************************/

#pragma once

#include "Bases/ResourceBase.h"

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

		UIBase* parent;
		Vector position;
		Vector scale;

	private:
		Vector screenPosition;
	
	protected:
		UIBase()
			: anchor{ HorizontalLocation::CENTER, VerticalLocation::MIDDLE }
			, pivot{ HorizontalLocation::CENTER, VerticalLocation::MIDDLE }
			, width(0.0f)
			, height(0.0f)
			, parent(nullptr)
			, position(Vector::Zero)
			, scale(Vector::One)
			, screenPosition(Vector::Zero) {}

	public:
		virtual ~UIBase() = default;

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
		void SetScale(const Vector& scale) { this->scale = scale; }
		void SetWidth(float width) { this->width = width; }
		void SetHeight(float height) { this->height = height; }
		void SetParent(UIBase* parent) { this->parent = parent; }
		
		const Vector& GetPosition() { return position; }
		const Vector& GetScale() { return scale; }
		float GetWidth() { return width; }
		float GetHeight() { return height; }

	protected:
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
	};
}