#pragma once
class bullet
{
public:
	bullet();
	~bullet();
	void move(int x, int y);
private:
	bool hit;
};

