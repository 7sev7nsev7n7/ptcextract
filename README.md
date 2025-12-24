# Pony Town Skin Extractor

This utility serves to extract information from Pony Town character files exported
from the game, allowing easier sharing of skin details.

This project is a work in progress and is not associated or affiliated with the
Pony Town team

# Usage

The program reads information from Pony Town character files (.ptc) and
decompresses and prints out the character's details, making sharing characters
much easier. To use the program, simply run it and specify the directory where
your character file is located:

```bash
ptextract ~/downloads/character.ptc
```

# Building

This project does not have any dependencies, which makes building the
executable much easier.

```bash
git clone https://github.com/7sev7nsev7n7/ptextractor.git
cd ptextractor
make
```

#### Disclaimer

Compatibility on Windows operating systems might be buggy or non-functional.
Please contact directly in case of any issues via Discord: 7sev7nsev7n7
