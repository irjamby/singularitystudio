////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File: “CWiimote.cpp”
// Author: Keith Maggio (KM)
// Purpose: Creates the ability to use the Nintendo Wii-Remote
//			as an alternate input device. Sweetness.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "CWiimote.h"
#include "CGame.h"
//#include "CWiiConnectState.h"

CWiimote::CWiimote()
{
	remote = NULL;
	m_bErr = false;
	m_fPrevRoll = 0.0f;
}

CWiimote::~CWiimote()
{
	Disconnect();
	if (remote)
	{
		delete remote;
	}
}

CWiimote* CWiimote::GetInstance()
{
	static CWiimote Inst;
	return &Inst;
}

void CWiimote::InitWiimote()
{

	remote = new wiimote();

	for(int i = 0; i < 10; ++i)
	{
		remote->Connect(wiimote::FIRST_AVAILABLE);
		if (remote->IsConnected())
			break;
	}

	if (remote->IsConnected())
		remote->SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT);
	else
		m_bErr = true;
}

bool CWiimote::Reconnect()
{
	if (remote->Connect(wiimote::FIRST_AVAILABLE))
	{
		remote->SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT);
		return true;
	}
	else
		return false;
	
}

bool CWiimote::UpdateWiimote()
{
	if (!GetErr())
	{
		/*if (remote->ConnectionLost() && (CGame::GetInstance()->GetCurState() != CWiiConnectState::GetInstance()))
		{
			CGame::GetInstance()->PushState(CWiiConnectState::GetInstance());
			return false;
		}
		else if(remote->IsConnected())*/
			return remote->RefreshState() == NO_CHANGE;
	}
	return false;
	
}

void CWiimote::Disconnect()
{
	if (remote->IsConnected())
		remote->Disconnect();
}