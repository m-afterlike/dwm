/* See LICENSE file for copyright and license details. */

/* Helper macros for spawning commands */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define CMD(...)   { .v = (const char*[]){ __VA_ARGS__, NULL } }
#define TAGSROWS 1

/* appearance */
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const unsigned int gappih         = 10;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 10;  /* vert inner gap between windows */
static const unsigned int gappoh         = 10;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 10;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 1;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const int bar_height              = 0;   /* 0 means derive from font, >= 1 explicit height */
#define ICONSIZE 15    /* icon size */
#define ICONSPACING 10  /* space between icon and title */
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = -1;
static const int horizpadbar             = 0;    /* horizontal padding for statusbar */
static const int vertpadbar              = 10;   /* vertical padding for statusbar */
static const char buttonbar[]            = "";

/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_TOP_BAR_SLIM;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_NONE;
static const char *fonts[]               = { "SF Pro Text:size=11", "PingFang SC:size=11:style=Regular", "PingFang SC:size=11:style=SemiBold", "Symbols Nerd Font:size=12" };
static const char dmenufont[]            = "SF Pro Text:size=11";

static char c000000[]                    = "#000000"; // placeholder value

static char normfgcolor[]                = "#d4be98";
static char normbgcolor[]                = "#1b1b1b";
static char normbordercolor[]            = "#3c3836";
static char normfloatcolor[]             = "#3c3836";

static char selfgcolor[]                 = "#ddc7a1";
static char selbgcolor[]                 = "#32302f";
static char selbordercolor[]             = "#ddc7a1";
static char selfloatcolor[]              = "#ddc7a1";

static char titlenormfgcolor[]           = "#d4be98";
static char titlenormbgcolor[]           = "#1b1b1b";
static char titlenormbordercolor[]       = "#3c3836";
static char titlenormfloatcolor[]        = "#3c3836";

static char titleselfgcolor[]            = "#ddc7a1";
static char titleselbgcolor[]            = "#32302f";
static char titleselbordercolor[]        = "#ddc7a1";
static char titleselfloatcolor[]         = "#ddc7a1";

static char tagsnormfgcolor[]            = "#d4be98";
static char tagsnormbgcolor[]            = "#1b1b1b";
static char tagsnormbordercolor[]        = "#3c3836";
static char tagsnormfloatcolor[]         = "#3c3836";

static char tagsselfgcolor[]             = "#ddc7a1";
static char tagsselbgcolor[]             = "#32302f";
static char tagsselbordercolor[]         = "#ddc7a1";
static char tagsselfloatcolor[]          = "#ddc7a1";

static char hidnormfgcolor[]             = "#d4be98";
static char hidselfgcolor[]              = "#1b1b1b";
static char hidnormbgcolor[]             = "#3c3836";
static char hidselbgcolor[]              = "#3c3836";

static char urgfgcolor[]                 = "#d4be98";
static char urgbgcolor[]                 = "#1b1b1b";
static char urgbordercolor[]             = "#3c3836";
static char urgfloatcolor[]              = "#3c3836";

static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]     = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};

static char *tagicons[][NUMTAGS*2] =
{
	[DEFAULT_TAGS]        = { "一", "二", "三", "四", "五", "一", "二", "三", "四", "五" },
};

/* A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */

static const Rule rules[] = {
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.class = "io.elementary.desktop.agent-polkit", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.class = "Spotify", .tags = 1 << 1, .monitor = 1)
	RULE(.class = "vesktop", .tags = 1 << 0)
};

/*    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */

