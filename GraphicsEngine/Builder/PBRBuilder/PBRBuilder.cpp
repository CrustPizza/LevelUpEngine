/********************************
*								*
*	PBR Builder.cpp				*
*								*
*	Created : 2022/08/04		*
*	Updated : 2022/08/11		*
*********************************/

#include "PBRBuilder.h"

namespace GraphicsEngineSpace
{
	PBRBuilder::PBRBuilder()
	{

	}

	PBRBuilder::~PBRBuilder()
	{

	}

	PBRModel* PBRBuilder::CreateNoneTextureModel(const std::string& name, Factory* factory, ModelBase* model)
	{
		PBRModel* newPBRModel = SetStandard(name, factory, model);

		if (newPBRModel == nullptr)
			return nullptr;

		/* Vertex Shader */
		ShaderBase* vertexShader = GetBasicVS(factory);

		/* Pixel Shader */
		ShaderBase* pixelShader = GetConstValuePS(factory);

		/* Parameter Buffer */

		// VS Parameter
		BufferBase* paramBuffer = GetVSParameterCB(factory);

		ConstantBufferSetting vsParamBufferOption;

		vsParamBufferOption.buffer = paramBuffer;
		vsParamBufferOption.slot = 2;
		vsParamBufferOption.type = ShaderType::VERTEX;
		vsParamBufferOption.data = &newPBRModel->PBR_VSParameter;

		// PS Parameter
		paramBuffer = GetPSParameterCB(factory);

		ConstantBufferSetting psParamBufferOption;

		psParamBufferOption.buffer = paramBuffer;
		psParamBufferOption.slot = 3;
		psParamBufferOption.type = ShaderType::PIXEL;
		psParamBufferOption.data = &newPBRModel->PBR_PSParameter;

		newPBRModel->GetPrefab()->SetVertexShader(vertexShader);
		newPBRModel->GetPrefab()->SetPixelShader(pixelShader);
		newPBRModel->GetPrefab()->AddOnceBuffer(vsParamBufferOption);
		newPBRModel->GetPrefab()->AddOnceBuffer(psParamBufferOption);

		/* Vertex Buffer */
		CreateBasicVB(factory, newPBRModel->GetPrefab());

		return newPBRModel;
	}

	PBRModel* PBRBuilder::CreateAlbedoModel(const std::string& name, Factory* factory, ModelBase* model)
	{
		PBRModel* newPBRModel = SetStandard(name, factory, model);

		if (newPBRModel == nullptr)
			return nullptr;

		/* Vertex Shader */
		ShaderBase* vertexShader = GetBasicVS(factory);

		/* Pixel Shader */
		ShaderBase* pixelShader = GetAlebedoMapPS(factory);

		/* Parameter Buffer */

		// VS Parameter
		BufferBase* paramBuffer = GetVSParameterCB(factory);

		ConstantBufferSetting vsParamBufferOption;

		vsParamBufferOption.buffer = paramBuffer;
		vsParamBufferOption.slot = 2;
		vsParamBufferOption.type = ShaderType::VERTEX;
		vsParamBufferOption.data = &newPBRModel->PBR_VSParameter;

		// PS Parameter
		paramBuffer = GetPSParameterCB(factory);

		ConstantBufferSetting psParamBufferOption;

		psParamBufferOption.buffer = paramBuffer;
		psParamBufferOption.slot = 3;
		psParamBufferOption.type = ShaderType::PIXEL;
		psParamBufferOption.data = &newPBRModel->PBR_PSParameter;

		newPBRModel->GetPrefab()->SetVertexShader(vertexShader);
		newPBRModel->GetPrefab()->SetPixelShader(pixelShader);
		newPBRModel->GetPrefab()->AddOnceBuffer(vsParamBufferOption);
		newPBRModel->GetPrefab()->AddOnceBuffer(psParamBufferOption);

		/* Vertex Buffer */
		CreateBasicVB(factory, newPBRModel->GetPrefab());

		return newPBRModel;
	}

