#ifndef __WXGUID_H_INCLUDED__
#define __WXGUID_H_INCLUDED__

#include <wx/wx.h>

class wxGuid
{
    public:
        // Create an empty guid
        wxGuid();
        // Copy constructor
        wxGuid(const wxGuid &other);
        // Construct from a wxString
        wxGuid(const wxString& srcStr);
        // Reset values to 0
        void Clear();
        // Generate the Guid values
        bool Generate();
        // Check if the values has been generated
        bool IsValid();
        // Get the Guid values as a wxString
        wxString ToString();
        // Assignment operator
        wxGuid &operator=(const wxGuid &other);
        // Equality operator
        bool operator==(const wxGuid &other) const;
        // Inequality operator
        bool operator!=(const wxGuid &other) const;
    private:
        // Hexadecimal single char to value
        unsigned char HexDigit2Char(unsigned char c);
        // Hexadecimal pair chars to value
        unsigned char HexPair2Char(unsigned char high, unsigned char low);
        // Guid values
        unsigned char m_cValues[16];
};

#endif // __WXGUID_H_INCLUDED__
