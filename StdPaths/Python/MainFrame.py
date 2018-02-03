import wx

class MainFrame(wx.Frame):

    def __init__(self):
        wx.Frame.__init__(self, None, title=wx.GetApp().GetAppName())
        self.SetIcon(wx.Icon('../../common/wxwin.ico'))

        self._createControls()

        self._updateValues()

    def _createControls(self):
        # A Statusbar in the bottom of the window
        self.CreateStatusBar(1)
        sMsg = 'wxPython ' + wx.version() + ' - ' + wx.GetLibraryVersionInfo().VersionString
        self.SetStatusText(sMsg)

        # Add a panel to the frame (needed under Windows to have a nice background)
        pnl = wx.Panel(self, wx.ID_ANY)

        szrMain = wx.BoxSizer(wx.VERTICAL)
        self._lstResults = wx.ListView(pnl, wx.ID_ANY)
        self._lstResults.AppendColumn('Name', wx.LIST_FORMAT_RIGHT)
        self._lstResults.AppendColumn('Value')
        szrMain.Add(self._lstResults, 1, wx.ALL|wx.EXPAND, 5)
        pnl.SetSizer(szrMain)

    def _updateValues(self):
        stdPth = wx.StandardPaths.Get()

        lIndex = self._lstResults.InsertItem(self._lstResults.GetItemCount(), 'AppDocumentsDir')
        self._lstResults.SetItem(lIndex, 1, stdPth.GetAppDocumentsDir())

        lIndex = self._lstResults.InsertItem(self._lstResults.GetItemCount(), 'ConfigDir')
        self._lstResults.SetItem(lIndex, 1, stdPth.GetConfigDir())

        lIndex = self._lstResults.InsertItem(self._lstResults.GetItemCount(), 'DataDir')
        self._lstResults.SetItem(lIndex, 1, stdPth.GetDataDir())

        lIndex = self._lstResults.InsertItem(self._lstResults.GetItemCount(), 'DocumentsDir')
        self._lstResults.SetItem(lIndex, 1, stdPth.GetDocumentsDir())

        lIndex = self._lstResults.InsertItem(self._lstResults.GetItemCount(), 'ExecutablePath')
        self._lstResults.SetItem(lIndex, 1, stdPth.GetExecutablePath())

        lIndex = self._lstResults.InsertItem(self._lstResults.GetItemCount(), 'InstallPrefix')
        sValue = stdPth.GetInstallPrefix()
        if sValue != '':
            self._lstResults.SetItem(lIndex, 1, sValue)
        else:
            self._lstResults.SetItem(lIndex, 1, 'Unavailable for this system')

        lIndex = self._lstResults.InsertItem(self._lstResults.GetItemCount(), 'LocalDataDir')
        self._lstResults.SetItem(lIndex, 1, stdPth.GetLocalDataDir())

        lIndex = self._lstResults.InsertItem(self._lstResults.GetItemCount(), 'LocalizedResourcesDir("lang")')
        self._lstResults.SetItem(lIndex, 1, stdPth.GetLocalizedResourcesDir('lang', wx.StandardPaths.ResourceCat_None))

        lIndex = self._lstResults.InsertItem(self._lstResults.GetItemCount(), 'PluginsDir')
        self._lstResults.SetItem(lIndex, 1, stdPth.GetPluginsDir())

        lIndex = self._lstResults.InsertItem(self._lstResults.GetItemCount(), 'ResourcesDir')
        self._lstResults.SetItem(lIndex, 1, stdPth.GetResourcesDir())

        lIndex = self._lstResults.InsertItem(self._lstResults.GetItemCount(), 'TempDir')
        self._lstResults.SetItem(lIndex, 1, stdPth.GetTempDir())

        lIndex = self._lstResults.InsertItem(self._lstResults.GetItemCount(), 'UserConfigDir')
        self._lstResults.SetItem(lIndex, 1, stdPth.GetUserConfigDir())

        lIndex = self._lstResults.InsertItem(self._lstResults.GetItemCount(), 'UserDataDir')
        self._lstResults.SetItem(lIndex, 1, stdPth.GetUserDataDir())

        for i in range(self._lstResults.ColumnCount):
            self._lstResults.SetColumnWidth(i, wx.LIST_AUTOSIZE)
