#ifndef _MENULAYER_H_
#define _MENULAYER_H_

#include "layer.h"
#include <standard/gui.h>

class CMenuLayer: public CLayer, public CUIEvent{
public:
    CMenuLayer();
    virtual ~CMenuLayer();
    virtual void Init( CWindow* pParent );
    virtual void Show();
    virtual void Hide();
    virtual void Update( int32 nDelta );
    virtual void Render();

public:
    virtual void OnClick( CUIElement *pSelf );
    void OnExtButtonClick( CUIElement* pElement );
    void OnColorTypeClick( CUIElement* pElement );
    void OnGameBeginClick( CUIElement* pElement );
    CPanel* m_pMenuLayerPanel;
    CButton* m_pBlockTypeCheck[ 2 ];
    CButton* m_pColorTypeCheck[ 3 ];

};


#endif
