#include "mainframe.h"

#include "main.h"
#include "dlgabout.h"

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
	new wxPanel(this, -1);

	// Create the menu bar
	wxMenuBar *menuBar = new wxMenuBar();
		// File menu
		wxMenu *fileMenu = new wxMenu();
		fileMenu->Append(wxID_EXIT, wxGetStockLabel(wxID_EXIT, wxSTOCK_WITH_MNEMONIC|wxSTOCK_WITH_ACCELERATOR), wxGetStockHelpString(wxID_EXIT));
		menuBar->Append(fileMenu, wxGetStockLabel(wxID_FILE));
		// Help menu
		wxMenu* helpMenu = new wxMenu();
		helpMenu->Append(wxID_ABOUT, wxGetStockLabel(wxID_ABOUT, wxSTOCK_WITH_MNEMONIC|wxSTOCK_WITH_ACCELERATOR), wxGetStockHelpString(wxID_ABOUT));
		menuBar->Append(helpMenu, wxGetStockLabel(wxID_HELP));
	SetMenuBar(menuBar);
#ifdef __WXMAC__
	// On OSX, Exit and About menu entries are handled by the osx-specific menu
	// So the File and Help menus became empty : we can delete them
	menuBar->Remove(1); // Remove and the Help menu
	delete helpMenu;    // and delete it
	menuBar->Remove(0); // Remove the File menu
	delete fileMenu;    // and delete it
#endif // __WXMAC__
}

void MainFrame::ConnectControls()
{
	Bind(wxEVT_MENU, &MainFrame::OnMenuExitClicked, this, wxID_EXIT);
	Bind(wxEVT_MENU, &MainFrame::OnMenuAboutClicked, this, wxID_ABOUT);
}

void MainFrame::OnMenuExitClicked(wxCommandEvent &event)
{
	Destroy();
}

void MainFrame::OnMenuAboutClicked(wxCommandEvent &event)
{
	DlgAbout dlg(this);
	dlg.ShowModal();
}
