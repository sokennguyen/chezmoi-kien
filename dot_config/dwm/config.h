/* See LICENSE file for copyright and license details. */
#define BROWSER "brave"
#define TERMINAL "st"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=16" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_green[]        = "#00FF00";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_green,  col_green  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_green, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,		        XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,		        XK_w,	   spawn,          {.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY|ShiftMask,	        XK_w,	   spawn,          {.v = (const char*[]){ TERMINAL, "-e", "sudo", "nmtui", NULL } } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_i,	   setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	{ 0, XF86XK_AudioMute,                         spawn,                  SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,                  spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%- && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%+; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,                  spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%+ && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%-; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,                         spawn,                  {.v = (const char*[]){ "mpc", "prev", NULL } } },
	{ 0, XF86XK_AudioNext,                         spawn,                  {.v = (const char*[]){ "mpc",  "next", NULL } } },
	{ 0, XF86XK_AudioPause,                        spawn,                  {.v = (const char*[]){ "mpc", "pause", NULL } } },
	{ 0, XF86XK_AudioPlay,                         spawn,                  {.v = (const char*[]){ "mpc", "play", NULL } } },
	{ 0, XF86XK_AudioStop,                         spawn,                  {.v = (const char*[]){ "mpc", "stop", NULL } } },
	{ 0, XF86XK_AudioRewind,                       spawn,                  {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	{ 0, XF86XK_AudioForward,                      spawn,                  {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
	{ 0, XF86XK_AudioMedia,                        spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	{ 0, XF86XK_AudioMicMute,                      spawn,                  SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	/* { 0, XF86XK_PowerOff,                       spawn,                  {.v = (const char*[]){ "sysact", NULL } } }, */
	{ 0, XF86XK_Calculator,                        spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "bc", "-l", NULL } } },
	{ 0, XF86XK_Sleep,                             spawn,                  {.v = (const char*[]){ "sudo", "-A", "zzz", NULL } } },
	{ 0, XF86XK_WWW,                               spawn,                  {.v = (const char*[]){ BROWSER, NULL } } },
	{ 0, XF86XK_DOS,                               spawn,                  {.v = termcmd } },
	{ 0, XF86XK_ScreenSaver,                       spawn,                  SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,                          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	{ 0, XF86XK_Mail,                              spawn,                  SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,                        spawn,                  {.v = (const char*[]){ TERMINAL, "-e",  "lfub",  "/", NULL } } },
	/* { 0, XF86XK_Battery,                        spawn,                  SHCMD("") }, */
	{ 0, XF86XK_Launch1,                           spawn,                  {.v = (const char*[]){ "xset", "dpms", "force", "off", NULL } } },
	{ 0, XF86XK_TouchpadToggle,                    spawn,                  SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,                       spawn,                  {.v = (const char*[]){ "synclient", "TouchpadOff=1", NULL } } },
	{ 0, XF86XK_TouchpadOn,                        spawn,                  {.v = (const char*[]){ "synclient", "TouchpadOff=0", NULL } } },
	{ 0, XF86XK_MonBrightnessUp,                   spawn,                  {.v = (const char*[]){ "xbacklight", "-inc", "15", NULL } } },
	{ 0, XF86XK_MonBrightnessDown,                 spawn,                  {.v = (const char*[]){ "xbacklight", "-dec", "15", NULL } } },


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

