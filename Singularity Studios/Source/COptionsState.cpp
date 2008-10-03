/////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:	"COptionsState.cpp"
//
// Authors: Nicholas Bucciarelli (NB)
// 
// Purpose: The menu state cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "COptionsState.h"

#include "..\Wrappers\CSGD_TextureManager.h"
#include "..\Wrappers\CSGD_DirectInput.h"

#include "..\Wrappers\CBitmapFont.h"

#include "CGame.h"


COptionsState::COptionsState(void)
{
	m_nCursorID = -1;
	m_nSelected = 0;
	m_pDI = NULL;
	m_pTM = NULL;
	m_pFont = NULL;

}

COptionsState::~COptionsState(void)
{
	if (m_pFont)	delete m_pFont;	m_pFont = NULL;
}

COptionsState* COptionsState::GetInstance(void)
{
	static COptionsState instance;
	return &instance;
}

void COptionsState::Enter(void)
{

	//	Load assets specific to state
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();

	//	Load assets specific to state
	m_nCursorID = m_pTM->LoadTexture("Resource/SS_MenuCursor.png", D3DCOLOR_XRGB(0, 0, 0));
	
	m_pFont = new CBitmapFont();
	m_pFont->SetCharHeight(20);
	m_pFont->SetCharWidth(16);
	m_pFont->SetNumCols(20);
	m_pFont->SetStartChar(' ');
	m_pFont->SetFontImageID(CSGD_TextureManager::GetInstance()->LoadTexture("Resource/SS_BloodFont.png", D3DCOLOR_XRGB(0,0,0)));


}

void COptionsState::Exit(void)
{
	//	Unload assets 
	m_pTM->ReleaseTexture(m_nCursorID);
	if (m_pFont)		delete m_pFont;		m_pFont = NULL;

}

bool COptionsState::Input(float fElapsedTime )
{
	if (m_pDI->KeyPressed(DIK_DOWN))
	{
		m_nSelected++;
		if (m_nSelected > 1)
			m_nSelected = 0;
	}
	if (m_pDI->KeyPressed(DIK_UP))
	{	
		m_nSelected--;
		if (m_nSelected < 0)
			m_nSelected = 1;
	}
	

	if (m_pDI->KeyPressed(DIK_RETURN))
	{
		switch(m_nSelected)
		{
		case 1:
			m_nSelected = 0;
			CGame::GetInstance()->PopState(  );
			break;		
		}
	}

	return true;
}

void COptionsState::Update(float fElapsedTime )
{

}

void COptionsState::Render(void)
{
	char buffer1[] = "Options Menu!";
	m_pFont->DrawString(buffer1, 100, 100);
	char buffer2[] = "Keys";
	m_pFont->DrawString(buffer2, 25, 200);		
	char buffer3[] = "Exit";
	m_pFont->DrawString(buffer3, 25, 240);

	if (m_nSelected == 0)
		m_pTM->Draw(m_nCursorID, 15, 200);
	if (m_nSelected == 1)
		m_pTM->Draw(m_nCursorID, 15, 250);
	
}