/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "Droid Sans Mono:pixelsize=14";
static const char normbordercolor[] = "#222222";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#00DDFF";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int gappx     = 4;        /* gap pixel between windows */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const Bool showsystray       = True;     /* False means no systray */
static const double shade           = 0.9;      /* opacity of unfocussed clients */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "h_web", "j_work", "k_com", "l_misc" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor   opacity */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1,       -1 }
};

/* layout(s) */
static const float mfact      = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

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
static const char *dmenucmd[]   = { "dmenu_run", /*"-m", dmenumon, "-fn", font,*/ "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]    = { "st", NULL };
static const char *kbdcmd[]     = { "sh", "-c", "killall svkbd-de || svkbd-de -d -g 1920x400", NULL };
static const char *ctrlcmd[]     = { "sh", "-c", "killall svkbd-ctrl || svkbd-ctrl -d -g 1920x100+0+20", NULL };
static const char *surfcmd[]    = { "sh", "-c", "gosurf", NULL };
static const char *suspendcmd[] = { "systemctl", "suspend", NULL};
static const char *domiddlecmd[] = { "xdotool", "click", "2", NULL };

static Key keys[] = {
	/* modifier                     key               function        argument */
	{ 0,                            XK_F12,           spawn,          {.v = dmenucmd } },
	{ 0,                            XK_KP_Add,        spawn,          {.v = surfcmd } },
	{ MODKEY,                       XK_plus,          spawn,          {.v = surfcmd } },
	{ MODKEY,                       XK_Escape,        spawn,          {.v = suspendcmd } },
	{ 0,                            XK_Print,         spawn,          {.v = termcmd } },
	{ 0,                            XK_KP_Multiply,   spawn,          {.v = dmenucmd } },
	{ 0,                            XK_KP_Divide,     spawn,          {.v = termcmd } },
	
	{ 0,                            XK_Menu,          spawn,          {.v = domiddlecmd } },     

	{ MODKEY,                       XK_b,             togglebar,      {0} },
	{ MODKEY,                       XK_Down,          focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Up,            focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,             incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,             incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_Right,         setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Left,          setmfact,       {.f = +0.05} },
	{ 0,                            XK_KP_Delete,     focusstack,     {.i = +1 } },
	{ 0,                            XK_KP_Next,       focusstack,     {.i = -1 } },
	{ 0,                            XK_KP_Prior,      incnmaster,     {.i = +1 } },
	{ 0,                            XK_KP_Right,      incnmaster,     {.i = -1 } },
	{ 0,                            XK_KP_End,        setmfact,       {.f = -0.05} },
	{ 0,                            XK_KP_Down,       setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,         zoom,           {0} },
	{ 0,				XK_KP_Enter,      zoom, 	  {0} },
	{ MODKEY,                       XK_Tab,           focusstack,     {.i = +1 } },
	{ 0,                            XK_Pause,         killclient,     {0} },
	{ 0,                            XK_KP_Subtract,   killclient,     {0} },
	{ 0,                            XK_KP_Begin,      setlayout,      {.v = &layouts[0]} },
	{ 0,                            XK_KP_Home,       setlayout,      {.v = &layouts[1]} },
	{ 0,                            XK_KP_Up,         setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_t,             setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,             setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,             setlayout,      {.v = &layouts[2]} },
	{ 0,                            XK_KP_Left,       togglefloating, {0} },
	{ MODKEY,                       XK_0,             view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,             tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,         focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,        focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,         tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,        tagmon,         {.i = +1 } },
	{ 0,                            XK_KP_Insert,     tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_KP_Insert,     focusmon,       {.i = +1 } },
	{ ControlMask,                  XK_KP_Insert,     focusmon,       {.i = +1 } },
	{ MODKEY | ShiftMask,           XK_m,             focusmon,       {.i = +1 } },
	TAGKEYS(                        XK_h,                      0)
	TAGKEYS(                        XK_j,                      1)
	TAGKEYS(                        XK_k,                      2)
	TAGKEYS(                        XK_l,                      3)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        spawn,          {.v = ctrlcmd } },
	{ ClkWinTitle,          0,              Button2,        killclient,     {0} },
	{ ClkWinTitle,          0,              Button4,        focusstack,     {.i = +1} },
	{ ClkWinTitle,          0,              Button5,        focusstack,     {.i = -1} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = kbdcmd  } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

