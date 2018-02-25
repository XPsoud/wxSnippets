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
#if wxCHECK_VERSION(3, 1, 0)
		wxStaticText *label=new wxStaticText(pnl, wxID_STATIC, _T("You can add up to 5 items to the list using the '+' button below"));
		szrMain->Add(label, 0, wxALL, 5);
		label=new wxStaticText(pnl, wxID_STATIC, _T("You can remove the selected item using the '-' button."));
		szrMain->Add(label, 0, wxLEFT|wxRIGHT|wxBOTTOM, 5);
		m_arCtrl=new wxAddRemoveCtrl(pnl);
			m_lstItems = new wxListBox(m_arCtrl, -1, wxDefaultPosition, wxSize(350, 200));
			m_arCtrl->SetAdaptor(new ListBoxAdaptor(m_lstItems, 5));
			m_arCtrl->SetButtonsToolTips(_T("Add a new item"), _T("Remove the selected item"));
		szrMain->Add(m_arCtrl, 1, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);
#else // wxCHECK_VERSION(3, 1, 0)
	wxStaticText *label=new wxStaticText(pnl, wxID_STATIC, _T("Sorry, but this snippet requires at least the version 3.1.0 of wxWidgets"));
	szrMain->Add(label, 0, wxALL, 15);
#endif // wxCHECK_VERSION(3, 1, 0)

	pnl->SetSizer(szrMain);

	szrMain->SetSizeHints(this);
}
