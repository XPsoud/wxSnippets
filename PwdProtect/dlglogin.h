#ifndef __DLGLOGIN_H_INCLUDED__
#define __DLGLOGIN_H_INCLUDED__

#include "wx/wx.h"

#include <wx/dialog.h>

class DlgLogin : public wxDialog
{
    public:
        DlgLogin(wxWindow *parent, const wxString& password, int iMaxAttemps=3);
        virtual ~DlgLogin();
    private:
        // Misc functions
        void CreateControls();
        void ConnectControls();
        // Events handlers
        void OnChkShowPasswordClicked(wxCommandEvent &event);
        void OnBtnOkClicked(wxCommandEvent &event);
        // Controls vars
        wxStaticText *m_lblWrongPwd;
        wxTextCtrl *m_txtPwd;
        wxCheckBox *m_chkShowPwd;
        wxButton *m_btnOk, *m_btnCancel;
        // Misc vars
        wxString m_sPassword;
        int m_iAttemps, m_iMaxAttemps;
};

#endif // __DLGLOGIN_H_INCLUDED__
