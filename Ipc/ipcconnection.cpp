#include "ipcconnection.h"

#include "mainframe.h"

IpcConnection::IpcConnection(wxWindow *handler)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"IpcConnection\" object\n"));
#endif // __WXDEBUG__
    m_frame = (MainFrame*)handler;
}

IpcConnection::~IpcConnection()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"IpcConnection\" object\n"));
#endif // __WXDEBUG__
}

bool IpcConnection::OnExecute(const wxString& topic, const void* data, size_t size, wxIPCFormat format)
{
#ifdef __WXDEBUG__
	wxPrintf(_T("IpcConnection::OnExecute : topic = %s\n"), topic);
#endif // __WXDEBUG__

    wxString strData((wxChar*)data);
#ifdef __WXDEBUG__
            wxPrintf(_T("\Data = %s\n"), strData);
#endif // __WXDEBUG__
    if (strData == _T("RaiseWindow"))
    {
        if (m_frame==NULL)
        {
#ifdef __WXDEBUG__
            wxPrintf(_T("\tError : RaiseWindow can't be done due to NULL ptr\n"));
#endif // __WXDEBUG__
            return false;
        }
        else
        {
            if (m_frame->IsIconized())
                m_frame->Iconize(false);
            m_frame->Raise();
            m_frame->AddMessageToLog(_T("IPC:") + strData);
            return true;
        }
    }
    if (strData.StartsWith(_T("CommandLine=")))
    {
        if (m_frame==NULL)
        {
#ifdef __WXDEBUG__
            wxPrintf(_T("\tError : CommandLine can't be done due to NULL ptr\n"));
#endif // __WXDEBUG__
            return false;
        }
        else
        {
            m_frame->AddMessageToLog(_T("IPC:") + strData);
            return true;
        }
    }

    // Unknown message
    if (m_frame==NULL)
    {
#ifdef __WXDEBUG__
        wxPrintf(_T("\tError : Unknown message can't be done due to NULL ptr\n"));
#endif // __WXDEBUG__
        return false;
    }
    else
    {
        m_frame->AddMessageToLog(_T("IPC Unknown message:") + strData);
        return true;
    }

    return false;
}
