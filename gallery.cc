// File: gallery.cc
// Date: Fri Apr 19 23:38:59 2013 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>

#include "gallery.hh"
using namespace std;
using namespace Magick;

Gallery::Gallery(list<Image>& List) {
	appendImages(&img, List.begin(), List.end(), true);
}

