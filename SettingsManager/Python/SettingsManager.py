import os
import zlib
from xml.etree.ElementTree import ElementTree, Element, SubElement
import xml.etree.ElementTree as ETree
import wx

def startupStringToPos(value):
    if value == 'CenterScreen':
        return wx.ALIGN_CENTER_VERTICAL|wx.ALIGN_CENTER_HORIZONTAL
    if value == 'LastKnownPos':
        return wx.ALIGN_NOT
    iHPos, iVPos = 0, 0
    if 'Left' in value:
        iHPos = wx.LEFT
    elif 'Right' in value:
        iHPos = wx.RIGHT
    else:
        iHPos = wx.ALIGN_CENTER_HORIZONTAL
    if 'Top' in value:
        iVPos = wx.TOP
    elif 'Bottom' in value:
        iVPos = wx.BOTTOM
    else:
        iVPos = wx.ALIGN_CENTER_VERTICAL

    return iHPos|iVPos

def startupPosToString(value):
    if value == (wx.ALIGN_CENTER_HORIZONTAL|wx.ALIGN_CENTER_VERTICAL):
        return 'CenterScreen'
    if value == wx.ALIGN_NOT:
        return 'LastKnownPos'
    sHPos, sVPos = '', ''
    if (value&wx.LEFT) == wx.LEFT:
        sHPos = 'Left'
    elif (value&wx.RIGHT) == wx.RIGHT:
        sHPos = 'Right'
    else:
        sHPos = 'Center'
    if (value&wx.TOP) == wx.TOP:
        sVPos = 'Top'
    elif (value&wx.BOTTOM) == wx.BOTTOM:
        sVPos = 'Bottom'
    else:
        sVPos = 'Center'
    return sVPos + sHPos

