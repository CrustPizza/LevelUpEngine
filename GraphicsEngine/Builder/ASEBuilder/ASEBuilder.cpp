/********************************
*								*
*	ASE Builder.cpp				*
*								*
*	Created : 2022/07/08		*
*	Updated : 2022/08/03		*
*********************************/

#include <assert.h>
#include "ASEBuilder.h"

namespace GraphicsEngineSpace
{
	ASEBuilder::ASEBuilder(const std::string& path, const std::string& functionName)
		: aseParser(nullptr)
		, xyzSwap{ 0, 1, 2 }
		, xyzSign{ 1, 1, 1 }
		, indices(nullptr)
		, indicesSize(0)
		, useAnimation(false)
	{
		hDll = LoadLibraryA(path.c_str());

		if (hDll == nullptr)
			assert(0);

		ASEParserConstructor parserConstructor = (ASEParserConstructor)GetProcAddress(hDll, functionName.c_str());
		aseParser = parserConstructor();

		if (aseParser == nullptr)
			assert(0);
	}

	ASEBuilder::~ASEBuilder()
	{
		if (aseParser != nullptr)
			delete aseParser;

		if (hDll != nullptr)
			FreeLibrary(hDll);

		if (indices != nullptr)
			delete indices;
	}

	ModelBase* ASEBuilder::CreateModel(const std::string& path, Factory* factory, const std::string& animationKey, SwapOrder swapOrder, SignOrder signOrder)
	{
		ModelBase* newModel = new ModelBase;

		if (newModel == nullptr)
			return nullptr;

		aseParser->LoadASEFile(path);

		SetSwap(swapOrder);
		SetSign(signOrder);

		if (animationKey.length() != 0)
		{
			useAnimation = true;
			this->animationKey = animationKey;
		}

		const SceneInfo& sceneInfo = aseParser->GetSceneInfo();

		// Material
		const std::map<int, MaterialInfo>& materials = aseParser->GetMaterials();

		for (auto& iter : materials)
		{
			if (iter.second.subMaterial.size() == 0)
			{
				MaterialBase* newMaterial = CreateMaterial(factory, iter.second);

				newModel->materials[iter.first] = newMaterial;
			}
			else
			{
				for (auto& subIter : iter.second.subMaterial)
				{
					MaterialBase* newMaterial = CreateMaterial(factory, subIter.second);

					newModel->materials[subIter.first] = newMaterial;
				}

				break;
			}
		}

		// Helper
		const std::vector<HelperInfo>& helpers = aseParser->GetHelpers();

		for (auto& iter : helpers)
		{
			HelperBase* newHelper = CreateHelper(iter);

			newModel->helpers.push_back(newHelper);

			if (useAnimation != true)
				continue;

			const AnimationInfo& animationInfo = iter.animationInfo;

			if (animationInfo.controlInfo.posSample.empty() && animationInfo.controlInfo.rotSample.empty())
				continue;

			AnimationBase* newAnimation = CreateAnimation(animationInfo, sceneInfo);

			newHelper->animations[animationKey] = newAnimation;
		}

		// Shape
		const std::vector<ShapeInfo>& shapes = aseParser->GetShapes();

		for (auto& iter : shapes)
		{
			ShapeBase* newShape = CreateShape(iter);

			newModel->shapes.push_back(newShape);

			if (useAnimation != true)
				continue;

			const AnimationInfo& animationInfo = iter.animationInfo;

			if (animationInfo.controlInfo.posSample.empty() && animationInfo.controlInfo.rotSample.empty())
				continue;

			AnimationBase* newAnimation = CreateAnimation(animationInfo, sceneInfo);

			newShape->animations[animationKey] = newAnimation;
		}

		// Mesh
		const std::vector<GeometryInfo>& geometries = aseParser->GetGeoMetries();

		Vector minPos = { FLT_MAX, FLT_MAX, FLT_MAX, 1.0f };
		Vector maxPos = { FLT_MIN, FLT_MIN, FLT_MIN, 1.0f };

		for (auto& iter : geometries)
		{
			MeshBase* newMesh = CreateMesh(iter);

			newMesh->indexBuffer = factory->CreateIndexBuffer(newMesh->GetName() + "_IB", USAGE::DEFAULT, 0, sizeof(WORD), indices, indicesSize);

			newModel->meshes.push_back(newMesh);

			for (int i = 0; i < 3; i++)
			{
				if (minPos[i] > newMesh->boundingBoxMin[i])
					minPos[i] = newMesh->boundingBoxMin[i];

				if (maxPos[i] < newMesh->boundingBoxMax[i])
					maxPos[i] = newMesh->boundingBoxMax[i];
			}

			if (useAnimation != true)
				continue;

			const AnimationInfo& animationInfo = iter.animationInfo;

			if (animationInfo.controlInfo.posSample.empty() && animationInfo.controlInfo.rotSample.empty())
				continue;

			AnimationBase* newAnimation = CreateAnimation(animationInfo, sceneInfo);

			newMesh->animations[animationKey] = newAnimation;
		}

		// Bone
		for (int i = 0; i < geometries.size(); i++)
		{
			if (geometries[i].boneInfo.boneList.empty() == true)
				continue;

			MeshBase* skin = newModel->meshes[i];
			newModel->meshes.erase(newModel->meshes.begin() + i);

			minPos = skin->boundingBoxMin;
			maxPos = skin->boundingBoxMax;

			for (auto& iter : geometries[i].boneInfo.boneList)
			{
				for (int j = 0; j < newModel->meshes.size(); j++)
				{
					if (iter.boneName.compare(newModel->meshes[j]->GetName()) != 0)
						continue;

					BoneBase* newBone = CreateBone(newModel->meshes[j], skin);

					if (newBone == nullptr)
						continue;

					newModel->bones.push_back(newBone);

					delete newModel->meshes[j];
					newModel->meshes.erase(newModel->meshes.begin() + j);

					break;
				}
			}

			for (auto* iter : newModel->meshes)
			{
				HelperBase* newHelper = new HelperBase;

				if (newHelper == nullptr)
					continue;

				newHelper->ConvertMeshToHelper(iter);

				newModel->helpers.push_back(newHelper);
				delete iter;
			}

			newModel->meshes.clear();
			newModel->meshes.push_back(skin);
			newModel->boneMatrix = new Matrix[64];

			break;
		}

		newModel->boundingBoxMin = minPos;
		newModel->boundingBoxMax = maxPos;

		newModel->SetHierarchy();
		SetOriginalLocation(newModel);

		return newModel;
	}

