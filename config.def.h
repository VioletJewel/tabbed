/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]        = "FiraCode Nerd Font:pixelsize=14:antialias=true:autohint=true";
static const char* normbgcolor  = "#2f334d";
static const char* normfgcolor  = "#636da6";
static const char* selbgcolor   = "#2d3f76";
static const char* selfgcolor   = "#c8d3f5";
static const char* urgbgcolor   = "#322639";
static const char* urgfgcolor   = "#c53b53";
static const char before[]      = "<";
static const char after[]       = ">";
static const char titletrim[]   = "..";
static const int  tabwidth      = 200;
static const Bool foreground    = True;
static       Bool urgentswitch  = False;
static       Bool showbar       = True;

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int  newposition   = +1;
static Bool npisrelative  = True;

#define SETPROP(p) { \
        .v = (char *[]){ "/bin/sh", "-c", \
                "prop=\"`xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
                "xargs -0 printf %b | dmenu -l 10 -w $1`\" &&" \
                "xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
                p, winid, NULL \
        } \
}

#define MODKEY ControlMask
static const Key keys[] = {
	/* modifier             key        function     argument */
	{ MODKEY|ShiftMask,     XK_Return, focusonce,   { 0 } },
	{ MODKEY|ShiftMask,     XK_Return, spawn,       { 0 } },

	{ MODKEY|ShiftMask,     XK_l,      rotate,      { .i = +1 } },
	{ MODKEY|ShiftMask,     XK_h,      rotate,      { .i = -1 } },
	{ MODKEY|ShiftMask,     XK_j,      movetab,     { .i = +1 } },
	{ MODKEY|ShiftMask,     XK_k,      movetab,     { .i = -1 } },
	{ MODKEY,               XK_Tab,    rotate,      { .i = 0 } },

	{ MODKEY,               XK_grave,  spawn,       SETPROP("_TABBED_SELECT_TAB") },
	{ MODKEY|Mod1Mask,      XK_1,      move,        { .i = 0 } },
	{ MODKEY|Mod1Mask,      XK_2,      move,        { .i = 1 } },
	{ MODKEY|Mod1Mask,      XK_3,      move,        { .i = 2 } },
	{ MODKEY|Mod1Mask,      XK_4,      move,        { .i = 3 } },
	{ MODKEY|Mod1Mask,      XK_5,      move,        { .i = 4 } },
	{ MODKEY|Mod1Mask,      XK_6,      move,        { .i = 5 } },
	{ MODKEY|Mod1Mask,      XK_7,      move,        { .i = 6 } },
	{ MODKEY|Mod1Mask,      XK_8,      move,        { .i = 7 } },
	{ MODKEY|Mod1Mask,      XK_9,      move,        { .i = 8 } },
	{ MODKEY|Mod1Mask,      XK_0,      move,        { .i = 9 } },

	{ MODKEY,               XK_q,      killclient,  { 0 } },

	{ MODKEY|ShiftMask,     XK_u,      focusurgent, { 0 } },
	{ MODKEY|Mod1Mask,      XK_u,      toggle,      { .v = (void*) &urgentswitch } },

	{ Mod1Mask|ShiftMask,   XK_Return, fullscreen,  { 0 } },
	{ MODKEY|Mod1Mask,      XK_l,      togglebar,   { 0 } },
};
