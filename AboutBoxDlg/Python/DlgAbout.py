import wx

class DlgAbout(wx.Dialog):
    def __init__(self, parent):
        wx.Dialog.__init__(self, parent, title=wx.GetStockLabel(wx.ID_ABOUT, wx.STOCK_NOFLAGS))

        self._createInterface()

        self.CenterOnParent()

    def _createInterface(self):

        sTitle = 'AboutBoxDlg (v1.0.0)'
        sVersion = wx.version()
        pos = sVersion.find(' wxWidgets')
        if pos != -1:
            sVersion = sVersion[:pos]
        sMsg = 'Made with wxPython ' + sVersion + '\nBased on ' + wx.GetLibraryVersionInfo().VersionString
        szrMain = wx.BoxSizer(wx.VERTICAL)

        szrTop = wx.BoxSizer(wx.HORIZONTAL)

        bmpCtrl = wx.StaticBitmap(self, wx.ID_ANY, wx.Bitmap('../../common/wxWidgets.png', wx.BITMAP_TYPE_PNG))
        szrTop.Add(bmpCtrl, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL, 5)

        szrRight = wx.BoxSizer(wx.VERTICAL)

        label = wx.StaticText(self, wx.ID_STATIC, sTitle)
        fntTitle = label.GetFont()
        fntTitle.MakeLarger()
        fntTitle.MakeBold()
        label.SetFont(fntTitle)
        szrRight.Add(label, 0, wx.ALL|wx.ALIGN_CENTER, 5)

        label = wx.StaticText(self, wx.ID_STATIC, 'Copyright (c) X.P. 2018')
        szrRight.Add(label, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM|wx.ALIGN_CENTER, 5)

        label = wx.StaticText(self, wx.ID_STATIC, 'wxWidgets Application')
        szrRight.Add(label, 0, wx.LEFT|wx.RIGHT|wx.TOP|wx.ALIGN_CENTER, 5)

        label = wx.StaticText(self, wx.ID_STATIC, sMsg, style=wx.ST_NO_AUTORESIZE|wx.ALIGN_CENTER)
        szrRight.Add(label, 0, wx.ALL|wx.EXPAND, 5)

        szrTop.Add(szrRight, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL, 5)

        szrMain.Add(szrTop, 0, wx.ALL, 5)

        btnSzr = self.CreateSeparatedButtonSizer(wx.CLOSE)
        szrMain.Add(btnSzr, 0, wx.ALL|wx.EXPAND, 5)

        self.SetSizer(szrMain)

        szrMain.SetSizeHints(self)
