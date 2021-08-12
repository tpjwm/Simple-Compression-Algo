# Simple Compression Algorithm
This is an experimentation with the lossless compression of simple text.

Compresses any string to 1 byte per occurrence for text with less than 160 duplicate values.

The limitation is 160 duplicates due to the way I use unique characters not common in text. Text with more than 160 
duplicates will still be compressed but the efficiency is greatly reduced after that limit is reached.

The only meta-data stored is the string value of the duplicates themselves, with no need to store index.

### Efficiency 
As with any compression, it is difficult to calculate efficiency without knowing how many duplicates of strings will be 
contained in the text.   
Obviously, the more duplicates, and the larger the size of those duplicates in characters, the more efficient this 
algorithm will be.  

**One thing that is effectively guaranteed is that the compressed file will never be larger than the original.**  

The same cannot be said about the standard compression found on Windows 10, which sometimes makes compressed text (especially text with few duplicate values) larger when zipped.