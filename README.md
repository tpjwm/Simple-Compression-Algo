# Simple Compression Algorithm
This is just an experimentation with compressing simple text.
There are severe limitation to this as it can only compress 32 unique duplicates 
(because of the hacky way I use chars to replace duplicates).

### Efficiency - or lack thereof
With the current text that is inside the repository, it is compressed from 1093 bytes, 
to 898 bytes. But as the vector of string duplicates are also needed to uncompress, those
are also added to the compressed byte count (as realistically that would have to be saved somewhere).
Taking the total compressed bytes to about 1002. Meaning if this sample is to be taken as the average, 
this algorithm compresses text to about 91% of its original size.

Compressing this file in Windows 10, compresses it to about 63%. So there is definitely room for improvement. 