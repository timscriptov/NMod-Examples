#include "SoundManager.h"

#include "util/JNIUtils.h"
#include "ICPE.h"
#include <fstream>

SoundManager::SoundManager(JavaVM&vm)
{
	jvm=&vm;
}
SoundManager::~SoundManager()
{
	for(MediaPlayer& mp : mDefaultSounds)
	{
		mp.release();
	}
	for(SoundItem item : soundItems)
	{
		if(item.player)
		{
			delete item.player;
			item.player=0;
		}
	}
}
SoundManager::SoundItem* SoundManager::getSoundItem(SoundManager::SoundID id)
{
	for(SoundItem item : soundItems)
	{
		if(item.id==id)
			return &item;
	}
	return 0;
}
void SoundManager::setListenerPos(Vec3 const&pos)
{
	listenerPos=pos;
	updateVolume();
}
MediaPlayer* SoundManager::getMediaPlayer(SoundManager::SoundID id)
{
	for(SoundItem item : soundItems)
	{
		if(item.id==id)
			return item.player;
	}
	return 0;
}
Vec3 SoundManager::getListenerPos()const
{
	return listenerPos;
}
SoundManager::SoundID SoundManager::playSound(Vec3 const&pos,std::string const&path)
{
	SoundItem si;
	si.player=new MediaPlayer(*jvm);
	std::ifstream ifs(ICPE::externalStorageDirectory+"/games/com.mojang/ICPE/sounds/"+path);
	if(ifs.is_open())
	{
		si.player->setDataSource(ICPE::externalStorageDirectory+"/games/com.mojang/ICPE/sounds/"+path);
		si.player->prepare();
	}
	si.player->start();
	si.id=soundItems.size();
	si.pos=pos;
	soundItems.push_back(si);
	updateVolume();
}
SoundManager::SoundID SoundManager::playLoopingSound(Vec3 const&pos,std::string const&path)
{
	SoundItem si;
	si.player=new MediaPlayer(*jvm);
	std::ifstream ifs(ICPE::externalStorageDirectory+"/games/com.mojang/ICPE/sounds/"+path);
	if(ifs.is_open())
	{
		si.player->setDataSource(ICPE::externalStorageDirectory+"/games/com.mojang/ICPE/sounds/"+path);
		si.player->prepare();
	}
	si.player->start();
	si.player->setLooping(true);
	si.id=soundItems.size();
	si.pos=pos;
	soundItems.push_back(si);
	updateVolume();
}
void SoundManager::stop(SoundManager::SoundID id)
{
	for(SoundItem item : soundItems)
	{
		if(item.id==id)
		{
			if(item.player)
			{
				item.player->stop();
				item.player->release();
				delete item.player;
				item.player=0;
			}
		}
	}
	updateVolume();
}
void SoundManager::updateVolume()
{
	
}
void SoundManager::playSound(std::string const&path)
{
	MediaPlayer player(*jvm);
	std::ifstream ifs(ICPE::externalStorageDirectory+"/games/com.mojang/ICPE/sounds/"+path);
	if(ifs.is_open())
	{
		player.setDataSource(ICPE::externalStorageDirectory+"/games/com.mojang/ICPE/sounds/"+path);
		player.prepare();
	}
	player.start();
	updateVolume();
}
