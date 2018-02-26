#include "dlglogin.h"

#include "key.png.h"

#include <wx/statline.h>

DlgLogin::DlgLogin(wxWindow *parent, const wxString& password, int iMaxAttemps) : wxDialog(parent, -1, _T("Restricted access"))
{
#ifdef __WXDEBUG__
    wxPrintf(_T("Creating a \"DlgLogin\" object\n"));
#endif // __WXDEBUG__

    m_sPassword=password;
    m_iAttemps = 0;
    m_iMaxAttemps = iMaxAttemps;

    CreateControls();

    ConnectControls();

    CenterOnParent();
}

DlgLogin::~DlgLogin()
{
#ifdef __WXDEBUG__
    wxPrintf(_T("Destroying a \"DlgLogin\" object\n"));
#endif // __WXDEBUG__
}

void DlgLogin::CreateControls()
{
    wxStaticText *label;
    wxBoxSizer *szrMain=new wxBoxSizer(wxVERTICAL), *hszr;

        hszr=new wxBoxSizer(wxHORIZONTAL);

            wxStaticBitmap *stBmp=new wxStaticBitmap(this, wxID_STATIC, wxGet_key_png_Bitmap());
            hszr->Add(stBmp, 0, wxALL|wxALIGN_CENTER_VERTICAL, 10);
            label=new wxStaticText(this, wxID_STATIC, _T("Access to this application has been\nprotected with a password."));
            hszr->Add(label, 0, wxALL|wxALIGN_CENTER_VERTICAL, 10);

        szrMain->Add(hszr, 0, wxALL, 0);

        label = new wxStaticText(this, wxID_STATIC, wxString::Format(_T("For this test application, the password is '%s'"), m_sPassword));
        szrMain->Add(label, 0, wxLEFT|wxRIGHT|wxBOTTOM, 10);

        m_lblWrongPwd=new wxStaticText(this, wxID_STATIC, _T("Incorrect password!"));
            wxFont fnt=m_lblWrongPwd->GetFont();
            fnt.MakeBold();
            m_lblWrongPwd->SetFont(fnt);
            m_lblWrongPwd->SetForegroundColour(*wxRED);
        szrMain->Add(m_lblWrongPwd, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL, 10);

        hszr=new wxBoxSizer(wxHORIZONTAL);

            label=new wxStaticText(this, wxID_STATIC, _T("Enter the access password:"));
            hszr->Add(label, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0);

            m_txtPwd=new wxTextCtrl(this, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
            hszr->Add(m_txtPwd, 1, wxLEFT, 5);

        szrMain->Add(hszr, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 10);

        m_chkShowPwd=new wxCheckBox(this, -1, _T("Display password in plain text"));
        szrMain->Add(m_chkShowPwd, 0, wxLEFT|wxRIGHT|wxBOTTOM, 10);

        szrMain->Add(new wxStaticLine(this, wxID_STATIC), 0, wxLEFT|wxRIGHT|wxEXPAND, 10);

        hszr=new wxBoxSizer(wxHORIZONTAL);

            m_btnOk=new wxButton(this, wxID_OK, _T("Access"));
            hszr->Add(m_btnOk, 0, wxALL, 0);

            m_btnCancel=new wxButton(this, wxID_CANCEL, _T("Cancel"));
            hszr->Add(m_btnCancel, 0, wxLEFT, 10);

        szrMain->Add(hszr, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 10);

    SetSizer(szrMain);

    m_lblWrongPwd->Hide();

    szrMain->SetSizeHints(this);

    m_btnOk->SetDefault();
}

void DlgLogin::ConnectControls()
{
    m_chkShowPwd->Bind(wxEVT_CHECKBOX, &DlgLogin::OnChkShowPasswordClicked, this);
    m_btnOk->Bind(wxEVT_BUTTON, &DlgLogin::OnBtnOkClicked, this);
}

void DlgLogin::OnChkShowPasswordClicked(wxCommandEvent& event)
{
    Freeze();
    wxString sPass=m_txtPwd->GetValue();
    wxSizer *szr=m_txtPwd->GetContainingSizer();
    long lFrom, lTo;
    m_txtPwd->GetSelection(&lFrom, &lTo);
    int iStyle=(m_chkShowPwd->IsChecked()?0:wxTE_PASSWORD);
    szr->Detach(m_txtPwd);
    delete m_txtPwd;
    m_txtPwd=new wxTextCtrl(this, -1, sPass, wxDefaultPosition, wxDefaultSize, iStyle);
    m_txtPwd->SetFocus();
    m_txtPwd->SetSelection(lFrom, lTo);
    szr->Add(m_txtPwd, 1, wxLEFT, 5);
    szr->Layout();
    Thaw();
}

void DlgLogin::OnBtnOkClicked(wxCommandEvent& event)
{
    bool bOk=(m_sPassword==m_txtPwd->GetValue());

    if (bOk || (m_iAttemps==(m_iMaxAttemps-1)))
        EndModal(bOk?wxID_OK:wxID_CANCEL);

    if (m_iAttemps==0)
    {
        m_lblWrongPwd->Show();
        GetSizer()->SetSizeHints(this);
        CenterOnParent();
    }
    m_txtPwd->SetFocus();
    m_txtPwd->SetSelection(-1, -1);
    m_iAttemps++;
    m_lblWrongPwd->SetLabel(wxString::Format(_T("Incorrect password: trial %d/%d"), m_iAttemps+1, m_iMaxAttemps));
    GetSizer()->Layout();
}
