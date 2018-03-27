#include "main.h"

#include "mainframe.h"
#include "appversion.h"
#include "ipcclient.h"
#include "ipcconnection.h"

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Initializing a \"wxApp\" derived object\n"));
#endif // __WXDEBUG__

	wxInitAllImageHandlers();
	// Set application name
	SetAppName(_T(PRODUCTNAME));

	m_ipcServer = NULL;

#ifdef __WXMSW__
	const wxString IPC_SERVICE = GetAppName();
#else
	const wxString IPC_SERVICE = wxString::Format(_T("/tmp/%s_%s.socket"), GetAppName(), wxGetUserName());
#endif // __WXMSW__
	const wxString IPC_TOPIC = GetAppName() + _T("IpcServer");

	// Try to connect to an existing instance
	IpcClient *client = new IpcClient();
	IpcConnection *connection = NULL;
	{
		// Use wxLogNull here to avoid framework's arror messages
		// about unsuccessfull connection
		wxLogNull logNull;
		connection = (IpcConnection*)client->MakeConnection(_T("localhost"), IPC_SERVICE, IPC_TOPIC);
		if (connection!=NULL)
		{
#ifdef __WXDEBUG__
			wxPrintf(_T("Found a running instance...\n"));
#endif // __WXDEBUG__
			// Be sure the already running instance is raised to top
			connection->Execute(_T("RaiseWindow"));
			// Is there something given using the command line ?
			wxString sCmdLine = wxEmptyString;
			for (int i=1; i<argc; ++i)
				sCmdLine << argv[i] << _T(" ");
			if (!sCmdLine.IsEmpty())
				connection->Execute(_T("CommandLine=") + sCmdLine);

			connection->Disconnect();
			delete connection;
			delete client;

			// return false to close this instance of the application
			return false;
		}
	}
	delete client;

	MainFrame* frame = new MainFrame(GetVersionString(true));
	SetTopWindow(frame);
	frame->Show();

	m_ipcServer = new IpcServer(IPC_TOPIC, frame);
	m_ipcServer->Create(IPC_SERVICE);

	return true;
}

int MyApp::OnExit()
{
	if (m_ipcServer!=NULL)
		delete m_ipcServer;

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
