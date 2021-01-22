#include <standard/applite.h>
#include <standard/gui.h>
#include <include/sound.h>
#include <include/stdio.h>
#include <include/time.h>
#include <standard/log.h>
#include "mainlayer.h"


class CRubikCubeApp: public CAppLite{
public:
    CWindow* m_pWindow;
    CMainLayer* m_pLayer;

    CRubikCubeApp(){

    }
    virtual ~CRubikCubeApp(){

    }
    virtual int32 Init( HUIHANDLE hParentHandle, int32 nWidth, int32 nHeight ){
        int32 _nWindowWidth = 800;
        int32 _nWindowHeight = 600;
        int32 _nWindowLeft = nWidth / 2 - _nWindowWidth / 2;
        int32 _nWindowTop = nHeight / 2 - _nWindowHeight / 2;
        SRand( time( 0 ) );
        m_pWindow = NEW CWindow( _nWindowLeft, _nWindowTop, _nWindowWidth, _nWindowHeight, "模型查看器" );
        m_pLayer = NEW CMainLayer();
        m_pLayer->Init( m_pWindow );
        return m_pWindow->GetHandle();
    }
    virtual int32 Update( int32 nDleta, float fDelta ){
        m_pLayer->Update( nDleta, fDelta );
        //m_pLayer->Update( 0, 0.1f );
        return 0;
    }
    virtual int32 Render(){
        m_pLayer->Render();
        return 0;
    }
    virtual int32 Final(){
        return 0;
    }
};

CAppLite* StartApplite(){
    return NEW CRubikCubeApp( );
}


