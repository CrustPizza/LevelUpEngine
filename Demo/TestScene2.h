#pragma once

#include "../GameEngine/Manager/Scene/Scene.h"

class TestScene2 : public GameEngineSpace::Scene
{
public:
	TestScene2();
	virtual ~TestScene2() final;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};