////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File: “CWiimote.h”
// Author: Keith Maggio (KM)
// Purpose: Creates the ability to use the Nintendo Wii-Remote
//			as an alternate input device. Sweetness.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../Wiimote/wiimote.h"

//These are so code outside of CWiimote can access the Hex code of the buttons.
enum btns
{
	WII_LEFT	= 0x0001,
	WII_RIGHT	= 0x0002,
	WII_DOWN	= 0x0004,
	WII_UP		= 0x0008,
	WII_PLUS	= 0x0010,
	WII_TWO		= 0x0100,
	WII_ONE		= 0x0200,
	WII_B		= 0x0400,	// ie. trigger
	WII_A		= 0x0800,
	WII_MINUS	= 0x1000,
	WII_HOME	= 0x8000,
	//
	WII_ALLBTNS		= WII_LEFT|WII_RIGHT|WII_DOWN|WII_UP|WII_PLUS|WII_TWO|WII_ONE|WII_A|WII_B|WII_MINUS|WII_HOME
};


class CWiimote
{
private:
	//Behold! The WII-REMOTE!
	wiimote* remote;

	//Error Check if there was a problem
	bool m_bErr;

	//The Previous Roll
	float m_fPrevRoll;

	struct last_btnPress
	{
		bool last_A;
		bool last_B;
		bool last_One;
		bool last_Two;
		bool last_Up;
		bool last_Down;
		bool last_Left;
		bool last_Right;
		bool last_Plus;
		bool last_Minus;
		bool last_Home;

		last_btnPress()
		{
			last_A = false;
			last_B = false;
			last_One = false;
			last_Two = false;
			last_Up = false;
			last_Down = false;
			last_Left = false;
			last_Right = false;
			last_Plus = false;
			last_Minus = false;
			last_Home = false;
		}
	} m_btnPress;

	//Constructor - Non-public
	CWiimote(void);

	//Destructor - Non-public
	virtual ~CWiimote(void);
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function: GetInstance
	// Last Modified: August 10th, 2008
	// Purpose: Gets the instance for the Wiimote class
	//			*DON'T forget to call InitWiimote!*
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static CWiimote* GetInstance();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function: InitWiimote
	// Last Modified: August 10th, 2008
	// Purpose: Initializes the wii-remote member so it can be used.
	//			MUST be called after GetInstance.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void InitWiimote(); 

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function: Reconnect
	// Last Modified: September 10th, 2008
	// Purpose: Call in case the Wii-Remote has been disconnected.
	//			Returns true if a Wii-Remote has been found.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool Reconnect();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function: UpdateWiimote
	// Last Modified: September 16th, 2008
	// Purpose: Update the Wii-Remote every frame. Returns true if
	//			there was no change in the state.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool UpdateWiimote();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function: Disconnect
	// Last Modified: August 12th, 2008
	// Purpose: Disconnects from the wii-remote completely.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Disconnect();

