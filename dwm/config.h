/* See LICENSE file for copyright and license details. */
#include <math.h>

/* alt-tab configuration */
static const unsigned int tabModKey 		= 0x40;	/* if this key is hold the alt-tab functionality stays acitve. This key must be the same as key that is used to active functin altTabStart `*/
static const unsigned int tabCycleKey 		= 0x17;	/* if this key is hit the alt-tab program moves one position forward in clients stack. This key must be the same as key that is used to active functin altTabStart */
static const unsigned int tabPosY 			= 1;	/* tab position on Y axis, 0 = bottom, 1 = center, 2 = top */
static const unsigned int tabPosX 			= 1;	/* tab position on X axis, 0 = left, 1 = center, 2 = right */
static const unsigned int maxWTab 			= 600;	/* tab menu width */
static const unsigned int maxHTab 			= 200;	/* tab menu height */

/* appearance */
static const unsigned int borderpx  = 2;        	/* border pixel of windows */
static const unsigned int snap      = 32;       	/* snap pixel */
static const unsigned int systraypinning = 0;  		/* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   	/* systray spacing */
static const int systraypinningfailfirst = 1;   	/* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 0;            /* 0 means no systray */
static const int rightpadding 		= 10; 			/* right side bar padding */
static const unsigned int gappih    = 10;      		/* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       	/* vert inner gap between windows */
static const unsigned int gappoh    = 10;       	/* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       	/* vert outer gap between windows and screen edge */
static int smartgaps        	    = 0;        	/* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        	/* 0 means no bar */
static const int topbar             = 1;        	/* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono NF:size=11", "Noto Sans CJK:size=11" };
static const char dmenufont[]       = "JetBrains Mono:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_background[]  = "#232136";
static const char col_foreground[]  = "#393552";
static const char col_primary[]     = "#e0def4";
static const char col_secondary[]   = "#ea9a97";
static const char *colors[][3]      = {
	/*               fg         	 bg         	 border   */
	[SchemeNorm] = { col_primary, 	 col_background, col_background },
	[SchemeSel]  = { col_foreground, col_secondary,  col_secondary  },
	[SchemeLay]	 = { col_secondary,  col_background, col_secondary  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,       NULL,       NULL,       0,            False,       -1 },
};

/* layout(s) */
static const float mfact     = 0.55; 				/* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    				/* number of clients in master area */
static const int resizehints = 0;    				/* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; 				/* 1 will force focus on the fullscreen window */
#define FORCE_VSPLIT 1  							/* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol   arrange function */
	{ "󰕰",    tile }, 							 /* dwindle */
	{ "", 	NULL }, 	   						/* floating */
	{ "",  	monocle }, 							/* monocle */
	{ "",  	dwindle }, 							/* dwindle */
};

/* functions */
static const Layout *previouslayout = NULL;

void
monoclelayout(const Arg *arg) {
    if (selmon->lt[selmon->sellt] != &layouts[2]) {  /* if not in monocle */
        previouslayout = selmon->lt[selmon->sellt];  /* save current layout */
        setlayout(&((Arg) { .v = &layouts[2] }));    /* set to monocle */
    } else {
        setlayout(&((Arg) { .v = previouslayout })); /* revert to prev layout*/
    }
}

void
dwindlelayout(const Arg *arg) {
    if (selmon->lt[selmon->sellt] != &layouts[3]) {  /* if not in dwindle */
        previouslayout = selmon->lt[selmon->sellt];  /* save current layout */
        setlayout(&((Arg) { .v = &layouts[3] }));    /* set to dwindle */
    } else {
        setlayout(&((Arg) { .v = previouslayout })); /* revert to prev layout*/
    }
}

void
floatinglayout(const Arg *arg) {
    if (selmon->lt[selmon->sellt] != &layouts[1]) {  /* if not in floating */
        previouslayout = selmon->lt[selmon->sellt];  /* save current layout */
        setlayout(&((Arg) { .v = &layouts[1] }));    /* set to floating */
    } else {
        setlayout(&((Arg) { .v = previouslayout })); /* revert to prev layout*/
    }
}

