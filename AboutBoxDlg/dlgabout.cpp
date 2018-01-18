#include "dlgabout.h"

#include "main.h"
#include "appversion.h"

#include <wx/bitmap.h>
#include <wx/statbmp.h>
#include <wx/statline.h>

#include "aboutlogo.h"

DlgAbout::DlgAbout(wxWindow *parent) : wxDialog(parent, -1, wxGetStockLabel(wxID_ABOUT, wxSTOCK_NOFLAGS))
{
	wxStaticBitmap *BmpCtrl;
	wxStaticText *label;
	wxStaticLine *hline;
	wxButton *btnClose;

	wxString sMsg=_T("Made with");
	sMsg << _T(" ") << wxGetApp().GetBuildInfos(false);

	wxString sTitle=_T(PRODUCTNAME);
	sTitle << _T(" (v") << VERSION_MAJOR << _T(".") << VERSION_MINOR << _T(".") << VERSION_REV << _T(".") << VERSION_BUILD << _T(")");

	wxBoxSizer *szrMain=new wxBoxSizer(wxVERTICAL);
		wxBoxSizer *szrTop=new wxBoxSizer(wxHORIZONTAL);
			BmpCtrl=new wxStaticBitmap(this, -1, wxGet_wxWidgets_png_Bitmap(), wxPoint(10,15));
			szrTop->Add(BmpCtrl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
			wxBoxSizer *szrRight=new wxBoxSizer(wxVERTICAL);
				label=new wxStaticText(this, -1, sTitle);
				wxFont fntTitle=label->GetFont();
				fntTitle.MakeLarger();
				fntTitle.MakeBold();
				label->SetFont(fntTitle);
				szrRight->Add(label, 0, wxALL|wxALIGN_CENTER, 5);
				label=new wxStaticText(this, -1, _T(COPYRIGHT));
				szrRight->Add(label, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxALIGN_CENTER, 5);
				label=new wxStaticText(this, -1,_(DESCRIPTION));
				szrRight->Add(label, 0, wxLEFT|wxRIGHT|wxTOP|wxALIGN_CENTER, 5);
				label=new wxStaticText(this, -1, sMsg);
				szrRight->Add(label, 0, wxALL|wxALIGN_CENTER, 5);
			szrTop->Add(szrRight, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
		szrMain->Add(szrTop, 0, wxALL, 5);
		hline=new wxStaticLine(this, -1);
		szrMain->Add(hline, 0, wxALL|wxEXPAND, 5);
		btnClose=new wxButton(this, wxID_CANCEL, wxGetStockLabel(wxID_CLOSE));
		szrMain->Add(btnClose, 0, wxALL|wxALIGN_RIGHT, 5);
	SetSizer(szrMain);
	szrMain->SetSizeHints(this);

	CenterOnParent();
}

DlgAbout::~DlgAbout()
{
}
