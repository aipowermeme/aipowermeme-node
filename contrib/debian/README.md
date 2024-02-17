
Debian
====================
This directory contains files used to package aipowermemed/aipowermeme-qt
for Debian-based Linux systems. If you compile aipowermemed/aipowermeme-qt yourself, there are some useful files here.

## aipowermeme: URI support ##


aipowermeme-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install aipowermeme-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your aipowermeme-qt binary to `/usr/bin`
and the `../../share/pixmaps/aipowermeme128.png` to `/usr/share/pixmaps`

aipowermeme-qt.protocol (KDE)

