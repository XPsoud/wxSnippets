#include "filesdroptargets.h"

wxDEFINE_EVENT(wxEVT_SINGLEFILE_DROPPED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_MULTIFILES_DROPPED, wxCommandEvent);

SingleFileDropTarget::SingleFileDropTarget(wxWindow *dstHandler)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"SingleFileDropTarget\" object\n"));
#endif // __WXDEBUG__
	m_wndTarget=dstHandler;
}

SingleFileDropTarget::~SingleFileDropTarget()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"SingleFileDropTarget\" object\n"));
#endif // __WXDEBUG__
}

bool SingleFileDropTarget::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString &filenames)
{
	// We can only accept one file at a time
	// So we take only the first element of the wxArrayString
	// And tell the destination handler that a new file has been dropped
	wxCommandEvent evt(wxEVT_SINGLEFILE_DROPPED, wxID_ANY);
	evt.SetString(filenames[0]);
	m_wndTarget->GetEventHandler()->AddPendingEvent(evt);
	return true;
}

MultiFilesDropTarget::MultiFilesDropTarget(wxWindow *dstHandler)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"MultiFilesDropTarget\" object\n"));
#endif // DEBUG
	m_wndTarget=dstHandler;
}

MultiFilesDropTarget::~MultiFilesDropTarget()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"MultiFilesDropTarget\" object\n"));
#endif // DEBUG
}

bool MultiFilesDropTarget::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString &filenames)
{
	// We can accept all the given files
	// We must reconstruct a string with all the files names and paths
	// separated wih '\n' witch shouldn't be present in any of them
	// And tell the destination handler that some files has been dropped
	wxString sFiles=filenames[0];
	for (size_t i=1; i<filenames.Count(); ++i)
		sFiles << _T('\n') << filenames[i];
	wxCommandEvent evt(wxEVT_MULTIFILES_DROPPED, wxID_ANY);
	evt.SetString(sFiles);
	m_wndTarget->GetEventHandler()->AddPendingEvent(evt);
	return true;
}
