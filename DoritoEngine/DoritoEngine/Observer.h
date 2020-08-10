#pragma once
#include "DoritoPCH.h"
#include <list>

enum class Event
{
	ENEMY_KILLED = 0,
	EMERALD_COLLECTED = 1,
	GOLD_COLLECTED = 2,

	EXTRA_LIFE = 3,
	LIFE_LOST = 4
};

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void OnNotify(Event event) = 0;
};

class Subject 
{
public:
	Subject() = default;
	~Subject();

	void AddObserver(Observer* pObsv);
	void RemoveObserver(Observer* pObsv);

protected:
	void Notify(Event event);

private:
	std::list<Observer*> m_pObservers;
	
};