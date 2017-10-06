#ifndef __MAINFRAME_H_INCLUDED__
#define __MAINFRAME_H_INCLUDED__

#include <wx/wx.h>

class SettingsManager;

class MainFrame: public wxFrame
{
	public:
		MainFrame(const wxString& title);
		~MainFrame();
	private:
		// Misc functions
		void CreateControls();
		void ConnectControls();
		// Events handlers
		void OnSize(wxSizeEvent &event);
		void OnMove(wxMoveEvent &event);
		void OnBtnPrefsClicked(wxCommandEvent &event);
		// Controls vars
		wxButton *m_btnPrefs;
		// Misc vars
		SettingsManager& m_settings;
};

#endif // __MAINFRAME_H_INCLUDED__
