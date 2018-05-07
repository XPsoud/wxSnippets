#include "mainframe.h"

#include "main.h"
#include "filesdroptargets.h"

#include <wx/tokenzr.h>

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
		stbSzr = new wxStaticBoxSizer(wxVERTICAL, pnl, _T("Single file or directory:"));
		stBox = stbSzr->GetStaticBox();
			label = new wxStaticText(stBox, wxID_STATIC, _T("Drop any file/folder from the files manager to the wxTextCtrl below"));
			stbSzr->Add(label, 0, wxLEFT|wxRIGHT|wxTOP, 5);
			stbSzr->AddSpacer(2);
			label = new wxStaticText(stBox, wxID_STATIC, _T("to see its full path. Even if you drop more than one item, only the"));
			stbSzr->Add(label, 0, wxLEFT|wxRIGHT, 5);
			stbSzr->AddSpacer(2);
			label = new wxStaticText(stBox, wxID_STATIC, _T("path of the first one will be shown."));
			stbSzr->Add(label, 0, wxLEFT|wxRIGHT|wxBOTTOM, 5);
			m_txtSingleFile = new wxTextCtrl(stBox, -1, wxEmptyString);
			stbSzr->Add(m_txtSingleFile, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);
		szrMain->Add(stbSzr, 0, wxALL|wxEXPAND, 5);

		stbSzr = new wxStaticBoxSizer(wxVERTICAL, pnl, _T("Multiple files or directories:"));
		stBox = stbSzr->GetStaticBox();
			label = new wxStaticText(stBox, wxID_STATIC, _T("Drop some files/folders from the files manager to the wxListBox below"));
			stbSzr->Add(label, 0, wxLEFT|wxRIGHT|wxTOP, 5);
			stbSzr->AddSpacer(2);
			label = new wxStaticText(stBox, wxID_STATIC, _T("Their full paths will be added to the list."));
			stbSzr->Add(label, 0, wxLEFT|wxRIGHT|wxBOTTOM, 5);
			m_lstMultiFiles = new wxListBox(stBox, -1);
			stbSzr->Add(m_lstMultiFiles, 1, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);
		szrMain->Add(stbSzr, 1, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);
	pnl->SetSizer(szrMain);

	szrMain->SetSizeHints(this);

	m_txtSingleFile->SetDropTarget(new SingleFileDropTarget(this));
	m_lstMultiFiles->SetDropTarget(new MultiFilesDropTarget(this));
}

void MainFrame::ConnectControls()
{
	Bind(wxEVT_SINGLEFILE_DROPPED, &MainFrame::OnSingleFileDropped, this);
	Bind(wxEVT_MULTIFILES_DROPPED, &MainFrame::OnMultiFilesDropped, this);
}

void MainFrame::OnSingleFileDropped(wxCommandEvent &event)
{
	m_txtSingleFile->ChangeValue(event.GetString());
}

void MainFrame::OnMultiFilesDropped(wxCommandEvent &event)
{
	wxArrayString arsItems = wxStringTokenize(event.GetString(), _T("\n"));

	m_lstMultiFiles->Append(arsItems);

	m_lstMultiFiles->EnsureVisible(m_lstMultiFiles->GetCount()-1);
}
