#pragma once
#include "extra/bass.h"
#include "includes.h"
#include <map>

class Audio
{
public:
	static std::map<std::string, Audio*> sLoadedAudios;
	HSAMPLE hSample;
	std::string filename;
	Audio();
	~Audio();

	HCHANNEL play(float volume, DWORD flags);

	static BOOL Stop(HCHANNEL channel);
	static Audio* Get(const char* filename);
	static Audio* Find(const char* filename);
	static HCHANNEL Play(const char* filename, DWORD flags);
	HSAMPLE LoadSample(const char* filename);
	void setName(const char* name);
};

