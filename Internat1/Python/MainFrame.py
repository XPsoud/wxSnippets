import wx
import wx.adv

_ = wx.GetTranslation

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

        # Menu bar
        menubar = wx.MenuBar()
        # File menu
        filemenu = wx.Menu()
        filemenu.Append(wx.ID_EXIT)
        menubar.Append(filemenu, wx.GetStockLabel(wx.ID_FILE))
        # Help menu
        helpmenu = wx.Menu()
        helpmenu.Append(wx.ID_ABOUT)
        menubar.Append(helpmenu, wx.GetStockLabel(wx.ID_HELP))

        self.SetMenuBar(menubar)

        # Add a panel to the frame (needed under Windows to have a nice background)
        pnl = wx.Panel(self, wx.ID_ANY)

        szrMain = wx.BoxSizer(wx.VERTICAL)
        szrMain.AddStretchSpacer(1)
        label = wx.StaticText(pnl, wx.ID_STATIC, _("Welcome from wxWidgets"))
        fnt = label.GetFont().MakeLarger().MakeLarger()
        label.SetFont(fnt)
        szrMain.Add(label, 0, wx.ALL|wx.ALIGN_CENTER, 10)
        szrMain.AddStretchSpacer(1)
        pnl.SetSizer(szrMain)

    def _connectControls(self):
        self.Bind(wx.EVT_MENU, self.onMenuExitClicked, id=wx.ID_EXIT)
        self.Bind(wx.EVT_MENU, self.onMenuAboutClicked, id=wx.ID_ABOUT)

    def onMenuExitClicked(self, evt):
        self.Close()

    def onMenuAboutClicked(self, evt):
        info = wx.adv.AboutDialogInfo()
        info.SetName('Internat')
        info.SetVersion('(v1.0.0)')
        info.SetDescription(_('wxWidgets I18N sample'))
        info.SetCopyright(_('Copyright (c) X.P. 2018'))
        info.SetIcon(wx.Icon('../../common/wxWidgets.png', wx.BITMAP_TYPE_PNG))

        wx.adv.AboutBox(info)