	PBRModel* PBRBuilder::CreateAlbedoNormalModel(const std::string& name, Factory* factory, ModelBase* model)
	{
		PBRModel* newPBRModel = SetStandard(name, factory, model);

		if (newPBRModel == nullptr)
			return nullptr;

		/* Vertex Shader */
		ShaderBase* vertexShader = GetNormalVS(factory);

		/* Pixel Shader */
		ShaderBase* pixelShader = GetAlebedoNormalMapPS(factory);

		/* Parameter Buffer */

		// VS Parameter
		BufferBase* paramBuffer = GetVSParameterCB(factory);

		ConstantBufferSetting vsParamBufferOption;

		vsParamBufferOption.buffer = paramBuffer;
		vsParamBufferOption.slot = 2;
		vsParamBufferOption.type = ShaderType::VERTEX;
		vsParamBufferOption.data = &newPBRModel->PBR_VSParameter;

		// PS Parameter
		paramBuffer = GetPSParameterCB(factory);

		ConstantBufferSetting psParamBufferOption;

		psParamBufferOption.buffer = paramBuffer;
		psParamBufferOption.slot = 3;
		psParamBufferOption.type = ShaderType::PIXEL;
		psParamBufferOption.data = &newPBRModel->PBR_PSParameter;

		newPBRModel->GetPrefab()->SetVertexShader(vertexShader);
		newPBRModel->GetPrefab()->SetPixelShader(pixelShader);
		newPBRModel->GetPrefab()->AddOnceBuffer(vsParamBufferOption);
		newPBRModel->GetPrefab()->AddOnceBuffer(psParamBufferOption);

		/* Vertex Buffer */
		CreateNormalVB(factory, newPBRModel->GetPrefab());

		return newPBRModel;
	}

	PBRModel* PBRBuilder::CreateSkinningModel(const std::string& name, Factory* factory, ModelBase* model)
	{
		PBRModel* newPBRModel = SetStandard(name, factory, model);

		if (newPBRModel == nullptr)
			return nullptr;

		/* Vertex Shader */
		ShaderBase* vertexShader = GetSkinnedVS(factory);

		/* Pixel Shader */
		ShaderBase* pixelShader = GetConstValuePS(factory);

		/* Parameter Buffer */

		// VS Parameter
		BufferBase* paramBuffer = GetVSParameterCB(factory);

		ConstantBufferSetting vsParamBufferOption;

		vsParamBufferOption.buffer = paramBuffer;
		vsParamBufferOption.slot = 2;
		vsParamBufferOption.type = ShaderType::VERTEX;
		vsParamBufferOption.data = &newPBRModel->PBR_VSParameter;

		// PS Parameter
		paramBuffer = GetPSParameterCB(factory);

		ConstantBufferSetting psParamBufferOption;

		psParamBufferOption.buffer = paramBuffer;
		psParamBufferOption.slot = 3;
		psParamBufferOption.type = ShaderType::PIXEL;
		psParamBufferOption.data = &newPBRModel->PBR_PSParameter;

		// Bone Matrix Buffer
		BufferBase* boneBuffer = GetBoneMatrixCB(factory);

		ConstantBufferSetting boneMatrixElements;

		boneMatrixElements.buffer = boneBuffer;
		boneMatrixElements.slot = 3;
		boneMatrixElements.type = ShaderType::VERTEX;
		boneMatrixElements.data = model->GetBoneMatrix();

		newPBRModel->GetPrefab()->SetVertexShader(vertexShader);
		newPBRModel->GetPrefab()->SetPixelShader(pixelShader);
		newPBRModel->GetPrefab()->AddOnceBuffer(vsParamBufferOption);
		newPBRModel->GetPrefab()->AddOnceBuffer(psParamBufferOption);
		newPBRModel->GetPrefab()->AddOnceBuffer(boneMatrixElements);

		/* Vertex Buffer */
		newPBRModel->GetPrefab()->SetSkinning(true);
		CreateSkinnedVB(factory, newPBRModel->GetPrefab());

		return newPBRModel;
	}

