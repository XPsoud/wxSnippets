
SUBDIRS = AboutBoxDlg AboutBoxWx AddRemoveCtrl AutoComplete DropTarget FileType Guid Internat1 Ipc NotifMsg PwdProtect SettingsManager StdPaths TestApp

ifeq ($(OS),Windows_NT)
OS_Detected=Windows
else
OS_Detected=$(shell uname -s)
endif

all: $(SUBDIRS)

.PHONY: $(SUBDIRS) all clean minclean infos

minclean: $(SUBDIRS)

clean: $(SUBDIRS)

infos :
	@$(MAKE) -f Makefile.$(OS_Detected) -w -C build $(MAKECMDGOALS) PRJNAME=TestApp

$(SUBDIRS):
	@$(MAKE) -f Makefile.$(OS_Detected) -w -C build $(MAKECMDGOALS) PRJNAME=$@ OS_Detected=$(OS_Detected)
