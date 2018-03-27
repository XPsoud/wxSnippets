#ifndef __IPCCONNECTION_H_INCLUDED
#define __IPCCONNECTION_H_INCLUDED

#include <wx/wx.h>
#include <wx/ipc.h>

class MainFrame;

class IpcConnection : public wxConnection
{
    public:
        IpcConnection(wxWindow *handler);
        virtual ~IpcConnection();
        bool OnExecute(const wxString& topic, const void *data, size_t size, wxIPCFormat format);
    protected:
    private:
        MainFrame *m_frame;
};

#endif // __IPCCONNECTION_H_INCLUDED