	//UnBuffered
	bool IsButtonPressed(int BUTTON)
	{	
		return (remote->Button.Bits & BUTTON) != FALSE;
	}
	//Buffered
	bool IsButtonJustPressed(int BUTTON)
	{
		bool Changed;
		//bool Pressed = ((remote->Button.Bits & BUTTON) != FALSE);

		switch (BUTTON)
		{
		case (WII_UP):
			{
				Changed = (remote->Button.Up() != m_btnPress.last_Up);

				if (Changed)
					m_btnPress.last_Up = remote->Button.Up();
			}
			break;
		case (WII_DOWN):
			{
				Changed = (remote->Button.Down() != m_btnPress.last_Down);

				if (Changed)
					m_btnPress.last_Down = remote->Button.Down();
			}
			break;
		case (WII_LEFT):
			{
				Changed = (remote->Button.Left() != m_btnPress.last_Left);

				if (Changed)
					m_btnPress.last_Left = remote->Button.Left();
			}
			break;
		case (WII_RIGHT):
			{
				Changed = (remote->Button.Right() != m_btnPress.last_Right);

				if (Changed)
					m_btnPress.last_Right = remote->Button.Right();
			}
			break;
		case (WII_A):
			{
				Changed = (remote->Button.A() != m_btnPress.last_A);

				if (Changed)
					m_btnPress.last_A = remote->Button.A();
			}
			break;
		case (WII_B):
			{
				Changed = (remote->Button.B() != m_btnPress.last_B);

				if (Changed)
					m_btnPress.last_B = remote->Button.B();
			}
			break;
		case (WII_ONE):
			{
				Changed = (remote->Button.One() != m_btnPress.last_One);

				if (Changed)
					m_btnPress.last_One = remote->Button.One();
			}
			break;
		case (WII_TWO):
			{
				Changed = (remote->Button.Two() != m_btnPress.last_Two);

				if (Changed)
					m_btnPress.last_Two = remote->Button.Two();
			}
			break;
		case (WII_PLUS):
			{
				Changed = (remote->Button.Plus() != m_btnPress.last_Plus);

				if (Changed)
					m_btnPress.last_Plus = remote->Button.Plus();
			}
			break;
		case (WII_MINUS):
			{
				Changed = (remote->Button.Minus() != m_btnPress.last_Minus);

				if (Changed)
					m_btnPress.last_Minus = remote->Button.Minus();
			}
			break;
		case (WII_HOME):
			{
				Changed = (remote->Button.Home() != m_btnPress.last_Home);

				if (Changed)
					m_btnPress.last_Home = remote->Button.Home();
			}
			break;
		default:
			{
				//WTF did you press?!
				return false;
			}

		}

		return (Changed && ((remote->Button.Bits & BUTTON) != FALSE));
	}
	//Released
	bool IsButtonReleased(int BUTTON)
	{
		bool UnPressed = ((remote->Button.Bits & BUTTON) != FALSE);
		return (UnPressed? false:true);
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function: Accessors
	// Last Modified: August 23th, 2008
	// Purpose: Access data in the Wiimote class
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	wiimote* GetWiimote() const				{	return remote;		}
	bool GetErr()const						{	return m_bErr;		}
	bool IsConnected()const					{	return remote->IsConnected();	}
	bool IsConnectionLost()const			{	return remote->ConnectionLost();}
	last_btnPress GetLastButtonPressed()	{	return m_btnPress;	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function: Roll Operators
	// Last Modified: September 18th, 2008
	// Purpose: Set up Roll modifications
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	float GetOrientRoll()const				{	return remote->Acceleration.Orientation.Roll;		}
	float CalcRollDiff(float fRoll)					
	{	
		if ((fRoll - m_fPrevRoll) < 0)
			return (fRoll - m_fPrevRoll)*-1;
		else
			return (fRoll - m_fPrevRoll);				
	}
	void SetPrevRoll(float fRoll)			{	m_fPrevRoll = fRoll;	}
	float GetPrevRoll()						{	return m_fPrevRoll;		}

	//HACK
	void SetLastBPress(bool bBtn)			{	m_btnPress.last_B = bBtn;	}
	void SetLastAPress(bool bBtn)			{	m_btnPress.last_A = bBtn;	}
	void SetErr(bool Err)					{	m_bErr = Err;				}



	

	//Button Press/Release : What to do when a button is pressed, then released
#define ON_PRESS_RELEASE(button, pressed_action, released_action)										\
	{ bool pressed = CWiimote::GetInstance()->GetWiimote()->Button.##button();							\
	if(pressed)																							\
	{				   /* just pressed? */																\
	if(!CWiimote::GetInstance()->GetLastButtonPressed().last_##button) pressed_action;					\
	}																									\
	else if(CWiimote::GetInstance()->GetLastButtonPressed().last_##button) /* just released */			\
	released_action;																				\
	/* remember the current button state for next time */												\
	CWiimote::GetInstance()->GetLastButtonPressed().last_##button = pressed; }


};

