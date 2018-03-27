#include "mainframe.h"

#include "main.h"

#ifndef __WXMSW__
#include "wxwin32x32.xpm"
#endif // __WXMSW__

MainFrame::MainFrame(const wxString& title) : wxFrame(NULL, -1, title)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"MainFrame\" object\n"));
#endif // __WXDEBUG__

	SetIcon(wxICON(appIcon)); // Defining app icon

	CreateControls();
}

MainFrame::~MainFrame()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"MainFrame\" object\n"));
#endif // __WXDEBUG__
}

void MainFrame::CreateControls()
{
	// Status bar
	CreateStatusBar(1);
	wxString sTxt=wxGetApp().GetBuildInfos(true);
	SetStatusText(sTxt);

	// Add a panel to the frame (needed under Windows to have a nice frame)
	wxPanel *pnl=new wxPanel(this, -1);

	wxBoxSizer *szrMain=new wxBoxSizer(wxVERTICAL);
		m_txtLog=new wxTextCtrl(pnl, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY);
		szrMain->Add(m_txtLog, 1, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);
	pnl->SetSizer(szrMain);

	sTxt = _T("This is the first instance of this application.");
	sTxt << _T("\n\nTo see IPC in action, try to launch another instance");
	sTxt << _T("\nYou can also drag a file on the executable.\n");
	m_txtLog->ChangeValue(sTxt);
}

void MainFrame::AddMessageToLog(const wxString& message)
{
	if (message.IsEmpty())
		return;

	*m_txtLog << _T("\n") << message;
}
