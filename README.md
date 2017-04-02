# Down-Sampling
Multi-thread Down Sampling Example in C++


## Installation:
Please install boost library first.
e.g. in ubuntu
sudo apt-get install libboost-all-dev

and then type "make".  A executable file "down" will be created.


## Usage:
down input [output]

Where input is the input image file with the following format.

[dimension - d] [L] x dimension [the image content...] X size (where size is 2^L1 X 2^L2 X ... 2^Ld)

## Limitation:
For demonstration purpose the source code only work for 2-dimension array image.  For multi-dimension, code will need to be modified and re-compiled.
