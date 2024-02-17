AIPowerMeme Core
==========

This is the official reference wallet for AIPowerMeme digital currency and comprises the backbone of the AIPowerMeme peer-to-peer network. You can [download AIPowerMeme Core](https://www.aipowermeme.org/downloads/) or [build it yourself](#building) using the guides below.

Running
---------------------
The following are some helpful notes on how to run AIPowerMeme Core on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/aipowermeme-qt` (GUI) or
- `bin/aipowermemed` (headless)

### Windows

Unpack the files into a directory, and then run aipowermeme-qt.exe.

### macOS

Drag AIPowerMeme Core to your applications folder, and then run AIPowerMeme Core.

### Need Help?

* See the [AIPowerMeme documentation](https://docs.aipowermeme.org)
for help and more information.
* Ask for help on [AIPowerMeme Discord](http://stayaipowermemey.com)
* Ask for help on the [AIPowerMeme Forum](https://aipowermeme.io/forum)

Building
---------------------
The following are developer notes on how to build AIPowerMeme Core on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [macOS Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [NetBSD Build Notes](build-netbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The AIPowerMeme Core repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Productivity Notes](productivity.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- Source Code Documentation ***TODO***
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [JSON-RPC Interface](JSON-RPC-interface.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* See the [AIPowerMeme Developer Documentation](https://aipowermeme.readme.io/)
  for technical specifications and implementation details.
* Discuss on the [AIPowerMeme Forum](https://aipowermeme.io/forum), in the Development & Technical Discussion board.
* Discuss on [AIPowerMeme Discord](http://stayaipowermemey.com)
* Discuss on [AIPowerMeme Developers Discord](http://chat.aipowermemedevs.org/)

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [aipowermeme.conf Configuration File](aipowermeme-conf.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [I2P Support](i2p.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [PSBT support](psbt.md)
- [Reduce Memory](reduce-memory.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [ZMQ](zmq.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
