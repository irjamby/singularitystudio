/////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:	"CMenuState.cpp"
//
// Authors: Nicholas Bucciarelli (NB)
// 
// Purpose: The menu state cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "CMainMenuState.h"
#include "COptionsState.h"

#include "..\Wrappers\CSGD_TextureManager.h"
#include "..\Wrappers\CSGD_DirectInput.h"

#include "..\Wrappers\CBitmapFont.h"
#include "CWiimote.h"

#include "CGame.h"


CMainMenuState::CMainMenuState(void)
{
	m_nImageID = -1;
	m_nSelected = 0;
	m_pDI = NULL;
	m_pTM = NULL;
	m_pFont = NULL;

}

CMainMenuState::~CMainMenuState(void)
{
	if (m_pFont)	delete m_pFont;	m_pFont = NULL;
}

CMainMenuState* CMainMenuState::GetInstance(void)
{
	static CMainMenuState instance;
	return &instance;
}

void CMainMenuState::Enter(void)
{

	//	Load assets specific to state
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();
	m_pWii = CWiimote::GetInstance();

	//	Load assets specific to state
	m_nImageID = m_pTM->LoadTexture("Resource/SS_MenuCursor.png", D3DCOLOR_XRGB(0, 0, 0));
	
	m_pFont = new CBitmapFont();
	m_pFont->SetCharHeight(20);
	m_pFont->SetCharWidth(16);
	m_pFont->SetNumCols(20);
	m_pFont->SetStartChar(' ');
	m_pFont->SetFontImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/SS_BloodFont.png", D3DCOLOR_XRGB(0,0,0)));


}

void CMainMenuState::Exit(void)
{
	//	Unload assets 
	m_pTM->ReleaseTexture(m_nImageID);

	if (m_pFont)		delete m_pFont;		m_pFont = NULL;

}

bool CMainMenuState::Input(float fElapsedTime )
{
	if (m_pDI->KeyPressed(DIK_DOWN) || m_pWii->IsButtonJustPressed(WII_DOWN))
	{
		m_nSelected++;
		if (m_nSelected > 5)
			m_nSelected = 0;
	}
	if (m_pDI->KeyPressed(DIK_UP) || m_pWii->IsButtonJustPressed(WII_UP))
	{	
		m_nSelected--;
		if (m_nSelected < 0)
			m_nSelected = 5;
	}



	if (m_pDI->KeyPressed(DIK_RETURN) || m_pWii->IsButtonJustPressed(WII_A))
	{
		switch(m_nSelected)
		{
		case 1:
			CGame::GetInstance()->PushState( COptionsState::GetInstance() );
			m_nSelected = 0;
			break;
		default:
			return false;
			break;
		}
	}

	//HOME Button or ESC exits the program
	if (m_pDI->KeyPressed(DIK_ESCAPE) || m_pWii->IsButtonJustPressed(WII_HOME))
		return false;
	


	return true;
}

void CMainMenuState::Update(float fElapsedTime )
{

}

void CMainMenuState::Render(void)
{
	
	char buffer1[] = "Play";
	m_pFont->DrawString(buffer1, 100, 160);
	char buffer2[] = "Options";
	m_pFont->DrawString(buffer2, 100, 200);
	char buffer3[] = "How to Play";
	m_pFont->DrawString(buffer3, 100, 240);
	char buffer4[] = "High Scores";
	m_pFont->DrawString(buffer4, 100, 280);
	char buffer5[] = "Credits";
	m_pFont->DrawString(buffer5, 100, 320);
	char buffer6[] = "Exit";
	m_pFont->DrawString(buffer6, 100, 360);


	if (m_nSelected == 0)
		m_pTM->Draw(m_nImageID, 50, 170);
	if (m_nSelected == 1)
		m_pTM->Draw(m_nImageID, 50, 200);
	if (m_nSelected == 2)
		m_pTM->Draw(m_nImageID, 50, 250);
	if (m_nSelected == 3)										 
		m_pTM->Draw(m_nImageID, 50, 290);
	if (m_nSelected == 4)										 
		m_pTM->Draw(m_nImageID, 50, 330);
	if (m_nSelected == 5)										 
		m_pTM->Draw(m_nImageID, 50, 370);


}