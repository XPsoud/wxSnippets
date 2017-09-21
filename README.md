# About this repository #

It is a place where I'll put snippets of codes related to wxWidgets.

Each of them is placed in its own subfolder, and should also contain all the needed for a buildable test application.

Each subfolder contains also a README file with a description of the snippet.

## Building the snippets ##

Building the snippets can be done using the provided Makefile.

It should work under Windows (MinGW only), Linux and Mac OS-X.

Under Windows, you must have a copy of the **wx-config** executable in your path. By default, il will search for the wxWidgets libs in **C:\wx30**, and in the **gcc_dll\mswu** lib subfolder.

You can override this using the command line. For example : **mingw32-make WXWIN=C:\wx31 WXCFG=gcc_lib\mswu**

To build all the snippets, just run the Makefile "as-is".

To build one of the snippets, use the name of the snippets sub-folder as build target. For example : **make TestApp** (or under Windows **mingw32-make WXWIN=C:\wx31 WXCFG=gcc_lib\mswu TestApp**)

Each build result (executable file or app bundle under OS-X) will be placed in a **bin** subfolder into the snippet's one.

## Snippets availables ##

None yet... sorry !

## To-Do ##

Snippets to store here :
- Settings manager
- Simple wxWidgets test application
- About box (wxWidgets provided and wxDialog one)
- ...
