/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:	�CGame.h�
//
// Author:  Keith Maggio (KM)
// 
// Purpose: Contains the main game loop for the game, as well as the state stack, pointers to the
//			wrappers, and data that's continuous through-out the game.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "IGameState.h"
#include <vector>
using std::vector;
#include <windows.h>


class CSGD_Direct3D;		
class CSGD_DirectInput;	
class CSGD_DirectSound;	
class CSGD_TextureManager;

class CGame
{
private:
	//Stacked Vector of Game States
	vector<IGameState*> m_vStackStates;

	//	For calculating elapsed time
	float				m_fElapsedTime;		//	holds the time (in seconds) that has passed between frames
	DWORD				m_dwPreviousTime;	//	holds the time stamp of the last frame

	//Window Properties
	int					m_nScreenWidth;
	int					m_nScreenHeight;
	HWND				m_hWnd;
	bool				m_bIsWindowed;		//Toggling windowed mode

	//Wrappers
	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_DirectSound*		m_pDS;
	CSGD_TextureManager*	m_pTM;


	//Trilogy of Evil - Deactivated
	//	constructor
	CGame(void);
	//	copy constructor
	CGame(const CGame&);
	//	assignment operator
	CGame& operator=(const CGame&);
	//	Plus destructor!
	~CGame(void);

public:
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Function: GetInstance
	//	Last Modified: August 20, 2008
	//  Purpose : Grabs an instance of the class
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	static CGame* GetInstance(void);

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Function: Initialize
	//	Last Modified: August 24, 2008
	//  Purpose : Initializes CGame and all of its members so it's ready for use
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	void Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed);
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Function: Main
	//	Last Modified: August 24, 2008
	//  Purpose : The main game loop for the program.
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	bool Main(void);
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Function: Shutdown
	//	Last Modified: August 24, 2008
	//  Purpose : Sets members to NULL and shutdown any wrapper pointers
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	void Shutdown(void);

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Function: ChangeState
	//	Last Modified: August 22, 2008
	//  Purpose : Changes the currently loaded state (empties stack)
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	void ChangeState(IGameState* pNewState);
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Function: PushState
	//	Last Modified: August 22, 2008
	//  Purpose : Pushes another state onto the stack
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	void PushState(IGameState* pState);
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Function: PopState
	//	Last Modified: August 22, 2008
	//  Purpose : Pops current state and loads the next state in the stack.
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	IGameState* PopState();

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Function: Accessors
	//	Last Modified: August 22, 2008
	//  Purpose : Gets Data
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	int GetScreenWidth()				{	return m_nScreenWidth;		}
	int GetScreenHeight()				{	return m_nScreenHeight;		}
	HWND GetHWND()						{	return m_hWnd;				}
	IGameState* GetCurState()			{	return m_vStackStates[m_vStackStates.size()-1];}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Function: Mutators
	//	Last Modified: August 22, 2008
	//  Purpose : Sets Data
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	void SetScreenWidth(int nScreenW)	{	m_nScreenWidth = nScreenW;	}
	void SetScreenHeight(int nScreenH)	{	m_nScreenHeight = nScreenH;	}

};
