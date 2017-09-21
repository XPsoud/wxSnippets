#ifndef __MAINFRAME_H_INCLUDED__
#define __MAINFRAME_H_INCLUDED__

#include <wx/wx.h>
#include <wx/listctrl.h>

class MainFrame: public wxFrame
{
	public:
		MainFrame(const wxString& title);
		~MainFrame();
	private:
		// Misc functions
		void CreateControls();
		void UpdateValues();
		// Controls vars
		wxListView* m_lstResults;
};

#endif // __MAINFRAME_H_INCLUDED__
