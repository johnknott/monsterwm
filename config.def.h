/* see LICENSE for copyright and license */

#ifndef CONFIG_H
#define CONFIG_H

#define CLEANMASK(mask) (mask & ~(numlockmask | LockMask))

/** buttons **/
#define MOD1            Mod1Mask    /* ALT key */
#define MOD4            Mod4Mask    /* Super/Windows key */
#define CONTROL         ControlMask /* Control key */
#define SHIFT           ShiftMask   /* Shift key */

/** generic settings **/
#define MASTER_SIZE     0.52
#define SHOW_PANEL      True      /* show panel by default on exec */
#define TOP_PANEL       True      /* False mean panel is on bottom */
#define PANEL_HEIGHT    18        /* 0 for no space for panel, thus no panel */
#define DEFAULT_MODE    TILE      /* TILE MONOCLE BSTACK GRID */
#define ATTACH_ASIDE    True      /* False means new window is master */
#define FOLLOW_MOUSE    False     /* Focus the window the mouse just entered */
#define FOLLOW_WINDOW   False     /* Follow the window when moved to a different desktop */
#define CLICK_TO_FOCUS  False     /* Focus an unfocused window when clicked */
#define BORDER_WIDTH    2         /* window border width */
#define FOCUS           "#ff950e" /* focused window border color   */
#define UNFOCUS         "#444444" /* unfocused window border color */
#define DESKTOPS        4         /* number of desktops - edit DESKTOPCHANGE keys to suit */
#define DEFAULT_DESKTOP 0         /* the desktop to focus on exec */
#define MINWSZ          50        /* minimum window size in pixels */

/** open applications to specified desktop **/
/*
 * desktop is the desktop in which the application with the given class/classname will be spawned,
 *         if follow is set or fetch is not set. if fetch is set then the current desktop is used.
 *         desktop index starts from 0.
 * follow  means that the application with the given class will be spawned on the given desktop,
 *         and desktop focus will change to that desktop.
 * fetch   means that if an application with the given class is already open, it will be moved to
 *         the specified desktop, if follow is set, otherwise to the current desktop
 *
 * in the example below:
 *   if app1 isn't opened, it will open on desktop 0 and desktop focus will change to that desktop
 *   if app1 is open, then it will be moved to desktop 0 and the focus will change to that desktop
 *   app2 will open on desktop 1, and desktop focus will change to that desktop
 *   if app3 isn't opened, it will be opened on the current desktop
 *   if app3 is open, then, it will be moved to the current desktop
 *   app4 will open on desktop 3, and focus will stay on current desktop
 */
static const AppRule rules[] = { \
    /* class    desktop   follow   fetch  */
    { "app1",      0,     True,    True,  },
    { "app2",      1,     True,    False, },
    { "app3",      2,     False,   True,  },
    { "app4",      3,     False,   False, },
};

/* helper for spawning shell commands */
#define SHCMD(cmd) {.com = (const char*[]){"/bin/sh", "-c", cmd, NULL}}

/** commands **/
static const char *termcmd[]  = { "xterm", NULL };
static const char *dmenucmd[] = { "dmenu", NULL };

#define DESKTOPCHANGE(K,N) \
    {  MOD1,             K,              change_desktop, {.i = N}}, \
    {  MOD1|ShiftMask,   K,              client_to_desktop, {.i = N}},

/** Shortcuts **/
static key keys[] = {
    /* modifier          key            function           argument */
    {  MOD1,             XK_b,          togglepanel,       {NULL}},
    {  MOD1,             XK_BackSpace,  focusurgent,       {NULL}},
    {  MOD1|SHIFT,       XK_c,          killclient,        {NULL}},
    {  MOD1,             XK_j,          next_win,          {NULL}},
    {  MOD1,             XK_k,          prev_win,          {NULL}},
    {  MOD1,             XK_h,          resize_master,     {.i = -10}}, /* decrease */
    {  MOD1,             XK_l,          resize_master,     {.i = +10}}, /* increase */
    {  MOD1,             XK_o,          resize_stack,      {.i = -10}}, /* shrink */
    {  MOD1,             XK_p,          resize_stack,      {.i = +10}}, /* grow   */
    {  MOD1|SHIFT,       XK_Left,       rotate_desktop,    {.i = -1}},  /* prev */
    {  MOD1|SHIFT,       XK_Right,      rotate_desktop,    {.i = +1}},  /* next */
    {  MOD1,             XK_Tab,        last_desktop,      {NULL}},
    {  MOD1,             XK_Return,     swap_master,       {NULL}},
    {  MOD1|SHIFT,       XK_j,          move_down,         {NULL}},
    {  MOD1|SHIFT,       XK_k,          move_up,           {NULL}},
    {  MOD1|SHIFT,       XK_t,          switch_mode,       {.i = TILE}},
    {  MOD1|SHIFT,       XK_m,          switch_mode,       {.i = MONOCLE}},
    {  MOD1|SHIFT,       XK_b,          switch_mode,       {.i = BSTACK}},
    {  MOD1|SHIFT,       XK_g,          switch_mode,       {.i = GRID}},
    {  MOD1|CONTROL,     XK_r,          quit,              {.i = 0}}, /* quit with exit value 0 */
    {  MOD1|CONTROL,     XK_q,          quit,              {.i = 1}}, /* quit with exit value 1 */
    {  MOD1|SHIFT,       XK_Return,     spawn,             {.com = termcmd}},
    {  MOD4,             XK_v,          spawn,             {.com = dmenucmd}},
       DESKTOPCHANGE(    XK_F1,                             0)
       DESKTOPCHANGE(    XK_F2,                             1)
       DESKTOPCHANGE(    XK_F3,                             2)
       DESKTOPCHANGE(    XK_F4,                             3)
};

#endif
