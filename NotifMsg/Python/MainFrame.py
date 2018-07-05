import wx
import wx.adv

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
        szrMain.AddStretchSpacer(1)
        self._btnShowMsg = wx.Button(pnl, wx.ID_ANY, 'Show a notification message')
        szrMain.Add(self._btnShowMsg, 0, wx.ALL|wx.ALIGN_CENTER, 5)
        szrMain.AddStretchSpacer(1)
        pnl.SetSizer(szrMain)

    def _connectControls(self):
        self._btnShowMsg.Bind(wx.EVT_BUTTON, self._onBtnShowMsgClicked)

    def _onBtnShowMsgClicked(self, evt):
        sTitle = 'wxWidgets notification'
        sMsg = 'This is a notification message.\n\nWelcome on wxWidgets ;-)'

        nmsg = wx.adv.NotificationMessage(title=sTitle, message=sMsg)
        nmsg.SetFlags(wx.ICON_INFORMATION)

        nmsg.Show(timeout=wx.adv.NotificationMessage.Timeout_Auto)
