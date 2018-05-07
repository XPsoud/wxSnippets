import wx

wxEVT_SINGLEFILE_DROPPED = wx.NewEventType()
EVT_SINGLEFILE_DROPPED = wx.PyEventBinder(wxEVT_SINGLEFILE_DROPPED, 1)
wxEVT_MULTIFILES_DROPPED = wx.NewEventType()
EVT_MULTIFILES_DROPPED = wx.PyEventBinder(wxEVT_MULTIFILES_DROPPED, 1)

class FileDropEvent(wx.PyCommandEvent):
    def __init__(self, evtType):
        wx.PyCommandEvent.__init__(self, evtType)
        self._items = []

    def SetSingleItem(self, item):
        self._items = [item]

    def GetSingleItem(self):
        if not self._items:
            return ''
        return self._items[0]

    def AddItem(self, item):
        self._items.append(item)

    def AddItems(self, items):
        self._items += items

    def GetItems(self):
        return self._items

class SingleFileDropTarget(wx.FileDropTarget):

    def __init__(self, dstHandler):
        wx.FileDropTarget.__init__(self)
        self._target = dstHandler

    def OnDropFiles(self, x, y, filenames):
        # As we can only accept one file at a time
	    # We take only the first element of the provided list
	    # And tell the destination handler that a new file has been dropped
        evt = FileDropEvent(wxEVT_SINGLEFILE_DROPPED)
        evt.SetSingleItem(filenames[0])
        self._target.GetEventHandler().AddPendingEvent(evt)
        return True

class MultiFilesDropTarget(wx.FileDropTarget):

    def __init__(self, dstHandler):
        wx.FileDropTarget.__init__(self)
        self._target = dstHandler

    def OnDropFiles(self, x, y, filenames):
        # We can accept all the given files
	    # And tell the destination handler that a new file has been dropped
        evt = FileDropEvent(wxEVT_MULTIFILES_DROPPED)
        evt.AddItems(filenames)
        self._target.GetEventHandler().AddPendingEvent(evt)
        return True
