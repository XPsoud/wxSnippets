import wx
from SettingsManager import SettingsManager

class DlgSettings(wx.Dialog):
    def __init__(self, parent):
        wx.Dialog.__init__(self, parent, title='Settings')

        self._createInterface()
        self._fillControls()
        self._connectEvents()
        self.CenterOnParent()

    def _createInterface(self):
        szrMain = wx.BoxSizer(wx.VERTICAL)

        nBook = wx.Notebook(self, -1)

        # Tab "General"
        page = wx.Panel(nBook, wx.ID_STATIC)
        pageszr = wx.BoxSizer(wx.VERTICAL)

        box = wx.StaticBoxSizer(wx.VERTICAL, page, 'Position of the main window:')
        label = wx.StaticText(page, wx.ID_STATIC, 'Position of the main window at application startup')
        box.Add(label, 0, wx.ALL, 5)
        lnszr = wx.BoxSizer(wx.HORIZONTAL)
        self.optStartType = []
        self.optStartType.append(wx.RadioButton(page, -1, 'Predefined position', style=wx.RB_GROUP))
        lnszr.Add(self.optStartType[0], 0, wx.ALL, 5)
        self.optStartType.append(wx.RadioButton(page, -1, 'Last registered position'))
        lnszr.Add(self.optStartType[1], 0, wx.TOP|wx.BOTTOM|wx.RIGHT, 5)
        box.Add(lnszr, 0, wx.ALL, 0)

        box2 = wx.StaticBoxSizer(wx.VERTICAL, page, 'Predefined positions:')
        self.stbPos = box2.GetStaticBox()
        flxszr = wx.FlexGridSizer(3, 5, 5)
        self.optDefPos = []
        index = -1
        for item in ['Top-Left', 'Top-Center', 'Top-Right', 'Middle-Left', 'Center-Screen', 'Middle-Right', 'Bottom-Left', 'Bottom-Center', 'Bottom-Right']:
            index += 1
            if index == 0:
                self.optDefPos.append(wx.RadioButton(page, -1, item, style=wx.RB_GROUP))
            else:
                self.optDefPos.append(wx.RadioButton(page, -1, item))
            flxszr.Add(self.optDefPos[index])
        flxszr.AddGrowableCol(0, 1)
        flxszr.AddGrowableCol(1, 1)
        box2.Add(flxszr, 0, wx.ALL|wx.EXPAND, 5)
        box.Add(box2, 0, wx.ALL|wx.EXPAND, 5)

        pageszr.Add(box, 0, wx.LEFT|wx.RIGHT|wx.EXPAND, 5)

        box = wx.StaticBoxSizer(wx.VERTICAL, page, 'Misc:')
        self.chkSingleInstance = wx.CheckBox(page, -1, 'Allow only one instance of the application')
        box.Add(self.chkSingleInstance, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM, 5)
        self.chkCompFile = wx.CheckBox(page, -1, 'Compress settings file (for size and privacy)')
        box.Add(self.chkCompFile, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM, 5)
        pageszr.Add(box, 0, wx.ALL|wx.EXPAND, 5)

        page.SetSizer(pageszr)
        nBook.AddPage(page, 'General')

        szrMain.Add(nBook, 1, wx.ALL|wx.EXPAND, 0)

        btnSizer = self.CreateSeparatedButtonSizer(wx.OK|wx.CANCEL|wx.APPLY)

        szrMain.Add(btnSizer, 0, wx.ALL|wx.EXPAND, 5)

        self.btnApply = self.FindWindowById(wx.ID_APPLY)

        self.SetSizer(szrMain)
        szrMain.SetSizeHints(self)

    def _connectEvents(self):
        self.Bind(wx.EVT_BUTTON, self.OnBtnOkClicked, id=wx.ID_OK)
        self.Bind(wx.EVT_BUTTON, self.OnBtnApplyClicked, id=wx.ID_APPLY)
        for item in self.optStartType:
            item.Bind(wx.EVT_RADIOBUTTON, self.OnStartupPosTypeChanged)
        self.Bind(wx.EVT_CHECKBOX, self.OnSomethingHasChanged)
        self.Bind(wx.EVT_RADIOBUTTON, self.OnSomethingHasChanged)

    def _fillControls(self):
        s = SettingsManager()
        iStartPos, _ = s.MainWndStartupPos
        if iStartPos == wx.ALIGN_NOT:
            self.optStartType[1].SetValue(True)
            self.optDefPos[4].SetValue(True)
        else:
            self.optStartType[0].SetValue(True)
            if iStartPos == (wx.ALIGN_CENTER_HORIZONTAL|wx.ALIGN_CENTER_VERTICAL):
                self.optDefPos[4].SetValue(True)
            else:
                iX = 0
                if (iStartPos&wx.RIGHT) == wx.RIGHT:
                    iX = 2
                elif (iStartPos&wx.LEFT) == wx.LEFT:
                    iX = 0
                else:
                    iX = 1
                iY = 0
                if (iStartPos&wx.BOTTOM) == wx.BOTTOM:
                    iY = 6
                elif (iStartPos&wx.TOP) == wx.TOP:
                    iY = 0
                else:
                    iY = 3
                self.optDefPos[iX+iY].SetValue(True)
        self.OnStartupPosTypeChanged(None)

        self.chkSingleInstance.SetValue(s.MultipleInstancesAllowed is False)
        self.chkCompFile.SetValue(s.CompressSettingsFile)

        self.btnApply.Disable()

    def _applySettings(self):
        s = SettingsManager()
        iIndex = wx.NOT_FOUND
        if self.optStartType[0].GetValue() is True:
            for i, o in enumerate(self.optDefPos):
                if o.GetValue() is True:
                    iIndex = i
                    break
        iStartPos = wx.ALIGN_NOT
        if iIndex > wx.NOT_FOUND:
            iH = 0
            if iIndex in [0, 3, 6]:
                iH = wx.LEFT
            elif iIndex in [1, 4, 7]:
                iH = wx.CENTER
            else:
                iH = wx.RIGHT
            iV = 0
            if (iIndex > -1) and (iIndex < 3):
                iV = wx.TOP
            elif (iIndex > 2) and (iIndex < 6):
                iV = wx.CENTER
            else:
                iV = wx.BOTTOM
            if (iH == wx.CENTER) and (iV == wx.CENTER):
                iStartPos = (wx.ALIGN_CENTER_HORIZONTAL|wx.ALIGN_CENTER_VERTICAL)
            else:
                iStartPos = iH | iV
        s.MainWndStartupPos = iStartPos

        s.MultipleInstancesAllowed = self.chkSingleInstance.IsChecked() is False
        s.CompressSettingsFile = self.chkCompFile.IsChecked()
        self.btnApply.Disable()

    def OnBtnApplyClicked(self, evt):
        self._applySettings()

    def OnBtnOkClicked(self, evt):
        self._applySettings()
        self.EndModal(wx.ID_OK)

    def OnStartupPosTypeChanged(self, evt):
        bEnable = self.optStartType[0].GetValue()
        self.stbPos.Enable(bEnable)
        for item in self.optDefPos:
            item.Enable(bEnable)
        self.OnSomethingHasChanged(evt)

    def OnSomethingHasChanged(self, evt):
        self.btnApply.Enable()
