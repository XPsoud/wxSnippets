#include "ipcclient.h"

#include "ipcconnection.h"

IpcClient::IpcClient(void)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"IpcClient\" object\n"));
#endif // __WXDEBUG__
}

IpcClient::~IpcClient()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"IpcClient\" object\n"));
#endif // __WXDEBUG__
}

wxConnectionBase* IpcClient::OnMakeConnection()
{
     return new IpcConnection(NULL);
}
