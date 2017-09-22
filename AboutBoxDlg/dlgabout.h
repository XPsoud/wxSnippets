#ifndef __DLGABOUT_H_INCLUDED__
#define __DLGABOUT_H_INCLUDED__

#include <wx/wx.h>

#include <wx/dialog.h>

class DlgAbout : public wxDialog
{
	public:
		DlgAbout(wxWindow *parent);
		virtual ~DlgAbout();
};

#endif // __DLGABOUT_H_INCLUDED__
