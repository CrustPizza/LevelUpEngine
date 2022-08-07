/********************************
*								*
*	Camera.h					*
*								*
*	Created : 2022/07/20		*
*	Updated : 2022/07/20		*
*********************************/

#pragma once

#include "../HeraclesMath/HeraclesMath.h"

#pragma comment(lib, "../MathLibrary/HeraclesMath.lib")

namespace GameEngineSpace
{
	using namespace HeraclesMath;

	class Camera
	{
		Matrix view;
		Matrix projection;

		float nearZ;
		float farZ;
		float fov;
		float aspectRatio;

		Vector position;
		Vector rotation;

		Vector right;
		Vector up;
		Vector look;

		float cameraSpeed;

	public:
		Camera();
		~Camera();

		void CameraMove(float tick);
		void CameraRotation();

		const Matrix& GetView();
		const Matrix& GetProjection();
		const Vector& GetWorldPosition();

		void LookAt(const Vector& targetPos);

		void UpdateViewMatrix();
		void UpdateProjectionMatrix(float width, float height);
	};
}