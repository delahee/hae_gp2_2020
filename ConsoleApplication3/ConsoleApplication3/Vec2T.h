#pragma once

template<typename T>
class Vec2T
{
public:
	T x;
	T y;

	Vec2T<T>() {
		x = {};
		y = {};
	};

	Vec2T<T>(T x, T y) {
		this->x = x;
		this->y = y;
	};

	Vec2T<T> add(Vec2T v) {
		Vec2T<T> res;
		res.x = this->x + v.x;
		res.y = this->y + v.y;
		return res;
	};

	Vec2T<T> add(T x, T y) {
		Vec2T<T> res;
		res.x = this->x + x;
		res.y = this->y + y;
		return res;
	};
};

