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
		void OnSingleFileDropped(wxCommandEvent &event);
		void OnMultiFilesDropped(wxCommandEvent &event);
		// Controls vars
		wxTextCtrl *m_txtSingleFile;
		wxListBox *m_lstMultiFiles;
};

#endif // __MAINFRAME_H_INCLUDED__
