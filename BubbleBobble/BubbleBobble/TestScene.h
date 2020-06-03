#pragma once
#include "Scene.h"

class TestScene : public Scene
{
public:
	TestScene(const std::string& sceneName);

	virtual ~TestScene() = default;
	TestScene(const TestScene& other) = delete;
	TestScene(TestScene&& other) = delete;
	TestScene& operator=(const TestScene& other) = delete;
	TestScene& operator=(TestScene&& other) = delete;

	void Initialize() override;
	void Update(float dt) override;
	void Render() const override;

private:


};