	ModelBase* ASEBuilder::CreateAnimation(const std::string& path, Factory* factory, const std::string& animationKey, SwapOrder swapOrder, SignOrder signOrder)
	{
		ModelBase* newModel = new ModelBase;

		if (newModel == nullptr)
			return nullptr;

		aseParser->LoadASEFile(path);

		SetSwap(swapOrder);
		SetSign(signOrder);

		const SceneInfo& sceneInfo = aseParser->GetSceneInfo();

		// Helper
		const std::vector<HelperInfo>& helpers = aseParser->GetHelpers();

		for (auto& iter : helpers)
		{
			const AnimationInfo& animationInfo = iter.animationInfo;

			if (animationInfo.controlInfo.posSample.empty() && animationInfo.controlInfo.rotSample.empty())
				continue;

			HelperBase* newHelper = new HelperBase;
			newHelper->SetName(iter.currentNode);

			newModel->helpers.push_back(newHelper);

			AnimationBase* newAnimation = CreateAnimation(animationInfo, sceneInfo);

			newHelper->animations[animationKey] = newAnimation;
		}

		// Shape
		const std::vector<ShapeInfo>& shapes = aseParser->GetShapes();

		for (auto& iter : shapes)
		{
			const AnimationInfo& animationInfo = iter.animationInfo;

			if (animationInfo.controlInfo.posSample.empty() && animationInfo.controlInfo.rotSample.empty())
				continue;

			ShapeBase* newShape = new ShapeBase;
			newShape->SetName(iter.currentNode);

			newModel->shapes.push_back(newShape);

			AnimationBase* newAnimation = CreateAnimation(animationInfo, sceneInfo);

			newShape->animations[animationKey] = newAnimation;
		}

		// Mesh
		const std::vector<GeometryInfo>& geometries = aseParser->GetGeoMetries();

		for (auto& iter : geometries)
		{
			MeshBase* newMesh = new MeshBase;
			newMesh->SetName(iter.currentNode);

			newModel->meshes.push_back(newMesh);

			const AnimationInfo& animationInfo = iter.animationInfo;

			if (animationInfo.controlInfo.posSample.empty() && animationInfo.controlInfo.rotSample.empty())
				continue;

			AnimationBase* newAnimation = CreateAnimation(animationInfo, sceneInfo);

			newMesh->animations[animationKey] = newAnimation;
		}

		// Bone
		for (int i = 0; i < geometries.size(); i++)
		{
			if (geometries[i].boneInfo.boneList.empty() == true)
				continue;

			MeshBase* skin = newModel->meshes[i];
			newModel->meshes.erase(newModel->meshes.begin() + i);

			for (auto& iter : geometries[i].boneInfo.boneList)
			{
				for (int j = 0; j < newModel->meshes.size(); j++)
				{
					if (iter.boneName.compare(newModel->meshes[j]->GetName()) != 0)
						continue;

					BoneBase* newBone = new BoneBase;

					newModel->bones.push_back(newBone);

					newBone->ConvertMeshToBone(newModel->meshes[j]);

					delete newModel->meshes[j];
					newModel->meshes.erase(newModel->meshes.begin() + j);

					break;
				}
			}

			for (auto* iter : newModel->meshes)
			{
				HelperBase* newHelper = new HelperBase;

				if (newHelper == nullptr)
					continue;

				newHelper->ConvertMeshToHelper(iter);

				newModel->helpers.push_back(newHelper);
				delete iter;
			}

			newModel->meshes.clear();
			newModel->meshes.push_back(skin);

			break;
		}

 		return newModel;
	}

