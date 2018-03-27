#ifndef __IPCSERVER_H_INCLUDED__
#define __IPCSERVER_H_INCLUDED__

#include <wx/wx.h>
#include <wx/ipc.h>

class IpcServer : public wxServer
{
    public:
        IpcServer(const wxString& topic, wxWindow *handler);
        virtual ~IpcServer();
        wxConnectionBase *OnAcceptConnection(const wxString& topic);
    protected:
    private:
        wxString m_sTopic;
        wxWindow *m_Handler;
};

#endif // __IPCSERVER_H_INCLUDED__
