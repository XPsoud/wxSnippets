#ifndef __IPCCLIENT_H_INCLUDED__
#define __IPCCLIENT_H_INCLUDED__

#include <wx/wx.h>
#include <wx/ipc.h>

class IpcClient : public wxClient
{
    public:
        IpcClient();
        ~IpcClient();
        wxConnectionBase* OnMakeConnection();
};

#endif // __IPCCLIENT_H_INCLUDED__
