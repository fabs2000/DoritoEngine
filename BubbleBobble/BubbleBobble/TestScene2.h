#pragma once
#include "Scene.h"

class TestScene2 : public Scene
{
public:
	TestScene2(const std::string& sceneName);

	virtual ~TestScene2() = default;
	TestScene2(const TestScene2& other) = delete;
	TestScene2(TestScene2&& other) = delete;
	TestScene2& operator=(const TestScene2& other) = delete;
	TestScene2& operator=(TestScene2&& other) = delete;

	void Initialize() override;
	void Update(float dt) override;
	void Render() const override;

private:

};

