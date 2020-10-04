#include <Provider.h>

EVRInitError CServerDriver_Sample::Init(vr::IVRDriverContext* pDriverContext)
{
	VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);
	//InitDriverLog(vr::VRDriverLog());

	//Note: should we make each Shoe a device?
	m_pControllerLeft = new CSampleControllerDriver( "SN-SHOES-00", "MN-ALPHA-00" );
	//log (Left Controller Initialized)
	m_pControllerRight = new CSampleControllerDriver( "SN-SHOES-01", "MN-ALPHA-01");
	//log (Right Controller Initialized)
	
	vr::VRServerDriverHost()->TrackedDeviceAdded(m_pControllerLeft->GetSerialNumber().c_str(), vr::TrackedDeviceClass_Controller, m_pControllerLeft);
	vr::VRServerDriverHost()->TrackedDeviceAdded(m_pControllerRight->GetSerialNumber().c_str(), vr::TrackedDeviceClass_Controller, m_pControllerRight);
	return VRInitError_None;
}

void CServerDriver_Sample::Cleanup()
{
	//CleanupDriverLog();
	delete m_pControllerLeft;
	m_pControllerLeft = NULL;
	//log (Left Controller Destroyed)
	delete m_pControllerRight;
	m_pControllerRight = NULL;
	//log (Right Controller Destroyed)
}


void CServerDriver_Sample::RunFrame()
{
	// Frame based checking of data sent over bluetooth
	if (m_pControllerLeft)
	{
		m_pControllerLeft->RunFrame();
	}

	if (m_pControllerRight)
	{
		m_pControllerRight->RunFrame();
	}

	vr::VREvent_t vrEvent;
	while (vr::VRServerDriverHost()->PollNextEvent(&vrEvent, sizeof(vrEvent)))
	{
		if (m_pControllerLeft)
		{
			m_pControllerLeft->ProcessEvent(vrEvent);
		}

		if (m_pControllerRight)
		{
			m_pControllerRight->ProcessEvent(vrEvent);
		}
	}
}