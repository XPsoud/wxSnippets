import os
import wx

from DlgLogin import DlgLogin
from MainFrame import MainFrame

class MyApp(wx.App):
    def OnInit(self):
        print('Running wxPython ' + wx.version() + ' - ' + wx.GetLibraryVersionInfo().VersionString)
        # Set Current directory to the one containing this file
        sDir = os.path.dirname(__file__)
        if not sDir == '': # Perhaps we already are in the correct place
            os.chdir(sDir)

        self.SetAppName('PwdProtect')

        dlg = DlgLogin(None, 'wxWidgets', 3)
        if dlg.ShowModal() != wx.ID_OK:
            wx.MessageBox('You can not access to this application!', 'Password required', wx.ICON_EXCLAMATION|wx.OK|wx.CENTER)
            return False
        dlg.Destroy()

        # Create the main window
        frm = MainFrame()
        self.SetTopWindow(frm)

        frm.Show()
        return True

if __name__ == '__main__':
    app = MyApp()
    app.MainLoop()
