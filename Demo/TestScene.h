#pragma once

#include "../GameEngine/Manager/Scene/Scene.h"

class TestScene : public GameEngineSpace::Scene
{
public:
	TestScene();
	virtual ~TestScene() final;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};