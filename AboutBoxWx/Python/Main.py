import os, wx

from MainFrame import MainFrame

class MyApp(wx.App):
    def OnInit(self):
        print('Running wxPython ' + wx.version() + ' - ' + wx.GetLibraryVersionInfo().VersionString)
        # Set Current directory to the one containing this file
        os.chdir(os.path.dirname(__file__))

        self.SetAppName('AboutBoxWx')

        # Create the main window
        frm = MainFrame()
        self.SetTopWindow(frm)

        frm.Show()
        return True

if __name__ == '__main__':
    app = MyApp()
    app.MainLoop()
