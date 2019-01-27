# GTK3 Sample app

Using:

* C with GTK3
* CMake
* GSettings
* Localization
* Glade UI file with common callbacks (quit/about)
* NSIS packager (Windows)

# What this application do

This application load and save a text in gschema.

# Make your own GTK application

* Clone or Download this repository
* Name your application

 The name of this template is 'sampleapp', you will need to rename a few files and directories by the name you want to give
 to your application.

 * Files ares:
     * second line of CMakeLists.txt
	 * sampleapp files in po/
	 * sampleapp folder at root of this repository
	 * sampleapp/ui/sampleapp.ui and sampleapp/sampleapp.png
	 * sampleapp/desktop and it's content
	 * share/share/glib-2.0/schemas/sampleapp.xml

There is a shell script "rename_app" in utils that do this work for you.
Use it at the root of the repository with your applicatio name as parameter (no space or special chars)

e.g
 sh utils/rename_app.sh MyApplication

 you are now ready to build

# Build (linux)

For instruction on building under Windows, see Windows.md

<pre>
--generate Makefile and config.h
$cmake .
--generate binary
$make
--install files, settings and binaries
#make install
</pre>

# Localization

Scan for translatable text in a Glade file

    xgettext --sort-output --keyword=translatable -o po/sampleapp.pot data/ui.glade

For Example, for French, copy pot file to fr/sampleapp.po

Set Content-type with "Content-Type: text/plain; charset=UTF-8\n"

Create binary file with `msgfmt`

    msgfmt sampleapp.po -o sampleapp.mo

Testing localization

List installed locales with the `locale` command

    locale -a

Under linux, test by changing the local with

    LANG=fr_FR.utf8 ./bin/sampleapp