	void ASEBuilder::MergeAnimation(ModelBase* boneModel, ModelBase* animation)
	{
		for (auto* meshIter : boneModel->meshes)
		{
			for (auto* animationIter : animation->meshes)
			{
				if (meshIter->GetName().compare(animationIter->GetName()) != 0)
					continue;

				for (auto& iter : animationIter->animations)
				{
					meshIter->animations[iter.first] = iter.second;
					iter.second = nullptr;
				}

				break;
			}
		}

		for (auto* helperIter : boneModel->helpers)
		{
			for (auto* animationIter : animation->helpers)
			{
				if (helperIter->GetName().compare(animationIter->GetName()) != 0)
					continue;

				for (auto& iter : animationIter->animations)
				{
					helperIter->animations[iter.first] = iter.second;
					iter.second = nullptr;
				}

				break;
			}
		}

		for (auto* shapeIter : boneModel->shapes)
		{
			for (auto* animationIter : animation->shapes)
			{
				if (shapeIter->GetName().compare(animationIter->GetName()) != 0)
					continue;

				for (auto& iter : animationIter->animations)
				{
					shapeIter->animations[iter.first] = iter.second;
					iter.second = nullptr;
				}

				break;
			}
		}

		for (auto* boneIter : boneModel->bones)
		{
			for (auto* animationIter : animation->bones)
			{
				if (boneIter->GetName().compare(animationIter->GetName()) != 0)
					continue;

				for (auto& iter : animationIter->animations)
				{
					boneIter->animations[iter.first] = iter.second;
					iter.second = nullptr;
				}

				break;
			}
		}
	}

