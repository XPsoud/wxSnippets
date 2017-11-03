#include "wxguid.h"

#if defined(__WXGTK__)
#include <uuid/uuid.h>
#elif defined(__WXMAC__)
#include <CoreFoundation/CFUUID.h>
#elif defined(__WXMSW__)
#include <objbase.h>
#endif // __WXMSW__

// Default contructor : create an empty Guid
wxGuid::wxGuid()
{
    Clear();
}

// Copy constructor
wxGuid::wxGuid(const wxGuid &other)
{
    memcpy(m_cValues, other.m_cValues, 16);
}

// Construct from a wxString
wxGuid::wxGuid(const wxString& srcStr)
{
    Clear();
    size_t iLen=srcStr.Length(), iDone=0;
    char c1, c2;
    wxUniChar c;
    bool bFirst=true;
    for (size_t i=0; i<iLen; ++i)
    {
        c=srcStr[i];
        if ((c==_T('-'))||(c==_T(' '))||(c==_T('_')))
            continue;
        if (bFirst)
        {
            if (c.GetAsChar(&c1))
            {
                bFirst=false;
            }
        }
        else
        {
            if (c.GetAsChar(&c2))
            {
                m_cValues[iDone]=HexPair2Char(c1, c2);
                iDone++;
                bFirst=true;
            }
        }
        if (iDone>=16)
            break;
    }
}
// Reset Guid values to 0
void wxGuid::Clear()
{
    memset(m_cValues, 0, 16);
}

// Generate the Guid values (or clear them and return false)
bool wxGuid::Generate()
{
#if defined(__WXGTK__)
    uuid_generate(m_cValues);
#elif defined(__WXMAC__)
    CFUUIDRef idRef = CFUUIDCreate(NULL);
    CFUUIDBytes idBytes = CFUUIDGetUUIDBytes(idRef);
    memcpy(m_cValues, (void*)&idBytes, 16);
    CFRelease(idRef);
#elif defined(__WXMSW__)
    CoCreateGuid((GUID*)m_cValues);
#else
    Clear();
    return false;
#endif
    return true;
}

bool wxGuid::IsValid()
{
    for (int i=0; i<16; ++i)
    {
        if (m_cValues[i]!=0)
            return true;
    }
    return false;
}

// Get the Guid values as a wxString
wxString wxGuid::ToString()
{
    wxString sRes=wxEmptyString;
    for (int i=0; i<16; ++i)
    {
        sRes << wxString::Format(_T("%02X"), m_cValues[i]);
        if ((i==3)||(i==5)||(i==7)||(i==9))
            sRes << _T("-");
    }
    return sRes;
}

// Assignment operator
wxGuid &wxGuid::operator=(const wxGuid &other)
{
    memcpy(m_cValues, other.m_cValues, 16);
    return *this;
}

// Equality operator
bool wxGuid::operator==(const wxGuid &other) const
{
    for (int i=0; i<16; ++i)
    {
        if (m_cValues[i]!=other.m_cValues[i])
            return false;
    }
    return true;
}

// Inequality operator
bool wxGuid::operator!=(const wxGuid &other) const
{
    return !((*this) == other);
}

// Hexadecimal single char to value
unsigned char wxGuid::HexDigit2Char(unsigned char c)
{
    if (c > 47 && c < 58)
        return c - 48;

    if (c > 96 && c < 103)
        return c - 87;

    if (c > 64 && c < 71)
        return c - 55;

  return 0;
}

// Hexadecimal pair chars to value
unsigned char wxGuid::HexPair2Char(unsigned char high, unsigned char low)
{
    return HexDigit2Char(high) * 16 + HexDigit2Char(low);
}
