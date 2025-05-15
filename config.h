#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx	= 3;        /* border pixel of windows */
static const unsigned int snap		= 10;       /* snap pixel */
static const unsigned int gappx		= 10;
static const int showbar		= 1;        /* 0 means no bar */
static const int topbar			= 1;        /* 0 means bottom bar */
static const float baropacity		= 0.8;	// IGNORE THIS (replaced)
static const int barspaced		= 0;	    /* 1 means bar will be affected by gaps */
static const unsigned int baralpha	= 0xd0;
static const unsigned int borderalpha = OPAQUE;

static const char *fonts[]		= { "monospace:size=10" };
static const char dmenufont[] 		= "monospace:size=10";
static const char col_gray1[] 		= "#000000";
static const char col_gray2[] 		= "#000000";
static const char col_gray3[] 		= "#ffffff";
static const char col_gray4[] 		= "#000000";
static const char col_cyan[] 		= "#aa6600";
static const char col_cool[]		= "#ff0000";
static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cool  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border*/
	[SchemeNorm] = { OPAQUE, baralpha, 0x00 },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class		inst	title	!tags 	float	mon	cntr */
	{ "pavucontrol",	NULL,	NULL,	0,	1,	-1,	1 },
	{ "copyq",		NULL,	NULL,	0,	1,	-1,	1 },
	{ "SpeedCrunch",	NULL,	NULL,	0,	1,	-1,	1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]		= { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
//static const char *dmenucmd[]		= { "rofi", "-show", "run", NULL};
static const char *termcmd[]		= { "kitty", NULL };
static const char *browsercmd[]		= { "zen-browser", NULL };
static const char *screenshotcmd[]	= { "flameshot", "gui", NULL };
static const char *lockcmd[]		= { "i3lock", "-ti", "/home/azy/.config/wallpaper.png", NULL };
static const char *filemancmd[]		= { "nemo", NULL }; 
static const char *audiocontrols[]	= { "pavucontrol", NULL };
static const char *clipboardcmd[]	= { "copyq", "show", NULL };
static const char *calculatorcmd[]	= { "speedcrunch", NULL };

static const char *audioplay[]		= { "playerctl", "play-pause", NULL };
static const char *audiopause[]		= { "playerctl", "pause", NULL };
static const char *audionext[]		= { "playerctl", "next", NULL };
static const char *audioprev[]		= { "playerctl", "previous", NULL };
//static const char *audiostop[]		= { "playerctl", "stop", NULL };
static const char *raisevolume[]	= { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+1%", NULL };
static const char *lowervolume[]	= { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-1%", NULL };
static const char *mutevolume[]		= { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };

static const char *quitcmd[]		= { "systemctl", "poweroff", NULL };

/* keys */
static const Key keys[] = {
	/* modifier			key		function        argument */
	{ MODKEY,		XK_p,		spawn,		{.v = dmenucmd } },
	{ MODKEY|ShiftMask,	XK_Return,	spawn,		{.v = termcmd } },
	{ MODKEY,		XK_y,		spawn,		{.v = browsercmd } },
	{ MODKEY|ShiftMask,	XK_s,		spawn,		{.v = screenshotcmd } },
	{ MODKEY|ShiftMask,	XK_a,		spawn,		SHCMD("scrot -e 'xclip -selection clipboard -t image/png <$f' -F /home/azy/Pictures/Screenshots/all") },
	{ MODKEY|ShiftMask,	XK_w,		spawn,		SHCMD("scrot -ue 'xclip -selection clipboard -t image/png <$f' -F /home/azy/Pictures/Screenshots/window") },
	{ MODKEY,		XK_n,		spawn,		{.v = filemancmd } },
	{ MODKEY,		XK_g,		spawn,		{.v = audiocontrols } },
	{ MODKEY,		XK_v,		spawn,		{.v = clipboardcmd } },
	{ MODKEY,		XK_o,		spawn,		{.v = calculatorcmd } },

	{ 0,			XF86XK_AudioPlay,	spawn,	{.v = audioplay } },
	{ 0,			XF86XK_AudioPause,	spawn,	{.v = audiopause } },
	{ 0,			XF86XK_AudioNext,	spawn,	{.v = audionext } },
	{ 0,			XF86XK_AudioPrev,	spawn,	{.v = audioprev } },
//	{ 0,			XF86XK_AudioStop,	spawn,	{.v = audiostop } }, /* annoying */

	{ 0,			XF86XK_AudioRaiseVolume,spawn,	{.v = raisevolume } },
	{ 0,			XF86XK_AudioLowerVolume,spawn,	{.v = lowervolume } },
	{ 0,			XF86XK_AudioMute,	spawn,	{.v = mutevolume } },

	{ MODKEY,               XK_j,		focusstack,	{.i = +1 } },
	{ MODKEY,               XK_k,		focusstack,	{.i = -1 } },
	{ MODKEY|ShiftMask,	XK_m,		focusmaster,	{0} },		
	{ MODKEY,               XK_i,		incnmaster,     {.i = +1 } },
	{ MODKEY,               XK_u,		incnmaster,     {.i = -1 } },
	{ MODKEY,               XK_h,		setmfact,       {.f = -0.05} },
	{ MODKEY,               XK_l,		setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,     XK_c,		killclient,     {0} },

	{ MODKEY,               XK_t,		setlayout,      {.v = &layouts[0]} },
	{ MODKEY,               XK_f,		setlayout,      {.v = &layouts[1]} },
	{ MODKEY,               XK_m,		setlayout,	{.v = &layouts[2]} },
	{ MODKEY,		XK_r,		togglefullscr,	{0} },
	{ MODKEY,		XK_b,		togglebar, 	{0} },
	{ MODKEY,		XK_space,	togglefloating, {0} },

	{ MODKEY,               XK_Return,	zoom,           {0} },
	{ MODKEY,               XK_Tab,		view,           {0} },
	{ MODKEY,               XK_0,		view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,		tag,            {.ui = ~0 } },
	{ MODKEY,               XK_comma,	focusmon,       {.i = -1 } },
	{ MODKEY,               XK_period,	focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_comma,	tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_period,	tagmon,         {.i = +1 } },

	{ MODKEY|ShiftMask,	XK_Delete,	spawn,		{.v = lockcmd } },
	{ MODKEY|ShiftMask|ControlMask|Mod1Mask,	XK_Delete,	spawn,	{.v = quitcmd } },

	TAGKEYS(		XK_1,				0)
	TAGKEYS(		XK_2,				1)
	TAGKEYS(		XK_3,				2)
	TAGKEYS(		XK_4,				3)
	TAGKEYS(		XK_5,				4)
	TAGKEYS(		XK_6,				5)
	TAGKEYS(		XK_7,				6)
	TAGKEYS(		XK_8,				7)
	TAGKEYS(		XK_9,				8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

