# Down-Sampling
Multi-threaded Down Sampling Example in C++


## Installation:
Please install boost library first.
e.g. in ubuntu
sudo apt-get install libboost-all-dev

and then type "make".  A executable file "down" will be created.


## Usage:
down input [output]

Where input is the input image file with the following format.

[dimension - d] [L] x dimension [the image content...] X size (where size is 2^L1 X 2^L2 X ... 2^Ld)

e.g. 2 2 3 1 1 1 1 1 1 1 1 1 2 1 2 1 2 1 2 1 1 2 2 2 2 2 2 1 2 2 2 2 2 2 2
where the first number 2 is the dimension
the next 2 and 3 are the L1 and L2
the rest data is the image content with the size of (2^2 x 2^3 = 4 x 8 = 32)


## Limitation:
For demonstration purpose the source code only work for 2-dimension array image.  For multi-dimension, code will need to be modified and re-compiled.
