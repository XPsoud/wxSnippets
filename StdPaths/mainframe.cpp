#include "mainframe.h"

#include "main.h"

#include <wx/stdpaths.h>

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

	UpdateValues();
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
		m_lstResults = new wxListView(pnl, -1);
		szrMain->Add(m_lstResults, 1, wxALL|wxEXPAND, 5);
			m_lstResults->AppendColumn(_T("Name"), wxLIST_FORMAT_RIGHT);
			m_lstResults->AppendColumn(_T("Value"));
	pnl->SetSizer(szrMain);
}

void MainFrame::UpdateValues()
{
	wxStandardPaths& stdPth=wxStandardPaths::Get();
	long lIndex;

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("wxHAS_NATIVE_STDPATHS"));
#ifdef wxHAS_NATIVE_STDPATHS
	m_lstResults->SetItem(lIndex, 1, _T("Yes"));
#else // wxHAS_NATIVE_STDPATHS
	m_lstResults->SetItem(lIndex, 1, _T("No"));
#endif // wxHAS_NATIVE_STDPATHS

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("AppDocumentsDir"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetAppDocumentsDir());

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("ConfigDir"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetConfigDir());
	
	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("DataDir"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetDataDir());

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("DocumentsDir"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetDocumentsDir());

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("ExecutablePath"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetExecutablePath());

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("InstallPrefix"));
#ifdef wxHAS_STDPATHS_INSTALL_PREFIX
	m_lstResults->SetItem(lIndex, 1, stdPth.GetInstallPrefix());
#else // wxHAS_STDPATHS_INSTALL_PREFIX
	m_lstResults->SetItem(lIndex, 1, _T("Unavailable for this system"));
#endif // wxHAS_STDPATHS_INSTALL_PREFIX

lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("LocalDataDir"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetLocalDataDir());

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("LocalizedResourcesDir(\"lang\")"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetLocalizedResourcesDir(_T("lang"), wxStandardPaths::ResourceCat_None));

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("PluginsDir"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetPluginsDir());

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("ResourcesDir "));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetResourcesDir());

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("TempDir"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetTempDir());

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("UserConfigDir"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetUserConfigDir());

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("UserDataDir"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetUserDataDir());
	
#if wxCHECK_VERSION(3, 1, 0)
	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("UserDir(Dir_Documents)"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetUserDir(wxStandardPaths::Dir_Documents));

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("UserDir(Dir_Desktop)"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetUserDir(wxStandardPaths::Dir_Desktop));

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("UserDir(Dir_Downloads)"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetUserDir(wxStandardPaths::Dir_Downloads));

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("UserDir(Dir_Music)"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetUserDir(wxStandardPaths::Dir_Music));

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("UserDir(Dir_Pictures)"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetUserDir(wxStandardPaths::Dir_Pictures));

	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("UserDir(Dir_Videos)"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetUserDir(wxStandardPaths::Dir_Videos));
#endif // wxCHECK_VERSION(3, 1, 0)
	lIndex=m_lstResults->InsertItem(m_lstResults->GetItemCount(), _T("UserLocalDataDir"));
	m_lstResults->SetItem(lIndex, 1, stdPth.GetUserLocalDataDir());

	for (int i=0; i<2; ++i)
		m_lstResults->SetColumnWidth(i, wxLIST_AUTOSIZE);
}