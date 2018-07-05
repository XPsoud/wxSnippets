#include "mainframe.h"

#include "main.h"

#ifndef __WXMSW__
#include "wxwin32x32.xpm"
#endif // __WXMSW__

#include <wx/notifmsg.h>

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
		szrMain->AddStretchSpacer(1);
		m_btnShowMsg=new wxButton(pnl, -1, _T("Show a notification message"));
		szrMain->Add(m_btnShowMsg, 0, wxALL|wxALIGN_CENTER, 5);
		szrMain->AddStretchSpacer(1);
	pnl->SetSizer(szrMain);
}

void MainFrame::ConnectControls()
{
	m_btnShowMsg->Bind(wxEVT_BUTTON, &MainFrame::OnBtnShowMsgClicked, this);
}

void MainFrame::OnBtnShowMsgClicked(wxCommandEvent &event)
{
	wxString sTitle = _T("wxWidgets notification");
	wxString sMsg = _T("This is a notification message.\n\nWelcome on wxWidgets ;-)");
	wxNotificationMessage nmsg(sTitle, sMsg);
	nmsg.SetFlags(wxICON_INFORMATION);

	nmsg.Show(wxNotificationMessage::Timeout_Auto);
}
