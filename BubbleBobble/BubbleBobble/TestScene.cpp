#include "TestScene.h"
#include "GameObject.h"
#include "TextObject.h"

TestScene::TestScene(const std::string& sceneName) : Scene(sceneName)
{
}

void TestScene::Initialize()
{
	auto go = new GameObject();

	go->SetTexture("background.jpg");
	AddObject(go);

	go = new GameObject();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	AddObject(go);

	auto to = new TextObject();
	to->SetFont("Lingua.otf");
	to->SetText("Programming 4 Assignment");
	to->SetPosition(80, 20);
	AddObject(to);
}

void TestScene::Update(float dt)
{
	(void)dt;
}

void TestScene::Render() const
{
}