	void ASEBuilder::SetSwap(SwapOrder swapOrder)
	{
		// XYZ 좌표 변환
		switch (swapOrder)
		{

		case SwapOrder::XYZ:
			xyzSwap[0] = 0;
			xyzSwap[1] = 1;
			xyzSwap[2] = 2;
			break;

		case SwapOrder::XZY:
			xyzSwap[0] = 0;
			xyzSwap[2] = 1;
			xyzSwap[1] = 2;
			break;

		case SwapOrder::YXZ:
			xyzSwap[1] = 0;
			xyzSwap[0] = 1;
			xyzSwap[2] = 2;
			break;

		case SwapOrder::YZX:
			xyzSwap[1] = 0;
			xyzSwap[2] = 1;
			xyzSwap[0] = 2;
			break;

		case SwapOrder::ZXY:
			xyzSwap[2] = 0;
			xyzSwap[0] = 1;
			xyzSwap[1] = 2;
			break;

		case SwapOrder::ZYX:
			xyzSwap[2] = 0;
			xyzSwap[1] = 1;
			xyzSwap[0] = 2;
			break;
		}
	}

	void ASEBuilder::SetSign(SignOrder signOrder)
	{
		xyzSign[0] = 1;
		xyzSign[1] = 1;
		xyzSign[2] = 1;

		// XYZ 부호 변환
		switch (signOrder)
		{
		case SignOrder::MMM:
			xyzSign[0] = -1;
		case SignOrder::PMM:
			xyzSign[1] = -1;
		case SignOrder::PPM:
			xyzSign[2] = -1;
			break;

		case SignOrder::MPM:
			xyzSign[2] = -1;
		case SignOrder::MPP:
			xyzSign[0] = -1;
			break;

		case SignOrder::MMP:
			xyzSign[0] = -1;
		case SignOrder::PMP:
			xyzSign[1] = -1;
			break;
		}
	}

	BoneBase* ASEBuilder::CreateBone(MeshBase* bone, MeshBase* skin)
	{
		BoneBase* newBone = new BoneBase;

		if (newBone == nullptr)
			return nullptr;

		Matrix boneWorld = bone->GetTransform().GetWorldTransform();
		Matrix boneInvWorld = MatrixInverse(boneWorld);

		Matrix skinWorld = skin->GetTransform().GetWorldTransform();

		Matrix boneOffset = skinWorld * boneInvWorld;

		newBone->SetOffSet(boneOffset);

		newBone->ConvertMeshToBone(bone);

		return newBone;
	}

	MeshBase* ASEBuilder::CreateMesh(const GeometryInfo& geometry)
	{
		Vector minPos = { FLT_MAX, FLT_MAX, FLT_MAX, 1.0f };
		Vector maxPos = { FLT_MIN, FLT_MIN, FLT_MIN, 1.0f };

		MeshBase* newMesh = new MeshBase;

		if (newMesh == nullptr)
			return nullptr;

		newMesh->SetName(geometry.currentNode);
		newMesh->SetParentName(geometry.parentNode);
		Matrix& world = newMesh->GetTransform().GetWorldTransform();

		// Transform
		for (const auto& iter : geometry.nodeList)
		{
			Matrix nodeTM;
			nodeTM = iter.second.transform;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
					world[i][j] = xyzSign[j] * nodeTM[xyzSwap[i]][xyzSwap[j]];

				world[3][i] = xyzSign[i] * nodeTM[3][xyzSwap[i]];
			}

			world[3][3] = 1.0f;
		}

		// Transform에서 로컬 SRT 추출
		newMesh->GetTransform().DecomposeWorldTransform(world);

		// 버텍스에 곱할 역행렬
		Matrix invWorld = MatrixInverse(world);

		// Mesh
		const VertexInfo& vertex = geometry.meshInfo.vertexInfo;
		const FaceInfo& face = geometry.meshInfo.faceInfo;
		const NormalInfo& normal = geometry.meshInfo.normalInfo;
		const TextureInfo& texture = geometry.meshInfo.textureInfo;

