#ifndef CUBE_COORD
#define CUBE_COORD

#include <functional>
#include <array>

class CubeCoord {
	public:
		CubeCoord();
		CubeCoord(int q, int r, int s);

		CubeCoord(const CubeCoord &c);

		~CubeCoord() = default;

		std::array<CubeCoord, 6> get_neighbours() const;

		std::pair<float, float> to_pixel(float radius) const;
		static CubeCoord from_pixel(float x, float y, float radius); 
		static CubeCoord round_values(float q, float r, float s);

		bool equals(const CubeCoord &c) const;
		void add(const CubeCoord &c);
		void subtract(const CubeCoord &c);

		bool operator==(const CubeCoord &c) const;
		bool operator!=(const CubeCoord &c) const;

		CubeCoord operator+(const CubeCoord &c) const;
		CubeCoord operator-(const CubeCoord &c) const;


		int m_q, m_r, m_s;

	private:
		void assert_valid() const;
};

namespace std
{
	template <>
	struct hash<CubeCoord>
	{
		size_t operator()(const CubeCoord& c) const
		{
			return ((hash<int>()(c.m_q) ^ (hash<int>()(c.m_r) << 1)) >> 1);
		}
	};
}

#endif