# Pony Town Skin Extractor

This utility serves to extract information from Pony Town character files exported
from the game, allowing easier sharing of skin details

**This project is a work in progress** and is not associated or affiliated with the
Pony Town team

# Usage

The program reads information from Pony Town character files (.ptc) and
decompresses and prints out the character's details, making sharing characters
much easier. To use the program, simply run it and specify the directory where
your character file is located:

```bash
ptcextract examples/example.ptc
```

There is an example pony in `examples`:

<p align="center">
    <img height="25%" src="assets/pony.png">
</p>

# Building

Building this program relies on `gcc` and `make`, available by default on most
Linux distributions. Make sure you have installed them along with the
dependencies listed in their respective section to avoid any errors

```bash
git clone https://github.com/7sev7nsev7n7/ptcextract.git
cd ptcextract
make
```

## Dependencies

- libb64 

#### Disclaimer

Compatibility on Windows operating systems might be buggy or non-functional.
Please contact directly in case of any issues via Discord: 7sev7nsev7n7
