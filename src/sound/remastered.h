
#ifndef _REMASTERED_H
#define _REMASTERED_H

#include <string>

struct remasteredSong
{
	Mix_Music *intro;
	Mix_Music *loop;
	bool playing;
	int volume;
	
	bool fading;
	uint32_t last_fade_time;
	uint32_t last_pos;
	bool doloop;
};

bool remastered_load(const std::string& fname, const std::string& dir);
bool remastered_start(const std::string& fname, const std::string& dir, int startbeat, bool loop);
void remastered_stop(void);
bool remastered_is_playing(void);
void remastered_fade(void);
void remastered_set_volume(int newvolume);
void remastered_run_fade(void);

#endif

