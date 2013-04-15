// File: keypoint.hh
// Date: Mon Apr 15 23:00:15 2013 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>

#pragma once
#include "feature.hh"
#include "sift.hh"

class KeyPoint {
	public:
		const DOGSpace& dogsp;
		int noctave, nscale;
		std::vector<Coor> keyp;

		std::vector<Feature> features;

		KeyPoint(const DOGSpace&);

		void detect_extrema();

		void judge_extrema(int no, int ns);

		bool judge_extrema(real_t center, int no, int ns, int i, int j);

		void get_feature(int nowo, int nows, int i, int j);

		Vec calc_offset(int, int, int, std::shared_ptr<DOG>&, real_t*, real_t*, real_t*);

		bool on_edge(int, int, const std::shared_ptr<GreyImg>&);

		void calc_dir();

};
