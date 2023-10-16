#ifndef SCROLLTEXT_H
#define SCROLLTEXT_H
#include "UILabel.h"

#define  SCROLLTEXT_EVENT_TIEM_ID	400
namespace DuiLib {

    class DUILIB_API CScrollTextUI : public CLabelUI
    {
    public:
        CScrollTextUI();
        virtual ~CScrollTextUI();

        virtual LPCTSTR GetClass() const;
        virtual LPVOID GetInterface(LPCTSTR pstrName);
        virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
        virtual void SetText(LPCTSTR pstrText);
        void SetSpeed(int nSpeed);

        void DoEvent(TEventUI& event);
        void PaintText(HDC hDC);
    private:
        int m_nSpeed;
        int m_nScrollWidth;
        int m_nOffset;
    };
}
#endif