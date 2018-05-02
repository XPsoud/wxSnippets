import wx

from ClassList import szClasses

class ClassCompleterSimple(wx.TextCompleterSimple):
    def __init__(self, maxResults=25):
        wx.TextCompleterSimple.__init__(self)
        self._iMaxResults = maxResults

    def GetCompletions(self, prefix):
        if len(prefix) < 3:
            return []
        res = []
        prfx = prefix.lower()
        for item in szClasses:
            if item.lower().startswith(prfx):
                res.append(item)
                # Max number of results reached ?
                if len(res) == self._iMaxResults:
                    return res

        return res

class ClassCompleter(wx.TextCompleter):
    def __init__(self):
        wx.TextCompleter.__init__(self)
        self._iLastReturned = wx.NOT_FOUND
        self._sPrefix = ''

    def Start(self, prefix):
        self._sPrefix = prefix.lower()
        self._iLastReturned = wx.NOT_FOUND
        for item in szClasses:
            if item.lower().startswith(self._sPrefix):
                return True
        # Nothing found
        return False

    def GetNext(self):
        for i in range(self._iLastReturned+1, len(szClasses)):
            if szClasses[i].lower().startswith(self._sPrefix):
                self._iLastReturned = i
                return szClasses[i]
        # No more corresponding item
        return ''
