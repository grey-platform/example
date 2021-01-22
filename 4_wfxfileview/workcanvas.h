#ifndef __WORKCANVAS_H__
#define __WORKCANVAS_H__

#include <standard/gui.h>
#include <standard/texturetarget.h>
#include <standard/renderbuffer.h>
#include <standard/texturefile.h>
#include <bigimage/directionlightscene.h>
#include <bigimage/orbitcontrols.h>
#include <bigimage/action.h>
#include <bigimage/springaction.h>
#include <standard/list.h>
#include <bigimage/panelgeometry.h>
#include <bigimage/geometrygameobject.h>
#include <bigimage/wfxgameobject.h>

class CWorkCanvas: public CImage, public CUIEvent, public CGameModelEvent{
public:
    CWorkCanvas( int32 nLeft, int32 nTop, int32 nWidth, int32 hHeight );
    virtual ~CWorkCanvas();
    void Init();
    void Final();
    virtual void Update( float fDelta );
    int32 Update( int32 nDelta, float fDelta );
    int32 Render();

    virtual void OnMouseEvent( CUIElement *pSelf, EUIMouseMessage eMouseMessage, int32 x, int32 y, int32 z, int32 s );
    virtual void OnKeyEvent( CUIElement *pSelf, EUIKeyMessage eKeyMessage, int32 nKey );
    void Reset();
    void Test0(int32 n );
    void OpenNewWFXFile( char* strFileName );
    virtual CTexture* OnGetTexture( CGameModel* pGameModel, const char* strFileName );
    void Play();
    void Pause();
    void SetAction( int32 nAction );

public:
    int32 m_nWidth, m_nHeight;

    bool32 m_bShiftDown;
    bool32 m_bCtrlDown;

    CTextureTarget* m_pTextureTarget;
    CCamera* m_pCamera;
    COrbitControls* m_pCameraControls;
    list<CAction*>m_vActionList;

    CWFXGameObject* m_pGameObject;
    bool32 m_bPause;

};



#endif
