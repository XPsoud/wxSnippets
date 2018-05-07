import wx

from FilesDropTargets import *

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
        szrMain.AddSpacer(5)

        stbSzr = wx.StaticBoxSizer(wx.VERTICAL, pnl, 'Single file or directory:')
        stBox = stbSzr.GetStaticBox()
        label = wx.StaticText(stBox, wx.ID_STATIC, 'Drop any file/folder from the files manager to the wxTextCtrl below')
        stbSzr.Add(label, 0, wx.LEFT|wx.RIGHT|wx.TOP, 5)
        stbSzr.AddSpacer(2)
        label = wx.StaticText(stBox, wx.ID_STATIC, 'to see its full path. Even if you drop more than one item, only the')
        stbSzr.Add(label, 0, wx.LEFT|wx.RIGHT, 5)
        stbSzr.AddSpacer(2)
        label = wx.StaticText(stBox, wx.ID_STATIC, 'path of the first one will be shown.')
        stbSzr.Add(label, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM, 5)
        self._txtSingleFile = wx.TextCtrl(stBox, -1, wx.EmptyString)
        stbSzr.Add(self._txtSingleFile, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM|wx.EXPAND, 5)

        szrMain.Add(stbSzr, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM|wx.EXPAND, 5)

        stbSzr = wx.StaticBoxSizer(wx.VERTICAL, pnl, 'Multiple files or directories:')
        stBox = stbSzr.GetStaticBox()
        label = wx.StaticText(stBox, wx.ID_STATIC, 'Drop some files/folders from the files manager to the wxListBox below')
        stbSzr.Add(label, 0, wx.LEFT|wx.RIGHT|wx.TOP, 5)
        stbSzr.AddSpacer(2)
        label = wx.StaticText(stBox, wx.ID_STATIC, 'Their full paths will be added to the list.')
        stbSzr.Add(label, 0, wx.LEFT|wx.RIGHT|wx.BOTTOM, 5)
        self._lstMultiFiles = wx.ListBox(stBox, -1)
        stbSzr.Add(self._lstMultiFiles, 1, wx.LEFT|wx.RIGHT|wx.BOTTOM|wx.EXPAND, 5)

        szrMain.Add(stbSzr, 1, wx.LEFT|wx.RIGHT|wx.BOTTOM|wx.EXPAND, 5)

        pnl.SetSizer(szrMain)
        szrMain.SetSizeHints(self)

        dt = SingleFileDropTarget(self)
        self._txtSingleFile.SetDropTarget(dt)

        dt = MultiFilesDropTarget(self)
        self._lstMultiFiles.SetDropTarget(dt)

    def _connectControls(self):
        self.Bind(EVT_SINGLEFILE_DROPPED, self._onSingleFileDropped)
        self.Bind(EVT_MULTIFILES_DROPPED, self._onMultiFilesDropped)

    def _onSingleFileDropped(self, evt):
        self._txtSingleFile.ChangeValue(evt.GetSingleItem())

    def _onMultiFilesDropped(self, evt):
        self._lstMultiFiles.Append(evt.GetItems())
        self._lstMultiFiles.EnsureVisible(self._lstMultiFiles.GetCount()-1)
