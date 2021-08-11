# Simple Compression Algorithm
This is an experimentation with compressing simple text.

Compresses any string to about 1 byte per occurrence for text with less than 160 duplicate values,
compresses to about 2 bytes per occurrence for text with less than 65535 duplicate values (but greater than 160).  

The ultimate limitation
is 65,535 duplicates as anything more will probably not be compressed enough to be worth it.

### Efficiency 
As with any compression, it is difficult to calculate efficiency without knowing how many duplicates of strings will be 
contained in the text.   
Obviously, the more duplicates, and the larger the size of those duplicates in characters, the more efficient this 
algorithm will be.  

**One thing that is effectively guaranteed is that the compressed file will never be larger than the original.**  

The same cannot be said about the standard compression found on Windows 10, which sometimes makes compressed text (especially text with few duplicate values) larger when zipped.