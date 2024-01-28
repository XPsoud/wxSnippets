import wx

class MainFrame(wx.Frame):

    def __init__(self):
        wx.Frame.__init__(self, None, title=wx.GetApp().GetAppName())
        self.SetIcon(wx.Icon('../../common/wxwin.ico'))

        self._createControls()

        self._connectControls()

        self._onOptGetFromClicked(None)

    def _createControls(self):
        # A Statusbar in the bottom of the window
        self.CreateStatusBar(1)
        sMsg = 'wxPython ' + wx.version()
        self.SetStatusText(sMsg)

        # Add a panel to the frame (needed under Windows to have a nice background)
        pnl = wx.Panel(self, wx.ID_ANY)

        self._szrMain = wx.BoxSizer(wx.VERTICAL)

        lnszr = wx.BoxSizer(wx.HORIZONTAL)
        label = wx.StaticText(pnl, wx.ID_STATIC, 'Get file type from:')
        lnszr.Add(label, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL, 0)
        self._optGetFTFrom = []
        self._optGetFTFrom.append(wx.RadioButton(pnl, wx.ID_ANY, 'MIME type', style=wx.RB_GROUP))
        lnszr.Add(self._optGetFTFrom[0], 0, wx.LEFT|wx.ALIGN_CENTER_VERTICAL, 5)
        self._optGetFTFrom.append(wx.RadioButton(pnl, wx.ID_ANY, 'File extension'))
        lnszr.Add(self._optGetFTFrom[1], 0, wx.LEFT|wx.ALIGN_CENTER_VERTICAL, 5)
        self._szrMain.Add(lnszr, 0, wx.ALL|wx.EXPAND, 10);

        lnszr = wx.BoxSizer(wx.HORIZONTAL)
        self._lblSource = wx.StaticText(pnl, wx.ID_STATIC, '')
        lnszr.Add(self._lblSource, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL, 0)
        self._cmbSource = wx.ComboBox(pnl, wx.ID_ANY)
        lnszr.Add(self._cmbSource, 1, wx.LEFT|wx.ALIGN_CENTER_VERTICAL, 5)
        self._szrMain.Add(lnszr, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM|wx.EXPAND, 10)

        self._txtInfos = wx.TextCtrl(pnl, wx.ID_ANY, style=wx.TE_MULTILINE|wx.TE_READONLY)
        self._szrMain.Add(self._txtInfos, 1, wx.LEFT|wx.RIGHT|wx.BOTTOM|wx.EXPAND, 10)

        pnl.SetSizer(self._szrMain)

    def _connectControls(self):
        self._optGetFTFrom[0].Bind(wx.EVT_RADIOBUTTON,self._onOptGetFromClicked)
        self._optGetFTFrom[1].Bind(wx.EVT_RADIOBUTTON,self._onOptGetFromClicked)
        self._cmbSource.Bind(wx.EVT_COMBOBOX, self._onCmbItemSelected)
        self._cmbSource.Bind(wx.EVT_TEXT, self._onCmbTextChanged)
        pass

    def _onOptGetFromClicked(self, evt):
        if self._optGetFTFrom[0].GetValue():
            self._lblSource.SetLabel('Enter a MIME type or select one in the list:')
            self._cmbSource.Clear()
            self._cmbSource.Append('text/plain')
            self._cmbSource.Append('application/zip')
            self._cmbSource.Append('image/png')
            self._cmbSource.Append('image/jpeg')
            self._cmbSource.Append('audio/mpeg')
            self._cmbSource.Append('video/mp4')
            self._cmbSource.Append('text/html')
        else:
            self._lblSource.SetLabel('Enter a file extension select one in the list:')
            self._cmbSource.Clear()
            self._cmbSource.Append('txt')
            self._cmbSource.Append('zip')
            self._cmbSource.Append('png')
            self._cmbSource.Append('jpg')
            self._cmbSource.Append('mp3')
            self._cmbSource.Append('mp4')
            self._cmbSource.Append('html')
        self._szrMain.Layout()
        self._doGetInfos()
    
    def _onCmbTextChanged(self, evt):
        if self._cmbSource.IsTextEmpty():
            self._doGetInfos()
        else:
            self._onCmbItemSelected(evt)
    
    def _onCmbItemSelected(self, evt):
        sTxt = "File type informations for "
        if self._optGetFTFrom[0].GetValue():
            sTxt = sTxt + 'MIME type'
        else:
            sTxt = sTxt + 'extension'
        sTxt = sTxt + '"' + self._cmbSource.GetValue() + '":'
        self._txtInfos.ChangeValue(sTxt)

        self._doGetInfos()
    
    def _doGetInfos(self):
        sValue = self._cmbSource.GetValue()
        if sValue.strip(' .') == '':
            if self._optGetFTFrom[0].GetValue():
                self._txtInfos.ChangeValue('No valid MIME type entered or selected.')
            else:
                self._txtInfos.ChangeValue('No valid extension entered or selected.')
            return
        fType = None
        if self._optGetFTFrom[0].GetValue():
            fType = wx.TheMimeTypesManager.GetFileTypeFromMimeType(sValue)
        else:
            fType = wx.TheMimeTypesManager.GetFileTypeFromExtension(sValue)
        
        if not fType:
            self._txtInfos.AppendText('\n\tError: No file type found!')
            return
        self._txtInfos.AppendText('\nDescription: ')
        self._txtInfos.AppendText(fType.GetDescription())

        if self._optGetFTFrom[0].GetValue():
            exts = fType.GetExtensions()
            self._txtInfos.AppendText('\nExtensions:')
            for e in exts:
                self._txtInfos.AppendText(f' {e}')
        else:
            sType = fType.GetMimeType()
            self._txtInfos.AppendText(f'\nMIME type: {sType}')

        icon, location, index = fType.GetIconInfo()
        self._txtInfos.AppendText(f'\nAssociated icon:\n - Index={index}\n - Location={location}')

        prms = wx.FileType.MessageParameters()
        verbs, commands = fType.GetAllCommands(prms)
        self._txtInfos.AppendText(f'\nFound {len(verbs)} command(s) for this file type.')
        for v, c in zip(verbs, commands):
            self._txtInfos.AppendText(f'\n - {v} => {c}')
