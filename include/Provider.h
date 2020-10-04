#pragma once
#include <Common.h>
#include <Driver.h>

// The Implementation of IServerTrackedDeviceProvider
class CServerDriver_Sample : public IServerTrackedDeviceProvider
{
public:
	virtual EVRInitError Init(vr::IVRDriverContext* pDriverContext);
	virtual void Cleanup();
	virtual const char* const* GetInterfaceVersions() { return vr::k_InterfaceVersions; }
	virtual void RunFrame();
	virtual bool ShouldBlockStandbyMode() { return false; }
	virtual void EnterStandby() {}
	virtual void LeaveStandby() {}

private:
	CSampleControllerDriver* m_pControllerLeft = nullptr;
	CSampleControllerDriver* m_pControllerRight = nullptr;
};