	PBRModel* PBRBuilder::CreateSkinningAlbedoModel(const std::string& name, Factory* factory, ModelBase* model)
	{
		PBRModel* newPBRModel = SetStandard(name, factory, model);

		if (newPBRModel == nullptr)
			return nullptr;

		/* Vertex Shader */
		ShaderBase* vertexShader = GetSkinnedVS(factory);

		/* Pixel Shader */
		ShaderBase* pixelShader = GetAlebedoMapPS(factory);

		/* Parameter Buffer */

		// VS Parameter
		BufferBase* paramBuffer = GetVSParameterCB(factory);

		ConstantBufferSetting vsParamBufferOption;

		vsParamBufferOption.buffer = paramBuffer;
		vsParamBufferOption.slot = 2;
		vsParamBufferOption.type = ShaderType::VERTEX;
		vsParamBufferOption.data = &newPBRModel->PBR_VSParameter;

		// PS Parameter
		paramBuffer = GetPSParameterCB(factory);

		ConstantBufferSetting psParamBufferOption;

		psParamBufferOption.buffer = paramBuffer;
		psParamBufferOption.slot = 3;
		psParamBufferOption.type = ShaderType::PIXEL;
		psParamBufferOption.data = &newPBRModel->PBR_PSParameter;

		// Bone Matrix Buffer
		BufferBase* boneBuffer = GetBoneMatrixCB(factory);

		ConstantBufferSetting boneMatrixElements;

		boneMatrixElements.buffer = boneBuffer;
		boneMatrixElements.slot = 3;
		boneMatrixElements.type = ShaderType::VERTEX;
		boneMatrixElements.data = model->GetBoneMatrix();

		newPBRModel->GetPrefab()->SetVertexShader(vertexShader);
		newPBRModel->GetPrefab()->SetPixelShader(pixelShader);
		newPBRModel->GetPrefab()->AddOnceBuffer(vsParamBufferOption);
		newPBRModel->GetPrefab()->AddOnceBuffer(psParamBufferOption);
		newPBRModel->GetPrefab()->AddOnceBuffer(boneMatrixElements);

		/* Vertex Buffer */
		newPBRModel->GetPrefab()->SetSkinning(true);
		CreateSkinnedVB(factory, newPBRModel->GetPrefab());

		return newPBRModel;
	}

	PBRModel* PBRBuilder::CreateSkinningAlbedoNormalModel(const std::string& name, Factory* factory, ModelBase* model)
	{
		PBRModel* newPBRModel = SetStandard(name, factory, model);

		if (newPBRModel == nullptr)
			return nullptr;

		/* Vertex Shader */
		ShaderBase* vertexShader = GetSkinnedNormalVS(factory);

		/* Pixel Shader */
		ShaderBase* pixelShader = GetAlebedoNormalMapPS(factory);

		/* Parameter Buffer */

		// VS Parameter
		BufferBase* paramBuffer = GetVSParameterCB(factory);

		ConstantBufferSetting vsParamBufferOption;

		vsParamBufferOption.buffer = paramBuffer;
		vsParamBufferOption.slot = 2;
		vsParamBufferOption.type = ShaderType::VERTEX;
		vsParamBufferOption.data = &newPBRModel->PBR_VSParameter;

		// PS Parameter
		paramBuffer = GetPSParameterCB(factory);

		ConstantBufferSetting psParamBufferOption;

		psParamBufferOption.buffer = paramBuffer;
		psParamBufferOption.slot = 3;
		psParamBufferOption.type = ShaderType::PIXEL;
		psParamBufferOption.data = &newPBRModel->PBR_PSParameter;

		// Bone Matrix Buffer
		BufferBase* boneBuffer = GetBoneMatrixCB(factory);

		ConstantBufferSetting boneMatrixElements;

		boneMatrixElements.buffer = boneBuffer;
		boneMatrixElements.slot = 3;
		boneMatrixElements.type = ShaderType::VERTEX;
		boneMatrixElements.data = model->GetBoneMatrix();

		newPBRModel->GetPrefab()->SetVertexShader(vertexShader);
		newPBRModel->GetPrefab()->SetPixelShader(pixelShader);
		newPBRModel->GetPrefab()->AddOnceBuffer(vsParamBufferOption);
		newPBRModel->GetPrefab()->AddOnceBuffer(psParamBufferOption);
		newPBRModel->GetPrefab()->AddOnceBuffer(boneMatrixElements);

		/* Vertex Buffer */
		newPBRModel->GetPrefab()->SetSkinning(true);
		CreateSkinnedNormalVB(factory, newPBRModel->GetPrefab());

		return newPBRModel;
	}

