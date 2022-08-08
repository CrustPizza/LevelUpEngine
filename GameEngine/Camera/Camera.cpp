/********************************
*								*
*	Camera.cpp					*
*								*
*	Created : 2022/07/20		*
*	Updated : 2022/07/20		*
*********************************/

#include "Camera.h"
#include "Manager/Input/Input.h"

namespace GameEngineSpace
{
	Camera::Camera()
		: view{}
		, projection{}
		, nearZ(0.1f)
		, farZ(1000.0f)
		, fov(PI / 2)
		, aspectRatio(1.0f)
		, position{ 0.0f, 3.0f, -20.0f, 1.0f }
		, rotation{ 0.0f, 0.0f, 0.0f, 0.0f }
		, right{}
		, up{}
		, look{}
		, cameraSpeed(10.0f)
	{

	}

	Camera::~Camera()
	{

	}

	void Camera::CameraMove(float tick)
	{
		// 좌, 우
		if (Input::GetInstance()->GetInputState('A', KeyState::STAY))
		{
			position -= right * cameraSpeed * tick;
			UpdateViewMatrix();
		}

		if (Input::GetInstance()->GetInputState('D', KeyState::STAY))
		{
			position += right * cameraSpeed * tick;
			UpdateViewMatrix();
		}

		// 상, 하
		if (Input::GetInstance()->GetInputState('Q', KeyState::STAY))
		{
			position -= up * cameraSpeed * tick;
			UpdateViewMatrix();
		}

		if (Input::GetInstance()->GetInputState('E', KeyState::STAY))
		{
			position += up * cameraSpeed * tick;
			UpdateViewMatrix();
		}

		// 앞, 뒤
		if (Input::GetInstance()->GetInputState('W', KeyState::STAY))
		{
			position += look * cameraSpeed * tick;
			UpdateViewMatrix();
		}

		if (Input::GetInstance()->GetInputState('S', KeyState::STAY))
		{
			position -= look * cameraSpeed * tick;
			UpdateViewMatrix();
		}
	}

	void Camera::CameraRotation()
	{
		// 카메라 마우스 회전
		if (Input::GetInstance()->GetInputState(VK_RBUTTON, KeyState::STAY))
		{
			Vector moveVector = Input::GetInstance()->GetMouseMoveVector();

			// x, y값이 반대로 들어가는 이유..
			// x회전이 상하 회전 (마우스 기준 y축)
			// y회전이 좌우 회전 (마우스 기준 x축)
			rotation[0] += moveVector[1];
			rotation[1] += moveVector[0];
			UpdateViewMatrix();
		}
	}

	const Matrix& Camera::GetView()
	{
		return view;
	}

	const Matrix& Camera::GetProjection()
	{
		return projection;
	}

	const Vector& Camera::GetWorldPosition()
	{
		return position;
	}

	void Camera::LookAt(const Vector& targetPos)
	{
		view = MatrixLookAtLH(position, targetPos, Vector::UnitY);

		right = { view[0][0], view[1][0], view[2][0], 0.0f };
		up = -Vector{ view[0][1], view[1][1], view[2][1], 0.0f };
		look = { view[0][2], view[1][2], view[2][2], 0.0f };

		rotation = ConvertRotationMatrixToEuler(MatrixInverse(view));
	}

	void Camera::UpdateViewMatrix()
	{
		view = ViewMatrix(position, rotation);

		right = { view[0][0], view[1][0], view[2][0], 0.0f };
		up = { view[0][1], view[1][1], view[2][1], 0.0f };
		look = { view[0][2], view[1][2], view[2][2], 0.0f };
	}

	void Camera::UpdateProjectionMatrix(float width, float height)
	{
		aspectRatio = width / height;

		projection = PerspectiveMatrix(fov, aspectRatio, nearZ, farZ);
	}
}