		// Vertex
		UINT verticesSize = vertex.verticesSize;
		std::vector<VertexData>& vertices = newMesh->vertices;
		vertices.resize(verticesSize);

		for (unsigned int i = 0; i < verticesSize; i++)
		{
			Vector tempVertex;

			for (int j = 0; j < 3; j++)
				tempVertex[j] = xyzSign[j] * vertex.vertices[i].r[xyzSwap[j] + 1];

			// Position
			for (int j = 0; j < 3; j++)
			{
				if (tempVertex[j] < minPos[j])
					minPos[j] = tempVertex[j];
				else if (tempVertex[j] > maxPos[j])
					maxPos[j] = tempVertex[j];

				vertices[i].position[j] =
					invWorld[0][j] * tempVertex[0] +
					invWorld[1][j] * tempVertex[1] +
					invWorld[2][j] * tempVertex[2] +
					invWorld[3][j];
			}

			vertices[i].position[3] = 1.0f;

			// Normal
			for (int j = 0; j < 3; j++)
				vertices[i].normal[j] = xyzSign[j] * vertex.vertices[i].normal[xyzSwap[j] + 1];

			vertices[i].normal[3] = 0.0f;

			// Texture
			vertices[i].texCoord = { 0.0f, 0.0f, 0.0f, 0.0f };

			if (vertex.vertices[i].textureIndex < texture.tVertex.size())
			{
				vertices[i].texCoord[0] = texture.tVertex[vertex.vertices[i].textureIndex].x;
				vertices[i].texCoord[1] = 1.0f - texture.tVertex[vertex.vertices[i].textureIndex].y;
			}

			vertices[i].weightIndex1 = 0;
			vertices[i].weightIndex2 = 0;
			vertices[i].weightIndex3 = 0;
			vertices[i].weightIndex4 = 0;

			float sum = 0.0f;

			for (int j = 0; j < 4; j++)
			{
				vertices[i].weightIndex1 |= (vertex.vertices[i].weightIndex[j] & 0xff) << (8 * j);
				vertices[i].weights1[j] = vertex.vertices[i].weights[j];

				vertices[i].weightIndex2 |= (vertex.vertices[i].weightIndex[j + 4] & 0xff) << (8 * j);
				vertices[i].weights2[j] = vertex.vertices[i].weights[j + 4];

				vertices[i].weightIndex3 |= (vertex.vertices[i].weightIndex[j + 8] & 0xff) << (8 * j);
				vertices[i].weights3[j] = vertex.vertices[i].weights[j + 8];

				vertices[i].weightIndex4 |= (vertex.vertices[i].weightIndex[j + 12] & 0xff) << (8 * j);
				vertices[i].weights4[j] = vertex.vertices[i].weights[j + 12];

				sum += vertex.vertices[i].weights[j];
				sum += vertex.vertices[i].weights[j + 4];
				sum += vertex.vertices[i].weights[j + 8];
				sum += vertex.vertices[i].weights[j + 12];
			}

			if (sum != 1.0f)
			{
				for (int j = 0; j < 4; j++)
				{
					vertices[i].weights1[j] /= sum;
					vertices[i].weights2[j] /= sum;
					vertices[i].weights3[j] /= sum;
					vertices[i].weights4[j] /= sum;
				}
			}

			vertices[i].tangent = { 0.0f, 0.0f, 0.0f, 0.0f };
		}

		// Face
		if (indices != nullptr)
			delete indices;

		indicesSize = face.facesSize * 3;
		indices = new WORD[indicesSize];

