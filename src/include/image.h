#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <vector>
#include <boost/multi_array.hpp>

typedef boost::multi_array<uint, 2> array_type;
typedef array_type::index index;

typedef unsigned int uint;

class Image {
  int _dimension;
  int* _L;
  int* _extents;
  int _size;
  int _max_sample;
  uint* _data;
  uint** _downSamples;
public:
  static int* extents_ (int d, int L[]);
  static int size (int d, int extents[]);

  Image (int d, int L[], uint* data);
  ~Image ();

  uint* downSample (int l);
  int* getL_ (int l);
  void show_array (int L[], uint* data);
  void show_array (int l);
  void show_array ();

  // properties
  const int& dimension;
  const int& max_sample;
};

#endif // IMGAGE_H