static const BarRule barrules[] = {
	/* monitor   bar    alignment         widthfunc                 drawfunc                clickfunc                hoverfunc                name */
	{ -1,        0,     BAR_ALIGN_LEFT,   width_stbutton,           draw_stbutton,          click_stbutton,          NULL,                    "statusbutton" },
	{ -1,        0,     BAR_ALIGN_LEFT,   width_tags,               draw_tags,              click_tags,              hover_tags,              "tags" },
	{ -1,        0,     BAR_ALIGN_LEFT,   width_ltsymbol,           draw_ltsymbol,          click_ltsymbol,          NULL,                    "layout" },
	{ statusmon, 0,     BAR_ALIGN_RIGHT,  width_status2d,           draw_status2d,          click_statuscmd,         NULL,                    "status2d" },
	{ -1,        0,     BAR_ALIGN_NONE,   width_wintitle,           draw_wintitle,          click_wintitle,          NULL,                    "wintitle" },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol		arrange function */
	{ "􀧉",			 tile },
	{ "􀅊",			monocle },
	{ "􀧍",			dwindle },
	{ "􀾋",			NULL },
};


/* functions */
static const Layout *previouslayout = NULL;

void
monoclelayout(const Arg *arg) {
    if (selmon->lt[selmon->sellt] != &layouts[1]) {  /* if not in monocle */
        previouslayout = selmon->lt[selmon->sellt];  /* save current layout */
        setlayout(&((Arg) { .v = &layouts[1] }));    /* set to monocle */
    } else {
        setlayout(&((Arg) { .v = previouslayout })); /* revert to prev layout*/
    }
}

void
dwindlelayout(const Arg *arg) {
    if (selmon->lt[selmon->sellt] != &layouts[2]) {  /* if not in dwindle */
        previouslayout = selmon->lt[selmon->sellt];  /* save current layout */
        setlayout(&((Arg) { .v = &layouts[2] }));    /* set to dwindle */
    } else {
        setlayout(&((Arg) { .v = previouslayout })); /* revert to prev layout*/
    }
}

void
floatinglayout(const Arg *arg) {
    if (selmon->lt[selmon->sellt] != &layouts[3]) {  /* if not in floating */
        previouslayout = selmon->lt[selmon->sellt];  /* save current layout */
        setlayout(&((Arg) { .v = &layouts[3] }));    /* set to floating */
    } else {
        setlayout(&((Arg) { .v = previouslayout })); /* revert to prev layout*/
    }
}

void
cyclelayout(const Arg *arg) {
    int i;
    for (i = 0; &layouts[i] != selmon->lt[selmon->sellt]; i++);
    
    if (layouts[i + 1].arrange != NULL) { // if next layout exists
        setlayout(&(Arg) { .v = &layouts[i + 1] });
    } else {
        setlayout(&(Arg) { .v = &layouts[0] }); // wrap to the first layout
    }
}