	PBRModel* PBRBuilder::CreateWithoutAOModel(const std::string& name, Factory* factory, ModelBase* model)
	{
		PBRModel* newPBRModel = SetStandard(name, factory, model);

		if (newPBRModel == nullptr)
			return nullptr;

		/* Vertex Shader */
		ShaderBase* vertexShader = GetSkinnedNormalVS(factory);

		/* Pixel Shader */
		ShaderBase* pixelShader = GetWithoutAOPS(factory);

		/* Parameter Buffer */

		// VS Parameter
		BufferBase* paramBuffer = GetVSParameterCB(factory);

		ConstantBufferSetting vsParamBufferOption;

		vsParamBufferOption.buffer = paramBuffer;
		vsParamBufferOption.slot = 2;
		vsParamBufferOption.type = ShaderType::VERTEX;
		vsParamBufferOption.data = &newPBRModel->PBR_VSParameter;

		// PS Parameter
		paramBuffer = GetPSParameterCB(factory);

		ConstantBufferSetting psParamBufferOption;

		psParamBufferOption.buffer = paramBuffer;
		psParamBufferOption.slot = 3;
		psParamBufferOption.type = ShaderType::PIXEL;
		psParamBufferOption.data = &newPBRModel->PBR_PSParameter;

		// Bone Matrix Buffer
		BufferBase* boneBuffer = GetBoneMatrixCB(factory);

		ConstantBufferSetting boneMatrixElements;

		boneMatrixElements.buffer = boneBuffer;
		boneMatrixElements.slot = 3;
		boneMatrixElements.type = ShaderType::VERTEX;
		boneMatrixElements.data = model->GetBoneMatrix();

		newPBRModel->GetPrefab()->SetVertexShader(vertexShader);
		newPBRModel->GetPrefab()->SetPixelShader(pixelShader);
		newPBRModel->GetPrefab()->AddOnceBuffer(vsParamBufferOption);
		newPBRModel->GetPrefab()->AddOnceBuffer(psParamBufferOption);
		newPBRModel->GetPrefab()->AddOnceBuffer(boneMatrixElements);

		/* Vertex Buffer */
		newPBRModel->GetPrefab()->SetSkinning(true);
		CreateSkinnedNormalVB(factory, newPBRModel->GetPrefab());

		return newPBRModel;
	}

	PBRModel* PBRBuilder::CreateWithoutAOStaticModel(const std::string& name, Factory* factory, ModelBase* model)
	{
		PBRModel* newPBRModel = SetStandard(name, factory, model);

		if (newPBRModel == nullptr)
			return nullptr;

		/* Vertex Shader */
		ShaderBase* vertexShader = GetNormalVS(factory);

		/* Pixel Shader */
		ShaderBase* pixelShader = GetWithoutAOPS(factory);

		/* Parameter Buffer */

		// VS Parameter
		BufferBase* paramBuffer = GetVSParameterCB(factory);

		ConstantBufferSetting vsParamBufferOption;

		vsParamBufferOption.buffer = paramBuffer;
		vsParamBufferOption.slot = 2;
		vsParamBufferOption.type = ShaderType::VERTEX;
		vsParamBufferOption.data = &newPBRModel->PBR_VSParameter;

		// PS Parameter
		paramBuffer = GetPSParameterCB(factory);

		ConstantBufferSetting psParamBufferOption;

		psParamBufferOption.buffer = paramBuffer;
		psParamBufferOption.slot = 3;
		psParamBufferOption.type = ShaderType::PIXEL;
		psParamBufferOption.data = &newPBRModel->PBR_PSParameter;

		newPBRModel->GetPrefab()->SetVertexShader(vertexShader);
		newPBRModel->GetPrefab()->SetPixelShader(pixelShader);
		newPBRModel->GetPrefab()->AddOnceBuffer(vsParamBufferOption);
		newPBRModel->GetPrefab()->AddOnceBuffer(psParamBufferOption);

		/* Vertex Buffer */
		CreateNormalVB(factory, newPBRModel->GetPrefab());

		return newPBRModel;
	}

	PBRModel* PBRBuilder::CreateAllTextureModel(const std::string& name, Factory* factory, ModelBase* model)
	{
		PBRModel* newPBRModel = SetStandard(name, factory, model);

		if (newPBRModel == nullptr)
			return nullptr;

		/* Vertex Shader */
		ShaderBase* vertexShader = GetSkinnedNormalVS(factory);

		/* Pixel Shader */
		ShaderBase* pixelShader = GetAllTexturePS(factory);

		/* Parameter Buffer */

		// VS Parameter
		BufferBase* paramBuffer = GetVSParameterCB(factory);

		ConstantBufferSetting vsParamBufferOption;

		vsParamBufferOption.buffer = paramBuffer;
		vsParamBufferOption.slot = 2;
		vsParamBufferOption.type = ShaderType::VERTEX;
		vsParamBufferOption.data = &newPBRModel->PBR_VSParameter;

		// PS Parameter
		paramBuffer = GetPSParameterCB(factory);

		ConstantBufferSetting psParamBufferOption;

		psParamBufferOption.buffer = paramBuffer;
		psParamBufferOption.slot = 3;
		psParamBufferOption.type = ShaderType::PIXEL;
		psParamBufferOption.data = &newPBRModel->PBR_PSParameter;

		// Bone Matrix Buffer
		BufferBase* boneBuffer = GetBoneMatrixCB(factory);

		ConstantBufferSetting boneMatrixElements;

		boneMatrixElements.buffer = boneBuffer;
		boneMatrixElements.slot = 3;
		boneMatrixElements.type = ShaderType::VERTEX;
		boneMatrixElements.data = model->GetBoneMatrix();

		newPBRModel->GetPrefab()->SetVertexShader(vertexShader);
		newPBRModel->GetPrefab()->SetPixelShader(pixelShader);
		newPBRModel->GetPrefab()->AddOnceBuffer(vsParamBufferOption);
		newPBRModel->GetPrefab()->AddOnceBuffer(psParamBufferOption);
		newPBRModel->GetPrefab()->AddOnceBuffer(boneMatrixElements);

		/* Vertex Buffer */
		newPBRModel->GetPrefab()->SetSkinning(true);
		CreateSkinnedNormalVB(factory, newPBRModel->GetPrefab());

		return newPBRModel;
	}

