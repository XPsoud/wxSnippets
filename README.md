# About this repository #

It is a place where I'll put snippets of codes related to wxWidgets.

Each of them is placed in its own subfolder, and should also contain all the needed for a buildable test application.

They are available for C++, and for Python (Python 3 required). Please note that not all snippets are actually tranlated in Python (this is a _work in progress_)

Each subfolder contains also a README file with a description of the snippet.

## Binaries versions of C++ code ##
Available for both 32 and 64 bits on [this site](https://wxstuff.xaviou.fr/index.html)

## Building the snippets (C++ version) ##

Building the snippets can be done using the provided Makefile.

It should work under Windows (MinGW only), Linux and Mac OS-X.

Under Windows, you must have a copy of the **wx-config** executable in your path. By default, il will search for the wxWidgets libs in **C:\wx30**, and in the **gcc_dll\mswu** lib subfolder.

You can override this using the command line. For example : **mingw32-make WXWIN=C:\wx31 WXCFG=gcc_lib\mswu**

You can also set these variables as environment ones so you won't have to specify them each time : in this case you'll just have to call **mingw32-make**.

To build all the snippets, just run the Makefile "as-is".

To build one of the snippets, use the name of the snippets sub-folder as build target. For example : **make TestApp** (or under Windows **mingw32-make WXWIN=C:\wx31 WXCFG=gcc_lib\mswu TestApp**)

Each build result (executable file or app bundle under OS-X) will be placed in a **bin** subfolder into the snippet's one.

## Running a snippet ##

For the C++ version, you'll have to first build it (see previous section). As it is said just above, the corresponding executable is placed in a **bin** subfolder of the snippet's one.

For the Python version, you'll find it in a **Python** subfolder of the snippet's one. Just run the _Main.py_ file to see it in action.

## Snippets availables ##

- ![Cpp](/common/cpp.png) ![Py](/common/python.png) **AboutBoxDlg**: A _home made_ about box
- ![Cpp](/common/cpp.png) ![Py](/common/python.png) **AboutBoxWx**: A _wxWidgets provided_ standard about box
- ![Cpp](/common/cpp.png) ![No](/common/empty.png) **AddRemoveCtrl**: A small example on how to use _**wxAddRemoveCtrl**_ (needs wxWidgets-3.1.0)
- ![Cpp](/common/cpp.png) ![Py](/common/python.png) **AutoComplete**: A small example on how to use autocompletion with wxWidgets textboxes
- ![Cpp](/common/cpp.png) ![No](/common/empty.png) **Guid**: A small cross-platform (Windows, Linux and Max) Guid class
- ![Cpp](/common/cpp.png) ![No](/common/empty.png) **Ipc** (Interprocess Communication): How to give the focus to an already running instance of an application
- ![Cpp](/common/cpp.png) ![Py](/common/python.png) **PwdProtect**: Password protected access to an application
- ![Cpp](/common/cpp.png) ![Py](/common/python.png) **StdPaths**: An application to show each values that can be returned by _**wxStandardPaths**_
- ![Cpp](/common/cpp.png) ![Py](/common/python.png) **SettingsManager**: wxWidgets singleton class to manage an application's settings
- ![Cpp](/common/cpp.png) ![Py](/common/python.png) **TestApp**: A simple wxWidgets application to quickly make tests


## Other things shown by these snippets ##

- Single instance checker (_**SettingsManager**_ snippet): It prevents the user from launching more than one instance of the application (this feature can be enabled or disabled using the settings dialog box)
- Datas file compression (_**SettingsManager**_ snippet): It allows to compress a file during its creation process so it can't be edited by a simple text editor
- Embedding images (or any other binary file) into the application (_**PwdProtect**_ snippet): It allows binary files such as images or other things to be integrated into the application without providing the file itself

## To-Do ##

Snippets to store here :

- I18n
- Splash screen
- ...