		for (unsigned int i = 0; i < face.facesSize; i++)
		{
			unsigned int index[3] =
			{
				face.faces[i].index[xyzSwap[0] + 1],
				face.faces[i].index[xyzSwap[1] + 1],
				face.faces[i].index[xyzSwap[2] + 1]
			};

			for (unsigned int j = 0; j < 3; j++)
			{
				// Index
				indices[i * 3 + j] = index[j];
			}

			// Tangent Space
			Vector p0 = vertices[index[0]].position;
			Vector p1 = vertices[index[1]].position;
			Vector p2 = vertices[index[2]].position;

			Vector w0 = vertices[index[0]].texCoord;
			Vector w1 = vertices[index[1]].texCoord;
			Vector w2 = vertices[index[2]].texCoord;

			Vector e1 = p1 - p0;
			Vector e2 = p2 - p0;

			float x1 = w1[0] - w0[0];
			float y1 = w1[1] - w0[1];

			float x2 = w2[0] - w0[0];
			float y2 = w2[1] - w0[1];

			float numerator = x1 * y2 - x2 * y1;

			if (numerator == 0.0f)
				numerator = 0.0001f;

			float r = 1.0f / numerator;

			Vector t = (e1 * y2 - e2 * y1) * r;
			Vector b = (e2 * x1 - e1 * x2) * r;

			vertices[index[0]].tangent += t;
			vertices[index[1]].tangent += t;
			vertices[index[2]].tangent += t;
			vertices[index[0]].binormal += b;
			vertices[index[1]].binormal += b;
			vertices[index[2]].binormal += b;
		}

		// 축 반전으로 인해 앞면 뒷면이 뒤집히면 인덱스를 뒤집어준다.
		if (xyzSign[0] * xyzSign[1] * xyzSign[2] < 0)
			std::reverse(indices, indices + indicesSize);

		for (int i = 0; i < vertex.verticesSize; i++)
		{
			Vector& n = vertices[i].normal;
			Vector& t = vertices[i].tangent;
			Vector& b = vertices[i].binormal;
			t = t - Vector3Dot(t, n) * n;
			b = Vector3Cross(n, t);
			//b = DirectX::XMVector3Normalize(b - DirectX::XMVector3Dot(b, n) * n - DirectX::XMVector3Dot(b, t) * t);
			//DirectX::XMVECTOR dotResult = DirectX::XMVector3Dot(DirectX::XMVector3Cross(n, t), b);
			//float sign = dotResult.m128_f32[0] < 0 ? -1.0f : 1.0f;
			//b *= sign;
		}

		newMesh->boundingBoxMin = minPos;
		newMesh->boundingBoxMax = maxPos;

