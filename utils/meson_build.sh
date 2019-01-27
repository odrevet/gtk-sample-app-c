rm -rf builddir/ ; CFLAGS=-rdynamic meson builddir && cd builddir && ninja && ./gtk-sample-app &&  cd ..
