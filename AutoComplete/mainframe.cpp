#include "mainframe.h"

#include "main.h"
#include "wxclasscompleter.h"

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

	ConnectControls();
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
		wxStaticText *label = new wxStaticText(pnl, wxID_STATIC, _T("Start entering a wxWidgets class name \nto see autocompletion working."));
		szrMain->Add(label, 0, wxALL, 5);
		m_txtEntry = new wxTextCtrl(pnl, -1, wxEmptyString);
		szrMain->Add(m_txtEntry, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);
	pnl->SetSizer(szrMain);

	m_txtEntry->AutoComplete(new wxClassCompleter());
}

void MainFrame::ConnectControls()
{
	// No event handler to bind for this snippet
}
