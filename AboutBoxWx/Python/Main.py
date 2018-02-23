import os
import wx

from MainFrame import MainFrame

class MyApp(wx.App):
    def OnInit(self):
        print('Running wxPython ' + wx.version() + ' - ' + wx.GetLibraryVersionInfo().VersionString)
        # Set Current directory to the one containing this file
        sDir = os.path.dirname(__file__)
        if not sDir == '': # Perhaps we already are in the correct place
            os.chdir(sDir)

        self.SetAppName('AboutBoxWx')

        # Create the main window
        frm = MainFrame()
        self.SetTopWindow(frm)

        frm.Show()
        return True

if __name__ == '__main__':
    app = MyApp()
    app.MainLoop()
