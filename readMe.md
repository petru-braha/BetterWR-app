# Archive file viewer

### Administrative:
1. Shortcuts:
   - GUI = graphical user interface 
   - CMD = bash commands
   - HUF = Huffaman trees functions
   - LZW = Lempel-Ziv-Welch functions

2. Map of execution pseudocode:
```
choose gui / bash boot
choose option, algorithm and paths
   if compression 
      create a temporary tar file (encoded in ASCII)
      compression is done
      delete temporary tar file
      place the encode file
   if decompression
```

3. Data structures: 
   - Heap
   - Binary trees 
   - Priority Queue
   - Dictionary
   - Hash Table

4. Workspace:
     - `admin`
     - `usage`
     - `constant files/test files` - exemples of execution

5. Principles:
   - the path to a folder always contains at the end of the string "/"
   - GUI-function has two components: visual method, functional method
   - object-oriented programming

6. Wireframes (screens):

- menu -> explorer -> menu + status box
 	  test (type string) -> output shown -> menu + status box
	  info (info-choose) -> TAR principle -> adaptation -> pseudocode -> exemples -> menu
			     -> HUF algorithm -> adaptation -> pseudocode -> exemples -> menu
			     -> LZW algorithm -> adaptation -> pseudocode -> exemples -> menu

## I. **Boot**:

- two ways of running the program: 
  - double-click on `start.exe` => opens GUI
  - openning the folder in command prompt
    - type `./name_of_executable *arguments*` 
    - if no arguments provided => opens GUI

### 1. GUI

- menu => file explorer / more information / test algorithms with a string

- explorer stages:
  1. choose partition
  2. choose files (displays: buttons, curent path, files, selected_files)
  3. status box 

- buttons:
```
Index		Class			Name		What it does
-------------------------------------------------------------------------------------------------
0 		button_0		exit		force the app to close
1 		button_menu_0		stored files	opens the file explorer
2 		button_menu_1   	+information	print exemples and 
3 		button_menu_2		test strings	convert keyboard input into huf/lzw code
4		button_expl_static	option		compression / decompression
5		button_expl_static	algorithm	HUF / LZW
6		button_expl_0           select		prepare files for option
```

### 2. CMD

- Usage: `./name_of_executable <operation> <algorithm> <nr_input_files> <input_file_paths> <output_path>`
- multiple files can be selectected to be encoded and decoded in one step
- some exemples:
```
.boot.exe decompress HUF 1 files/encoded/unpack/huf files/decoded/ originalFiles

./bin/Debug/BetterWR.exe compress LZW 2 '/constant files/test files/to_encode/element_1/' '/constant files/test files/to_encode/element_2/' unpack
```


## II. **Algorithms**:

### 1. HUF algorithm

- Huffman encoding involves computing the frequency for each unique character that appears in the initial string
- each character and its corresponding frequency is stored in a map => build the Huffman tree 
- Huffman tree necessary for both encoding and decoding
- based on the tree, we convert the initial string into a string of binary values - grouped such that a byte(8 bits) can be created and converted into the corresponding ASCII character. 
- finally, the resulting string is encoded and ready to be written to the output file. Also in this file we will keep the information needed to reconstruct the tree, i.e. each character together with its frequency plus the size of the tree. When we read the contents of the file to perform the decoding, we make sure that we first read the tree data correctly and then read the encoded string. Decoding will be done by traversing the reconstructed tree, and when the encoded value corresponding to a character is found, we will write it to our created decoding string.

- encoding/decoding pseudocode:
```
Creation of a Priority Queue Q, which contains each character
Sorting in ascending order of their frequencies 
For all unique characters:
    Create a newNode
    Extraction of the minimum value from Q and assigning it to the leftChild of the newNode 
    Retrieving the minimum value from Q and assigning it to the right child rightChild of newNode
    Computing the sum of the two minimum values and assigning this value to the newNode
    Inserting the newNode into the tree
return root
```

### 2. LZW algorithm

- Lempel-Ziv-Welch algorithm is a lossless data compression algorithm. Abraham Lempel, Jakob Ziv and Terry Welch are the scientists who developed it. Procedure: it scans a file for data patterns that occur multiple times, which are saved later in a dictionary and their references are placed in a compressed file whenever repetitive data occurs. In hardware implementations, the algorithm is simple and has the potential for very high throughput. Other usages: GIF image format, Unix file compression utility.

