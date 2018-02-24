import os
import wx

from MainFrame import MainFrame
from SettingsManager import SettingsManager

class MyApp(wx.App):
    _snglInstChecker = None

    def OnInit(self):
        print('Running wxPython ' + wx.version() + ' - ' + wx.GetLibraryVersionInfo().VersionString)
        # Set Current directory to the one containing this file
        sDir = os.path.dirname(__file__)
        if not sDir == '': # Perhaps we already are in the correct place
            os.chdir(sDir)

        self.SetAppName('SettingsManager')

        s = SettingsManager()
        s.ReadSettings()
        self._snglInstChecker = wx.SingleInstanceChecker()
        self._snglInstChecker.CreateDefault()
        if self._snglInstChecker.IsAnotherRunning() and not s.MultipleInstancesAllowed:
            wx.MessageBox('Another instance of this application is already running!', 'Multiple instances not allowed', wx.OK | wx.ICON_EXCLAMATION | wx.CENTER)
            return False

        # Create the main window
        frm = MainFrame()
        self.SetTopWindow(frm)

        frm.Show()
        return True

    def OnExit(self):
        s = SettingsManager()
        if s.Modified is True:
            s.SaveSettings()
        return wx.App.OnExit(self)

if __name__ == '__main__':
    app = MyApp()
    app.MainLoop()
