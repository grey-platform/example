
#include <standard/applite.h>
#include <standard/gui.h>

#include "menulayer.h"
#include "mainlayer.h"
#include <include/sound.h>
#include <include/stdio.h>
#include <include/time.h>

class CTirsApp: public CAppLite, public CLayerSwitchEvent{
public:
    CWindow* m_pWindow;
    CLayer* m_pLayer0;
    CLayer* m_pLayer1;
    CLayer* m_pCurLayer;

    CTirsApp(){
    }
    virtual ~CTirsApp(){

    }
    virtual int32 Init( HUIHANDLE hParentHandle, int32 nWidth, int32 nHeight ){
        int32 _nWindowWidth = 360;
        int32 _nWindowHeight = 440;
        int32 _nWindowLeft = nWidth / 2 - _nWindowWidth / 2;
        int32 _nWindowTop = nHeight / 2 - _nWindowHeight / 2;

        SRand( time( 0 ) );
        m_pWindow = NEW CWindow( _nWindowLeft, _nWindowTop, _nWindowWidth, _nWindowHeight, "¶íÂÞË¹·½¿é" );
        m_pLayer0 = NEW CMenuLayer();
        m_pLayer0->Init( m_pWindow );
        m_pLayer0->m_pSwitcherEventObject = this;
        m_pLayer1 = NEW CMainLayer();
        m_pLayer1->Init( m_pWindow );
        m_pLayer1->m_pSwitcherEventObject = this;
        m_pCurLayer = NULL;
        OnSwitchLayer( 1 );
        return m_pWindow->GetHandle();
    }
    void OnSwitchLayer( int32 nLayer ){
        if( nLayer == 0 ){
            m_pLayer0->Hide();
            m_pLayer1->Show();
            m_pCurLayer = m_pLayer1;
        } else{
            m_pLayer1->Hide();
            m_pLayer0->Show();
            m_pCurLayer = m_pLayer0;
        }
    }
    virtual int32 Update( int32 nDleta, float fDelta ){
        m_pCurLayer->Update( nDleta );
        return 0;
    }
    virtual int32 Render(){
        m_pCurLayer->Render();
        return 0;
    }
    virtual int32 Final(){
        return 0;
    }
};

CAppLite* StartApplite(){
    return NEW CTirsApp( );
}


