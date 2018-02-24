import wx
from SettingsManager import SettingsManager
from DlgSettings import DlgSettings

class MainFrame(wx.Frame):

    def __init__(self):
        wx.Frame.__init__(self, None, title=wx.GetApp().GetAppName())
        self.SetIcon(wx.Icon('../../common/wxwin.ico'))

        self._createControls()

        # Minimum client size of the main window
        self.SetMinClientSize(wx.Size(400, 300))

        s = SettingsManager()
        mode, pos = s.MainWndStartupPos
        sz = s.MainWndStartupSize
        if mode == wx.ALIGN_NOT:
            if sz == wx.DefaultSize:
                if pos == wx.DefaultPosition:
                    self.Maximize()
                else:
                    self.CenterOnScreen()
            else:
                self.Move(pos)
                self.SetSize(sz)
        else:
            iWScr, iHScr = wx.GetDisplaySize()
            if sz == wx.DefaultSize:
                sz = self.GetSize()
            pt = wx.DefaultPosition
            if (mode & wx.LEFT) == wx.LEFT:
                pt.x = 0
            elif (mode & wx.RIGHT) == wx.RIGHT:
                pt.x = iWScr - sz.GetWidth()
            else:
                pt.x = (iWScr - sz.GetWidth()) / 2
            if (mode & wx.TOP) == wx.TOP:
                pt.y = 0
            elif (mode & wx.BOTTOM) == wx.BOTTOM:
                pt.y = iHScr - sz.GetHeight()
            else:
                pt.y = (iHScr - sz.GetHeight()) / 2
            self.Move(pt)
            self.SetSize(sz)

        self._connectControls()

    def _createControls(self):
        # A Statusbar in the bottom of the window
        self.CreateStatusBar(1)
        sMsg = 'wxPython ' + wx.version() + ' - ' + wx.GetLibraryVersionInfo().VersionString
        self.SetStatusText(sMsg)

        # Add a panel to the frame (needed under Windows to have a nice background)
        pnl = wx.Panel(self, wx.ID_ANY)

        szrMain = wx.BoxSizer(wx.VERTICAL)
        self._btnPrefs = wx.Button(pnl, wx.ID_ANY, 'Edit Settings')
        szrMain.Add(self._btnPrefs, 0, wx.ALL, 5)
        pnl.SetSizer(szrMain)

    def _connectControls(self):
        self.Bind(wx.EVT_SIZE, self._onWindowResized)
        self.Bind(wx.EVT_MOVE, self._onWindowMoved)
        self._btnPrefs.Bind(wx.EVT_BUTTON, self._onBtnEditPrefstClicked)

    def _onWindowResized(self, evt):
        if not self.IsShown():
            return
        s = SettingsManager()
        if self.IsMaximized():
            s.MainWndStartupPos = wx.DefaultPosition
            s.MainWndStartupSize = wx.DefaultSize
        else:
            s.MainWndStartupRect = self.GetRect()

        evt.Skip()

    def _onWindowMoved(self, evt):
        if not self.IsShown():
            return
        SettingsManager().MainWndStartupRect = self.GetRect()

        evt.Skip()

    def _onBtnEditPrefstClicked(self, evt):
        dlg = DlgSettings(self)
        dlg.ShowModal()
        dlg.Destroy()
