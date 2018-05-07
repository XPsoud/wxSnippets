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

	// Vars that will be used more than 1 time
	wxStaticText *label;
	wxStaticBoxSizer *stbSzr;
	wxStaticBox *stBox;

	wxBoxSizer *szrMain=new wxBoxSizer(wxVERTICAL);
		stbSzr = new wxStaticBoxSizer(wxVERTICAL, pnl, _T("wxTextCompleterSimple:"));
		stBox = stbSzr->GetStaticBox();
			label = new wxStaticText(stBox, wxID_STATIC, _T("Start entering a wxWidgets class name in the wxTextCtrl below."));
			stbSzr->Add(label, 0, wxLEFT|wxRIGHT|wxTOP, 5);
			stbSzr->AddSpacer(2);
			label = new wxStaticText(stBox, wxID_STATIC, _T("Auto-completion should start working at the 3rd char."));
			stbSzr->Add(label, 0, wxLEFT|wxRIGHT|wxBOTTOM, 5);
			m_txtEntry1 = new wxTextCtrl(stBox, -1, wxEmptyString);
			stbSzr->Add(m_txtEntry1, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);
		szrMain->Add(stbSzr, 0, wxALL|wxEXPAND, 5);

		stbSzr = new wxStaticBoxSizer(wxVERTICAL, pnl, _T("wxTextCompleter:"));
		stBox = stbSzr->GetStaticBox();
			label = new wxStaticText(stBox, wxID_STATIC, _T("Start entering a wxWidgets class name in the wxTextCtrl below."));
			stbSzr->Add(label, 0, wxLEFT|wxRIGHT|wxTOP, 5);
			stbSzr->AddSpacer(2);
			label = new wxStaticText(stBox, wxID_STATIC, _T("Auto-completion should start working at 1rst char."));
			stbSzr->Add(label, 0, wxLEFT|wxRIGHT|wxBOTTOM, 5);
			m_txtEntry2 = new wxTextCtrl(stBox, -1, wxEmptyString);
			stbSzr->Add(m_txtEntry2, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);
		szrMain->Add(stbSzr, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);
	pnl->SetSizer(szrMain);
	szrMain->SetSizeHints(this);

	bool bRes = m_txtEntry1->AutoComplete(new wxClassCompleterSimple());
	bRes |= m_txtEntry2->AutoComplete(new wxClassCompleter());
	if (!bRes)
		wxMessageBox(_T("It seems that AutoCompletion isn't supported !"), _T("Error"), wxICON_ERROR|wxOK|wxCENTER);
}

void MainFrame::ConnectControls()
{
	// No event handler to bind for this snippet
}
