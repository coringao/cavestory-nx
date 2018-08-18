
#include "nx.h"
#include <stdarg.h>
#include <cstring>
#include <string>
#include <vector>

#include "debug.h"
#include "game.h"
#include "input.h"
#include "graphics/graphics.h"
#include "graphics/font.h"
#include "graphics/sprites.h"
using namespace Graphics;
using namespace Sprites;
#include "sound/sound.h"
#include "common/stat.h"
#include "common/misc.h"
#include "playerstats.h"
#include "player.h"
#include "settings.h"
#include "console.h"
#include "map.h"
#include "object.h"
#include "siflib/sif.h"

#define MAX_DEBUG_MARKS		80
static struct
{
	int x, y, x2, y2;
	char type;
	uint8_t r, g, b;
} debugmarks[MAX_DEBUG_MARKS];

static int ndebugmarks = 0;
std::vector<std::string> DebugList;


void DrawDebug(void)
{
	if (settings->enable_debug_keys)
	{
		// handle debug keys
		if (justpushed(DEBUG_GOD_KEY))
		{
			game.debug.god ^= 1;
			sound(SND_MENU_SELECT);
		}
		
		if (justpushed(DEBUG_SAVE_KEY))
		{
			game_save(settings->last_save_slot);
			sound(SND_SWITCH_WEAPON);
			console.Print("Game saved.");
		}
		
		if (justpushed(F6KEY))
		{
			game.debug.DrawBoundingBoxes ^= 1;
			sound(SND_COMPUTER_BEEP);
		}
		
		if (justpushed(F9KEY))
		{
			AddXP(1);
		}
		
		if (inputs[DEBUG_FLY_KEY])
		{
			player->yinertia = -0x880;
			if (!player->hurt_time) player->hurt_time = 20;		// make invincible
		}
	}
	
	debug_draw();
	DrawDebugMarks();
}


void DrawBoundingBoxes()
{
	Object *o;
	FOREACH_OBJECT(o)
	{
		if (o->onscreen || o == player)
		{
			uint32_t color;
			
			if (o == player)
			{
				color = 0xffff00;
			}
			else if (o->flags & FLAG_INVULNERABLE)
			{
				color = 0xffffff;
			}
			else if (o->flags & FLAG_SHOOTABLE)
			{
				color = 0x00ff00;
			}
			else if (o->flags & FLAG_SOLID_MUSHY)
			{
				color = 0xff0080;
			}
			else
			{
				color = 0xff0000;
			}
			
			AddDebugMark(o->Left(), o->Top(), o->Right(), o->Bottom(),
						DM_BOX, color>>16, (color>>8)&0xff, color&0xff);
			AddDebugMark(o->CenterX(), o->CenterY(), o->CenterX(), o->CenterY(),
						DM_PIXEL, 255,0,255);
		}
	}
}

static void draw_pointlist(Object *o, SIFPointList *points)
{
	int xoff = (o->x / CSFI);
	int yoff = (o->y / CSFI);
	
	for(int i=0;i<points->count;i++)
	{
		DebugPixel((xoff + points->point[i].x) * CSFI, \
			(yoff + points->point[i].y) * CSFI, 255, 0, 255);
	}
}

void DrawAttrPoints()
{
	Object *o;
	FOREACH_OBJECT(o)
	{
		draw_pointlist(o, &sprites[o->sprite].block_l);
		draw_pointlist(o, &sprites[o->sprite].block_r);
		draw_pointlist(o, &sprites[o->sprite].block_u);
		draw_pointlist(o, &sprites[o->sprite].block_d);
	}
}


/*
void c------------------------------() {}
*/

// debug text display debug() useful for reporting game vars etc
void debug(const char *fmt, ...)
{
char buffer[128];
va_list ar;

	va_start(ar, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, ar);
	va_end(ar);
	
	DebugList.push_back(buffer);
}

void debug_draw(void)
{
	for(unsigned int i=0;i<DebugList.size();i++)
	{
		const char *text = DebugList.at(i).c_str();
		
		int x = (SCREEN_WIDTH - 8) - GetFontWidth(text, true);
		int y = 4 + (i * (GetFontHeight() + 1));
		font_draw(x, y, text, 0x00FF00, true);
	}
}

void debug_clear()
{
	DebugList.clear();
}

/*
void c------------------------------() {}
*/

#include "autogen/objnames.h"

// given an object type returns the name of the object e.g. "OBJ_TOROKO"
const char *DescribeObjectType(int type)
{
	if (type >= 0 && type < OBJ_LAST && object_names[type])
		return stprintf("OBJ_%s(%d)", object_names[type], type);
	
	return stprintf("[Type %d]", type);
}

