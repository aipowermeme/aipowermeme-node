# macOS Build Instructions and Notes

The commands in this guide should be executed in a Terminal application.
The built-in one is located in
```
/Applications/Utilities/Terminal.app
```

## Preparation
Install the macOS command line tools:

```shell
xcode-select --install
```

When the popup appears, click `Install`.

Then install [Homebrew](https://brew.sh).

## Dependencies
```shell
brew install automake berkeley-db4 libtool boost gmp miniupnpc pkg-config python qt libevent libnatpmp qrencode sqlite
```

If you run into issues, check [Homebrew's troubleshooting page](https://docs.brew.sh/Troubleshooting).
See [dependencies.md](dependencies.md) for a complete overview.

## Berkeley DB

It is recommended to use Berkeley DB 4.8. If you have to build it yourself,
you can use [the installation script included in contrib/](contrib/install_db4.sh)
like so:

```shell
./contrib/install_db4.sh .
```

from the root of the repository.

**Note**: You only need Berkeley DB if the wallet is enabled (see the section *Disable-Wallet mode* below).

## Build AIPowerMeme Core

1. Clone the AIPowerMeme Core source code:
    ```shell
    git clone https://github.com/aipowermeme
    cd aipowermeme
    ```

2.  Build AIPowerMeme Core:

    Configure and build the headless AIPowerMeme Core binaries as well as the GUI (if Qt is found).

    You can disable the GUI build by passing `--without-gui` to configure.
    ```shell
    ./autogen.sh
    ./configure
    make
    ```

3.  It is recommended to build and run the unit tests:
    ```shell
    make check
    ```

4.  You can also create a  `.dmg` that contains the `.app` bundle (optional):
    ```shell
    make deploy
    ```

## `disable-wallet` mode
When the intention is to run only a P2P node without a wallet, AIPowerMeme Core may be
compiled in `disable-wallet` mode with:
```shell
./configure --disable-wallet
```

In this case there is no dependency on Berkeley DB 4.8 and SQLite.

Mining is also possible in disable-wallet mode using the `getblocktemplate` RPC call.

## Running

AIPowerMeme Core is now available at `./src/aipowermemed`

Before running, you may create an empty configuration file:
```shell
mkdir -p "/Users/${USER}/Library/Application Support/AIPowerMeme"

touch "/Users/${USER}/Library/Application Support/AIPowerMeme/aipowermeme.conf"

chmod 600 "/Users/${USER}/Library/Application Support/AIPowerMeme/aipowermeme.conf"
```

The first time you run aipowermemed, it will start downloading the blockchain. This process could take many hours, or even days on slower than average systems.

You can monitor the download process by looking at the debug.log file:
```shell
tail -f $HOME/Library/Application\ Support/AIPowerMeme/debug.log
```

## Other commands:

```shell
./src/aipowermemed -daemon      # Starts the aipowermeme daemon.
./src/aipowermeme-cli --help    # Outputs a list of command-line options.
./src/aipowermeme-cli help      # Outputs a list of RPC commands when the daemon is running.
```

## Notes

* Tested on OS X 10.12 Sierra through macOS 10.15 Catalina on 64-bit Intel
processors only.
* Building with downloaded Qt binaries is not officially supported. See the notes in [#7714](https://github.com/bitcoin/bitcoin/issues/7714).
