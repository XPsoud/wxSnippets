import os
import wx

from MainFrame import MainFrame

class MyApp(wx.App):
    def OnInit(self):
        print('Running wxPython ' + wx.version())
        # Set Current directory to the one containing this file
        os.chdir(os.path.dirname(os.path.abspath(__file__)))

        self.SetAppName('AboutBoxDlg')

        # Create the main window
        frm = MainFrame()
        self.SetTopWindow(frm)

        frm.Show()
        return True

if __name__ == '__main__':
    app = MyApp()
    app.MainLoop()
