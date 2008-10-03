//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	File:			"Messages.h"
//	Author:			Nick Bucciarelli
//	Purpose:		Handles the messages
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "SGD_Math.h" // for tVector2D


enum eMessageTypes
{
	MSG_NULL = 0,
	
	
	MSG_MAX		// My total number of messages
};

typedef unsigned int MESSAGEID; // incase you want to change the message id type

class CBaseMessage
{
private:
	MESSAGEID	m_Msg;		//	The message id
public:
	CBaseMessage(MESSAGEID msg = MSG_NULL) { m_Msg = msg; }
	virtual ~CBaseMessage(void) {}

	//	Accessor
	inline MESSAGEID GetMessageID(void) { return m_Msg; }
};