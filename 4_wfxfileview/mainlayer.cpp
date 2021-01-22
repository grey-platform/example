#include "mainlayer.h"
#include <include/string.h>
#include <include/stdio.h>
#include <standard/log.h>
#include <standard/dialogs.h>
#include "actiondlg.h"

CMainLayer::CMainLayer(){
    m_strFileName[0] = 0;
    m_nUpdateCount = 0;
}

CMainLayer::~CMainLayer(){

}

void CMainLayer::Init( CWindow* pParent ){
    m_pLayerPanel = NEW CPanel( 4, 30, 792, 567 );
    pParent->AddElement( m_pLayerPanel );
    CPanel* _pPanel = NEW CPanel( 4, 30, 792, 32 );
    m_pLayerPanel->AddElement( _pPanel );
    CButton* _pBtn = NEW CButton( 8, 34, 60, 24, "打开" );
    _pBtn->SetID( 0 );
    _pBtn->AddUIEvent( UEM_CLICK );
    _pBtn->OnClickEventObject = this;
    m_pLayerPanel->AddElement( _pBtn );

    _pBtn = NEW CButton( 72, 34, 80, 24, "动作列表" );
    _pBtn->SetID( 1 );
    _pBtn->AddUIEvent( UEM_CLICK );
    _pBtn->OnClickEventObject = this;
    m_pLayerPanel->AddElement( _pBtn );

    _pBtn = NEW CButton( 156, 34, 80, 24, "文件属性" );
    _pBtn->SetID( 2 );
    _pBtn->AddUIEvent( UEM_CLICK );
    _pBtn->OnClickEventObject = this;
    m_pLayerPanel->AddElement( _pBtn );
    
    _pPanel = NEW CPanel( 4, 532, 792, 32 );
    m_pLayerPanel->AddElement( _pPanel );

    _pBtn = NEW CButton( 8, 536, 60, 24, "播放" );
    _pBtn->SetID( 10 );
    _pBtn->AddUIEvent( UEM_CLICK );
    _pBtn->OnClickEventObject = this;
    m_pLayerPanel->AddElement( _pBtn );

    _pBtn = NEW CButton( 72, 536, 80, 24, "暂停" );
    _pBtn->SetID( 11 );
    _pBtn->AddUIEvent( UEM_CLICK );
    _pBtn->OnClickEventObject = this;
    m_pLayerPanel->AddElement( _pBtn );

    _pBtn = NEW CButton( 156, 536, 80, 24, "下一动作" );
    _pBtn->SetID( 12 );
    _pBtn->AddUIEvent( UEM_CLICK );
    _pBtn->OnClickEventObject = this;
    m_pLayerPanel->AddElement( _pBtn );

    _pBtn = NEW CButton( 240, 536, 80, 24, "上一动作" );
    _pBtn->SetID( 13 );
    _pBtn->AddUIEvent( UEM_CLICK );
    _pBtn->OnClickEventObject = this;
    m_pLayerPanel->AddElement( _pBtn );


    _pPanel = NEW CPanel( 4, 564, 792, 32 );
    m_pLayerPanel->AddElement( _pPanel );

    m_pWorkCanvas = NEW CWorkCanvas( 4, 63, 788, 466 );
    m_pWorkCanvas->Init();
    m_pLayerPanel->AddElement( m_pWorkCanvas );

    OpenFile("model/atom_aurora.wfx");
}
void CMainLayer::Update( int32 nDelta, float fDelta ){
    //if( m_nUpdateCount < 1 ){
        m_pWorkCanvas->Update( nDelta, fDelta );
    //    m_nUpdateCount ++;
    //}
}
void CMainLayer::Render(){
    m_pWorkCanvas->Render();
}
void CMainLayer::OnClick( CUIElement* pSelf ){
    int32 _nID = pSelf->GetID();
    switch( _nID ){
    case 0: {
        list<const char*> _vFileList;
        _vFileList.push_back( "atom_aurora.wfx" );
        _vFileList.push_back( "campfire.wfx" );
        _vFileList.push_back( "wooden.wfx" );
        NEW COpenFileDialog( _vFileList, m_strFileName, "选择模型文件", this, 10001 );
    }break;
    case 1:{
        list<SActionInfo> _vActionInfoList;
        for( int32 i = 0, n = m_pWorkCanvas->m_pGameObject->GetSequenceCount(); i < n; i++ ){
            SActionInfo _sActionInfo;
            _sActionInfo.m_nIndex = i;
            m_pWorkCanvas->m_pGameObject->GetSeqenceInfo( i, _sActionInfo.m_strName, &_sActionInfo.m_fStartTime, &_sActionInfo.m_fEndTime, &_sActionInfo.m_fSpeed );
            _vActionInfoList.push_back( _sActionInfo );
        }
        NEW CActionDialog( _vActionInfoList );
    }break;
    case 10:{
        m_pWorkCanvas->Play();
    }break;
    case 11:{
        m_pWorkCanvas->Pause();
    }break;
    case 12:{
        m_nCurAction ++;
        m_nCurAction %= m_nSequenceCount;
        m_pWorkCanvas->SetAction( m_nCurAction );
    }break;
    case 13:{
        m_nCurAction --;
        if( m_nCurAction < 0 ){
            m_nCurAction = m_nSequenceCount - 1;
        }
        m_pWorkCanvas->SetAction( m_nCurAction );
    }break;
    case 10001:{
        char _strFileName[256];
        COpenFileDialog* _pOpenDlg = (COpenFileDialog*)pSelf;
        _pOpenDlg->GetFileName( m_strFileName );
        Format( _strFileName, "model/%s", m_strFileName );
        OpenFile( _strFileName );
    }break;

    }
}

void CMainLayer::OpenFile( char* strFileName ){
    m_pWorkCanvas->OpenNewWFXFile( strFileName );
    m_nSequenceCount = m_pWorkCanvas->m_pGameObject->GetSequenceCount();
    m_nCurAction = 0;

}
