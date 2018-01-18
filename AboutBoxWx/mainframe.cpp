#include "mainframe.h"

#include "main.h"
#include "aboutlogo.h"
#include "appversion.h"

#include <wx/aboutdlg.h>

#ifndef __WXMSW__
#include "wxwin32x32.xpm"
#endif // __WXMSW__

const wxChar* g_szLicence = _T(
"This application is provided \"as is\" without any licence\n"
"\n"
"Everyone is free to copy, modify, sell, and do anything with it.\n"
"\n"
"This application and its source code is provided as a small\n"
"sample to show the use of wxWidgets standard about box."
);

const wxChar* g_szTranslators[] = {
	_T("Xaviou (en = app default)"),
	_T("Nobody Else (no translations support)")
};

const int g_iCheckedBoxes[] = {
	CHK_APP_NAME,
	CHK_APP_VERSION,
	CHK_APP_DESCRIPTION,
	CHK_COPYRIGHT,
	CHK_ICON
};

MainFrame::MainFrame(const wxString& title) : wxFrame(NULL, -1, title)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"MainFrame\" object\n"));
#endif // __WXDEBUG__

	SetIcon(wxICON(appIcon)); // Defining app icon

	CreateControls();

	ConnectControls();

	UpdateInterface();
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
		wxStaticBoxSizer *stbSzr=new wxStaticBoxSizer(wxVERTICAL, pnl, _T("Informations to show in the \"About\" box:"));

			m_optInfos[OPT_MINIMAL] = new wxRadioButton(pnl, wxID_ANY, _T("Application's name only (minimal \"Aboud\" box)"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
			stbSzr->Add(m_optInfos[0], 0, wxALL, 5);

			m_optInfos[OPT_MAXIMAL] = new wxRadioButton(pnl, wxID_ANY, _T("All available informations"));
			stbSzr->Add(m_optInfos[1], 0, wxLEFT|wxRIGHT|wxBOTTOM, 5);

			m_optInfos[OPT_CUSTOM] = new wxRadioButton(pnl, wxID_ANY, _T("Let me select the informations I want to see"));
			stbSzr->Add(m_optInfos[2], 0, wxLEFT|wxRIGHT|wxEXPAND, 5);

			wxBoxSizer *lnSzr=new wxBoxSizer(wxHORIZONTAL);
				lnSzr->AddSpacer(10);
				wxFlexGridSizer *flxSzr=new wxFlexGridSizer(2, 5, 5);

					m_chkInfos[CHK_APP_NAME] = new wxCheckBox(pnl, wxID_ANY, _T("Application's name"));
						m_chkInfos[CHK_APP_NAME]->Disable();
					flxSzr->Add(m_chkInfos[CHK_APP_NAME]);

					m_chkInfos[CHK_APP_VERSION] = new wxCheckBox(pnl, wxID_ANY, _T("Application's version"));
					flxSzr->Add(m_chkInfos[CHK_APP_VERSION]);

					m_chkInfos[CHK_APP_DESCRIPTION] = new wxCheckBox(pnl, wxID_ANY, _T("Description"));
					flxSzr->Add(m_chkInfos[CHK_APP_DESCRIPTION]);

					m_chkInfos[CHK_COPYRIGHT] = new wxCheckBox(pnl, wxID_ANY, _T("Copyright"));
					flxSzr->Add(m_chkInfos[CHK_COPYRIGHT]);

					m_chkInfos[CHK_ICON] = new wxCheckBox(pnl, wxID_ANY, _T("Icon"));
					flxSzr->Add(m_chkInfos[CHK_ICON]);

					m_chkInfos[CHK_LICENCE] = new wxCheckBox(pnl, wxID_ANY, _T("Licence text"));
					flxSzr->Add(m_chkInfos[CHK_LICENCE]);

					m_chkInfos[CHK_DEVELOPPER] = new wxCheckBox(pnl, wxID_ANY, _T("Main developper"));
					flxSzr->Add(m_chkInfos[CHK_DEVELOPPER]);

					m_chkInfos[CHK_DEVELOPPERS] = new wxCheckBox(pnl, wxID_ANY, _T("Multiple developpers"));
					flxSzr->Add(m_chkInfos[CHK_DEVELOPPERS]);

					m_chkInfos[CHK_WEBSITE] = new wxCheckBox(pnl, wxID_ANY, _T("Website url"));
					flxSzr->Add(m_chkInfos[CHK_WEBSITE]);

					m_chkInfos[CHK_TRANSLATORS] = new wxCheckBox(pnl, wxID_ANY, _T("Translators"));
					flxSzr->Add(m_chkInfos[CHK_TRANSLATORS]);

				lnSzr->Add(flxSzr, 0, wxALL, 0);
			stbSzr->Add(lnSzr, 0, wxALL, 5);
		szrMain->Add(stbSzr, 1, wxALL|wxEXPAND, 5);
	pnl->SetSizer(szrMain);

	// At startup, select the "All available infos" option
	m_optInfos[OPT_MAXIMAL]->SetValue(true);
	// Check the wxCheckBoxes depending on the global array (see on top of this file)
	for (size_t i=0; i<WXSIZEOF(g_iCheckedBoxes); ++i)
	{
		m_chkInfos[g_iCheckedBoxes[i]]->SetValue(true);
	}

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

	szrMain->SetSizeHints(this);
}

void MainFrame::ConnectControls()
{
	Bind(wxEVT_MENU, &MainFrame::OnMenuExitClicked, this, wxID_EXIT);
	Bind(wxEVT_MENU, &MainFrame::OnMenuAboutClicked, this, wxID_ABOUT);
	Bind(wxEVT_RADIOBUTTON, &MainFrame::OnOptInfosClicked, this);
}

void MainFrame::UpdateInterface()
{
	// Checkboxes are only shown if the "custom" option is selected
	bool bShow = m_optInfos[OPT_CUSTOM]->GetValue();
	for (int i=0; i<CHK_COUNT; ++i)
		m_chkInfos[i]->Show(bShow);
}

void MainFrame::OnMenuExitClicked(wxCommandEvent &event)
{
	Destroy();
}

void MainFrame::OnMenuAboutClicked(wxCommandEvent &event)
{
	// Get the index of the selected option
	int iOpt=OPT_MAXIMAL;
	for (int i=0; i<OPT_COUNT; ++i)
	{
		if (m_optInfos[i]->GetValue())
			iOpt = i;
	}
	wxAboutDialogInfo info;
	wxIcon ico;

	for (int i=0; i<CHK_COUNT; ++i)
	{
		if ((i==CHK_APP_NAME)||(iOpt==OPT_MAXIMAL)||((iOpt==OPT_CUSTOM)&&(m_chkInfos[i]->GetValue())))
		{
			switch(i)
			{
				case CHK_APP_NAME:
					info.SetName(_T(PRODUCTNAME));
					break;
				case CHK_APP_VERSION:
					info.SetVersion(wxGetApp().GetVersionNumString(true));
					break;
				case CHK_APP_DESCRIPTION:
					info.SetDescription(wDESCRIPTION);
					break;
				case CHK_COPYRIGHT:
					info.SetCopyright(COPYRIGHT);
					break;
				case CHK_ICON:
					ico.CopyFromBitmap(wxGet_wxWidgets_png_Bitmap());
					info.SetIcon(ico);
					break;
				case CHK_LICENCE:
					info.SetLicence(g_szLicence);
					break;
				case CHK_DEVELOPPER:
					info.AddDeveloper(_T("X. Perrissoud AKA Xaviou"));
					break;
				case CHK_DEVELOPPERS:
					info.AddDeveloper(_T("An unknown developper"));
					info.AddDeveloper(_T("Another unknown developper"));
					break;
				case CHK_WEBSITE:
					info.SetWebSite(_T("https://wxstuff.xaviou.fr"), _T("X@v's wxStuff website"));
					break;
				case CHK_TRANSLATORS:
					info.SetTranslators(wxArrayString(WXSIZEOF(g_szTranslators), g_szTranslators));
					break;
			}
		}
	}

	wxAboutBox(info);
}
void MainFrame::OnOptInfosClicked(wxCommandEvent& event)
{
	UpdateInterface();
}
