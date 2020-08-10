#include "Observer.h"

Subject::~Subject()
{
	for (auto& obv : m_pObservers)
	{
		SafeDelete(obv);
	}
}

void Subject::AddObserver(Observer* pObsv)
{
	m_pObservers.push_back(pObsv);
}

void Subject::RemoveObserver(Observer* pObsv)
{
	const auto it = std::find(m_pObservers.begin(), m_pObservers.end(), pObsv);

	if (it != m_pObservers.end())
	{
		m_pObservers.erase(it);
		SafeDelete(pObsv);
	}
}

void Subject::Notify(Event event)
{
	for (auto& obsv : m_pObservers)
	{
		obsv->OnNotify(event);
	}
}