// tries to convert a string, such as OBJ_TOROKO, into it's numeric type,
// with a small bit of english-language intelligence.
int ObjectNameToType(const char *name_in)
{
	// if all characters are numeric they're specifying by number
	// so simply return the atoi
	for(int i=0;;i++)
	{
		if (name_in[i] == 0)
		{
			return atoi(name_in);
		}
		
		if (!isdigit(name_in[i])) break;
	}
	
	char *name = strdup(name_in);	// make string writeable
	
	// some string preprocessing
	for(int i=0;name[i];i++)
	{
		if (name[i] == ' ')
		{
			name[i] = '_';
		}
		else
		{
			name[i] = toupper(name[i]);
		}
	}
	
	// remove the "OBJ_" suffix if it's present
	const char *searchstring = name;
	if (strbegin(name, "OBJ_"))
		searchstring += 4;
	
	// search for it in the object_names table
	for(int i=0;i<OBJ_LAST;i++)
	{
		if (object_names[i] && !strcmp(object_names[i], searchstring))
		{
			free(name);
			return i;
		}
	}
	
	stat("ObjectNameToType: couldn't find object 'OBJ_%s'", searchstring);
	free(name);
	return -1;
}

const char *DescribeDir(int dir)
{
	switch(dir)
	{
		case LEFT: return "LEFT";
		case RIGHT: return "RIGHT";
		case UP: return "UP";
		case DOWN: return "DOWN";
		case CENTER: return "CENTER";
		default: return stprintf("[Invalid Direction %d]", dir);
	}
}

/*
void c------------------------------() {}
*/

const char *strhex(int value)
{
	if (value < 0)
		return stprintf("-0x%x", -value);
	else
		return stprintf("0x%x", value);
}


/*
void c------------------------------() {}
*/

void DrawDebugMarks(void)
{
int i;
int x, y, x2, y2;
uint8_t r, g, b;

	for(i=0;i<ndebugmarks;i++)
	{
		x = (debugmarks[i].x / CSFI) - (map.displayed_xscroll / CSFI);
		y = (debugmarks[i].y / CSFI) - (map.displayed_yscroll / CSFI);
		x2 = (debugmarks[i].x2 / CSFI) - (map.displayed_xscroll / CSFI);
		y2 = (debugmarks[i].y2 / CSFI) - (map.displayed_yscroll / CSFI);
		r = debugmarks[i].r;
		g = debugmarks[i].g;
		b = debugmarks[i].b;
		
		switch(debugmarks[i].type)
		{
			case DM_PIXEL:
				DrawPixel(x, y, r, g, b);
			break;
			
			case DM_CROSSHAIR:
				DrawPixel(x, y, r, g, b);
				DrawPixel(x+1, y, r, g, b);
				DrawPixel(x-1, y, r, g, b);
				DrawPixel(x, y+1, r, g, b);
				DrawPixel(x, y-1, r, g, b);
			break;
			
			case DM_XLINE:
				FillRect(x, 0, x, SCREEN_HEIGHT, r, g, b);
			break;
			
			case DM_YLINE:
				FillRect(0, y, SCREEN_WIDTH, y, r, g, b);
			break;
			
			case DM_BOX:
				DrawRect(x, y, x2, y2, r, g, b);
			break;
		}
	}
	
	ndebugmarks = 0;
}

void AddDebugMark(int x, int y, int x2, int y2, char type, uint8_t r, uint8_t g, uint8_t b)
{
	if (ndebugmarks >= MAX_DEBUG_MARKS)
		return;
	
	debugmarks[ndebugmarks].x = x;
	debugmarks[ndebugmarks].y = y;
	debugmarks[ndebugmarks].x2 = x2;
	debugmarks[ndebugmarks].y2 = y2;
	debugmarks[ndebugmarks].r = r;
	debugmarks[ndebugmarks].g = g;
	debugmarks[ndebugmarks].b = b;
	debugmarks[ndebugmarks].type = type;
	ndebugmarks++;
}

// draw a pixel of the specified color at [x,y] in object coordinates
void DebugPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
	AddDebugMark(x, y, 0, 0, DM_PIXEL, r, g, b);
}

void DebugCrosshair(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
	AddDebugMark(x, y, 0, 0, DM_CROSSHAIR, r, g, b);
}

void crosshair(int x, int y)
{
	debugVline(x, 255, 0, 0);
	debugHline(y, 0, 255, 0);
}

void DebugPixelNonCSF(int x, int y, uint8_t r, uint8_t g, uint8_t b) { DebugPixel(x * CSFI, y * CSFI, r, g, b); }
void DebugCrosshairNonCSF(int x, int y, uint8_t r, uint8_t g, uint8_t b) { DebugCrosshair(x * CSFI, y * CSFI, r, g, b); }

void debugVline(int x, uint8_t r, uint8_t g, uint8_t b)
{
	AddDebugMark(x, 0, 0, 0, DM_XLINE, r, g, b);
}

void debugHline(int y, uint8_t r, uint8_t g, uint8_t b)
{
	AddDebugMark(0, y, 0, 0, DM_YLINE, r, g, b);
}

void debugbox(int x1, int y1, int x2, int y2, uint8_t r, uint8_t g, uint8_t b)
{
	AddDebugMark(x1, y1, x2, y2, DM_BOX, r, g, b);
}

void debugtile(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
int x1, y1, x2, y2;

	x *= (TILE_W * CSFI);
	y *= (TILE_H * CSFI);
	
	x1 = x; y1 = y;
	x2 = x1 + (TILE_W * CSFI);
	y2 = y1 + (TILE_H * CSFI);
	AddDebugMark(x1, y1, x2, y2, DM_BOX, r, g, b);
}

