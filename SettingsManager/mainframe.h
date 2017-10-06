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
		// Events handlers
		void OnBtnTestClicked(wxCommandEvent &event);
		// Controls vars
		wxButton *m_btnDoTest;
		wxTextCtrl *m_txtResult;
};

#endif // __MAINFRAME_H_INCLUDED__
