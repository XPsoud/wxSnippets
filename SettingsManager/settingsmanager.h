#ifndef __SETTINGSMANAGER_H_INCLUDED__
#define __SETTINGSMANAGER_H_INCLUDED__

#include <wx/wx.h>

#define MAINFRAME_MIN_SIZE wxSize(400, 300)
#define iStdXmlHeaderSize 38
extern const wxChar* g_szStdXmlFileHeader1;
extern const wxChar* g_szStdXmlFileHeader2;

class SettingsManager
{
	public:
		static SettingsManager& Get();
		bool ReadSettings();
		bool SaveSettings();
		// Accessors
		bool IsModified();
		wxString GetAppPath() { return m_sAppPath; }
		wxString GetSettingsPath() { return m_sSettingsPath; }
		// Settings file compression
		bool GetCompressSettings() { return m_bCompSettings; }
		void SetCompressSettings(bool value=true);
		// Position of the main window at application startup
		int GetMainWndStartupPos() { return m_iStartPos; }
		void SetMainWndStartupPos(int value);
		void GetMainWndStartupPos(wxPoint& pos) { pos=m_ptStartPos; }
		const wxSize& GetMainWndStartupSize() { return m_szStartSize; }
		void SetLastWindowRect(const wxPoint& pos, const wxSize& size);
		// Multiple instances
		bool GetMultipleInstancesAllowed() { return (m_bSingleInstance==false); }
		void SetMultipleInstancesAllowed(bool value);
	protected:
	private:
		SettingsManager();
		virtual ~SettingsManager();
		void Initialize();
		const wxString StartupPos2String(int iValue);
		int StartupString2Pos(const wxString& sValue);
		// Unique instance of the singleton
		static SettingsManager m_instance;
		// Misc vars
		bool m_bInitialized, m_bModified;
		wxString m_sAppPath, m_sSettingsPath;
		static const wxChar* m_szSettingsFName;
		// Settings vars
		bool m_bCompSettings;
		int m_iStartPos;
		wxPoint m_ptStartPos;
		wxSize m_szStartSize;
		bool m_bSingleInstance;
};

#endif // __SETTINGSMANAGER_H_INCLUDED__
