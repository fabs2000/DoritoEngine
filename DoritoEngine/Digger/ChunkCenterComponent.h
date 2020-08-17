#pragma once
#include "BaseComponent.h"

class ColliderComponent;


enum class ChunkType : int
{
	DIRT = 0,
	EMERALD = 1,
	GOLD = 2,
	NOTHING = 3
};


class ChunkCenterComponent : public BaseComponent
{
public:
	explicit ChunkCenterComponent(ChunkType type);

	ChunkCenterComponent(const ChunkCenterComponent&) = delete;
	ChunkCenterComponent(ChunkCenterComponent&&) = delete;
	ChunkCenterComponent& operator= (const ChunkCenterComponent&) = delete;
	ChunkCenterComponent& operator= (const ChunkCenterComponent&&) = delete;

protected:
	void Initialize() override;
	void Update(float) override {};
	void Render() override {};

private:
	ColliderComponent* m_pCollider;

	ChunkType m_ChunkType;

	void HandleInTrigger();

};

