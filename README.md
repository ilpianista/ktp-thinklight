tkp-thinklight
==============

A plugin for [KDE Telepathy](https://userbase.kde.org/Telepathy) which turns on the ThinkPad light when a new message is coming.

It requires you to have write access to `/proc/acpi/ibm/light`. A way to do this is to change its permissions to 777.

## Build and install

    $ mkdir build
    $ cd build
    $ cmake ../
    $ make
    # make install

If you don't install the plugin in the directory listed by `qtpaths --plugin-dir`, be sure that directory is in your QT_PLUGIN_PATH.

## Donate

Donations via [Liberapay](https://liberapay.com/ilpianista) or Bitcoin (1Ph3hFEoQaD4PK6MhL3kBNNh9FZFBfisEH) are always welcomed, _thank you_!

## License

LGPL
