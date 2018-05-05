import wx

from ClassCompleter import ClassCompleter, ClassCompleterSimple

class MainFrame(wx.Frame):

    def __init__(self):
        wx.Frame.__init__(self, None, title=wx.GetApp().GetAppName())
        self.SetIcon(wx.Icon('../../common/wxwin.ico'))

        self._createControls()

        self._connectControls()

    def _createControls(self):
        # A Statusbar in the bottom of the window
        self.CreateStatusBar(1)
        sMsg = 'wxPython ' + wx.version()
        self.SetStatusText(sMsg)

        # Add a panel to the frame (needed under Windows to have a nice background)
        pnl = wx.Panel(self, wx.ID_ANY)

        szrMain = wx.BoxSizer(wx.VERTICAL)
        szrMain.AddSpacer(5)

        stbSzr = wx.StaticBoxSizer(wx.VERTICAL, pnl, 'wxTextCompleterSimple:')
        stBox = stbSzr.GetStaticBox()
        label = wx.StaticText(stBox, wx.ID_STATIC, 'Start entering a wxWidgets class name in the wxTextCtrl below.')
        stbSzr.Add(label, 0, wx.LEFT|wx.RIGHT|wx.TOP, 5)
        stbSzr.AddSpacer(2)
        label = wx.StaticText(stBox, wx.ID_STATIC, 'Auto-completion should start working at the 3rd char.')
        stbSzr.Add(label, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM, 5)
        self._txtEntry1 = wx.TextCtrl(stBox, -1, wx.EmptyString)
        stbSzr.Add(self._txtEntry1, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM|wx.EXPAND, 5)

        szrMain.Add(stbSzr, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM|wx.EXPAND, 5)

        stbSzr = wx.StaticBoxSizer(wx.VERTICAL, pnl, 'wxTextCompleter:')
        stBox = stbSzr.GetStaticBox()
        label = wx.StaticText(stBox, wx.ID_STATIC, 'Start entering a wxWidgets class name in the wxTextCtrl below.')
        stbSzr.Add(label, 0, wx.LEFT|wx.RIGHT|wx.TOP, 5)
        stbSzr.AddSpacer(2)
        label = wx.StaticText(stBox, wx.ID_STATIC, 'Auto-completion should start working at the 1rst char.')
        stbSzr.Add(label, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM, 5)
        self._txtEntry2 = wx.TextCtrl(stBox, -1, wx.EmptyString)
        stbSzr.Add(self._txtEntry2, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM|wx.EXPAND, 5)

        szrMain.Add(stbSzr, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM|wx.EXPAND, 5)

        pnl.SetSizer(szrMain)
        szrMain.SetSizeHints(self)

        self._txtEntry1.AutoComplete(ClassCompleterSimple())
        self._txtEntry2.AutoComplete(ClassCompleter())

    def _connectControls(self):
        # No event handler to bind for this snippet
        pass
