#ifndef __LISTBOXADAPTER_H_INCLUDED__
#define __LISTBOXADAPTER_H_INCLUDED__

#include <wx/wx.h>

#if wxCHECK_VERSION(3, 1, 0)
#include <wx/addremovectrl.h>

class ListBoxAdaptor : public wxAddRemoveAdaptor
{
	public:
		ListBoxAdaptor(wxListBox* lbox, int maxItems);
		virtual wxWindow* GetItemsCtrl() const;
		virtual bool CanAdd() const;
		virtual bool CanRemove() const;
		virtual void OnAdd();
		virtual void OnRemove();
	private:
		wxListBox* m_lbox;
		int m_iMaxItems;
};
#endif // wxCHECK_VERSION(3, 1, 0)

#endif // __LISTBOXADAPTER_H_INCLUDED__