		return newMesh;
	}

	ShapeBase* ASEBuilder::CreateShape(const ShapeInfo& shape)
	{
		ShapeBase* newShape = new ShapeBase;

		if (newShape == nullptr)
			return nullptr;

		newShape->SetName(shape.currentNode);
		newShape->SetParentName(shape.parentNode);
		Matrix& world = newShape->GetTransform().GetWorldTransform();

		// Transform
		for (const auto& iter : shape.nodeList)
		{
			Matrix nodeTM;
			nodeTM = iter.second.transform;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
					world[i][j] = xyzSign[j] * nodeTM[xyzSwap[i]][xyzSwap[j]];

				world[3][i] = xyzSign[i] * nodeTM[3][xyzSwap[i]];
			}

			world[3][3] = 1.0f;
		}

		// Transform에서 로컬 SRT 추출
		newShape->GetTransform().DecomposeWorldTransform(world);

		return newShape;
	}

	HelperBase* ASEBuilder::CreateHelper(const HelperInfo& helper)
	{
		HelperBase* newHelper = new HelperBase;

		if (newHelper == nullptr)
			return nullptr;

		newHelper->SetName(helper.currentNode);
		newHelper->SetParentName(helper.parentNode);
		Matrix& world = newHelper->GetTransform().GetWorldTransform();

		// Transform
		for (const auto& iter : helper.nodeList)
		{
			Matrix nodeTM;
			nodeTM = iter.second.transform;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
					world[i][j] = xyzSign[j] * nodeTM[xyzSwap[i]][xyzSwap[j]];

				world[3][i] = xyzSign[i] * nodeTM[3][xyzSwap[i]];
			}

			world[3][3] = 1.0f;
		}

		// Transform에서 로컬 SRT 추출
		newHelper->GetTransform().DecomposeWorldTransform(world);

		return newHelper;
	}

	MaterialBase* ASEBuilder::CreateMaterial(Factory* const factory, const MaterialInfo& material)
	{
		MaterialBase* newMaterial = new MaterialBase;

		MaterialData matData;

		// Ambient
		matData.ambient[0] = material.ambient[xyzSwap[0]];
		matData.ambient[1] = material.ambient[xyzSwap[1]];
		matData.ambient[2] = material.ambient[xyzSwap[2]];

		// Diffuse
		matData.diffuse[0] = material.diffuse[xyzSwap[0]];
		matData.diffuse[1] = material.diffuse[xyzSwap[1]];
		matData.diffuse[2] = material.diffuse[xyzSwap[2]];

		// Specular
		matData.specular[0] = material.specular[xyzSwap[0]];
		matData.specular[1] = material.specular[xyzSwap[1]];
		matData.specular[2] = material.specular[xyzSwap[2]];

		// Maps
		for (auto& map : material.maps)
		{
			MapData tempMapData;

			// Texture
			int index = map.bitmap.rfind('\\');

			if (index != -1)
			{
				std::string path = "Resources/Texture/" + map.bitmap.substr(index + 1);

				tempMapData.map = factory->CreateTexture(map.bitmap.substr(index + 1), path);

				// Type
				tempMapData.type = static_cast<GraphicsEngineSpace::MapType>(map.type);
			}
			else
			{
				continue;
			}

			// Offset
			tempMapData.offset[0] = map.uOffset;
			tempMapData.offset[1] = map.vOffset;

			// Tiling
			tempMapData.tiling[0] = map.uTiling;
			tempMapData.tiling[1] = map.vTiling;

			matData.maps.push_back(tempMapData);
		}

		newMaterial->SetMaterial(matData);

		return newMaterial;
	}

	AnimationBase* ASEBuilder::CreateAnimation(const AnimationInfo& animation, const SceneInfo& sceneInfo)
	{
		AnimationBase* newAnimation = new AnimationBase;

		// Control Info
		const ControlInfo& controlInfo = animation.controlInfo;

		// Animation Pos
		for (const auto& iter : controlInfo.posSample)
		{
			Vector animPos =
			{
				xyzSign[0] * iter.r[xyzSwap[0]],
				xyzSign[1] * iter.r[xyzSwap[1]],
				xyzSign[2] * iter.r[xyzSwap[2]],
				1.0f
			};

			float tick = (iter.tick / static_cast<float>(sceneInfo.tick) - sceneInfo.firstFrame) * (1.0f / sceneInfo.frameSpeed);

			newAnimation->positions.push_back({ tick, animPos });
		}

		Vector angle = {};
		// Animation Rot
		for (const auto& iter : controlInfo.rotSample)
		{
			angle = ConvertRotationAxisAngleToQuaternion({ iter.r[xyzSwap[0]], iter.r[xyzSwap[1]], iter.r[xyzSwap[2]] }, iter.w);

			float tick = (iter.tick / static_cast<float>(sceneInfo.tick) - sceneInfo.firstFrame) * (1.0f / sceneInfo.frameSpeed);

			newAnimation->rotations.push_back({ tick, angle });
		}

		return newAnimation;
	}

	void ASEBuilder::SetOriginalLocation(ModelBase* model)
	{
		for (auto* mesh : model->meshes)
		{
			mesh->GetTransform().SetOriginal();
		}

		for (auto* shape : model->shapes)
		{
			shape->GetTransform().SetOriginal();
		}

		for (auto* helper : model->helpers)
		{
			helper->GetTransform().SetOriginal();
		}

		for (auto* bone : model->bones)
		{
			bone->GetTransform().SetOriginal();
		}
	}
}