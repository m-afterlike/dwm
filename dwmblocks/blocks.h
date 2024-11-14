static const Block blocks[] = {
	/*Icon*/	/*Command*/												/*Update Interval*/	/*Update Signal*/
	{"^c#ea9a97^  ", "/home/m/.config/dwmblocks/scripts/spotify.sh",	1,					10},
	{"^c#e0def4^", "/home/m/.config/dwmblocks/scripts/volume.sh",		0,					4},
	{"^c#e0def4^", "/home/m/.config/dwmblocks/scripts/ethernet.sh",		5,					2},
	{"^c#e0def4^󰃰  ", "/home/m/.config/dwmblocks/scripts/time.sh",		 1,		 			 1},

};

// sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 3;
