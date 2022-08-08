/********************************
*								*
*	Factory.cpp					*
*								*
*	Created : 2022/07/01		*
*	Updated : 2022/07/26		*
*********************************/

#include "Factory.h"
#include "Bases/PrefabBase.h"
#include "Builder/ASEBuilder/ASEBuilder.h"
#include "Builder/PBRBuilder/PBRBuilder.h"

namespace GraphicsEngineSpace
{
	Factory::Factory()
		: graphicsFactory(nullptr)
		, resourceManager(nullptr)
	{

	}

	Factory::~Factory()
	{
		if (graphicsFactory != nullptr)
			delete graphicsFactory;
	}

	ModelBase* Factory::CreateModelFromASEFile(const std::string& name, const std::string& path, const std::string& animationKey)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr)
			return nullptr;

#ifdef x64
#ifdef _DEBUG
		ASEBuilder aseBuilder("DLL/ASEParser_Debug_x64.dll", "CreateASEParser");
#else
		ASEBuilder aseBuilder("DLL/ASEParser_Release_x64.dll", "CreateASEParser");
#endif
#else
#ifdef _DEBUG
		ASEBuilder aseBuilder("DLL/ASEParser_Debug_x86.dll", "CreateASEParser");
#else
		ASEBuilder aseBuilder("DLL/ASEParser_Release_x86.dll", "CreateASEParser");
#endif
#endif

		ModelBase* newModel = aseBuilder.CreateModel(path, this, animationKey, SwapOrder::XZY);

		if (newModel == nullptr)
			return nullptr;

		if (resourceManager->AddModel(name, newModel) != true)
		{
			newModel->Release();

			return nullptr;
		}

		return resourceManager->GetModel(name);
	}

	ModelBase* Factory::CreateAnimationFromASEFile(const std::string& name, const std::string& path, const std::string& animationKey)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr)
			return nullptr;

		ModelBase* animationModel = resourceManager->GetModel(name);

		if (animationModel == nullptr)
			return nullptr;

#ifdef x64
#ifdef _DEBUG
		ASEBuilder aseBuilder("DLL/ASEParser_Debug_x64.dll", "CreateASEParser");
#else
		ASEBuilder aseBuilder("DLL/ASEParser_Release_x64.dll", "CreateASEParser");
#endif
#else
#ifdef _DEBUG
		ASEBuilder aseBuilder("DLL/ASEParser_Debug_x86.dll", "CreateASEParser");
#else
		ASEBuilder aseBuilder("DLL/ASEParser_Release_x86.dll", "CreateASEParser");
