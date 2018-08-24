#include "main.h"

#include "mainframe.h"
#include "appversion.h"

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Initializing a \"wxApp\" derived object\n"));
#endif // __WXDEBUG__

	wxInitAllImageHandlers();
	// Set application name
	SetAppName(_T(PRODUCTNAME));

	InitLanguage();

	MainFrame* frame = new MainFrame(GetVersionString(true));
	SetTopWindow(frame);
	frame->Show();

	return true;
}

int MyApp::OnExit()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Exiting from a \"wxApp\" derived object\n"));
#endif // __WXDEBUG__

	return wxApp::OnExit();
}

wxString MyApp::GetBuildInfos(bool all)
{
	wxString wxbuild(wxVERSION_STRING);
	if (sizeof(void *)==4)
		wxbuild << _T("-32 Bits");
	else
		wxbuild << _T("-64 Bits");
	if (all)
	{
#if defined(__WXMSW__)
		wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
		wxbuild << _T("-OSX");
#elif defined(__UNIX__)
		wxbuild << _T("-Linux");
#endif

#if defined(wxUSE_UNICODE)
		wxbuild << _T("-Unicode");
#else
		wxbuild << _T("-Ansi");
#endif // wxUSE_UNICODE

#if defined(WXUSINGDLL)
		wxbuild << _T("-Dynamic");
#else
		wxbuild << _T("-Static");
#endif

		wxbuild << _T(" build");
	}
	return wxbuild;
}

wxString MyApp::GetVersionString(bool full, bool build)
{
	wxString sRes=wxTheApp->GetAppName();
	sRes << _T(" (v") << VERSION_MAJOR << _T(".") << VERSION_MINOR;
	if (full) sRes << _T(".") << VERSION_REV;
	sRes << _T(")");
	if (build)
		sRes << _T(" build ") << VERSION_BUILD;
	return sRes;
}

void MyApp::InitLanguage()
{
	static const wxLanguage langIds[] =
	{
		wxLANGUAGE_DEFAULT,
		wxLANGUAGE_ENGLISH,
		wxLANGUAGE_FRENCH,
		wxLANGUAGE_GERMAN,
		wxLANGUAGE_ITALIAN,
	};

	static const wxString langNames[] =
	{
		_T("System default"),
		_T("English"),
		_T("French"),
		_T("German"),
		_T("Italian"),
	};
	// Sizes of the arrays must match
	wxCOMPILE_TIME_ASSERT( WXSIZEOF(langNames) == WXSIZEOF(langIds), LangArraysMismatch );

	int lng = wxGetSingleChoiceIndex(_T("Please choose language:"), _T("Language"), WXSIZEOF(langNames), langNames);
	wxLanguage lang = lng == -1 ? wxLANGUAGE_DEFAULT : langIds[lng];

	// We don't have to do anything if the selected language is english
	// As the strings of this app have been written in this lang
	if (lang == wxLANGUAGE_ENGLISH)
		return;

	wxLocale::AddCatalogLookupPathPrefix(_T("../langs"));
	if ( !m_locale.Init(lang, wxLOCALE_LOAD_DEFAULT) )
	{
		wxLogWarning(_T("This language is not supported by the system."));
	}
	if (!m_locale.AddCatalog(_T("internat")))
	{
		const wxLanguageInfo* pInfo = wxLocale::GetLanguageInfo(lang);
		wxLogError(_T("Couldn't find/load the 'internat' catalog for locale '%s'."), pInfo->GetLocaleName());
	}
}
