#pragma once

namespace Swallow {

	class TimeStep
	{
	public:
		TimeStep(float time = 0.0f) : m_time(time){}

		// set as seconds
		void operator=(float time) { m_time = time; }
		// return seconds
		operator float() { return m_time; }

		float GetSeconds() const { return m_time; }
		float GetMiliseconds() const { return m_time * 1000; }

	private:
		float m_time;
	};
}