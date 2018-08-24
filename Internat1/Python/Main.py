import os
import wx

from MainFrame import MainFrame

_ = wx.GetTranslation

class MyApp(wx.App):
    locale = None

    def OnInit(self):
        print('Running wxPython ' + wx.version())
        # Set Current directory to the one containing this file
        os.chdir(os.path.dirname(os.path.abspath(__file__)))

        self.SetAppName('Internat')

        self.InitLanguage()

        # Create the main window
        frm = MainFrame()
        self.SetTopWindow(frm)

        frm.Show()
        return True

    def InitLanguage(self):
        langsAvail = {
            "System default" : wx.LANGUAGE_DEFAULT,
            "English"        : wx.LANGUAGE_ENGLISH,
            "French"         : wx.LANGUAGE_FRENCH,
            "German"         : wx.LANGUAGE_GERMAN,
            "Italian"        : wx.LANGUAGE_ITALIAN,
        }

        sel = wx.GetSingleChoice("Please choose language:", "Language", list(langsAvail.keys()))
        if sel == "":
            sel = "System default"

        lang = langsAvail[sel]
        # We don't have to do anything if the selected language is english
        # As the strings of this app have been written in this lang
        if lang == wx.LANGUAGE_ENGLISH:
            return

        wx.Locale.AddCatalogLookupPathPrefix("../langs")
        self.locale = wx.Locale()
        if not self.locale.Init(lang):
            wx.LogWarning("This language is not supported by the system.")
        if not self.locale.AddCatalog("internat"):
            wx.LogError("Couldn't find/load the 'internat' catalog for locale '" + self.locale.GetCanonicalName() + "'.")

if __name__ == '__main__':
    app = MyApp()
    app.MainLoop()
