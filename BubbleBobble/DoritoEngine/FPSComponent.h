
class FPSComp final
{
public:

	void Update(float dt)
	{
		m_FPSNb = 1 / dt;
	}

	int GetFPS() const { return int(m_FPSNb); };

private:

	float m_FPSNb;
};