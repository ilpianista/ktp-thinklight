# tkp-thinklight

A plugin for [KDE Telepathy](https://userbase.kde.org/Telepathy) which turns on the ThinkPad light when a new message is coming.

It requires [thinkalert](http://www.mike.tl/other/ThinkAlert.html) which allows to turn on/off the light without root privileges.

[![Flattr this git repo](http://api.flattr.com/button/flattr-badge-large.png)](https://flattr.com/submit/auto?user_id=ilpianista&url=http://blog.andreascarpino.it/kde-telepathy-thinklight-plugin&title=ktp-thinklight&language=&tags=kde&category=software)

## Build and install

    $ mkdir build
    $ cd build
    $ cmake ../
    $ make
    # make install

If you don't install the plugin in the directory listed by `qtpaths --plugin-dir`, be sure that directory is in your QT_PLUGIN_PATH.
