#pragma once

// Size : 16
class Color
{
public:
	static Color WHITE;
	static Color GREEN;
	static Color ORANGE;
	static Color NIL;
	static Color RED;
	static Color BLUE;
	static Color CYAN;
	static Color GREY;
	static Color BLACK;
	static Color PURPLE;
	static Color YELLOW;
	static Color SHADE_DOWN;
	static Color SHADE_WEST_EAST;
	static Color SHADE_NORTH_SOUTH;
	static Color SHADE_UP;

public:
	float red;		// 0
	float green;	// 4
	float blue;		// 8
	float alpha;	// 12

public:
	Color()=default;
	Color(float r, float g, float b, float a) : red(r), green(g), blue(b), alpha(a) {};
	static Color fromHSB(float, float, float);
	int toARGB()const;
	int toABGR()const;
	bool operator==(Color const&c)
	{
		return red==c.red&&green==c.green&&blue==c.blue&&alpha==c.alpha;
	}
};
