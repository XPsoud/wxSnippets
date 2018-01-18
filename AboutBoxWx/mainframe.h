#ifndef __MAINFRAME_H_INCLUDED__
#define __MAINFRAME_H_INCLUDED__

#include <wx/wx.h>

enum
{
	OPT_MINIMAL,
	OPT_MAXIMAL,
	OPT_CUSTOM,

	OPT_COUNT
};

enum
{
	CHK_APP_NAME,
	CHK_APP_VERSION,
	CHK_APP_DESCRIPTION,
	CHK_COPYRIGHT,
	CHK_ICON,
	CHK_LICENCE,
	CHK_DEVELOPPER,
	CHK_DEVELOPPERS,
	CHK_WEBSITE,
	CHK_TRANSLATORS,

	CHK_COUNT
};

class MainFrame: public wxFrame
{
	public:
		MainFrame(const wxString& title);
		~MainFrame();
	private:
		// Misc functions
		void CreateControls();
		void ConnectControls();
		void UpdateInterface();
		// Events handlers
		void OnMenuExitClicked(wxCommandEvent &event);
		void OnMenuAboutClicked(wxCommandEvent &event);
		void OnOptInfosClicked(wxCommandEvent &event);
		// Controls variables
		wxRadioButton *m_optInfos[OPT_COUNT];
		wxCheckBox *m_chkInfos[CHK_COUNT];
};

#endif // __MAINFRAME_H_INCLUDED__
