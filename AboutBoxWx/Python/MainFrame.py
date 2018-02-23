import wx
import wx.adv

class Options:
    MINIMAL = 0
    MAXIMAL = 1
    CUSTOM = 2

    COUNT = 3

class Details:
    APP_NAME = 0
    APP_VERSION = 1
    APP_DESCRIPTION = 2
    COPYRIGHT = 3
    ICON = 4
    LICENCE = 5
    DEVELOPPER = 6
    DEVELOPPERS = 7
    WEBSITE = 8
    TRANSLATORS = 9

    COUNT = 10

iCheckedBoxes = [
    Details.APP_NAME,
    Details.APP_VERSION,
    Details.APP_DESCRIPTION,
    Details.COPYRIGHT,
    Details.ICON
]

sLicence = '''This application is provided "as is" without any licence

Everyone is free to copy, modify, sell, and do anything with it.

This application and its source code is provided as a small
sample to show the use of wxWidgets standard about box.'''

aTranslators = ['Xaviou (en = app default)', 'Nobody Else (no translations support)']

class MainFrame(wx.Frame):

    def __init__(self):
        wx.Frame.__init__(self, None, title=wx.GetApp().GetAppName())
        self.SetIcon(wx.Icon('../../common/wxwin.ico'))

        self._optInfos = [0] * Options.COUNT
        self._chkInfos = [0] * Details.COUNT

        self._createControls()

        self._connectControls()

        self._updateInterface()

    def _createControls(self):
        # A Statusbar in the bottom of the window
        self.CreateStatusBar(1)
        sMsg = 'wxPython ' + wx.version() + ' - ' + wx.GetLibraryVersionInfo().VersionString
        self.SetStatusText(sMsg)

        # Add a panel to the frame (needed under Windows to have a nice background)
        pnl = wx.Panel(self, wx.ID_ANY)

        szrMain = wx.BoxSizer(wx.VERTICAL)
        stbSzr = wx.StaticBoxSizer(wx.VERTICAL, pnl, 'Informations to show in the "About" box:')

        self._optInfos[Options.MINIMAL] = wx.RadioButton(pnl, wx.ID_ANY, 'Application\'s name only (minimal "About" box)', style=wx.RB_GROUP)
        stbSzr.Add(self._optInfos[Options.MINIMAL], 0, wx.ALL, 5)

        self._optInfos[Options.MAXIMAL] = wx.RadioButton(pnl, wx.ID_ANY, 'All available informations')
        stbSzr.Add(self._optInfos[Options.MAXIMAL], 0, wx.LEFT|wx.RIGHT|wx.BOTTOM, 5)

        self._optInfos[Options.CUSTOM] = wx.RadioButton(pnl, wx.ID_ANY, 'Let me select the informations I want to see')
        stbSzr.Add(self._optInfos[Options.CUSTOM], 0, wx.LEFT|wx.RIGHT, 5)

        lnSzr = wx.BoxSizer(wx.HORIZONTAL)
        lnSzr.AddSpacer(10)

        flxSzr = wx.FlexGridSizer(2, 5, 5)

        self._chkInfos[Details.APP_NAME] = wx.CheckBox(pnl, wx.ID_ANY, 'Application\'s name')
        self._chkInfos[Details.APP_NAME].Disable()
        flxSzr.Add(self._chkInfos[Details.APP_NAME])

        self._chkInfos[Details.APP_VERSION] = wx.CheckBox(pnl, wx.ID_ANY, 'Application\'s version')
        flxSzr.Add(self._chkInfos[Details.APP_VERSION])

        self._chkInfos[Details.APP_DESCRIPTION] = wx.CheckBox(pnl, wx.ID_ANY, 'Description')
        flxSzr.Add(self._chkInfos[Details.APP_DESCRIPTION])

        self._chkInfos[Details.COPYRIGHT] = wx.CheckBox(pnl, wx.ID_ANY, 'Copyright')
        flxSzr.Add(self._chkInfos[Details.COPYRIGHT])

        self._chkInfos[Details.ICON] = wx.CheckBox(pnl, wx.ID_ANY, 'Icon')
        flxSzr.Add(self._chkInfos[Details.ICON])

        self._chkInfos[Details.LICENCE] = wx.CheckBox(pnl, wx.ID_ANY, 'Licence text')
        flxSzr.Add(self._chkInfos[Details.LICENCE])

        self._chkInfos[Details.DEVELOPPER] = wx.CheckBox(pnl, wx.ID_ANY, 'Main developper')
        flxSzr.Add(self._chkInfos[Details.DEVELOPPER])

        self._chkInfos[Details.DEVELOPPERS] = wx.CheckBox(pnl, wx.ID_ANY, 'Multiple developpers')
        flxSzr.Add(self._chkInfos[Details.DEVELOPPERS])

        self._chkInfos[Details.WEBSITE] = wx.CheckBox(pnl, wx.ID_ANY, 'Website url')
        flxSzr.Add(self._chkInfos[Details.WEBSITE])

        self._chkInfos[Details.TRANSLATORS] = wx.CheckBox(pnl, wx.ID_ANY, 'Translators')
        flxSzr.Add(self._chkInfos[Details.TRANSLATORS])

        lnSzr.Add(flxSzr, 0, wx.ALL, 0)

        stbSzr.Add(lnSzr, 0, wx.ALL, 5)

        szrMain.Add(stbSzr, 1, wx.ALL|wx.EXPAND, 5)

        pnl.SetSizer(szrMain)

        # At startup, select the "All available infos" option
        self._optInfos[Options.MAXIMAL].SetValue(True)
        # Check the wxCheckBoxes depending on the defined array (see on top of this file)
        for i in iCheckedBoxes:
            self._chkInfos[i].SetValue(True)

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

        # Adjust window size
        szrMain.SetSizeHints(self)

    def _connectControls(self):
        self.Bind(wx.EVT_MENU, self._onMenuExitClicked, id=wx.ID_EXIT)
        self.Bind(wx.EVT_MENU, self._onMenuAboutClicked, id=wx.ID_ABOUT)
        self.Bind(wx.EVT_RADIOBUTTON, self._onOptInfosClicked)

    def _updateInterface(self):
        # Checkboxes are only shown if the "custom" option is selected
        bShow = self._optInfos[Options.CUSTOM].GetValue()
        for chk in self._chkInfos:
            chk.Show(bShow)

    def _onMenuExitClicked(self, evt):
        self.Close()

    def _onMenuAboutClicked(self, evt):
        # Get the index of the selected option
        iOpt = Options.MAXIMAL
        for i in range(Options.COUNT):
            if self._optInfos[i].GetValue():
                iOpt = i
                break
        info = wx.adv.AboutDialogInfo()

        for i in range(Details.COUNT):
            if (i == Details.APP_NAME or iOpt == Options.MAXIMAL or
                (iOpt == Options.CUSTOM and self._chkInfos[i].GetValue())):

                if i == Details.APP_NAME:
                    info.SetName('AboutBoxWx')
                elif i == Details.APP_VERSION:
                    info.SetVersion('1.0.0')
                elif i == Details.APP_DESCRIPTION:
                    info.SetDescription('wxWidgets provided AboutBox')
                elif i == Details.COPYRIGHT:
                    info.SetCopyright('Copyright (c) X.P. 2018')
                elif i == Details.ICON:
                    info.SetIcon(wx.Icon('../../common/wxWidgets.png', wx.BITMAP_TYPE_PNG))
                elif i == Details.LICENCE:
                    info.SetLicence(sLicence)
                elif i == Details.DEVELOPPER:
                    info.AddDeveloper('X. Perrissoud AKA Xaviou')
                elif i == Details.DEVELOPPERS:
                    info.AddDeveloper('An unknown developper')
                    info.AddDeveloper('Another unknown developper')
                elif i == Details.WEBSITE:
                    info.SetWebSite('https://wxstuff.xaviou.fr', 'X@v\'s wxStuff website')
                elif i == Details.TRANSLATORS:
                    info.SetTranslators(aTranslators)

        wx.adv.AboutBox(info)

    def _onOptInfosClicked(self, evt):
        self._updateInterface()
