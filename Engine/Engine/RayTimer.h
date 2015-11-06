//=============================================================================================
// RayTimer: Ray timer, designed for statstic time elapsed and calculate FPS
//=============================================================================================

#pragma once

class RayTimer
{
public:
	RayTimer();
	~RayTimer();

	float DeltaTime() const; // in seconds
	float TotalTime() const; // in seconds

	void Reset(); // call before render loop
	void Start(); // call when unpaused
	void Stop();  // call when paused
	void Tick();  // call every frame

private:
	double m_SecondPerCount;
	double m_DeltaTime;

	__int64 m_BaseTime;
	__int64 m_PausedTime;
	__int64 m_StopTime;
	__int64 m_LastTime;
	__int64 m_CurrTime;

	bool m_bPaused;
};