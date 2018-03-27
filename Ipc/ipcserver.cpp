#include "ipcserver.h"

#include "ipcconnection.h"

IpcServer::IpcServer(const wxString& topic, wxWindow *handler)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"IpcServer\" object\n"));
#endif // __WXDEBUG__
    m_sTopic = topic;
    m_Handler = handler;
}

IpcServer::~IpcServer()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"IpcServer\" object\n"));
#endif // __WXDEBUG__
}

wxConnectionBase* IpcServer::OnAcceptConnection(const wxString& topic)
{
    if (topic == m_sTopic)
        return new IpcConnection(m_Handler);

    return NULL;
}
