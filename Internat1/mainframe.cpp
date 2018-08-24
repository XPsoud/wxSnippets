#include "mainframe.h"

#include "main.h"
#include "aboutlogo.h"
#include "appversion.h"

#include <wx/aboutdlg.h>

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

	// Menu bar
	wxMenuBar *menuBar = new wxMenuBar();
	// File menu
	wxMenu *fileMenu = new wxMenu();
	fileMenu->Append(wxID_EXIT);
	menuBar->Append(fileMenu, wxGetStockLabel(wxID_FILE));
	// Help menu
	wxMenu* helpMenu = new wxMenu();
	helpMenu->Append(wxID_ABOUT);
	menuBar->Append(helpMenu, wxGetStockLabel(wxID_HELP));

	SetMenuBar(menuBar);

	// Add a panel to the frame (needed under Windows to have a nice frame)
	wxPanel *pnl=new wxPanel(this, -1);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
		sizer->AddStretchSpacer(1);
		wxStaticText *label = new wxStaticText(pnl, wxID_STATIC, _("Welcome from wxWidgets"));
			wxFont fnt=label->GetFont().MakeLarger().MakeLarger();
			label->SetFont(fnt);
		sizer->Add(label, 0, wxALL|wxALIGN_CENTER, 10);
		sizer->AddStretchSpacer(1);
	pnl->SetSizer(sizer);
}

void MainFrame::ConnectControls()
{
	Bind(wxEVT_MENU, &MainFrame::OnMenuExitClicked, this, wxID_EXIT);
	Bind(wxEVT_MENU, &MainFrame::OnMenuAboutClicked, this, wxID_ABOUT);
}

void MainFrame::OnMenuExitClicked(wxCommandEvent& event)
{
	Close();
}

void MainFrame::OnMenuAboutClicked(wxCommandEvent& event)
{
	wxAboutDialogInfo info;
	info.SetName(_(PRODUCTNAME));
	info.SetVersion(wxString::Format(_T("(v%d.%d.%d)"), VERSION_MAJOR, VERSION_MINOR, VERSION_REV));
	info.SetDescription(_(DESCRIPTION));
	info.SetCopyright(COPYRIGHT);
	wxIcon ico;
	ico.CopyFromBitmap(wxGet_wxWidgets_png_Bitmap());
	info.SetIcon(ico);

	wxAboutBox(info);
}
