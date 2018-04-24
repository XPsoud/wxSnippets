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
