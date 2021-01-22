#ifndef _MAINLAYER_H_
#define _MAINLAYER_H_

#include <standard/gui.h>
#include <standard/planematerial.h>
#include <standard/renderbuffer.h>
#include <standard/texturefile.h>
#include <standard/texturetarget.h>
#include <standard/math.h>
#include "workcanvas.h"

class CMainLayer: public CUIEvent{
public:
    CMainLayer();
    virtual ~CMainLayer();
    virtual void Init( CWindow* pParent );
    virtual void Update( int32 nDelta, float fDelta );
    virtual void Render();
    virtual void OnClick( CUIElement* pSelf );
    void OpenFile( char* strFileName );
public:
    CPanel* m_pLayerPanel;
    CWorkCanvas* m_pWorkCanvas;
    char m_strFileName[64];
    int32 m_nCurAction;
    int32 m_nSequenceCount;
    int32 m_nUpdateCount;
};




#endif
