#ifndef __MAINFRAME_H_INCLUDED__
#define __MAINFRAME_H_INCLUDED__

#include <wx/wx.h>

class MainFrame: public wxFrame
{
	public:
		MainFrame(const wxString& title);
		~MainFrame();
		void AddMessageToLog(const wxString& message);
	private:
		// Misc functions
		void CreateControls();
		// Controls vars
		wxTextCtrl *m_txtLog;
};

#endif // __MAINFRAME_H_INCLUDED__