	PBRModel* PBRBuilder::CreateAllTextureStaticModel(const std::string& name, Factory* factory, ModelBase* model)
	{
		PBRModel* newPBRModel = SetStandard(name, factory, model);

		if (newPBRModel == nullptr)
			return nullptr;

		/* Vertex Shader */
		ShaderBase* vertexShader = GetNormalVS(factory);

		/* Pixel Shader */
		ShaderBase* pixelShader = GetAllTexturePS(factory);

		/* Parameter Buffer */

		// VS Parameter
		BufferBase* paramBuffer = GetVSParameterCB(factory);

		ConstantBufferSetting vsParamBufferOption;

		vsParamBufferOption.buffer = paramBuffer;
		vsParamBufferOption.slot = 2;
		vsParamBufferOption.type = ShaderType::VERTEX;
		vsParamBufferOption.data = &newPBRModel->PBR_VSParameter;

		// PS Parameter
		paramBuffer = GetPSParameterCB(factory);

		ConstantBufferSetting psParamBufferOption;

		psParamBufferOption.buffer = paramBuffer;
		psParamBufferOption.slot = 3;
		psParamBufferOption.type = ShaderType::PIXEL;
		psParamBufferOption.data = &newPBRModel->PBR_PSParameter;

		newPBRModel->GetPrefab()->SetVertexShader(vertexShader);
		newPBRModel->GetPrefab()->SetPixelShader(pixelShader);
		newPBRModel->GetPrefab()->AddOnceBuffer(vsParamBufferOption);
		newPBRModel->GetPrefab()->AddOnceBuffer(psParamBufferOption);

		/* Vertex Buffer */
		CreateNormalVB(factory, newPBRModel->GetPrefab());

		return newPBRModel;
	}

	PBRModel* PBRBuilder::SetStandard(const std::string& name, Factory* factory, ModelBase* model)
	{
		if (factory == nullptr)
			return nullptr;

		BufferBase* matrixCB = factory->resourceManager->GetBuffer("MatrixCB");

		if (matrixCB == nullptr)
			return nullptr;

		PBRModel* newPBRModel = new PBRModel;

		if (newPBRModel == nullptr)
		{
			matrixCB->Release();

			return nullptr;
		}

		PrefabBase* prefab = factory->CreatePrefab(name + "_Prefab", model, matrixCB, 0);

		if (prefab == nullptr)
		{
			matrixCB->Release();
			delete newPBRModel;

			return nullptr;
		}

		newPBRModel->SetPrefab(prefab);

		return newPBRModel;
	}

	ShaderBase* PBRBuilder::GetBasicVS(Factory* factory)
	{
		ShaderBase* vertexShader = factory->resourceManager->GetShader("PBRBasicVS");

		if (vertexShader == nullptr)
		{
			LayoutBase* pbrLayout = factory->CreateLayout("PBRBasicLayout");

			pbrLayout->AddElements("POSITION", 0, GraphicsFormat::Float_R32G32B32A32, 0, 0);
			pbrLayout->AddElements("NORMAL", 0, GraphicsFormat::Float_R32G32B32A32, 0, 16);
			pbrLayout->AddElements("TEXCOORD", 0, GraphicsFormat::Float_R32G32B32A32, 0, 32);

			vertexShader = factory->CreateVertexShader("PBRBasicVS", "Shader/PBRModel/PBRModelVS.hlsl", "BasicMain", "vs_5_0", pbrLayout);

			pbrLayout->Release();

			if (vertexShader == nullptr)
				return nullptr;
		}

		return vertexShader;
	}