class SettingsManager(object):
    _instance = None
    # Default settings
    _iStartPos = wx.ALIGN_CENTER_VERTICAL|wx.ALIGN_CENTER_HORIZONTAL
    _ptStartPos = wx.DefaultPosition
    _szStartSize = wx.Size(600, 400)
    _bSingleInstanceOnly = False
    _bCompSettings = False
    # Other default values
    _bModified = False
    _sSettingsFName = 'settings'

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super(SettingsManager, cls).__new__(cls)
            cls._instance.Initialize()
        return cls._instance

    def Initialize(self):
        self._bModified = False
        sScriptDir = os.path.dirname(os.path.abspath(__file__))
        if os.path.isfile(os.path.join(sScriptDir, self._sSettingsFName)):
            self._sSettingsPath = sScriptDir
        else:
            self._sSettingsPath = wx.StandardPaths.Get().GetUserDataDir()

    def _getDatasPath(self):
        return self._sSettingsPath

    def _isModified(self):
        return self._bModified

    def SetModified(self):
        self._bModified = True

    def _getMainWndStartupPos(self):
        if self._iStartPos == wx.ALIGN_NOT:
            return self._iStartPos, self._ptStartPos

        return self._iStartPos, None

    def _setMainWndStartupPos(self, mode, pos=None):
        if mode != self._iStartPos:
            self._iStartPos = mode
            self._bModified = True
        if not pos is None:
            if pos != self._ptStartPos:
                self._ptStartPos = pos
                self._bModified = True

    def _getMainWndStartupSize(self):
        return self._szStartSize

    def _setMainWndStartupSize(self, size):
        if size != self._szStartSize:
            self._szStartSize = size
            self._bModified = True

    def _getMainWndStartupRect(self):
        return wx.Rect(self._ptStartPos, self._szStartSize)

    def _setMainWndStartupRect(self, rect):
        if not rect == wx.Rect(self._ptStartPos, self._szStartSize):
            self._ptStartPos = rect.GetPosition()
            self._szStartSize = rect.GetSize()
            self._bModified = True

    def _getMultipleInstancesAllowed(self):
        return self._bSingleInstanceOnly is False

    def _setMultipleInstancesAllowed(self, value):
        if self._bSingleInstanceOnly == value:
            self._bSingleInstanceOnly = not value
            self._bModified = True

    def _getCompressSettings(self):
        return self._bCompSettings

    def _setCompressSettings(self, value):
        if not self._bCompSettings == value:
            self._bCompSettings = value
            self._bModified = True

    def ReadSettings(self):
        # Check whether the settings folder exists
        if not os.path.isdir(self._sSettingsPath):
            return
        # Construct the settings file name and check if it exists
        sFName = os.path.join(self._sSettingsPath, self._sSettingsFName)
        if not os.path.isfile(sFName):
            return
        # Try to load the xml settings file
        f = open(sFName, 'rb')
        datas = f.read()
        f.close()
        if datas[0:5] != b'<?xml':
            # Compressed file
            datas = zlib.decompress(datas)

        tree = ElementTree(ETree.fromstring(datas.decode()))
        #tree.parse(sFName)
        rootNode = tree.getroot()
        #Read each xml entry
        for childNode in rootNode:
            nodeName = childNode.tag
            if nodeName == 'StartupPos':
                self._iStartPos = startupStringToPos(childNode.get('Value', 'CenterScreen'))
                iX = int(childNode.get('X', '-1'))
                iY = int(childNode.get('Y', '-1'))
                self._ptStartPos = wx.Point(iX, iY)
                iW = int(childNode.get('W', '-1'))
                iH = int(childNode.get('H', '-1'))
                self._szStartSize = wx.Size(iW, iH)
            elif nodeName == 'MultiInstances':
                self._bSingleInstanceOnly = (childNode.text != 'Allowed')
            elif nodeName == 'CompressSettingsFile':
                self._bCompSettings = (childNode.text == 'Yes')

    def SaveSettings(self):
        # Create the root node of the xml tree
        rootNode = Element('Settings-file')
        rootNode.set('Version', '1.0')

        # Position of the main window at application startup
        node = SubElement(rootNode, 'StartupPos')
        node.set('Value', startupPosToString(self._iStartPos))
        iX, iY = self._ptStartPos.Get()
        iW, iH = self._szStartSize.Get()
        node.set('X', str(iX))
        node.set('Y', str(iY))
        node.set('W', str(iW))
        node.set('H', str(iH))

        # Allowing or not multiple instances of the application
        node = SubElement(rootNode, 'MultiInstances')
        if self._bSingleInstanceOnly:
            node.text = 'Not-Allowed'
        else:
            node.text = 'Allowed'

        # Settings file compression
        node = SubElement(rootNode, 'CompressSettingsFile')
        if self._bCompSettings:
            node.text = 'Yes'
        else:
            node.text = 'No'

        # Check if the settings folder exists
        if not os.path.isdir(self._sSettingsPath):
            os.makedirs(self._sSettingsPath)
        # Construct the settings file name and check if it exists
        sFName = os.path.join(self._sSettingsPath, self._sSettingsFName)
        if os.path.isfile(sFName):
            os.remove(sFName)
        # Save the new xml file
        if self._bCompSettings:
            datas = ETree.tostring(rootNode, encoding='UTF8', method='xml')
            datas = datas.replace(b'UTF8', b'UTF-8')
            compDatas = zlib.compress(datas, 9)
            f = open(sFName, 'wb')
            f.write(compDatas)
            f.close()
        else:
            tree = ElementTree(rootNode)
            tree.write(sFName, encoding='UTF-8', xml_declaration=True)

    DatasPath = property(_getDatasPath)
    Modified = property(_isModified)
    MainWndStartupPos = property(_getMainWndStartupPos, _setMainWndStartupPos)
    MainWndStartupSize = property(_getMainWndStartupSize, _setMainWndStartupSize)
    MainWndStartupRect = property(_getMainWndStartupRect, _setMainWndStartupRect)
    MultipleInstancesAllowed = property(_getMultipleInstancesAllowed, _setMultipleInstancesAllowed)
    CompressSettingsFile = property(_getCompressSettings, _setCompressSettings)
