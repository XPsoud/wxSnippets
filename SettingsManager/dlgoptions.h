#ifndef __DLGOPTIONS_H_INCLUDED__
#define __DLGOPTIONS_H_INCLUDED__

#include <wx/wx.h>

class SettingsManager;
class wxNotebook;

class DlgOptions : public wxDialog
{
    public:
	DlgOptions(wxWindow *parent);
	virtual ~DlgOptions();
    private:
	// Misc functions
	void CreateControls();
	void FillControls();
	void ConnectControls();
	bool ApplySettings();
	// Events handlers
	void OnStartupPosTypeChanged(wxCommandEvent &event);
	void OnSomethingHasChanged(wxCommandEvent &event);
	void OnBtnApplyClicked(wxCommandEvent &event);
	void OnBtnOkClicked(wxCommandEvent &event);
	// "General" tab controls vars
	wxRadioButton *m_optStartType[2], *m_optDefPos[9];
	wxStaticBox *m_stbPos;
	wxCheckBox *m_chkSingleInstance, *m_chkCompSettings;
	// Main dialog box controls
	wxNotebook *m_nBook;
	wxButton *m_btnApply;
	// Misc vars
	SettingsManager& m_options;
};

#endif // __DLGOPTIONS_H_INCLUDED__