	ShaderBase* PBRBuilder::GetNormalVS(Factory* factory)
	{
		ShaderBase* vertexShader = factory->resourceManager->GetShader("PBRNormalVS");

		if (vertexShader == nullptr)
		{
			LayoutBase* pbrLayout = factory->CreateLayout("PBRNormalLayout");

			pbrLayout->AddElements("POSITION", 0, GraphicsFormat::Float_R32G32B32A32, 0, 0);
			pbrLayout->AddElements("NORMAL", 0, GraphicsFormat::Float_R32G32B32A32, 0, 16);
			pbrLayout->AddElements("TEXCOORD", 0, GraphicsFormat::Float_R32G32B32A32, 0, 32);
			pbrLayout->AddElements("TANGENT", 0, GraphicsFormat::Float_R32G32B32A32, 0, 48);

			vertexShader = factory->CreateVertexShader("PBRNormalVS", "Shader/PBRModel/PBRModelVS.hlsl", "NormalMain", "vs_5_0", pbrLayout);

			pbrLayout->Release();

			if (vertexShader == nullptr)
				return nullptr;
		}

		return vertexShader;
	}

	ShaderBase* PBRBuilder::GetSkinnedVS(Factory* factory)
	{
		ShaderBase* vertexShader = factory->resourceManager->GetShader("PBRSkinnedVS");

		if (vertexShader == nullptr)
		{
			LayoutBase* pbrLayout = factory->CreateLayout("PBRSkinnedLayout");

			pbrLayout->AddElements("POSITION", 0, GraphicsFormat::Float_R32G32B32A32, 0, 0);
			pbrLayout->AddElements("NORMAL", 0, GraphicsFormat::Float_R32G32B32A32, 0, 16);
			pbrLayout->AddElements("TEXCOORD", 0, GraphicsFormat::Float_R32G32B32A32, 0, 32);
			pbrLayout->AddElements("BLENDWEIGHT", 0, GraphicsFormat::Float_R32G32B32A32, 0, 48);
			pbrLayout->AddElements("BLENDWEIGHT", 1, GraphicsFormat::Float_R32G32B32A32, 0, 64);
			pbrLayout->AddElements("BLENDWEIGHT", 2, GraphicsFormat::Float_R32G32B32A32, 0, 80);
			pbrLayout->AddElements("BLENDWEIGHT", 3, GraphicsFormat::Float_R32G32B32A32, 0, 96);
			pbrLayout->AddElements("BLENDINDICES", 0, GraphicsFormat::UINT_R8G8B8A8, 0, 112);
			pbrLayout->AddElements("BLENDINDICES", 1, GraphicsFormat::UINT_R8G8B8A8, 0, 116);
			pbrLayout->AddElements("BLENDINDICES", 2, GraphicsFormat::UINT_R8G8B8A8, 0, 120);
			pbrLayout->AddElements("BLENDINDICES", 3, GraphicsFormat::UINT_R8G8B8A8, 0, 124);

			vertexShader = factory->CreateVertexShader("PBRSkinnedVS", "Shader/PBRModel/PBRModelVS.hlsl", "SkinnedMain", "vs_5_0", pbrLayout);

			pbrLayout->Release();

			if (vertexShader == nullptr)
				return nullptr;
		}

		return vertexShader;
	}

