#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <mutex>
#include "include/image.h"

using namespace std;

mutex mu;

void toConsole (Image* img, int l) {
  img->downSample(l);
  {
    lock_guard<mutex> locker(mu);
    img->show_array(l); // note: show_array is not thread safe because all threads are sharing the same cout.
  }
}

void toFile (Image* img, int l, string& filename) {
  img->downSample(l);
  ostringstream outputFilename;
  outputFilename << filename << "_d" << l;
  int* L = img->getL_(l);
  int* extents = Image::extents_(img->dimension, L);
  int N = Image::size(img->dimension, extents);
  { // although each down-sample has its own assoicated file, it is better not to make the hard drive dance.
    lock_guard<mutex> locker(mu);
    cout << "output to: " << outputFilename.str() << endl;
    ofstream ofile(outputFilename.str());
    ofile << img->dimension << " ";
    for (int i=0, len=img->dimension; i < len; i++)
      ofile << L[i] << " ";
    for (int i=0; i < N; i++)
      ofile << img->downSample(l)[i] << " ";  // running downSample second time will just return the image pointer.
    ofile.close();
  }
  delete [] extents;
  delete [] L;
}

// Use this class as a wrapper to handle multi-threading.
// for proper deallocating the "th" array.
class Down {
  thread* _th;
  Image* _img;
public:
  Down (Image* img) {
    _img = img;
    _th = new thread[_img->max_sample];
  }
  ~Down () {
    delete [] _th;
  }
  void output () {
    for (int i=0, len=_img->max_sample; i < len; i++)
      _th[i] = thread(toConsole, _img, i+1);
  }
  void output (string& filename) {
    for (int i=0, len=_img->max_sample; i < len; i++)
      _th[i] = thread(toFile, _img, i+1, ref(filename));
  }
  void join () {
    for (int i=0, len=_img->max_sample; i < len; i++)
      _th[i].join();
  }
};

int main (int argc, char* argv[]) {
  string inputFilename, outputFilename;
  ifstream ifile;
  int d, *L, *extents;
  Image* img;

  if (argc < 2) {
    cerr << "Please enter the Original-Image filename as the input.\n";
    return 1;
  }
  inputFilename = argv[1];

  ifile.open(inputFilename);
  if (!ifile.is_open()) {
    cerr << "File not found.\n";
    return 1;
  }

  cout << "Begin processing...\n";

  ifile >> d;
  L = new int[d];
  for (int i=0; i < d; i++)
    ifile >> L[i];
  extents = Image::extents_(d, L);
  array_type A(boost::extents[extents[0]][extents[1]]);
  for (index i = 0; i < extents[0]; i++)
    for (index j = 0; j < extents[1]; j++)
      ifile >> A[i][j];
  ifile.close();

  img = new Image(d, L, A.data());

  Down downAll(img);
  if (argc < 3) {
    img->show_array();  // cout the Original-Image
    downAll.output();  // multi-threading
  } else {
    outputFilename = argv[2];
    downAll.output(outputFilename);  // multi-threading
  }

  downAll.join();

  delete img;
  delete [] extents;
  delete [] L;

  cout << "End processing.\n";
  return 0;
}
