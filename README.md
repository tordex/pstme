# PSTME - paste text chunks into applications

<div style="text-align:center"><img src="images/screeshot.jpg" /></div>

PSTME helps to paste the selected text chunks into any applications. Actually PSTME just writes the selected text chunk to the stdout. I recommend [ydotool](https://github.com/ReimuNotMoe/ydotool) as tool to insert text from PSTME into any application.

## Using PSTME with ydotool

To use PSTME with ydotool you have to create a shell script:

```bash
#!/bin/bash

pstme $1 | ydotool type -f -
```

This script accepts the chunks files as first argument and passes it to the PSTME. Now you can create a keyboard shortcut to this script with required chunks file as argument.

## Chunks file format

Format of chunks file is following:

```
<name of chunks sets>
--
<name of chunk>
<semicolon separated tags>
<chunk text>
--
```

First line defines the name of sets of chunks (name of file). This name will be shown as PSTME window title.

Then the any number of chunks are follow with "--" separator. The first line after "--" is the name of chunk (shown in the list). The second line are semicolon separated tags. PSTME uses tags to search required chunk. And since the third line - chunk text. The chunk block must be finished with "--" separator.

The [demo.txt](demo/demotxt) file contains a small example.

**Note:** It is possible to save passwords in the chunks but it is not recommended because all files are in plain text format and this is insecure.

## Building PSTME

Required libraries: **gtkmm-3.0**

PSTME uses CMake as the build system. The usual commands:

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
make
sudo make install
```
