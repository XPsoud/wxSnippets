import wx
from DlgAbout import DlgAbout

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
        wx.Panel(self, wx.ID_ANY)

        # Create the menu bar
        menuBar = wx.MenuBar()
        # File menu
        menuFile = wx.Menu()
        menuFile.Append(wx.ID_EXIT)
        menuBar.Append(menuFile, wx.GetStockLabel(wx.ID_FILE))
        # Help menu
        menuHelp = wx.Menu()
        menuHelp.Append(wx.ID_ABOUT)
        menuBar.Append(menuHelp, wx.GetStockLabel(wx.ID_HELP))
        # Assigne the menubar
        self.SetMenuBar(menuBar)

        # On OS X, delete the created menus
        # as the About and Exit items are handled by the OS specific menu
        if wx.GetOsDescription()[:8] == 'Mac OS X':
            menuBar.Remove(1)
            del menuHelp
            menuBar.Remove(0)
            del menuFile

    def _connectControls(self):
        self.Bind(wx.EVT_MENU, self._onMenuExitClicked, id=wx.ID_EXIT)
        self.Bind(wx.EVT_MENU, self._onMenuAboutClicked, id=wx.ID_ABOUT)

    def _onMenuExitClicked(self, evt):
        self.Close()

    def _onMenuAboutClicked(self, evt):
        dlg = DlgAbout(self)
        dlg.ShowModal()
