static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"", "/home/m/.config/dwmblocks/scripts/spotify.sh",	1,		6},
	{"", "/home/m/.config/dwmblocks/scripts/volume.sh",		0,		4},
	{"", "/home/m/.config/dwmblocks/scripts/ethernet.sh",	5,		2},
	{"", "/home/m/.config/dwmblocks/scripts/time.sh",		1,		1},

};

// sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " ";
static unsigned int delimLen = 5;