/* key definitions */
#define MODKEY Mod1Mask
#define SUPER Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ SUPER,                        KEY,      view,           {.ui = 1 << TAG} }, \
	{ SUPER|ShiftMask,              KEY,      tag,            {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
	"dmenu_run",
	"-m", dmenumon,
	"-fn", dmenufont,
	"-nb", normbgcolor,
	"-nf", normfgcolor,
	"-sb", selbgcolor,
	"-sf", selfgcolor,
	NULL
};
static const char *termcmd[]  = { "kitty", NULL };

static const StatusCmd statuscmds[] = {
    { "/home/m/.config/dwm/status/statusbar.sh $BUTTON SPOTIFY", 1 },
    { "/home/m/.config/dwm/status/statusbar.sh $BUTTON VOLUME", 2 },
    { "/home/m/.config/dwm/status/statusbar.sh $BUTTON ETHERNET", 3 },
    { "/home/m/.config/dwm/status/statusbar.sh $BUTTON TIME", 4 },
};

static const char *statuscmd[] = { "/bin/sh", "-c", NULL, NULL };
static const char *sscmd[] = { "flameshot", "gui", "-c", "-p", "/home/m/Pictures/Screenshots", NULL };

static const Key keys[] = {
	/* modifier                     key             function                argument */
	{ MODKEY,                       XK_space,		spawn,                  {.v = dmenucmd } },
	{ MODKEY,             			XK_1,			spawn,                  {.v = termcmd } },
	{ SUPER|ShiftMask,              XK_s,      		spawn,          		{.v = sscmd } },
	// { MODKEY,                       XK_b,		  togglebar,              {0} },
	// { MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
	// { MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
	{ MODKEY,                       XK_j,			focusdir,               {.i = 0 } }, // left
	{ MODKEY,                       XK_l,			focusdir,               {.i = 1 } }, // right
	{ MODKEY,                       XK_i,			focusdir,               {.i = 2 } }, // up
	{ MODKEY,                       XK_k,			focusdir,               {.i = 3 } }, // down
	// { MODKEY,                       XK_=,          incnmaster,             {.i = +1 } },
	// { MODKEY,                       XK_-,          incnmaster,             {.i = -1 } },
	{ MODKEY,                       XK_minus,		setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_equal,		setmfact,               {.f = +0.05} },
	{ MODKEY,                       XK_Return,		zoom,                   {0} },
	// { MODKEY|Mod4Mask,              XK_u,          incrgaps,               {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_u,          incrgaps,               {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_i,          incrigaps,              {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_i,          incrigaps,              {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_o,          incrogaps,              {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_o,          incrogaps,              {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_6,          incrihgaps,             {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_6,          incrihgaps,             {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_7,          incrivgaps,             {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_7,          incrivgaps,             {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_8,          incrohgaps,             {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_8,          incrohgaps,             {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_9,          incrovgaps,             {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_9,          incrovgaps,             {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_0,          togglegaps,             {0} },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_0,          defaultgaps,            {0} },
	// { MODKEY,                       XK_Tab,        view,                   {0} },
	{ MODKEY,             			XK_q,			killclient,             {0} },
	{ MODKEY|ShiftMask,             XK_q,			quit,                   {0} },
	{ MODKEY|ShiftMask,             XK_f,			floatinglayout, 		{0} },
	{ MODKEY|ShiftMask,             XK_Return,		monoclelayout,  		{0} },
	{ MODKEY|ShiftMask,             XK_d,			dwindlelayout,  		{0} },
	{ MODKEY|ShiftMask,             XK_t,			setlayout,      		{.v = &layouts[0]} },
	// { MODKEY,                       XK_f,          setlayout,              {.v = &layouts[1]} },
	// { MODKEY,                       XK_m,          setlayout,              {.v = &layouts[2]} },
	// { MODKEY,                       XK_space,	  setlayout,              {0} },
	{ MODKEY,             			XK_f,      		togglefloating,         {0} },
	{ MODKEY,                       XK_0,			view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,			tag,                    {.ui = ~0 } },
	{ MODKEY,                       XK_Right,		focusmon,               {.i = -1 } },
	{ MODKEY,                       XK_Left,		focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Right,		tagmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,		tagmon,                 {.i = +1 } },
	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	// TAGKEYS(                        XK_6,                                  5)
	// TAGKEYS(                        XK_7,                                  6)
	// TAGKEYS(                        XK_8,                                  7)
	// TAGKEYS(                        XK_9,                                  8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask           button          function        argument */
    { ClkButton,            0,                   Button1,        spawn,          {.v = termcmd } },
    { ClkButton,            0,                   Button3,        spawn,          {.v = dmenucmd } },
	{ ClkLtSymbol,          0,                   Button1,        cyclelayout,    {.i = +1} }, // Left-click cycles forward
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[0]} }, // Right-click resets to default
    { ClkWinTitle,          0,                   Button2,        zoom,           {0} },
    { ClkStatusText,        0,                   Button1,        spawn,          {.v = statuscmd } },
    { ClkStatusText,        0,                   Button2,        spawn,          {.v = statuscmd } },
    { ClkStatusText,        0,                   Button3,        spawn,          {.v = statuscmd } },
    { ClkStatusText,        0,                   Button4,        spawn,          {.v = statuscmd } }, // Scroll up
    { ClkStatusText,        0,                   Button5,        spawn,          {.v = statuscmd } }, // Scroll down
    { ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,                   Button1,        view,           {0} },
    { ClkTagBar,            0,                   Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};