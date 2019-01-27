# Under Windows

MSYS2 with MinGW-W64 is the 'official' build method.

* Get MSYS2 from http://msys2.github.io/
* With MSYS2 shell Install MinGW toolchain (gcc, make) and dependencies (cmake and gtk3)

pacman -S  mingw-w64-i686-toolchain mingw32/mingw-w64-i686-cmake mingw32/mingw-w64-i686-gtk3

(Restart msys2 to ensure you are using the new environment variables settings)

With a MinGW Shell go to the gtk-sample-app directory and do :

    cmake.exe -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release . && mingw32-make.exe && mingw32-make.exe install

## Create an installer

* Install NSIS from sourceforge

in a MinGW-W64 shell go to the gjitenkai directory and  do :

    cmake.exe -DCMAKE_BUILD_TYPE=Release -DNSIS=ON . && cpack.exe

## Create a Standalone directory

Will install all required files (dll, icons) in the install directory

The resulting install directory is the same after an install with the NSIS installer,
except no installer is build and used.

    cmake.exe -DCMAKE_BUILD_TYPE=Release -DSTANDALONE=ON . && mingw32-make.exe install


Please note that:
* The project's cache must be cleaned up after using -DNSIS or -DSTANDALONE otherwise
the next install will also be standalone. You can clean with sh ./utils/cmake_clean_cache.sh

* After using -DNSIS, a standalone install tree can be found in _CPack_Packages\win32\NSIS

## Standalone directory tree

Gtk Application can find required files in at a relative location

The application final tree looks like this:

<pre>
bin/gtkapplication.exe
bin/*.dll
share/loader.cache
share/glib-2.0/gschemas.compiled
share/icons/Adwaita/scalable/*
share/icons/Adwaita/icon-theme.cache
share/icons/Adwaita/index.theme
lib/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-svg.dll
lib/gdk-pixbuf-2.0/2.10.0/loaders/loaders.cache
</pre>


## GSettings schemas with standalone Windows applications

In a standard install .xml schemas files are copied in the system at share/glib-2.0/
 and the gschemas.compiled is re-generated on the system with all the other software.

In a standalone build, we do not need all other installed software schemas, because each standalone application have a  gschemas.compiled file installed in a directory relative to the exe (at bin/../share/glib-2.0/gschemas.compiled).
The required system settings are GTK settings org.gtk.Settings.ColorChooser.gschema.xml and org.gtk.Settings.FileChooser.gschema.xml.

Unfortunatly glib-compile-schemas can only compile entires directory and not a selection of file.

So when building a standalone exe, xml schemas sampleapp.gschema.xml, org.gtk.Settings.ColorChooser.gschema.xml and org.gtk.Settings.FileChooser.gschema.xml are put in a separate tmp directory (%tmp%/gtk-sample-app) to create the gschemas.compiled file

## Icons with standalone Windows applications

SVG icons of the default theme (adwaita) needs to be copyed to a share directory relative to the bin directory bin../share/icons/Adwaita/scalable/* also bin../share/icons/Adwaita/icon-theme.cache and bin../share/icons/Adwaita/index.theme

After several test, it appears that the following files are also required:
* lib/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-svg.dll
* lib/gdk-pixbuf-2.0/2.10.0/loaders/loaders.cache The first line of this file also needs to be edited to "../lib/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-svg.dll"

## Windows XP missing dll
Windows XP misses the dwmapi.dll file.

A compatible version of this dll can be downloaded from http://src.repairdll.org/download/18825_dwmapi.dll
