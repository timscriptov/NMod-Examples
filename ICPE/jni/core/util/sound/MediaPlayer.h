#pragma once

#include <jni.h>
#include <string>

class MediaPlayer
{
private:
	JavaVM* jvm;
	jobject mediaPlayer;
	bool released;
	std::string sourceData;
public:
	MediaPlayer(JavaVM&);
	MediaPlayer();
	~MediaPlayer();
public:
	void setDataSource(std::string const&);
	void prepare();
	void prepareAsync();
	void start();
	void pause();
	void release();
	void stop();
	bool isLopping();
	bool isPlaying();
	void reset();
	void setLooping(bool);
	void seekTo(int);
	int getCurrentPosition();
	int getDuration();
	int getVideoHeight();
	int getVideoWidth();
	void setVolume(float,float);
	std::string getDataSource()const;
};
