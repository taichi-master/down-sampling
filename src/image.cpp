#include <iostream>
#include <math.h>
#include "include/image.h"
#include "include/modal.h"

using namespace std;

// static function(s)

// Caution: Dynamic memory will be allocated in this function.  Needs to dealloc properly.
int* Image::extents_ (int d, int L[]) {
  int* extents = new int[d];
  for (int i=0; i < d; i++)
    extents[i] = pow(2, L[i]);
  return extents;
}

int Image::size (int d, int extents[]) {
  int size = 1;
  for (int i=0; i < d; i++)
    size *= extents[i];
  return size;
}

Image::Image (int d, int L[], uint* data) : dimension(_dimension), max_sample(_max_sample) {
  _dimension = d;
  _L = L;
  _data = data;
  _extents = Image::extents_(_dimension, _L);
  _size = Image::size(_dimension, _extents);
  _max_sample = *min_element(_L, _L+_dimension);
  _downSamples = new uint*[_max_sample];
  for (int i=0; i < _max_sample; i++)
    _downSamples[i] = 0;
}

Image::~Image () {
  for (int i=0; i < _max_sample; i++)
    if (_downSamples[i])
      delete [] _downSamples[i];
  delete [] _downSamples;
  delete [] _extents;
}

// Caution: Dynamic memory will be allocated in this function.  Needs to dealloc properly.
int* Image::getL_ (int l) {  // get L by given l-downsample index.
  int* L = new int[_dimension];
  for (int i=0; i < _dimension; i++)
    L[i] = _L[i]-l;
  return L;
}

uint* Image::downSample (int l) {
  if (_downSamples[l-1])
    return _downSamples[l-1];

  int* L = getL_(l);
  int* extents = Image::extents_(_dimension, L);
  int N = Image::size(_dimension, extents);
  int T = _size / N, S = pow(2, l);  // Trunk and Section sizes.

  _downSamples[l-1] = new uint[N];
  uint (*D)[extents[1]] = (uint (*)[extents[1]]) _downSamples[l-1];

  uint (*A)[_extents[1]] = (uint (*)[_extents[1]]) _data;

  // down sample algorithm.
  uint x, y, z;
  uint* arr = new uint[T];
  for (uint i=0; i < extents[0]; i++) {
    for (uint j=0; j < extents[1]; j++) {
      x = i * S;
      y = j * S;
      z = 0;
      for (uint a=S; a ; a--) {
        for (uint b=S; b; b--)
          arr[z++] = A[x][y++];
        x++;
        y = j * S;
      }
      D[i][j] = modal(T, arr);
    }
  }

  delete [] arr;
  delete [] extents;
  delete [] L;

  return _downSamples[l-1];
}

// display the array on screen.
void Image::show_array (int L[], uint* data) {
  int* extents = Image::extents_(_dimension, L);
  uint (*A)[extents[1]] = (uint (*)[extents[1]]) data;
  for (index i = 0; i < extents[0]; i++) {
    for (index j = 0; j < extents[1]; j++)
      cout << A[i][j] << " ";
    cout << endl;
  }
  delete [] extents;
}

void Image::show_array (int l) {
  if (_downSamples[l-1]) {
    int *L = getL_(l);
    show_array(L, _downSamples[l-1]);
    delete [] L;
  }
}

void Image::show_array () {
  show_array(_L, _data);
}
