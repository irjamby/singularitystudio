/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:	“CGame.h”
//
// Author: Keith Maggio (KM)
// 
// Purpose: Contains the main game loop for the game, as well as the state stack, pointers to the
//			wrappers, and data that's continuous through-out the game.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "CGame.h"
//#include "CWiimote.h"

//SGD Wrappers
#include "../Wrappers/CSGD_Direct3D.h"
#include "../Wrappers/CSGD_TextureManager.h"
#include "../Wrappers/CSGD_DirectSound.h"
//#include "CSGD_WaveManager.h"
#include "../Wrappers/CSGD_DirectInput.h"

#include "CMainMenuState.h"



CGame::CGame(void)
{
	//Set Wrapper members to Null here
	//m_bIsWindowed = true;
	m_pD3D = NULL;
	m_pTM = NULL;
	m_pDI = NULL;
	m_pDS = NULL;
	
	
}
CGame::~CGame(void)
{
}

CGame* CGame::GetInstance()
{
	static CGame Instance;
	return &Instance;
}

void CGame::Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed)
{
	//Set Window Members
	m_hWnd = hWnd;
	SetScreenWidth(nScreenWidth);
	SetScreenHeight(nScreenHeight);
	bIsWindowed = m_bIsWindowed;

	//TODO Init All Wrappers

	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();


	m_pD3D->InitDirect3D(hWnd, nScreenWidth, nScreenHeight, bIsWindowed, false);
	m_pTM->InitTextureManager(m_pD3D->GetDirect3DDevice(), m_pD3D->GetSprite());

	//For a Splash Screen
	//int nSplashScreen = m_pTM->LoadTexture("Resource\\ScreenImages\\BS_SplashScreen.png");
		
	/*m_pD3D->DeviceBegin();
	m_pD3D->SpriteBegin();
	m_pD3D->Clear(0,0,0);
	m_pTM->Draw(nSplashScreen,0,0);

	m_pD3D->SpriteEnd();
	m_pD3D->DeviceEnd();
	m_pD3D->Present();*/

	ChangeState( CMainMenuState::GetInstance() );

	m_pDI = CSGD_DirectInput::GetInstance();
	m_pDS = CSGD_DirectSound::GetInstance();
	m_pDS->InitDirectSound(hWnd);

	m_pDI->InitDirectInput(hWnd, hInstance, DI_KEYBOARD | DI_MOUSE, 0);

	//CSoundManager::GetInstance()->InitSounds(); //Inits FMOD
	//CMusicManager::GetInstance()->InitMusic();
	
	/*CAnimationManager::GetInstance()->LoadAnimation("Animations/BS_blob.anim","Resource/Animations/BS_blob_spritesheet2.png", D3DCOLOR_ARGB(255, 160, 208, 248));
	CAnimationManager::GetInstance()->LoadAnimation("Animations/BS_blob_Spring.anim","Resource/Animations/BS_SpringANIM.png", D3DCOLOR_ARGB(255, 160, 208, 248));
	CAnimationManager::GetInstance()->LoadAnimation("Animations/BS_blob_Umbrella.anim","Resource/Animations/BS_UmbrellaANIM.png", D3DCOLOR_ARGB(255, 160, 208, 248));*/

	////TODO Set the Initial State Here
	//ChangeState(CAttractState::GetInstance());
	////ChangeState(CGamePlayState::GetInstance());
	//m_cTransition = CTransitionScreen::GetInstance();
	//m_fTransitionTimer = 0;

	//CWiimote::GetInstance()->InitWiimote();
	//if (CWiimote::GetInstance()->GetErr())
	//{
	//	//MessageBox(hWnd, "Wii-Remote Init Failed", "Wii-Remote Failed", MB_OK);
	//	//exit(0);
	//}
	
}

