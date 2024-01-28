#include "mainframe.h"

#include "main.h"

#ifndef __WXMSW__
#include "wxwin32x32.xpm"
#endif // __WXMSW__

#include <wx/mimetype.h>

MainFrame::MainFrame(const wxString& title) : wxFrame(NULL, -1, title)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"MainFrame\" object\n"));
#endif // __WXDEBUG__

	SetIcon(wxICON(appIcon)); // Defining app icon

	CreateControls();

	ConnectControls();

	// Simulate a click on the first radiobutton
	wxCommandEvent evt(wxEVT_RADIOBUTTON, m_optGetFTFrom[0]->GetId());
	m_optGetFTFrom[0]->SetValue(true);
	OnOptGetFromClicked(evt);
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

	m_szrMain=new wxBoxSizer(wxVERTICAL);
        wxBoxSizer *lnszr = new wxBoxSizer(wxHORIZONTAL);
            wxStaticText *label = new wxStaticText(pnl, wxID_STATIC, _T("Get file type from:"));
            lnszr->Add(label, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0);
            m_optGetFTFrom[0] = new wxRadioButton(pnl, wxID_ANY, _T("MIME type"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
            lnszr->Add(m_optGetFTFrom[0], 0, wxLEFT|wxALIGN_CENTER_VERTICAL, 5);
            m_optGetFTFrom[1] = new wxRadioButton(pnl, wxID_ANY, _T("File extension"));
            lnszr->Add(m_optGetFTFrom[1], 0, wxLEFT|wxALIGN_CENTER_VERTICAL, 5);
        m_szrMain->Add(lnszr, 0, wxALL|wxEXPAND, 10);

        lnszr = new wxBoxSizer(wxHORIZONTAL);
            m_lblSource = new wxStaticText(pnl, wxID_STATIC, wxEmptyString);
            lnszr->Add(m_lblSource, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0);
            m_cmbSource = new wxComboBox(pnl, wxID_ANY);
            lnszr->Add(m_cmbSource, 1, wxLEFT|wxALIGN_CENTER_VERTICAL, 5);
        m_szrMain->Add(lnszr, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 10);

        m_txtInfos = new wxTextCtrl(pnl, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY);
        m_szrMain->Add(m_txtInfos, 1, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 10);
	pnl->SetSizer(m_szrMain);
}

void MainFrame::ConnectControls()
{
	m_optGetFTFrom[0]->Bind(wxEVT_RADIOBUTTON, &MainFrame::OnOptGetFromClicked, this);
	m_optGetFTFrom[1]->Bind(wxEVT_RADIOBUTTON, &MainFrame::OnOptGetFromClicked, this);
	m_cmbSource->Bind(wxEVT_COMBOBOX, &MainFrame::OnCmbItemSelected, this);
	m_cmbSource->Bind(wxEVT_TEXT, &MainFrame::OnCmbTextChanged, this);
}

void MainFrame::DoGetInfos()
{
    wxString sValue = m_cmbSource->GetValue();
    sValue.Trim(true);
    sValue.Trim(false);
    sValue.Replace(_T('.'), _T(""));

    if (sValue.IsEmpty())
    {
        if (m_optGetFTFrom[0]->GetValue())
            m_txtInfos->ChangeValue(_T("No valid MIME type entered or selected."));
        else
            m_txtInfos->ChangeValue(_T("No valid extension entered or selected."));
        return;
    }
    sValue = m_cmbSource->GetValue();
    wxFileType *fType=NULL;
    if (m_optGetFTFrom[0]->GetValue())
        fType = wxTheMimeTypesManager->GetFileTypeFromMimeType(sValue);
    else
        fType = wxTheMimeTypesManager->GetFileTypeFromExtension(sValue);
    if (fType == NULL)
    {
        m_txtInfos->AppendText(_T("\n\tError: No file type found!"));
        return;
    }
    if (fType->GetDescription(&sValue))
    {
        m_txtInfos->AppendText(_T("\nDescription: "));
        m_txtInfos->AppendText(sValue);
    }

    if (m_optGetFTFrom[0]->GetValue())
    {
        wxArrayString arsExt;
        fType->GetExtensions(arsExt);
        m_txtInfos->AppendText(_T("\nExtensions:"));
        for (size_t i=0; i<arsExt.GetCount(); ++i)
            m_txtInfos->AppendText(wxString::Format(_T(" %s"), arsExt[i]));
    }
    else
    {
        fType->GetMimeType(&sValue);
        m_txtInfos->AppendText(_T("\nMIME type: "));
        m_txtInfos->AppendText(sValue);
    }
    wxLogNull noLog;
    wxIconLocation icoLoc;
    fType->GetIcon(&icoLoc);
    m_txtInfos->AppendText(_T("\nAssociated icon: "));
    m_txtInfos->AppendText(icoLoc.GetFileName());

    wxArrayString arsVerbs, arsCommands;
    wxFileType::MessageParameters mp;
    int iCount = fType->GetAllCommands(&arsVerbs, &arsCommands, mp);
    *m_txtInfos << _T("\nFound ") << iCount << _T(" command(s) for this file type.");
    for (int i=0; i<iCount; ++i)
        *m_txtInfos << _T("\n - ") << arsVerbs[i] << _T(" => ") << arsCommands[i];

    delete fType;
}

void MainFrame::OnOptGetFromClicked(wxCommandEvent& event)
{
    if (m_optGetFTFrom[0]->GetValue())
    {
        m_lblSource->SetLabel(_("Enter a MIME type or select one in the list:"));
        m_cmbSource->Clear();
        m_cmbSource->Append(_T("text/plain"));
        m_cmbSource->Append(_T("application/zip"));
        m_cmbSource->Append(_T("image/png"));
        m_cmbSource->Append(_T("image/jpeg"));
        m_cmbSource->Append(_T("audio/mpeg"));
        m_cmbSource->Append(_T("video/mp4"));
        m_cmbSource->Append(_T("text/html"));
    }
    else
    {
        m_lblSource->SetLabel(_("Enter a file extension select one in the list:"));
        m_cmbSource->Clear();
        m_cmbSource->Append(_T("txt"));
        m_cmbSource->Append(_T("zip"));
        m_cmbSource->Append(_T("png"));
        m_cmbSource->Append(_T("jpg"));
        m_cmbSource->Append(_T("mp3"));
        m_cmbSource->Append(_T("mp4"));
        m_cmbSource->Append(_T("html"));
    }
    m_szrMain->Layout();
    DoGetInfos();
}

void MainFrame::OnCmbItemSelected(wxCommandEvent& event)
{
    wxString sTxt = _T("File type informations for ");
    if (m_optGetFTFrom[0]->GetValue())
        sTxt << _T("MIME type");
    else
        sTxt << _T("extension");
    sTxt << _T("\"") << m_cmbSource->GetValue() << _T("\":");
    m_txtInfos->ChangeValue(sTxt);

    DoGetInfos();
}

void MainFrame::OnCmbTextChanged(wxCommandEvent& event)
{
    if (m_cmbSource->IsTextEmpty())
        DoGetInfos();
    else
        OnCmbItemSelected(event);
}
