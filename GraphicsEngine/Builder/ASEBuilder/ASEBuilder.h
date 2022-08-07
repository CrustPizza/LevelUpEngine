/********************************
*								*
*	ASE Builder.h				*
*								*
*	Created : 2022/07/08		*
*	Updated : 2022/07/19		*
*********************************/

#pragma once

#include <string>
#include <Windows.h>
#include "../ASEParser/ASEParserFramework.h"
#include "Bases/MeshBase.h"
#include "Bases/BoneBase.h"
#include "Bases/ShapeBase.h"
#include "Bases/ModelBase.h"
#include "Bases/LayoutBase.h"
#include "Bases/HelperBase.h"
#include "Bases/MaterialBase.h"
#include "Bases/AnimationBase.h"
#include "GraphicsEngine/Factory/Factory.h"

namespace GraphicsEngineSpace
{
	enum class SwapOrder
	{
		XYZ,
		XZY,
		YXZ,
		YZX,
		ZXY,
		ZYX
	};

	enum class SignOrder
	{
		PPP,
		PPM,
		PMP,
		MPP,
		PMM,
		MPM,
		MMP,
		MMM
	};

	class ASEBuilder
	{
		HMODULE hDll;
		ASEParser* aseParser;

		WORD*	indices;
		UINT	indicesSize;

		int xyzSwap[3];
		int xyzSign[3];

		bool useAnimation;

		std::string animationKey;

	public:
		ASEBuilder(const std::string& path, const std::string& functionName);
		~ASEBuilder();

		ModelBase* CreateModel(const std::string& path, Factory* factory, const std::string& animationKey = "", SwapOrder swapOrder = SwapOrder::XYZ, SignOrder signOrder = SignOrder::PPP);
		ModelBase* CreateAnimation(const std::string& path, Factory* factory, const std::string& animationKey = "", SwapOrder swapOrder = SwapOrder::XYZ, SignOrder signOrder = SignOrder::PPP);

		void MergeAnimation(ModelBase* boneModel, ModelBase* animation);

	private:
		void SetSwap(SwapOrder swapOrder);
		void SetSign(SignOrder signOrder);

		BoneBase* CreateBone(MeshBase* bone, MeshBase* skin);
		MeshBase* CreateMesh(const GeometryInfo& geometry);
		ShapeBase* CreateShape(const ShapeInfo& shape);
		HelperBase* CreateHelper(const HelperInfo& helper);
		MaterialBase* CreateMaterial(Factory* const factory, const MaterialInfo& material);
		AnimationBase* CreateAnimation(const AnimationInfo& animation, const SceneInfo& sceneInfo);

		void SetOriginalLocation(ModelBase* model);
	};
}