#include "wxclasscompleter.h"

#include "wxclasslist.h"

wxClassCompleter::wxClassCompleter()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"wxClassCompleter\" object\n"));
#endif // __WXDEBUG__
    m_iLastReturned = wxNOT_FOUND;
    m_sPrefix = wxEmptyString;
}

wxClassCompleter::~wxClassCompleter()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"wxClassCompleter\" object\n"));
#endif // __WXDEBUG__
}

bool wxClassCompleter::Start(const wxString& prefix)
{
    m_sPrefix = prefix.Lower();
    m_iLastReturned = wxNOT_FOUND;

    for (int i=0; i<CLASSES_COUNT; ++i)
    {
        if (szClasses[i].Lower().StartsWith(m_sPrefix))
            return true;
    }
    // Nothing found
    return false;
}

wxString wxClassCompleter::GetNext()
{
    for (int i=m_iLastReturned+1; i<CLASSES_COUNT; ++i)
    {
        if (szClasses[i].Lower().StartsWith(m_sPrefix))
        {
            m_iLastReturned = i;
            return szClasses[i];
        }
    }
    // No more corresponding item
    return wxEmptyString;
}


wxClassCompleterSimple::wxClassCompleterSimple()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Creating a \"wxClassCompleterSimple\" object\n"));
#endif // __WXDEBUG__
}

wxClassCompleterSimple::~wxClassCompleterSimple()
{
#ifdef __WXDEBUG__
	wxPrintf(_T("Destroying a \"wxClassCompleterSimple\" object\n"));
#endif // __WXDEBUG__
}

void wxClassCompleterSimple::GetCompletions(const wxString& prefix, wxArrayString& res)
{
    // Don't return anything if prefix has less than 3 chas
    if (prefix.Length()<3)
        return;
    wxString sPrfx = prefix.Lower();
    for (int i=0; i<CLASSES_COUNT; ++i)
    {
        if (szClasses[i].Lower().StartsWith(sPrfx))
        {
            res.Add(szClasses[i]);
        }
    }
}
