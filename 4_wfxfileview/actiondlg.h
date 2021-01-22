#ifndef __ACTIONDLG_H__
#define __ACTIONDLG_H__

#include <standard/dialogs.h>
#include <include/string.h>

struct SActionInfo{
    int32 m_nIndex;
    char m_strName[128];
    float m_fStartTime;
    float m_fEndTime;
    float m_fSpeed;

    bool operator==( const SActionInfo& rhs ){
        return rhs.m_nIndex == this->m_nIndex;
    }
};

class CActionDialog: public CDialog{
public:
    CActionDialog( list<SActionInfo>& vActionInfoList );
    virtual ~CActionDialog();
    
private:
    virtual void OnClick( CUIElement *pSelf );
    virtual void Close();
    CUIElement* m_vElementList[4];
};


#endif
