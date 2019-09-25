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
		m_btnDoTest=new wxButton(pnl, -1, _T("Start test"));
		szrMain->Add(m_btnDoTest, 0, wxALL, 5);
		m_txtResult=new wxTextCtrl(pnl, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
		szrMain->Add(m_txtResult, 1, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);
	pnl->SetSizer(szrMain);
}

void MainFrame::ConnectControls()
{
	m_btnDoTest->Bind(wxEVT_BUTTON, &MainFrame::OnBtnTestClicked, this);
}

void MainFrame::OnBtnTestClicked(wxCommandEvent &event)
{
	wxMessageBox(_T("Test function terminated!"), _T("Done"), wxICON_INFORMATION|wxOK|wxCENTER);
}