#endif
#endif

		ModelBase* newAnimation = aseBuilder.CreateAnimation(path, this, animationKey, SwapOrder::XZY);

		if (newAnimation == nullptr)
		{
			animationModel->Release();

			return nullptr;
		}

		aseBuilder.MergeAnimation(animationModel, newAnimation);
		delete newAnimation;

		return animationModel;
	}

	TextureBase* Factory::CreateTexture(const std::string& name, const std::string& path)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr)
			return nullptr;

		TextureBase* newTexture = graphicsFactory->CreateTexture(name, path);

		if (newTexture == nullptr)
			return nullptr;

		if (resourceManager->AddTexture(name, newTexture) != true)
		{
			newTexture->Release();

			return nullptr;
		}

		return resourceManager->GetTexture(name);
	}

	LayoutBase* Factory::CreateLayout(const std::string& name)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr)
			return nullptr;

		LayoutBase* newLayout = graphicsFactory->CreateLayout(name);

		if (newLayout == nullptr)
			return nullptr;

		if (resourceManager->AddLayout(name, newLayout) != true)
		{
			newLayout->Release();

			return nullptr;
		}

		return resourceManager->GetLayout(name);
	}

	ShaderBase* Factory::CreateVertexShader(const std::string& name, const std::string& path, const char* entryName, const char* shaderModel, LayoutBase* layout)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr)
			return nullptr;

		ShaderBase* newShader = graphicsFactory->CreateVertexShader(name, path, entryName, shaderModel, layout);

		if (newShader == nullptr)
			return nullptr;

		if (resourceManager->AddShader(name, newShader) != true)
		{
			newShader->Release();

			return nullptr;
		}

		return resourceManager->GetShader(name);
	}

	ShaderBase* Factory::CreatePixelShader(const std::string& name, const std::string& path, const char* entryName, const char* shaderModel)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr)
			return nullptr;

		ShaderBase* newShader = graphicsFactory->CreatePixelShader(name, path, entryName, shaderModel);

		if (newShader == nullptr)
			return nullptr;

		if (resourceManager->AddShader(name, newShader) != true)
		{
			newShader->Release();

			return nullptr;
		}

		return resourceManager->GetShader(name);
	}

	BufferBase* Factory::CreateVertexBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize, void* dataPtr, UINT size)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr)
			return nullptr;

		BufferBase* newBuffer = graphicsFactory->CreateVertexBuffer(name, usage, CPUflag, typeSize, dataPtr, size);

		if (newBuffer == nullptr)
			return nullptr;

		if (resourceManager->AddBuffer(name, newBuffer) != true)
		{
			int count = 1;

			while (resourceManager->AddBuffer(name + std::to_string(count++), newBuffer) != true)
			{
				if (count >= 100)
					return nullptr;
			}
		}

		return resourceManager->GetBuffer(name);
	}

	BufferBase* Factory::CreateIndexBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize, void* dataPtr, UINT size)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr)
			return nullptr;

		BufferBase* newBuffer = graphicsFactory->CreateIndexBuffer(name, usage, CPUflag, typeSize, dataPtr, size);

		if (newBuffer == nullptr)
			return nullptr;

		if (resourceManager->AddBuffer(name, newBuffer) != true)
		{
			newBuffer->Release();

			return nullptr;
		}

		return resourceManager->GetBuffer(name);
	}

	BufferBase* Factory::CreateConstantBuffer(const std::string& name, USAGE usage, UINT CPUflag, UINT typeSize)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr)
			return nullptr;

		BufferBase* newBuffer = graphicsFactory->CreateConstantBuffer(name, usage, CPUflag, typeSize);

		if (newBuffer == nullptr)
			return nullptr;

		if (resourceManager->AddBuffer(name, newBuffer) != true)
		{
			newBuffer->Release();

			return nullptr;
		}

		return resourceManager->GetBuffer(name);
	}

	SamplerBase* Factory::CreateSampler(const std::string& name, FilterOption filter)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr)
			return nullptr;

		SamplerBase* newSampler = graphicsFactory->CreateSampler(name, filter);

		if (newSampler == nullptr)
			return nullptr;

		if (resourceManager->AddSampler(name, newSampler) != true)
		{
			newSampler->Release();

			return nullptr;
		}

		return resourceManager->GetSampler(name);
	}

	PrefabBase* Factory::CreatePrefab(const std::string& name, ModelBase* model, BufferBase* matrixBuffer, UINT slot)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr)
			return nullptr;

		ConstantBufferSetting matrixBufferOption;

		matrixBufferOption.buffer = matrixBuffer;
		matrixBufferOption.slot = slot;
		matrixBufferOption.type = ShaderType::VERTEX;
		matrixBufferOption.data = nullptr;

		PrefabBase* newPrefab = new PrefabBase(model, matrixBufferOption);

		if (newPrefab == nullptr)
			return nullptr;

		if (resourceManager->AddPrefab(name, newPrefab) != true)
		{
			newPrefab->Release();

			return nullptr;
		}

		return resourceManager->GetPrefab(name);
	}

	SkyBoxBase* Factory::CreateSkyBox(const std::string& name)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr)
			return nullptr;

		/* Vertex Shader */
		ShaderBase* skyBoxVS = resourceManager->GetShader("SkyBoxVS");

		if (skyBoxVS == nullptr)
		{
			LayoutBase* layout = CreateLayout("SkyBoxLayout");

			layout->AddElements("SV_POSITION", 0, GraphicsFormat::Float_R32G32B32A32, 0, 0);

			skyBoxVS = CreateVertexShader("SkyBoxVS", "Shader/SkyBox/SkyBoxVS.hlsl", "main", "vs_5_0", layout);

			resourceManager->SubLayout("SkyBoxLayout");

			if (skyBoxVS == nullptr)
				return nullptr;
		}

		/* Pixel Shader */
		ShaderBase* skyBoxPS = resourceManager->GetShader("SkyBoxPS");

		if (skyBoxPS == nullptr)
		{
			skyBoxPS = CreatePixelShader("SkyBoxPS", "Shader/SkyBox/SkyBoxPS.hlsl", "main", "ps_5_0");

			if (skyBoxPS == nullptr)
				return nullptr;
		}

		/* Vertex Buffer */
		BufferBase* skyBoxVB = resourceManager->GetBuffer("SkyBoxVB");

		if (skyBoxVB == nullptr)
		{
			Vector vertices[24] =
			{
				{ +1.0f, +1.0f, +1.0f, 1.0f },
				{ +1.0f, -1.0f, +1.0f, 1.0f },
				{ -1.0f, -1.0f, +1.0f, 1.0f },
				{ -1.0f, +1.0f, +1.0f, 1.0f },
				{ -1.0f, +1.0f, -1.0f, 1.0f },
				{ -1.0f, -1.0f, -1.0f, 1.0f },
				{ +1.0f, -1.0f, -1.0f, 1.0f },
				{ +1.0f, +1.0f, -1.0f, 1.0f },
				{ +1.0f, +1.0f, -1.0f, 1.0f },
				{ +1.0f, -1.0f, -1.0f, 1.0f },
				{ +1.0f, -1.0f, +1.0f, 1.0f },
				{ +1.0f, +1.0f, +1.0f, 1.0f },
				{ -1.0f, +1.0f, +1.0f, 1.0f },
				{ -1.0f, -1.0f, +1.0f, 1.0f },
				{ -1.0f, -1.0f, -1.0f, 1.0f },
				{ -1.0f, +1.0f, -1.0f, 1.0f },
				{ -1.0f, +1.0f, +1.0f, 1.0f },
				{ -1.0f, +1.0f, -1.0f, 1.0f },
				{ +1.0f, +1.0f, -1.0f, 1.0f },
				{ +1.0f, +1.0f, +1.0f, 1.0f },
				{ +1.0f, -1.0f, +1.0f, 1.0f },
				{ +1.0f, -1.0f, -1.0f, 1.0f },
				{ -1.0f, -1.0f, -1.0f, 1.0f },
				{ -1.0f, -1.0f, +1.0f, 1.0f }
			};
			skyBoxVB = CreateVertexBuffer("SkyBoxVB", USAGE::DEFAULT, 0, sizeof(Vector), vertices, 24);

			if (skyBoxVB == nullptr)
				return nullptr;
		}

		/* Index Buffer */
		BufferBase* skyBoxIB = resourceManager->GetBuffer("SkyBoxIB");

		if (skyBoxIB == nullptr)
		{
			WORD indices[36] =
			{
				0, 1, 2,
				0, 2, 3,
				4, 5, 6,
				4, 6, 7,
				8, 9, 10,
				8, 10, 11,
				12, 13, 14,
				12, 14, 15,
				16, 17, 18,
				16, 18, 19,
				20, 21, 22,
				20, 22, 23
				//2, 1, 0,
				//3, 2, 0,
				//6, 5, 4,
				//7, 6, 4,
				//10, 9, 8,
				//11, 10, 8,
				//14, 13, 12,
				//15, 14, 12,
				//18, 17, 16,
				//19, 18, 16,
				//22, 21, 20,
				//23, 22, 20
			};
			skyBoxIB = CreateIndexBuffer("SkyBoxIB", USAGE::DEFAULT, 0, sizeof(WORD), indices, 36);

			if (skyBoxIB == nullptr)
				return nullptr;
		}

		/* View Projection Buffer */
		BufferBase* viewProjBuffer = resourceManager->GetBuffer("ViewProjectionCB");

		if (viewProjBuffer == nullptr)
		{
			viewProjBuffer = CreateConstantBuffer("ViewProjectionCB", USAGE::DEFAULT, 0, sizeof(Matrix));

			if (viewProjBuffer == nullptr)
				return nullptr;
		}

		/* Sampler */
		SamplerBase* sampler = resourceManager->GetSampler("LinearSampler");

		if (sampler == nullptr)
		{
			sampler = CreateSampler("LinearSampler", FilterOption::LINEAR);

			if (sampler == nullptr)
				return nullptr;
		}

		SkyBoxBase* newSkyBox = new SkyBoxBase;

		if (newSkyBox == nullptr)
			return nullptr;

		newSkyBox->vertexShader = skyBoxVS;
		newSkyBox->pixelShader = skyBoxPS;
		newSkyBox->vertexBuffer = skyBoxVB;
		newSkyBox->indexBuffer = skyBoxIB;
		newSkyBox->viewProjBuffer = viewProjBuffer;
		newSkyBox->sampler = sampler;

		if (resourceManager->AddSkyBox(name, newSkyBox) != true)
		{
			newSkyBox->Release();

			return nullptr;
		}

		return resourceManager->GetSkyBox(name);
	}

	PBRModel* Factory::CreateNoneTextureModel(const std::string& name, ModelBase* model)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr || model == nullptr)
			return nullptr;

		PBRBuilder builder;

		PBRModel* newPBRModel = builder.CreateNoneTextureModel(name, this, model);

		if (newPBRModel == nullptr)
			return nullptr;

		if (resourceManager->AddPBRModel(name, newPBRModel) != true)
		{
			newPBRModel->Release();

			return nullptr;
		}

		return resourceManager->GetPBRModel(name);
	}

	PBRModel* Factory::CreateAlbedoModel(const std::string& name, ModelBase* model)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr || model == nullptr)
			return nullptr;

		PBRBuilder builder;

		PBRModel* newPBRModel = builder.CreateAlbedoModel(name, this, model);

		if (newPBRModel == nullptr)
			return nullptr;

		if (resourceManager->AddPBRModel(name, newPBRModel) != true)
		{
			newPBRModel->Release();

			return nullptr;
		}

		return resourceManager->GetPBRModel(name);
	}

	PBRModel* Factory::CreateAlbedoNormalModel(const std::string& name, ModelBase* model)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr || model == nullptr)
			return nullptr;

		PBRBuilder builder;

		PBRModel* newPBRModel = builder.CreateAlbedoNormalModel(name, this, model);

		if (newPBRModel == nullptr)
			return nullptr;

		if (resourceManager->AddPBRModel(name, newPBRModel) != true)
		{
			newPBRModel->Release();

			return nullptr;
		}

		return resourceManager->GetPBRModel(name);
	}

	PBRModel* Factory::CreateSkinningModel(const std::string& name, ModelBase* model)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr || model == nullptr)
			return nullptr;

		PBRBuilder builder;

		PBRModel* newPBRModel = builder.CreateSkinningModel(name, this, model);

		if (newPBRModel == nullptr)
			return nullptr;

		if (resourceManager->AddPBRModel(name, newPBRModel) != true)
		{
			newPBRModel->Release();

			return nullptr;
		}

		return resourceManager->GetPBRModel(name);
	}

	PBRModel* Factory::CreateSkinningAlbedoModel(const std::string& name, ModelBase* model)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr || model == nullptr)
			return nullptr;

		PBRBuilder builder;

		PBRModel* newPBRModel = builder.CreateSkinningAlbedoModel(name, this, model);

		if (newPBRModel == nullptr)
			return nullptr;

		if (resourceManager->AddPBRModel(name, newPBRModel) != true)
		{
			newPBRModel->Release();

			return nullptr;
		}

		return resourceManager->GetPBRModel(name);
	}

	IBLTexture* Factory::CreateIBLTexture(const std::string& name, const std::string& radiancePath, const std::string& irradiancePath)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr)
			return nullptr;

		IBLTexture* newIBLTexture = new IBLTexture;

		if (newIBLTexture == nullptr)
			return nullptr;

		if (resourceManager->AddIBLTexture(name, newIBLTexture) != true)
		{
			delete newIBLTexture;

			return nullptr;
		}

		TextureBase* radiance = CreateTexture(name + "_radiance", radiancePath);

		if (radiance == nullptr)
		{
			delete newIBLTexture;

			return nullptr;
		}

		TextureBase* irradiance = CreateTexture(name + "_irradiance", irradiancePath);

		if (irradiance == nullptr)
		{
			delete newIBLTexture;
			delete radiance;

			return nullptr;
		}

		BufferBase* mipLevelCB = CreateConstantBuffer(name + "_CB", USAGE::DEFAULT, 0, sizeof(int) * 4);

		if (mipLevelCB == nullptr)
		{
			delete newIBLTexture;
			delete radiance;
			delete irradiance;

			return nullptr;
		}

		newIBLTexture->SetIBLTexture(radiance, irradiance, mipLevelCB);

		return resourceManager->GetIBLTexture(name);
	}

	DirectionalLight* Factory::CreateDirectionalLight(const std::string& name)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr)
			return nullptr;

		DirectionalLight* newLight = new DirectionalLight;

		BufferBase* constantBuffer = resourceManager->GetBuffer("DirectionalLightCB");

		if (constantBuffer == nullptr)
		{
			constantBuffer = CreateConstantBuffer("DirectionalLightCB", USAGE::DEFAULT, 0, sizeof(Vector) * 4);

			if (constantBuffer == nullptr)
			{
				delete newLight;

				return nullptr;
			}
		}

		if (resourceManager->AddLight(name, newLight) != true)
		{
			delete newLight;

			return nullptr;
		}

		newLight->SetBuffer(constantBuffer);

		return dynamic_cast<DirectionalLight*>(resourceManager->GetLight(name));
	}

	PointLight* Factory::CreatePointLight(const std::string& name)
	{
		if (graphicsFactory == nullptr || resourceManager == nullptr)
			return nullptr;

		PointLight* newLight = new PointLight;

		BufferBase* constantBuffer = resourceManager->GetBuffer("PointLightCB");

		if (constantBuffer == nullptr)
		{
			constantBuffer = CreateConstantBuffer("PointLightCB", USAGE::DEFAULT, 0, sizeof(Vector) * 3);

			if (constantBuffer == nullptr)
			{
				delete newLight;

				return nullptr;
			}
		}

		if (resourceManager->AddLight(name, newLight) != true)
		{
			delete newLight;

			return nullptr;
		}

		newLight->SetBuffer(constantBuffer);

		return dynamic_cast<PointLight*>(resourceManager->GetLight(name));
	}

	bool Factory::InitFactory(FactoryBase* factory, ResourceManager* resourceManager)
	{
		if (graphicsFactory != nullptr)
			return false;

		if (factory == nullptr)
			return false;

		graphicsFactory = factory;
		this->resourceManager = resourceManager;

		InitDefaultData();

		return true;
	}

	void Factory::InitDefaultData()
	{
		/* Matrix Buffer */
		CreateConstantBuffer("MatrixCB", USAGE::DEFAULT, 0, sizeof(Matrix) * 2);

		/* View Buffer*/
		CreateConstantBuffer("ViewProjectionCB", USAGE::DEFAULT, 0, sizeof(Matrix));
		CreateConstantBuffer("ViewWorldPosCB", USAGE::DEFAULT, 0, sizeof(Vector));

		/* Material Buffer */
		CreateConstantBuffer("LegacyMaterialCB", USAGE::DEFAULT, 0, sizeof(Vector) * 3);

		/* Light Buffer */
		CreateConstantBuffer("DirectionalLightCB", USAGE::DEFAULT, 0, sizeof(Vector) * 4);
		CreateConstantBuffer("PointLightCB", USAGE::DEFAULT, 0, sizeof(Vector) * 3);

		/* Bone Matrix Buffer */
		CreateConstantBuffer("BoneMatrixCB", USAGE::DEFAULT, 0, sizeof(Matrix) * 64);

		/* Sampler */
		CreateSampler("LinearSampler", FilterOption::LINEAR);

		/* Shader */
		LayoutBase* basicLayout = CreateLayout("BasicLayout");

		basicLayout->AddElements("POSITION", 0, GraphicsFormat::Float_R32G32B32A32, 0, 0);
		basicLayout->AddElements("COLOR", 0, GraphicsFormat::Float_R32G32B32A32, 0, 16);

		/* Basic Color Shader */
		CreateVertexShader("BasicColorVS", "Shader/BasicColor/BasicColorVS.hlsl", "main", "vs_5_0", basicLayout);
		CreatePixelShader("BasicColorPS", "Shader/BasicColor/BasicColorPS.hlsl", "main", "ps_5_0");
		
		/* Basic Model Shader */
		CreateVertexShader("BasicModelVS", "Shader/BasicModel/BasicModelVS.hlsl", "main", "vs_5_0", basicLayout);
		CreatePixelShader("BasicModelPS", "Shader/BasicModel/BasicModelPS.hlsl", "main", "ps_5_0");

		resourceManager->SubLayout("BasicLayout");

		/* Legacy Model Shader */
		LayoutBase* legacyLayout = CreateLayout("LegacyLayout");

		legacyLayout->AddElements("POSITION", 0, GraphicsFormat::Float_R32G32B32A32, 0, 0);
		legacyLayout->AddElements("NORMAL", 0, GraphicsFormat::Float_R32G32B32A32, 0, 16);
		legacyLayout->AddElements("TEXCOORD", 0, GraphicsFormat::Float_R32G32B32A32, 0, 32);
		legacyLayout->AddElements("TANGENT", 0, GraphicsFormat::Float_R32G32B32A32, 0, 48);

		CreateVertexShader("LegacyModelVS", "Shader/LegacyModel/LegacyModelVS.hlsl", "main", "vs_5_0", legacyLayout);
		CreatePixelShader("LegacyModelPS", "Shader/LegacyModel/LegacyModelPS.hlsl", "main", "ps_5_0");

		resourceManager->SubLayout("LegacyLayout");

		/* Skinning Model Shader */
		LayoutBase* skinningLayout = CreateLayout("SkinningLayout");

		skinningLayout->AddElements("POSITION", 0, GraphicsFormat::Float_R32G32B32A32, 0, 0);
		skinningLayout->AddElements("NORMAL", 0, GraphicsFormat::Float_R32G32B32A32, 0, 16);
		skinningLayout->AddElements("TEXCOORD", 0, GraphicsFormat::Float_R32G32B32A32, 0, 32);
		skinningLayout->AddElements("TANGENT", 0, GraphicsFormat::Float_R32G32B32A32, 0, 48);
		skinningLayout->AddElements("BLENDWEIGHT", 0, GraphicsFormat::Float_R32G32B32A32, 0, 64);
		skinningLayout->AddElements("BLENDINDICES", 0, GraphicsFormat::UINT_R8G8B8A8, 0, 80);

		CreateVertexShader("SkinningModelVS", "Shader/SkinningModel/SkinningModelVS.hlsl", "main", "vs_5_0", skinningLayout);

		resourceManager->SubLayout("SkinningLayout");

		/* PBR Model Shader */
		
		// Basic 
		LayoutBase* pbrBasicLayout = CreateLayout("PBRBasicLayout");

		pbrBasicLayout->AddElements("POSITION", 0, GraphicsFormat::Float_R32G32B32A32, 0, 0);
		pbrBasicLayout->AddElements("NORMAL", 0, GraphicsFormat::Float_R32G32B32A32, 0, 16);
		pbrBasicLayout->AddElements("TEXCOORD", 0, GraphicsFormat::Float_R32G32B32A32, 0, 32);

		CreateVertexShader("PBRBasicVS", "Shader/PBRModel/PBRModelVS.hlsl", "BasicMain", "vs_5_0", pbrBasicLayout);

		resourceManager->SubLayout("PBRLayout");

		// Normal
		LayoutBase* pbrNormalLayout = CreateLayout("PBRNormalLayout");

		pbrNormalLayout->AddElements("POSITION", 0, GraphicsFormat::Float_R32G32B32A32, 0, 0);
		pbrNormalLayout->AddElements("NORMAL", 0, GraphicsFormat::Float_R32G32B32A32, 0, 16);
		pbrNormalLayout->AddElements("TEXCOORD", 0, GraphicsFormat::Float_R32G32B32A32, 0, 32);
		pbrNormalLayout->AddElements("TANGENT", 0, GraphicsFormat::Float_R32G32B32A32, 0, 48);

		CreateVertexShader("PBRNormalVS", "Shader/PBRModel/PBRModelVS.hlsl", "NormalMain", "vs_5_0", pbrNormalLayout);

		resourceManager->SubLayout("PBRLayout");

		// Skinning
		LayoutBase* pbrSkinnedLayout = CreateLayout("PBRSkinnedLayout");

		pbrSkinnedLayout->AddElements("POSITION", 0, GraphicsFormat::Float_R32G32B32A32, 0, 0);
		pbrSkinnedLayout->AddElements("NORMAL", 0, GraphicsFormat::Float_R32G32B32A32, 0, 16);
		pbrSkinnedLayout->AddElements("TEXCOORD", 0, GraphicsFormat::Float_R32G32B32A32, 0, 32);
		pbrSkinnedLayout->AddElements("BLENDWEIGHT", 0, GraphicsFormat::Float_R32G32B32A32, 0, 48);
		pbrSkinnedLayout->AddElements("BLENDINDICES", 0, GraphicsFormat::UINT_R8G8B8A8, 0, 64);

		CreateVertexShader("PBRSkinnedVS", "Shader/PBRModel/PBRModelVS.hlsl", "SkinnedMain", "vs_5_0", pbrSkinnedLayout);

		resourceManager->SubLayout("PBRSkinnedLayout");

		CreatePixelShader("PBRConstVarPS", "Shader/PBRModel/PBRModelPS.hlsl", "ConstVarMain", "ps_5_0");
		CreatePixelShader("PBRAlbedoPS", "Shader/PBRModel/PBRModelPS.hlsl", "AlbedoMain", "ps_5_0");
		CreatePixelShader("PBRAlbedoNormalPS", "Shader/PBRModel/PBRModelPS.hlsl", "AlbedoNormalMain", "ps_5_0");

	}
}