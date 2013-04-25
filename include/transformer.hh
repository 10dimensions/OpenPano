// File: transformer.hh
// Date: Thu Apr 25 09:54:03 2013 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>

#pragma once
#include "matcher.hh"
#include "matrix.hh"

class TransFormer {
	private:
		const MatchData& match;

		Matrix cal_transform(const std::vector<int>&) const;

		Matrix cal_homo_transform(const std::vector<int>&) const;

		Matrix cal_affine_transform(const std::vector<int>&) const;

		int cal_inliers(const Matrix &) const;

		std::vector<int> get_inliers(const Matrix &) const;


	public:
		TransFormer(const MatchData& m_match):
			match(m_match) { }

		Matrix get_transform();

		static Vec2D cal_project(const Matrix &, const Vec2D&);
};