	ShaderBase* PBRBuilder::GetSkinnedNormalVS(Factory* factory)
	{
		ShaderBase* vertexShader = factory->resourceManager->GetShader("PBRSkinnedNormalVS");

		if (vertexShader == nullptr)
		{
			LayoutBase* pbrLayout = factory->CreateLayout("PBRSkinnedNormalLayout");

			pbrLayout->AddElements("POSITION", 0, GraphicsFormat::Float_R32G32B32A32, 0, 0);
			pbrLayout->AddElements("NORMAL", 0, GraphicsFormat::Float_R32G32B32A32, 0, 16);
			pbrLayout->AddElements("TEXCOORD", 0, GraphicsFormat::Float_R32G32B32A32, 0, 32);
			pbrLayout->AddElements("TANGENT", 0, GraphicsFormat::Float_R32G32B32A32, 0, 48);
			pbrLayout->AddElements("BLENDWEIGHT", 0, GraphicsFormat::Float_R32G32B32A32, 0, 64);
			pbrLayout->AddElements("BLENDWEIGHT", 1, GraphicsFormat::Float_R32G32B32A32, 0, 80);
			pbrLayout->AddElements("BLENDWEIGHT", 2, GraphicsFormat::Float_R32G32B32A32, 0, 96);
			pbrLayout->AddElements("BLENDWEIGHT", 3, GraphicsFormat::Float_R32G32B32A32, 0, 112);
			pbrLayout->AddElements("BLENDINDICES", 0, GraphicsFormat::UINT_R8G8B8A8, 0, 128);
			pbrLayout->AddElements("BLENDINDICES", 1, GraphicsFormat::UINT_R8G8B8A8, 0, 132);
			pbrLayout->AddElements("BLENDINDICES", 2, GraphicsFormat::UINT_R8G8B8A8, 0, 136);
			pbrLayout->AddElements("BLENDINDICES", 3, GraphicsFormat::UINT_R8G8B8A8, 0, 140);

			vertexShader = factory->CreateVertexShader("PBRSkinnedNormalVS", "Shader/PBRModel/PBRModelVS.hlsl", "SkinnedNormalMain", "vs_5_0", pbrLayout);

			pbrLayout->Release();

			if (vertexShader == nullptr)
				return nullptr;
		}

		return vertexShader;
	}

	ShaderBase* PBRBuilder::GetConstValuePS(Factory* factory)
	{
		ShaderBase* pixelShader = factory->resourceManager->GetShader("PBRConstVarPS");

		if (pixelShader == nullptr)
		{
			pixelShader = factory->CreatePixelShader("PBRConstVarPS", "Shader/PBRModel/PBRModelPS.hlsl", "ConstVarMain", "ps_5_0");

			if (pixelShader == nullptr)
				return nullptr;
		}

		return pixelShader;
	}

	ShaderBase* PBRBuilder::GetAlebedoMapPS(Factory* factory)
	{
		ShaderBase* pixelShader = factory->resourceManager->GetShader("PBRAlbedoPS");

		if (pixelShader == nullptr)
		{
			pixelShader = factory->CreatePixelShader("PBRAlbedoPS", "Shader/PBRModel/PBRModelPS.hlsl", "AlbedoMain", "ps_5_0");

			if (pixelShader == nullptr)
				return nullptr;
		}

		return pixelShader;
	}

	ShaderBase* PBRBuilder::GetAlebedoNormalMapPS(Factory* factory)
	{
		ShaderBase* pixelShader = factory->resourceManager->GetShader("PBRAlbedoNormalPS");

		if (pixelShader == nullptr)
		{
			pixelShader = factory->CreatePixelShader("PBRAlbedoNormalPS", "Shader/PBRModel/PBRModelPS.hlsl", "AlbedoNormalMain", "ps_5_0");

			if (pixelShader == nullptr)
				return nullptr;
		}

		return pixelShader;
	}

	ShaderBase* PBRBuilder::GetWithoutAOPS(Factory* factory)
	{
		ShaderBase* pixelShader = factory->resourceManager->GetShader("PBRWithoutAOPS");

		if (pixelShader == nullptr)
		{
			pixelShader = factory->CreatePixelShader("PBRWithoutAOPS", "Shader/PBRModel/PBRModelPS.hlsl", "WithoutAOMain", "ps_5_0");

			if (pixelShader == nullptr)
				return nullptr;
		}

		return pixelShader;
	}

	ShaderBase* PBRBuilder::GetAllTexturePS(Factory* factory)
	{
		ShaderBase* pixelShader = factory->resourceManager->GetShader("PBRAllTexturePS");

		if (pixelShader == nullptr)
		{
			pixelShader = factory->CreatePixelShader("PBRAllTexturePS", "Shader/PBRModel/PBRModelPS.hlsl", "AllTextureMain", "ps_5_0");

			if (pixelShader == nullptr)
				return nullptr;
		}

		return pixelShader;
	}

	BufferBase* PBRBuilder::GetVSParameterCB(Factory* factory)
	{
		// VS Parameter
		BufferBase* paramBuffer = factory->resourceManager->GetBuffer("PBR_VSParameterCB");

		if (paramBuffer == nullptr)
		{
			paramBuffer = factory->CreateConstantBuffer("PBR_VSParameterCB", USAGE::DEFAULT, 0, sizeof(Vector));

			if (paramBuffer == nullptr)
				return nullptr;
		}

		return paramBuffer;
	}

