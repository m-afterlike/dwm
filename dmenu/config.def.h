/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom */
static int center = 1;                      /* -c  option; if 0, dmenu won't be centered on the screen */
static int min_width = 500;                 /* minimum width when centered */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] =
{
	"SF Pro Text:size=12"
};
static const char *prompt      = "􀊫";      /* -p  option; prompt to the left of input field */
// static const char *prompt      = NULL;
static
const
char *colors[][2] = {
	/*               fg         bg       */
	[SchemeNorm] = { "#d4be98", "#1b1b1b" },
	[SchemeSel]  = { "#ddc7a1", "#32302f" },
	[SchemeOut]  = { "#d4be98", "#1b1b1b" },
	[SchemeHp]   = { "#d4be98", "#1b1b1b" },
};

/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 10;
/* -g option; if nonzero, dmenu uses a grid comprised of columns and lines */
static unsigned int columns    = 1;
static unsigned int lineheight = 32;         /* -h option; minimum height of a menu line     */
static unsigned int min_lineheight = 32;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";