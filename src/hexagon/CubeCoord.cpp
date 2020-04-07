#include "hexagon/CubeCoord.hpp"

#include <utility>
#include <cassert>
#include <cmath>

CubeCoord::CubeCoord() {
	m_q = m_r = m_s = 0;
}

CubeCoord::CubeCoord (int q, int r, int s) :
	m_q(q), m_r(r), m_s(s) {
	assert_valid();
}

CubeCoord::CubeCoord(const CubeCoord &c) {
	c.assert_valid();

	m_q = c.m_q;
	m_r = c.m_r;
	m_s = c.m_s;
}

std::pair<float, float> CubeCoord::to_pixel(float radius) const {
	return {
		radius * (sqrt(3) * m_q  +  sqrt(3)/2. * m_r), //+ sqrt(3) * radius/ 2,
    	radius * (3./2. * m_r),//+ radius,
	};
}

CubeCoord CubeCoord::from_pixel(float x, float y, float radius) {
	// x -= sqrt(3) * radius / 2;
	// y -= radius;
	float frac_q = (sqrt(3)/3. * x  -  1./3. * y) / radius;
	float frac_r = (2./3. * y) / radius;
	float frac_s = -frac_r - frac_s;
	return CubeCoord::round_values (
		frac_q,
		frac_r,
		frac_s
	);
}

CubeCoord CubeCoord::round_values(float x, float y, float z) {
	int rx = round(x);
	int ry = round(y);
	int rz = round(z);

	int x_diff = abs(rx - x);
	int y_diff = abs(ry - y);
	int z_diff = abs(rz - z);

	if (x_diff > y_diff and x_diff > z_diff) {
		rx = -ry-rz;
	} else if (y_diff > z_diff) {
		ry = -rx-rz;
	} else {
		rz = -rx-ry;
	}

    return CubeCoord(rx, ry, rz);
}

bool CubeCoord::equals(const CubeCoord &c) const {
	return m_q == c.m_q && 
		m_r == c.m_r && 
		m_s == c.m_s;
}

void CubeCoord::add(const CubeCoord &c) {
	c.assert_valid();

	m_q += c.m_q;
	m_r += c.m_r;
	m_s += c.m_s;
}

void CubeCoord::subtract(const CubeCoord &c) {
	c.assert_valid();

	m_q -= c.m_q;
	m_r -= c.m_r;
	m_s -= c.m_s;
}


void CubeCoord::assert_valid() const {
	assert(m_q + m_r + m_s == 0);
}



bool CubeCoord::operator==(const CubeCoord &c) const {
	return equals(c);
}

bool CubeCoord::operator!=(const CubeCoord &c) const {
	return !equals(c);
}

CubeCoord CubeCoord::operator+(const CubeCoord &c) const {
	CubeCoord tmp = *this;
	tmp.add(c);
	return tmp;
}

CubeCoord CubeCoord::operator-(const CubeCoord &c) const {
	CubeCoord tmp = *this;
	tmp.subtract(c);
	return tmp;
}

std::array<CubeCoord, 6> CubeCoord::get_neighbours() const {
	const static  std::array<CubeCoord, 6> directions = {{
		{1, -1, 0}, {1, 0, -1}, {0, 1, -1},
		{-1, 1, 0}, {-1, 0, 1}, {0, -1, 1}
	}};
	CubeCoord tmp(m_q, m_r, m_s);	
	std::array<CubeCoord, 6> neighbours;

	int i = 0;
	for (auto dir : directions) {
		neighbours[i] = tmp + dir;
		++i;
	}
	return neighbours;
}