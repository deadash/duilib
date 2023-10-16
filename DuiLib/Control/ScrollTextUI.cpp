#include "StdAfx.h"
#include "ScrollTextUI.h"
namespace DuiLib {

    CScrollTextUI::CScrollTextUI()
    {
        m_nSpeed = 20;
        m_nScrollWidth = 0;
        m_nOffset = 0;
    }

    CScrollTextUI::~CScrollTextUI()
    {

    }

    LPCTSTR CScrollTextUI::GetClass() const
    {
        return DUI_CTR_LABEL_SCROLL;
    }

    LPVOID CScrollTextUI::GetInterface(LPCTSTR pstrName)
    {
        if (_tcscmp(pstrName, DUI_CTR_LABEL_SCROLL) == 0) return static_cast<CScrollTextUI*>(this);
        return CLabelUI::GetInterface(pstrName);
    }

    void CScrollTextUI::SetSpeed(int nSpeed)
    {
        m_nSpeed = nSpeed;
    }

    void CScrollTextUI::PaintText(HDC hDC)
    {
        if (m_dwTextColor == 0) m_dwTextColor = m_pManager->GetDefaultFontColor();
        if (m_dwDisabledTextColor == 0) m_dwDisabledTextColor = m_pManager->GetDefaultDisabledColor();

        RECT rc = m_rcItem;
        rc.left += m_rcTextPadding.left;
        rc.right -= m_rcTextPadding.right;
        rc.top += m_rcTextPadding.top;
        rc.bottom -= m_rcTextPadding.bottom;

        rc.left -= m_nOffset;

        if (m_sText.IsEmpty()) return;
        int nLinks = 0;
        if (IsEnabled()) {
            if (m_bShowHtml)
                CRenderEngine::DrawHtmlText(hDC, m_pManager, rc, m_sText, m_dwTextColor, \
                    NULL, NULL, nLinks, m_iFont, DT_SINGLELINE | m_uTextStyle);
            else
                CRenderEngine::DrawText(hDC, m_pManager, rc, m_sText, m_dwTextColor, \
                    m_iFont, DT_SINGLELINE | m_uTextStyle);
        }
        else {
            if (m_bShowHtml)
                CRenderEngine::DrawHtmlText(hDC, m_pManager, rc, m_sText, m_dwDisabledTextColor, \
                    NULL, NULL, nLinks, m_iFont, DT_SINGLELINE | m_uTextStyle);
            else
                CRenderEngine::DrawText(hDC, m_pManager, rc, m_sText, m_dwDisabledTextColor, \
                    m_iFont, DT_SINGLELINE | m_uTextStyle);
        }
    }

    void CScrollTextUI::DoEvent(TEventUI& event)
    {
        if (event.Type == UIEVENT_TIMER) {
            m_nOffset++;
            if (m_nOffset >= m_nScrollWidth)
                m_nOffset = 0;
            Invalidate();
        }
        /*if (event.Type == UIEVENT_MOUSEENTER)
        {
            SIZE sz;
            sz = CRenderEngine::GetTextSize(m_pManager->GetPaintDC(), m_pManager, m_sText.GetData(), m_iFont, m_uTextStyle);
            if (sz.cx - GetWidth() > 0) {
                m_uTextStyle &= ~DT_END_ELLIPSIS;
                m_nScrollWidth = sz.cx;
                m_pManager->SetTimer(this, SCROLLTEXT_EVENT_TIEM_ID, m_nSpeed);
            }
        }
        if (event.Type == UIEVENT_MOUSELEAVE)
        {
            m_uTextStyle |= DT_END_ELLIPSIS;
            m_nOffset = 0;
            m_nScrollWidth = 0;
            m_pManager->KillTimer(this, SCROLLTEXT_EVENT_TIEM_ID);
        }*/
        CLabelUI::DoEvent(event);
    }

    void CScrollTextUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
    {
        if (_tcscmp(pstrName, _T("speed")) == 0) SetSpeed(_ttoi(pstrValue));
        CLabelUI::SetAttribute(pstrName, pstrValue);
    }

    void CScrollTextUI::SetText(LPCTSTR pstrText)
    {
        CLabelUI::SetText(pstrText);

        if (0 != _tcscmp(pstrText,_T("")))
        {
            SIZE sz;
            sz = CRenderEngine::GetTextSize(m_pManager->GetPaintDC(), m_pManager, m_sText.GetData(), m_iFont, m_uTextStyle);
            if (sz.cx - GetWidth() > 0) {
                m_uTextStyle &= ~DT_END_ELLIPSIS;
                m_nScrollWidth = sz.cx;
                m_pManager->SetTimer(this, SCROLLTEXT_EVENT_TIEM_ID, m_nSpeed);
            }
        }
        else
        {
            m_uTextStyle |= DT_END_ELLIPSIS;
            m_nOffset = 0;
            m_nScrollWidth = 0;
            m_pManager->KillTimer(this, SCROLLTEXT_EVENT_TIEM_ID);
        }

    }
}
