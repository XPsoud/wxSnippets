#ifndef __MAINFRAME_H_INCLUDED__
#define __MAINFRAME_H_INCLUDED__

#include <wx/wx.h>

class MainFrame: public wxFrame
{
	public:
		MainFrame(const wxString& title);
		~MainFrame();
	private:
		// Misc functions
		void CreateControls();
		void ConnectControls();
		void DoGetInfos();
		// Events handlers
		void OnOptGetFromClicked(wxCommandEvent &event);
		void OnCmbItemSelected(wxCommandEvent &event);
		void OnCmbTextChanged(wxCommandEvent &event);
		// Controls vars
		wxBoxSizer *m_szrMain;
		wxRadioButton *m_optGetFTFrom[2];
		wxStaticText *m_lblSource;
		wxComboBox *m_cmbSource;
		wxTextCtrl *m_txtInfos;
};

#endif // __MAINFRAME_H_INCLUDED__
