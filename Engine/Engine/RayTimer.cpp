#include "RayTimer.h"
#include <windows.h>

RayTimer::RayTimer()
	: m_SecondPerCount(0)
	, m_DeltaTime(0)
	, m_BaseTime(0)
	, m_PausedTime(0)
	, m_StopTime(0)
	, m_LastTime(0)
	, m_CurrTime(0)
	, m_bPaused(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_SecondPerCount = 1.0 / static_cast<double>(countsPerSec);
}

RayTimer::~RayTimer()
{

}

float RayTimer::TotalTime() const
{
	// If we are stopped, do not count the time that has passed since we stopped.
	// Moreover, if we previously already had a pause, the distance 
	// mStopTime - mBaseTime includes paused time, which we do not want to count.
	// To correct this, we can subtract the paused time from mStopTime:  
	//
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mStopTime    mCurrTime
	if (m_bPaused)
	{
		return static_cast<float>(((m_StopTime - m_PausedTime) - m_BaseTime)*m_SecondPerCount);
	}

	// The distance mCurrTime - mBaseTime includes paused time,
	// which we do not want to count.  To correct this, we can subtract 
	// the paused time from mCurrTime:  
	//
	//  (mCurrTime - mPausedTime) - mBaseTime 
	//
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mCurrTime
	else
	{
		return  static_cast<float>(((m_CurrTime - m_PausedTime) - m_BaseTime)*m_SecondPerCount);
	}
}

float RayTimer::DeltaTime() const
{
	return static_cast<float>(m_DeltaTime);
}

void RayTimer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_BaseTime = currTime;
	m_LastTime = currTime;
	m_StopTime = 0;
	m_bPaused = false;
}

void RayTimer::Start()
{
	// Accumulate the time elapsed between stop and start pairs.
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------> time
	//  mBaseTime       mStopTime        startTime    
	
	if (m_bPaused)
	{
		__int64 startTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

		m_PausedTime += startTime - m_StopTime;

		m_LastTime = startTime;
		m_StopTime= 0;
		m_bPaused = false;
	}
}

void RayTimer::Stop()
{
	if (!m_bPaused)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		
		m_StopTime = currTime;
		m_bPaused = true;
	}
}

void RayTimer::Tick()
{
	if (m_bPaused)
	{
		m_DeltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_CurrTime = currTime;

	m_DeltaTime = (m_CurrTime - m_LastTime)*m_SecondPerCount;
	m_LastTime = m_CurrTime;

	if (m_DeltaTime < 0.0)
	{
		m_DeltaTime = 0.0;
	}
}




















