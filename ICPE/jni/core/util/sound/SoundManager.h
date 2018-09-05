#pragma once

#include "MediaPlayer.h"

#include <string>
#include <vector>
#include <jni.h>
#include "mcpe/util/Vec3.h"

class SoundManager
{
public:
	typedef long long SoundID;
	struct SoundItem
	{
		SoundID id;
		Vec3 pos;
		MediaPlayer* player;
	};
private:
	std::vector<SoundItem> soundItems;
	std::vector<MediaPlayer> mDefaultSounds;
	Vec3 listenerPos;
	JavaVM* jvm;
public:
	SoundManager(JavaVM&);
	~SoundManager();
public:
	void setListenerPos(Vec3 const&);
	Vec3 getListenerPos()const;
	MediaPlayer* getMediaPlayer(SoundID);
	SoundID playSound(Vec3 const&,std::string const&);
	void playSound(std::string const&);
	SoundID playLoopingSound(Vec3 const&,std::string const&);
	SoundItem* getSoundItem(SoundID);
	void stop(SoundID);
	void updateVolume();
};
