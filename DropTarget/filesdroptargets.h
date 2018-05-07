#ifndef __FILESDROPTARGETS_H_INCLUDED__
#define __FILESDROPTARGETS_H_INCLUDED__

#include <wx/wx.h>
#include <wx/dnd.h>

wxDECLARE_EVENT(wxEVT_SINGLEFILE_DROPPED, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_MULTIFILES_DROPPED, wxCommandEvent);

class SingleFileDropTarget : public wxFileDropTarget
{
	public:
		SingleFileDropTarget(wxWindow *dstHandler);
		virtual ~SingleFileDropTarget();
		virtual bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString &filenames);
	private:
		wxWindow *m_wndTarget;
};

class MultiFilesDropTarget : public wxFileDropTarget
{
	public:
		MultiFilesDropTarget(wxWindow *dstHandler);
		virtual ~MultiFilesDropTarget();
		virtual bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString &filenames);
	private:
		wxWindow *m_wndTarget;
};

#endif // __FILESDROPTARGETS_H_INCLUDED__
