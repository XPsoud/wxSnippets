#ifndef __WXCLASSCOMPLETER_H_INCLUDED__
#define __WXCLASSCOMPLETER_H_INCLUDED__

#include <wx/wx.h>
#include <wx/textcompleter.h>

class wxClassCompleter : public wxTextCompleter
{
    public:
        wxClassCompleter();
        virtual ~wxClassCompleter();
        virtual bool Start(const wxString& prefix);
        virtual wxString GetNext();
    protected:
    private:
        int m_iLastReturned;
        wxString m_sPrefix;
};

#endif // __WXCLASSCOMPLETER_H_INCLUDED__