	BufferBase* PBRBuilder::GetPSParameterCB(Factory* factory)
	{
		// PS Parameter
		BufferBase* paramBuffer = factory->resourceManager->GetBuffer("PBR_PSParameterCB");

		if (paramBuffer == nullptr)
		{
			paramBuffer = factory->CreateConstantBuffer("PBR_PSParameterCB", USAGE::DEFAULT, 0, sizeof(Vector) * 2);

			if (paramBuffer == nullptr)
				return nullptr;
		}

		return paramBuffer;
	}

	BufferBase* PBRBuilder::GetBoneMatrixCB(Factory* factory)
	{
		// PS Parameter
		BufferBase* boneBuffer = factory->resourceManager->GetBuffer("BoneMatrixCB");

		if (boneBuffer == nullptr)
		{
			boneBuffer = factory->CreateConstantBuffer("BoneMatrixCB", USAGE::DEFAULT, 0, sizeof(Matrix) * 64);

			if (boneBuffer == nullptr)
				return nullptr;
		}

		return boneBuffer;
	}

	void PBRBuilder::CreateBasicVB(Factory* factory, PrefabBase* prefab)
	{
		struct NoneTexturePBRVertex
		{
			Vector position;
			Vector normal;
			Vector texCoord;
		};

		prefab->CreateVertexBuffer<NoneTexturePBRVertex>(factory, [&](const VertexData& data) -> NoneTexturePBRVertex
			{
				NoneTexturePBRVertex temp;
				temp.position = data.position;
				temp.normal = data.normal;
				temp.texCoord = data.texCoord;

				return temp;
			});
	}

	void PBRBuilder::CreateNormalVB(Factory* factory, PrefabBase* prefab)
	{
		struct NoneTexturePBRVertex
		{
			Vector position;
			Vector normal;
			Vector texCoord;
			Vector tangent;
		};

		prefab->CreateVertexBuffer<NoneTexturePBRVertex>(factory, [&](const VertexData& data) -> NoneTexturePBRVertex
			{
				NoneTexturePBRVertex temp;
				temp.position = data.position;
				temp.normal = data.normal;
				temp.texCoord = data.texCoord;
				temp.tangent = data.tangent;

				return temp;
			});
	}

	void PBRBuilder::CreateSkinnedVB(Factory* factory, PrefabBase* prefab)
	{
		struct SkinnedPBRVertex
		{
			Vector position;
			Vector normal;
			Vector texCoord;
			Vector weights1;
			Vector weights2;
			Vector weights3;
			Vector weights4;
			unsigned int weightIndex1;
			unsigned int weightIndex2;
			unsigned int weightIndex3;
			unsigned int weightIndex4;
		};

		prefab->CreateVertexBuffer<SkinnedPBRVertex>(factory, [&](const VertexData& data) -> SkinnedPBRVertex
			{
				SkinnedPBRVertex temp;
				temp.position = data.position;
				temp.normal = data.normal;
				temp.texCoord = data.texCoord;
				temp.weights1 = data.weights1;
				temp.weights2 = data.weights2;
				temp.weights3 = data.weights3;
				temp.weights4 = data.weights4;
				temp.weightIndex1 = data.weightIndex1;
				temp.weightIndex2 = data.weightIndex2;
				temp.weightIndex3 = data.weightIndex3;
				temp.weightIndex4 = data.weightIndex4;

				return temp;
			});
	}

	void PBRBuilder::CreateSkinnedNormalVB(Factory* factory, PrefabBase* prefab)
	{
		struct SkinnedPBRVertex
		{
			Vector position;
			Vector normal;
			Vector texCoord;
			Vector tangent;
			Vector weights1;
			Vector weights2;
			Vector weights3;
			Vector weights4;
			unsigned int weightIndex1;
			unsigned int weightIndex2;
			unsigned int weightIndex3;
			unsigned int weightIndex4;
		};

		prefab->CreateVertexBuffer<SkinnedPBRVertex>(factory, [&](const VertexData& data) -> SkinnedPBRVertex
			{
				SkinnedPBRVertex temp;
				temp.position = data.position;
				temp.normal = data.normal;
				temp.texCoord = data.texCoord;
				temp.tangent = data.tangent;
				temp.weights1 = data.weights1;
				temp.weights2 = data.weights2;
				temp.weights3 = data.weights3;
				temp.weights4 = data.weights4;
				temp.weightIndex1 = data.weightIndex1;
				temp.weightIndex2 = data.weightIndex2;
				temp.weightIndex3 = data.weightIndex3;
				temp.weightIndex4 = data.weightIndex4;

				return temp;
			});
	}
}