# Pony Town Skin Extractor

This utility serves to extract information from Pony Town character files
exported from the game, allowing easier sharing of skin details. It works by
processing the raw data contained within the file and formatting it in a
human-readable way, in order to allow easy sharing of character details and
values such as colors and options.

# Usage

To use the program, simply run it and specify the directory where
your character file is located:

```bash
ptcextract examples/horse.ptc
```

You may optionally specify multiple files to be processed, however processing
of complete exports (after selecting "Export all characters") is not yet
supported.

There is an example pony in `examples`:

<p align="center">
    <img height="25%" src="assets/horse.png">
</p>

# Building

Building this program relies on `gcc` and `make`, available by default on most
Linux distributions. Make sure you have installed them along with the
dependencies listed in their respective section to avoid any errors.

```bash
git clone https://github.com/7sev7nsev7n7/ptcextract.git
cd ptcextract
make
```

## Dependencies

- libb64 

# TODO

- Complete extraction of pattern/body part/accessory structure
- Complete assignment of colors via color table to body parts
- Complete full structured output with patterns, body parts and accessories, along with corresponding colors

#### Disclaimer

Compatibility on Windows operating systems might be buggy or non-functional.
Please contact directly in case of any issues via Discord: 7sev7nsev7n7

**This project is a work in progress and may not function as described here for
the time being**. I am not associated or affiliated with the Pony Town team.

This software is distributed as is and in good faith. I am not responsible for
the unintended or irresponsible use of this tool, or any unintended side
effects resulting from the usage of this tool.
