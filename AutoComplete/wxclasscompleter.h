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

class wxClassCompleterSimple : public wxTextCompleterSimple
{
    public:
        wxClassCompleterSimple();
        virtual ~wxClassCompleterSimple();
        virtual void GetCompletions(const wxString &prefix, wxArrayString &res);
    protected:
    private:
};
#endif // __WXCLASSCOMPLETER_H_INCLUDED__
