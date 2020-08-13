#pragma once
#include "DoritoPCH.h"
#include <list>

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void OnNotify(uint32_t event) = 0;
};

class Subject 
{
public:
	Subject() = default;
	~Subject();

	void AddObserver(const std::string& name, Observer* pObsv);
	Observer* GetObserver(const std::string& name);
	void RemoveObserver(const std::string& pObsv);

	void Notify(uint32_t event);

private:
	std::map<std::string, Observer*> m_pObservers;
	
};