void
focusdir(const Arg *arg) {
    if (!selmon->sel)
        return;

    Client *c = NULL, *closest = NULL;
    int mindistance = INT_MAX;
    int direction = arg->i;  /* 0 = up, 1 = down, 2 = left, 3 = right */
    int cx = selmon->sel->x + selmon->sel->w / 2;
    int cy = selmon->sel->y + selmon->sel->h / 2;

    for (c = selmon->clients; c; c = c->next) {
        if (c == selmon->sel || !ISVISIBLE(c))
            continue;
        
        int tx = c->x + c->w / 2;
        int ty = c->y + c->h / 2;

        int distance = (tx - cx) * (tx - cx) + (ty - cy) * (ty - cy);

        if ((direction == 0 && ty < cy && abs(tx - cx) < abs(ty - cy)) ||     /* up */
            (direction == 1 && ty > cy && abs(tx - cx) < abs(ty - cy)) ||     /* down */
            (direction == 2 && tx < cx && abs(ty - cy) < abs(tx - cx)) ||     /* left */
            (direction == 3 && tx > cx && abs(ty - cy) < abs(tx - cx))) {     /* right */
            if (distance < mindistance) {
                mindistance = distance;
                closest = c;
            }
        }
    }
    if (closest)
        focus(closest);
}

/* key definitions */
#define MODKEY Mod1Mask
#define SUPER Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ SUPER,                        KEY,      view,           {.ui = 1 << TAG} }, \
	{ SUPER|ShiftMask,              KEY,      tag,            {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "drun", "-modi", "drun", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *sscmd[] = { "flameshot", "gui", "-c", "-p", "~/Pictures/Screenshots", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument 				usage*/
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },		/* open search menu */
	{ MODKEY,                       XK_1,      spawn,          {.v = termcmd } },		/* open terminal */
	{ SUPER|ShiftMask,              XK_s,      spawn,          {.v = sscmd } }, 		/* open screenshot */
	{ MODKEY,                       XK_b,      togglebar,      {0} },					/* toggle top bar */
	{ MODKEY,           			XK_i,      focusdir,       {.i = 0 } },  			/* focus up */
	{ MODKEY,           			XK_k,      focusdir,       {.i = 1 } },  			/* focus down*/
	{ MODKEY,           			XK_j,      focusdir,       {.i = 2 } },  			/* focus left*/
	{ MODKEY,           			XK_l,      focusdir,       {.i = 3 } },  			/* focus right */
	{ MODKEY|ShiftMask,             XK_equal,  incnmaster,     {.i = +1 } },			/* increase # of windows in master */
	{ MODKEY|ShiftMask,             XK_minus,  incnmaster,     {.i = -1 } },			/* decrease # of windows in master */
	{ MODKEY,                       XK_minus,  setmfact,       {.f = -0.05} },			/* decrease master size by 5% */
	{ MODKEY,                       XK_equal,  setmfact,       {.f = +0.05} },			/* increase master size by 5% */
	{ MODKEY,                       XK_Return, zoom,           {0} },					/* make currently focused window take master position */
	{ MODKEY,                       XK_q,      killclient,     {0} },					/* close the current window */
	{ MODKEY|ShiftMask,             XK_f,      floatinglayout, {0} },					/* set layout to floating */
	{ MODKEY|ShiftMask,             XK_Return, monoclelayout,  {0} },					/* set layout to monocle */
	{ MODKEY|ShiftMask,             XK_d,      dwindlelayout,  {0} },					/* set layout to dwindle */
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },	/* set layout to tile/reset */
	{ MODKEY,		                XK_f,      togglefloating, {0} },					/* toggle floating for focused window */
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },			/* view all tags at once */
	{ MODKEY,                       XK_Left,   focusmon,       {.i = -1 } },			/* focus left monitor */
	{ MODKEY,                       XK_Right,  focusmon,       {.i = +1 } },			/* focus right monitor */
	{ MODKEY|ShiftMask,             XK_Left ,  tagmon,         {.i = -1 } },			/* move current tag to monitor on the left */
	{ MODKEY|ShiftMask,             XK_Right,  tagmon,         {.i = +1 } },			/* move current tag to monitor on the right */

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },					/* quit dwm */
	{ MODKEY,                       XK_Tab,    altTabStart,    {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
};