- the dictinonary is initialised with all the char elements from 0 to 255. 
- dictionary's memory + compressed message's memory < uncompressed message's memory
- dictionary is not send with the compressed message - you build the dictionary along the way (the receiver will constructor decoder alone)
- ideal for repetitive and long strings
- no prior information about the input data stream
- compress the input stream in one single step
- fast execution

- enconding pseudocode:
```
repeat
	repeat
		if temp is in dictionary
		    add the following character
	until it is no longer in the dictionary
	add it to the dictionary
	output the part that was already in the dictionary 
	//((strlen(temp)>1) means it is in the dictionary - memory saving method)
	
	reset variables 
until they reach the end of the input
```

- basic principle: the first character is always in the dictionary and the second character if it is not, means it is a copy of the previous one
- decode pseudocode:
```
repeat
    if not in dictionary next
	    copy previous
    else
	    we put it in the analysis on next
	output<<temp
    add to dictionary(previous, current)
until final input
```

## III. **Packaging**:

### 1. Tar format (used in my case)

- tape archive file format is an UNIX-based utility 
- connects files (tarballs) without compression - often compressed with gzip or bzip2.
- data encoded in ASCII
- each file object includes its data and a 512-byte record-anthet. Files' data is written unmodified, except that its length is rounded to a multiple of 512 bytes. At the end of the archive file there are two 512-byte blocks, filled with binary zeros, to mark the end of the file. To ensure portability between different architectures with different byte orderings, the information in the header record is encoded in ASCII. TAR files are fully compatible between UNIX and Windows systems because all header information is represented in ASCII.	

- Pros and cons:
  + we can use any compression algorithm after the unification
  + deletes doubled information (files)
  - can lose metadata of files (index of files)

- how content of the `tar.bin` file will look like:
```
element_1//
	forth.txt

patru s-a luat
cuci s-au aruncat
hahalero, kokos s-a diluat
am ster so mor decaptat

*5EPArAToR*

	lyrics/
		1.txt

hello world
pleasure to meet youu

*5EPArAToR*

	end_oF_lyrics/
end_oF_element_1//

```

### 2. Zip format
- .zip extension is an archive that can hold files. The archive may have compression applied to the included files. As soon as the then existing specifications were made available, many companies made the ZIP file format part of their software utilities, including Microsoft (since Windows 7), Apple (Mac OS X) and many others.
- the file is a compressed archive that supports lossless data compression. It is often used to send zipped email attachments; this way the message cannot be blocked by email server filters. It can also be used to hide a file type or prevent it from being opened.
- the order of events: firstly individual compression of the files then the unification
- pros and cons:
  + you can view and unarchive only one archive item
  + parallelize the archiving process on the CPU -> faster
  - compression ratio -- (join duplicates, something that is redundant)

### 3. Binary files 

- images: jpg, png, gif, bmp.
- videos: mp4, mkv, avi, mov.
- audio: mp3, aac, wav, flac.
- documents: pdf, doc, xls.
- archive: zip, rar, 7z, tar.
- executable: exe, dll, so.

### 4. Text files

- web standards: html, xml, css, svg, json, ...
- source code: c, cpp, h, cs, js, py, java, rb, pl, php, sh, ...
- documents: txt, tex, markdown, asciidoc, rtf, ps, ...
- configuration: ini, cfg, rc, reg, ...

[Source](https://www.nayuki.io/page/what-are-binary-and-text-files)

## IV **Limitations**:

1. Small number for input paths
2. From the graphical point of view:
- graphics.h is a primitive library [Additional documentation](https://www.programmingsimplified.com/c/graphics.h)

3. 32-bit compiler - it was used such that the project could support graphics.h

## V **Future improvements**:

* first alpha version launch: 10 june 2024

1. Add more languages:
- [x] english
- [ ] romanian
- [ ] french

2. use `temp.tar` as a binary file s. t. binary files coud be read. !!!

3. concrete implementation of the following menu buttons:
- "+information"
- "with strings"

4. navigation of the explorer with keyboard

## VI **How to set up this project in CodeBlocks**

1. Have g++ follow at least the C++17 GNU C++ language standard (ISO C++ plus GNU extensions)

2. Install a 32-bit compiler and set it up

3. Install graphics.h
- set up linker settings: `-lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32`
