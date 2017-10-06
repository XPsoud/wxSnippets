#ifndef __MAIN_H_INCLUDED__
#define __MAIN_H_INCLUDED__

#include <wx/wx.h>
#include <wx/snglinst.h>

class MyApp : public wxApp
{
	public:
		virtual bool OnInit();
		virtual int OnExit();
		wxString GetBuildInfos(bool all=false);
		wxString GetVersionString(bool full=false, bool build=false);
	private:
		wxSingleInstanceChecker *m_pSnglInstChkr;
};

DECLARE_APP(MyApp)

#endif // __MAIN_H_INCLUDED__
