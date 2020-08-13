#include "Observer.h"

Subject::~Subject()
{
	for (auto& obv : m_pObservers)
	{
		SafeDelete(obv.second);
	}
}

void Subject::AddObserver(const std::string& name, Observer* pObsv)
{
	m_pObservers.emplace(name, pObsv);
}

Observer* Subject::GetObserver(const std::string& name)
{
	auto it = m_pObservers.find(name);

	if (it != m_pObservers.end())
	{
		return (*it).second;
	}

	std::cout << "Observer doesn't exists\n";

	return nullptr;
}

void Subject::RemoveObserver(const std::string& pObsv)
{
	auto it = m_pObservers.find(pObsv);

	if (it != m_pObservers.end())
	{
		m_pObservers.erase(it);
		SafeDelete((*it).second);
	}
}

void Subject::Notify(uint32_t event)
{
	for (auto& obsv : m_pObservers)
	{
		obsv.second->OnNotify(event);
	}
}