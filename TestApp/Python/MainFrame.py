import wx

class MainFrame(wx.Frame):

    def __init__(self):
        wx.Frame.__init__(self, None, title=wx.GetApp().GetAppName())
        self.SetIcon(wx.Icon('../../common/wxwin.ico'))

        self._createControls()

        self._connectControls()

    def _createControls(self):
        # A Statusbar in the bottom of the window
        self.CreateStatusBar(1)
        sMsg = 'wxPython ' + wx.version() + ' - ' + wx.GetLibraryVersionInfo().VersionString
        self.SetStatusText(sMsg)

        # Add a panel to the frame (needed under Windows to have a nice background)
        pnl = wx.Panel(self, wx.ID_ANY)

        szrMain = wx.BoxSizer(wx.VERTICAL)
        self._btnDoTest = wx.Button(pnl, wx.ID_ANY, 'Start test')
        szrMain.Add(self._btnDoTest, 0, wx.ALL, 5)
        self._txtResult = wx.TextCtrl(pnl, -1, wx.EmptyString, style=wx.TE_MULTILINE)
        szrMain.Add(self._txtResult, 1, wx.LEFT|wx.RIGHT|wx.BOTTOM|wx.EXPAND, 5)
        pnl.SetSizer(szrMain)

    def _connectControls(self):
        self._btnDoTest.Bind(wx.EVT_BUTTON, self._onBtnTestClicked)

    def _onBtnTestClicked(self, evt):
        wx.MessageBox('Test function terminated!', 'Done', wx.ICON_INFORMATION|wx.OK|wx.CENTER);
