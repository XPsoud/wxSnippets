import os
import sys
import wx

from MainFrame import MainFrame

_ = wx.GetTranslation

if sys.platform == 'darwin':
    def MyGetSystemLanguage():
        import locale
        loc, enc = locale.getlocale()
        return loc

class MyApp(wx.App):
    locale = None
    sysLng = None

    def __init__(self, lng=wx.LANGUAGE_DEFAULT):
        self.sysLng = lng
        wx.App.__init__(self)

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
            "System default" : self.sysLng,
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
    iLng = wx.LANGUAGE_DEFAULT
    if sys.platform == 'darwin':
        sLng = MyGetSystemLanguage()
        if not sLng is None:
            lInfo = wx.Locale.FindLanguageInfo(sLng)
            iLng = lInfo.Language

    app = MyApp(iLng)
    app.MainLoop()
