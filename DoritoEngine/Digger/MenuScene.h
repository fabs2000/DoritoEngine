#include "Scene.h"

class TextComponent;

class MenuScene : public Scene
{
public:
	MenuScene(const std::string& sceneName, const GameInfo& gameInfo);

	virtual ~MenuScene() = default;
	MenuScene(const MenuScene& other) = delete;
	MenuScene(MenuScene&& other) = delete;
	MenuScene& operator=(const MenuScene& other) = delete;
	MenuScene& operator=(MenuScene&& other) = delete;

	void Initialize() override;
	void Update(float dt) override;
	void Render() const override;

private:
	TextComponent* m_pNameScore;
};