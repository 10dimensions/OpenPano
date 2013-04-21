// File: main.cc
// Date: Sun Apr 21 21:26:18 2013 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>

#include "keypoint.hh"
#include "render/filerender.hh"
#include "planedrawer.hh"
#include "filter.hh"
#include "matcher.hh"
#include "gallery.hh"
#include <ctime>

using namespace std;
using namespace Magick;

#define LABEL_LEN 7

inline real_t gen_rand()
{ return (real_t)rand() / RAND_MAX; }

vector<Feature> get_feature(shared_ptr<Img> ptr) {
	ScaleSpace ss(ptr, NUM_OCTAVE, NUM_SCALE);
	DOGSpace sp(ss);
	KeyPoint ex(sp, ss);
	ex.work();
	return move(ex.features);
}

void test_feature(const char* fname) {
	shared_ptr<Img> test(new Img(fname));
	RenderBase* r = new FileRender(test, "out.png");
	r->write(test);
	cout << r->get_geo().w << r->get_geo().h << endl;
	PlaneDrawer pld(r);

	vector<Feature> ans = get_feature(test);
	cout << ans.size() << endl;
	for (auto i : ans)
		pld.arrow(i.real_coor, i.dir, LABEL_LEN);
	r->finish();

	int a;
	cin  >> a;
	/*
	 *shared_ptr<GreyImg> ptr1 = Filter::GreyScale(ptr);
	 *shared_ptr<GreyImg> ptr2 = Filter::GaussianBlur(ptr1, 3);
	 */
	delete r;
}


void gallery(const char* f1, const char* f2) {
	list<Image> imagelist;
	Image pic1(f1);
	Image pic2(f2);
	imagelist.push_back(pic1);
	imagelist.push_back(pic2);
	Gallery ga(imagelist);

	shared_ptr<Img> test(new Img(ga.get()));
	RenderBase* r = new FileRender(test, "out.png");
	PlaneDrawer pld(r);
	r->write(test);

	vector<Feature> ans = get_feature(test);
	for (auto i : ans) pld.arrow(i.real_coor, i.dir, LABEL_LEN);

	shared_ptr<Img> ptr1(new Img(pic1));
	shared_ptr<Img> ptr2(new Img(pic2));
	vector<Feature> feat1 = get_feature(ptr1);
	vector<Feature> feat2 = get_feature(ptr2);

	Matcher match(feat1, feat2);
	auto ret = match.match();
	for (auto &x : ret.data) {
		pld.set_color(::Color(gen_rand(), gen_rand(), gen_rand()));
		pld.circle(x.first, LABEL_LEN);
		pld.circle(x.second + Coor(ptr1->w, 0), LABEL_LEN);
		pld.line(x.first, x.second + Coor(ptr1->w, 0));
	}

	r->finish();
	delete r;
}

void test_memory(const char* fname) {
	shared_ptr<Img> test(new Img(fname));
	get_feature(test);
	return;
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	/*
	 *test_feature(argv[1]);
	 */
	/*
	 *gallery(argv[1], argv[2]);
	 */
}
