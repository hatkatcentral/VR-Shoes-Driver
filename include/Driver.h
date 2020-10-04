#pragma once
#include <Common.h>

//Austin's notes
// |Driver
//    |Device(s)
//	     |Component(s)
//          |Property(s)

//Provider -> Driver

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
class CSampleControllerDriver : public vr::ITrackedDeviceServerDriver
{
public:
	CSampleControllerDriver(const std::string aSerialNumber, const std::string aModelNumber);

	virtual ~CSampleControllerDriver() {};

	virtual EVRInitError Activate(vr::TrackedDeviceIndex_t unObjectId);

	virtual void Deactivate()
	{
		m_unObjectId = vr::k_unTrackedDeviceIndexInvalid;
	}

	virtual void EnterStandby() {};


	void* GetComponent(const char* pchComponentNameAndVersion)
	{
		// override this to add a component to a driver
		//5 types of component
		//1. Display Component (UNUSED BY VRSHOES)
		//2. Controller Component (Actually controlled by IVRDriverInput)
		//3. Camera Component (UNUSED BY VRSHOES)
		//4. DriverDirectMode Component (UNUSED BY VRSHOES)
		//5. VirtualDisplay Component (UNUSED BY VRSHOES)
		return NULL;
	}

	/** debug request from a client */
	virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize)
	{
		if (unResponseBufferSize >= 1)
			pchResponseBuffer[0] = 0;
	}

	virtual DriverPose_t GetPose();

	//helper functions
	// aren't called by the VRServer
	// could be private or public

	void RunFrame();

	void ProcessEvent(const vr::VREvent_t& vrEvent);

	std::string GetSerialNumber() const { return m_sSerialNumber; }

private:
	vr::TrackedDeviceIndex_t m_unObjectId;
	vr::PropertyContainerHandle_t m_ulPropertyContainer;

	vr::VRInputComponentHandle_t m_compA;
	vr::VRInputComponentHandle_t m_compB;
	vr::VRInputComponentHandle_t m_compC;
	vr::VRInputComponentHandle_t m_compHaptic;

	std::string m_sSerialNumber;
	std::string m_sModelNumber;


};
