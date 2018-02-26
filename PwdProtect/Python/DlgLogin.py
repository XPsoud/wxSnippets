import wx
from Key_png import Key_Png

class DlgLogin(wx.Dialog):
    def __init__(self, parent, password, maxAttemps):
        wx.Dialog.__init__(self, parent, title='Restricted access')

        self._iMaxAttemps = maxAttemps
        self._iAttemps = 0
        self._sPassword = password

        self._createInterface()
        self._txtPwd.SetFocus()

        self._connectControls()

        self.CenterOnParent()

    def _createInterface(self):
        szrMain = wx.BoxSizer(wx.VERTICAL)

        lnszr = wx.BoxSizer(wx.HORIZONTAL)
        bmpCtrl = wx.StaticBitmap(self, wx.ID_STATIC, Key_Png.GetBitmap())
        lnszr.Add(bmpCtrl, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL, 10)
        label = wx.StaticText(self, wx.ID_STATIC, 'Access to this application has been\nprotected with a password.')
        lnszr.Add(label, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL, 10)
        szrMain.Add(lnszr, 0, wx.ALL, 0)

        label = wx.StaticText(self, wx.ID_STATIC, 'For this test application, the password is "' + self._sPassword + '"')
        szrMain.Add(label, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM, 10)

        self._lblWrongPwd = wx.StaticText(self, wx.ID_STATIC, 'Incorrect password!')
        self._lblWrongPwd.SetFont(label.GetFont().MakeBold())
        self._lblWrongPwd.SetForegroundColour(wx.RED)
        szrMain.Add(self._lblWrongPwd, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM|wx.ALIGN_CENTER_HORIZONTAL, 10)

        lnszr = wx.BoxSizer(wx.HORIZONTAL)
        label = wx.StaticText(self, wx.ID_STATIC, 'Enter the access password:')
        lnszr.Add(label, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL, 0)
        self._txtPwd = wx.TextCtrl(self, wx.ID_ANY, '', style=wx.TE_PASSWORD)
        lnszr.Add(self._txtPwd, 1, wx.LEFT|wx.ALIGN_CENTER_VERTICAL, 5)
        szrMain.Add(lnszr, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM|wx.EXPAND, 10)

        self._chkShowPwd = wx.CheckBox(self, wx.ID_ANY, 'Display password in plain text')
        szrMain.Add(self._chkShowPwd, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM, 10)

        btnSzr = self.CreateSeparatedButtonSizer(wx.OK|wx.CANCEL)
        btnOk = self.FindWindowById(wx.ID_OK)
        if not btnOk is None:
            btnOk.SetLabel('Access')
            btnOk.SetDefault()
        szrMain.Add(btnSzr, 0, wx.ALL|wx.EXPAND, 10)

        self.SetSizer(szrMain)

        self._lblWrongPwd.Hide()

        szrMain.SetSizeHints(self)

    def _connectControls(self):
        self._chkShowPwd.Bind(wx.EVT_CHECKBOX, self._onChkShowPasswordClicked)
        self.Bind(wx.EVT_BUTTON, self._onBtnOkClicked, id=wx.ID_OK)

    def _onChkShowPasswordClicked(self, evt):
        self.Freeze()

        sPass = self._txtPwd.GetValue()
        lnszr = self._txtPwd.GetContainingSizer()
        iStyle = 0
        if not self._chkShowPwd.IsChecked():
            iStyle = wx.TE_PASSWORD

        lnszr.Detach(self._txtPwd)
        self._txtPwd.Destroy()
        self._txtPwd = wx.TextCtrl(self, wx.ID_ANY, sPass, style=iStyle)
        lnszr.Add(self._txtPwd, 1, wx.LEFT|wx.ALIGN_CENTER_VERTICAL, 5)

        lnszr.Layout()

        self.Thaw()

    def _onBtnOkClicked(self, evt):
        iRes = wx.ID_OK
        if self._txtPwd.GetValue() != self._sPassword:
            iRes = wx.ID_CANCEL

        if (iRes == wx.ID_OK) or (self._iAttemps == (self._iMaxAttemps - 1)):
            self.EndModal(iRes)

        if self._iAttemps == 0:
            self._lblWrongPwd.Show()
            self.GetSizer().SetSizeHints(self)
            self.CenterOnParent()

        self._txtPwd.SetFocus()
        self._txtPwd.SetSelection(-1, -1)

        self._iAttemps += 1
        self._lblWrongPwd.SetLabel('Incorrect password: trial {:0d}/{:0d}'.format(self._iAttemps+1, self._iMaxAttemps))
        self.GetSizer().Layout()
