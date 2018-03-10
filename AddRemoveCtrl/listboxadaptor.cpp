#include "listboxadaptor.h"

#if wxCHECK_VERSION(3, 1, 0)

ListBoxAdaptor::ListBoxAdaptor(wxListBox* lbox, int maxItems)
{
    m_iMaxItems = maxItems;
    m_lbox = lbox;
}

wxWindow* ListBoxAdaptor::GetItemsCtrl() const
{
    return m_lbox;
}

bool ListBoxAdaptor::CanAdd() const
{
    return m_iMaxItems>(int)m_lbox->GetCount();
}

bool ListBoxAdaptor::CanRemove() const
{
    return m_lbox->GetSelection() != wxNOT_FOUND;
}

void ListBoxAdaptor::OnAdd()
{
    wxString sNewEntry = wxGetTextFromUser(_T("Enter the new item to add"));
    if (sNewEntry.IsEmpty())
        return;
    m_lbox->Append(sNewEntry);
}

void ListBoxAdaptor::OnRemove()
{
    if (wxMessageBox(_T("Remove the selected item?"), _T("Confirm"), wxYES_NO|wxICON_QUESTION|wxCENTER)==wxNO)
        return;
    m_lbox->Delete(m_lbox->GetSelection());
}

#endif // wxCHECK_VERSION(3, 1, 0)
