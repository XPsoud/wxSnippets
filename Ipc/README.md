# Ipc snippet #

THis snippet shows how to detect an already running instance of an application, and to transmit _orders_ to this instance instead of running another one.

This code has been inspired from the Code::Blocks sources.

To test :
- Launch a first instance of the application : it will show a simple window with a wxTextCtrl in witch actions will be logged
- Try to launch another instance : the first instance will be raises, even if it was iconized
- Try to launch another instance with a file (or what else you want) as argument : these arguments will be passed to the first instance.

