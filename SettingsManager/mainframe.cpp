#include "mainframe.h"

#include "main.h"
#include "dlgoptions.h"
#include "settingsmanager.h"

#include <wx/display.h>

#ifndef __WXMSW__
#include "wxwin32x32.xpm"
#endif // __WXMSW__

MainFrame::MainFrame(const wxString& title) : wxFrame(NULL, -1, title),
	m_settings(SettingsManager::Get())
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"MainFrame\" object\n"));
#endif // __WXDEBUG__

	SetIcon(wxICON(appIcon)); // Defining app icon

	CreateControls();

	int iStartPos = m_settings.GetMainWndStartupPos();
	wxSize szStartSize = m_settings.GetMainWndStartupSize();
	wxPoint ptStartPos;
	m_settings.GetMainWndStartupPos(ptStartPos);
	if (iStartPos==wxALIGN_NOT)
	{
		if (szStartSize == wxDefaultSize)
		{
			if (ptStartPos == wxDefaultPosition)
			{
				Maximize(true);
			}
			else
			{
				SetSize(MAINFRAME_MIN_SIZE);
				CenterOnScreen();
			}
		}
		else
		{
			Move(ptStartPos);
			SetSize(szStartSize);
		}
	}
	else
	{

		wxDisplay d;
		wxRect rcD=d.GetClientArea();
		int iWScr=rcD.GetWidth();
		int iHScr=rcD.GetHeight();
		wxPoint pt=wxDefaultPosition;
		if (szStartSize == wxDefaultSize)
			szStartSize = MAINFRAME_MIN_SIZE;
		pt.x=(((iStartPos&wxLEFT)==wxLEFT)?0:((iStartPos&wxRIGHT)==wxRIGHT)?iWScr-szStartSize.GetWidth():(iWScr-szStartSize.GetWidth())/2);
		pt.y=(((iStartPos&wxTOP)==wxTOP)?0:((iStartPos&wxBOTTOM)==wxBOTTOM)?iHScr-szStartSize.GetHeight():(iHScr-szStartSize.GetHeight())/2);
		Move(pt);
		SetSize(szStartSize);
	}
	SetMinSize(MAINFRAME_MIN_SIZE);

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
		m_btnPrefs=new wxButton(pnl, -1, _T("Edit Settings"));
		szrMain->Add(m_btnPrefs, 0, wxALL, 5);
	pnl->SetSizer(szrMain);
}

void MainFrame::ConnectControls()
{
	// General events handlers
	Bind(wxEVT_SIZE, &MainFrame::OnSize, this);
	Bind(wxEVT_MOVE, &MainFrame::OnMove, this);

	m_btnPrefs->Bind(wxEVT_BUTTON, &MainFrame::OnBtnPrefsClicked, this);
}

void MainFrame::OnSize(wxSizeEvent& event)
{
	if (!IsShown()) return;
	if (IsMaximized())
	{
		m_settings.SetLastWindowRect(wxDefaultPosition, wxDefaultSize);
	}
	else
	{
		m_settings.SetLastWindowRect(GetPosition(), GetSize());
	}
	event.Skip();
}

void MainFrame::OnMove(wxMoveEvent& event)
{
	if (!IsShown()) return;
	m_settings.SetLastWindowRect(GetPosition(), GetSize());
	event.Skip();
}

void MainFrame::OnBtnPrefsClicked(wxCommandEvent &event)
{
	DlgOptions dlg(this);
	dlg.ShowModal();
}
