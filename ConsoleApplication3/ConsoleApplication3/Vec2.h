#pragma once

#include <iostream>
#include <string>

using namespace std;

class Vec2
{
public:
	float x = 0.0f;
	float y = 0.0f;

	Vec2(){
	}

	Vec2(float x , float y ) {
		this->x = x;
		this->y = y;
	}

	~Vec2() {
		cout << "supprimé " << to_string(x) << endl;
	}

	Vec2 add(Vec2 v) {
		Vec2 res;
		res.x = x + v.x;
		res.y = y + v.y;
		return res;
	}

	void incr(Vec2 * v) {
		//(*v).x+=this->x;
		v->x += this->x;
	}

	void incr(Vec2 & v) {
		v.x += this->x;
	}
};

