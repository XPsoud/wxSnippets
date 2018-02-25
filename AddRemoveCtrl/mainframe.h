#ifndef __MAINFRAME_H_INCLUDED__
#define __MAINFRAME_H_INCLUDED__

#include <wx/wx.h>

#include "listboxadaptor.h"

class MainFrame: public wxFrame
{
	public:
		MainFrame(const wxString& title);
		~MainFrame();
	private:
		// Misc functions
		void CreateControls();
		// Controls vars
#if wxCHECK_VERSION(3, 1, 0)
		wxAddRemoveCtrl *m_arCtrl;
		wxListBox *m_lstItems;
#endif // wxCHECK_VERSION(3, 1, 0)
};

#endif // __MAINFRAME_H_INCLUDED__
