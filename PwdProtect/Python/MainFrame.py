import wx

class MainFrame(wx.Frame):

    def __init__(self):
        wx.Frame.__init__(self, None, title=wx.GetApp().GetAppName())
        self.SetIcon(wx.Icon('../../common/wxwin.ico'))

        self._createControls()

        self.CenterOnScreen()

    def _createControls(self):
        # A Statusbar in the bottom of the window
        self.CreateStatusBar(1)
        sMsg = 'wxPython ' + wx.version() + ' - ' + wx.GetLibraryVersionInfo().VersionString
        self.SetStatusText(sMsg)

        # Add a panel to the frame (needed under Windows to have a nice background)
        pnl = wx.Panel(self, wx.ID_ANY)

        szrMain = wx.BoxSizer(wx.VERTICAL)
        szrMain.AddSpacer(15)
        label = wx.StaticText(pnl, wx.ID_STATIC, 'Well done!.\nYou have successfully entered the required password.')
        szrMain.Add(label, 0, wx.ALL, 15)
        szrMain.AddSpacer(15)

        pnl.SetSizer(szrMain)

        szrMain.SetSizeHints(self)