void CGame::Shutdown(void)
{
	//	Make sure to shutdown the current state
	ChangeState(NULL);

	//TODO	Shutdown in the OPPOSITE order you initialized in.
	//CSoundManager::GetInstance()->ShutdownSounds();
	//CMusicManager::GetInstance()->ShutdownMusic();	//Shuts down FMOD
	m_pDS->ShutdownDirectSound();
	m_pDI->ShutdownDirectInput();
	m_pTM->ShutdownTextureManager();
	m_pD3D->ShutdownDirect3D();
}
bool CGame::Main(void)
{
	static float time = 0;
	static int frames = 0;
	int FPS = 0;
	//////Calculate the elapsed time//////
	DWORD dwCurrentTime = GetTickCount();
	//	Calculate the difference between the current and the previous time
	m_fElapsedTime = (float)(dwCurrentTime - m_dwPreviousTime) / 1000.0f;
	// remember last frames time stamp
	m_dwPreviousTime = dwCurrentTime; 
		

	
	//1.	INPUT

	//WII UPDATE


		//TODO	Place any Input that's constant through-out
		//		the entire game.
		
		//CWiimote* pWii = CWiimote::GetInstance();
		//pWii->UpdateWiimote();
		
		m_pDI->ReadDevices();

		if (m_pDI->KeyDown(DIK_RALT) ||m_pDI->KeyDown(DIK_LALT))
		{
			if (m_pDI->KeyPressed(DIK_RETURN))
			{
				m_bIsWindowed = !m_bIsWindowed;
				m_pD3D->ChangeDisplayParam(m_nScreenWidth, m_nScreenHeight, m_bIsWindowed);
			}
			else if (!m_vStackStates[(int)m_vStackStates.size() - 1]->Input(m_fElapsedTime))
				return false;
		}
		//Input from the state
		else if (!m_vStackStates[(int)m_vStackStates.size() - 1]->Input(m_fElapsedTime))
			return false;

	//2.	UPDATE

	//TODO	Update the Music/Sound Player
	/*if (!CMusicManager::GetInstance()->GetPause())
	{
		CMusicManager::GetInstance()->UpdateMusic(); 
	}
	CSoundManager::GetInstance()->UpdateSounds();*/

	//Update the current State
	if (m_vStackStates[(int)m_vStackStates.size() - 1])
		m_vStackStates[(int)m_vStackStates.size() - 1]->Update(m_fElapsedTime);





	//3.	DRAW

	//Start the D3DX Device so it may begin drawing
	m_pD3D->DeviceBegin();
	m_pD3D->SpriteBegin();
	m_pD3D->LineBegin();
	m_pD3D->Clear(0, 0, 0);

	//Render all frames in the vector
	for (int i = 0; i < (int)m_vStackStates.size(); ++i)
		m_vStackStates[i]->Render();

	//char wiioutput[64];
	//sprintf_s(wiioutput, "wii = %i", CWiimote::GetInstance()->GetWiimote()[0]->orient.a_roll);

	//CBitmapFontEngine::GetInstance()->RenderString(wiioutput, FontID, 0.0, 0xFFFFFFFF, 10, 100, 0);
	//End the D3DX Device and present
	

	m_pD3D->LineEnd();


	time+= m_fElapsedTime;
	frames ++;
	char buff[128];
	if (time >= 1.0f)
	{
		time = 0;
		FPS = frames;	
		sprintf_s(buff,"FPS:%d",FPS);
		frames = 0;
	}
	
    //CBitmapFonts::GetInstance()->RenderString(buff,FONT_COMPUTER,700,700,0xFFFF0000);
	//CBitmapFontEngine::GetInstance()->RenderString(buff,FontID,0,0xFFFFFFFF,700,200,0);
	
	m_pD3D->SpriteEnd();
	m_pD3D->DeviceEnd();

	m_pD3D->Present();
	


	return true;
}

void CGame::ChangeState(IGameState* pNewState)
{

	
	for (unsigned int i = 0; i < m_vStackStates.size(); ++i)
		m_vStackStates[i]->Exit();

	m_vStackStates.clear();

	m_vStackStates.push_back(pNewState);

	if (pNewState)
		pNewState->Enter();

}

void CGame::PushState(IGameState* pState)
{
	if (pState)
	{
		pState->Enter();
		m_vStackStates.push_back(pState);
	}
}

IGameState* CGame::PopState()
{
	IGameState* pTempState = m_vStackStates[m_vStackStates.size() - 1];

	pTempState->Exit();
	m_vStackStates.pop_back();

	return pTempState;
}
