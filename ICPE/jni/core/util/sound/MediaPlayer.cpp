#include "MediaPlayer.h"

MediaPlayer::MediaPlayer(JavaVM&vm)
{
	jvm=&vm;
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID initMediaPlayer=env->GetMethodID(jMediaPlayer,"<init>","()V");
	mediaPlayer=env->NewObject(jMediaPlayer,initMediaPlayer);
}
MediaPlayer::MediaPlayer()
{
	
}
MediaPlayer::~MediaPlayer()
{
	if(!released)
		release();
}
std::string MediaPlayer::getDataSource()const
{
	return sourceData;
}
void MediaPlayer::setDataSource(std::string const&str)
{
	sourceData=str;
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID setDataSource=env->GetMethodID(jMediaPlayer,"setDataSource","(Ljava/lang/String;)V");
	env->CallVoidMethod(mediaPlayer,setDataSource,env->NewStringUTF(str.c_str()));
}
void MediaPlayer::prepare()
{
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID mid=env->GetMethodID(jMediaPlayer,"prepare","()V");
	env->CallVoidMethod(mediaPlayer,mid);
}
void MediaPlayer::prepareAsync()
{
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID mid=env->GetMethodID(jMediaPlayer,"prepareAsync","()V");
	env->CallVoidMethod(mediaPlayer,mid);
}
void MediaPlayer::start()
{
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID mid=env->GetMethodID(jMediaPlayer,"start","()V");
	env->CallVoidMethod(mediaPlayer,mid);
}
void MediaPlayer::pause()
{
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID mid=env->GetMethodID(jMediaPlayer,"pause","()V");
	env->CallVoidMethod(mediaPlayer,mid);
}
void MediaPlayer::release()
{
	if(released)
		return;
	released=true;
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID mid=env->GetMethodID(jMediaPlayer,"release","()V");
	env->CallVoidMethod(mediaPlayer,mid);
}
void MediaPlayer::stop()
{
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID mid=env->GetMethodID(jMediaPlayer,"stop","()V");
	env->CallVoidMethod(mediaPlayer,mid);
}
bool MediaPlayer::isLopping()
{
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID mid=env->GetMethodID(jMediaPlayer,"isLooping","()Z");
	return env->CallBooleanMethod(mediaPlayer,mid);
}
bool MediaPlayer::isPlaying()
{
	if(!mediaPlayer)
		return false;
	if(released)
		return false;
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID mid=env->GetMethodID(jMediaPlayer,"isPlaying","()Z");
	return env->CallBooleanMethod(mediaPlayer,mid);
}
void MediaPlayer::reset()
{
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID mid=env->GetMethodID(jMediaPlayer,"reset","()V");
	env->CallVoidMethod(mediaPlayer,mid);
}
void MediaPlayer::setLooping(bool looping)
{
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID mid=env->GetMethodID(jMediaPlayer,"setLooping","(Z)V");
	return env->CallVoidMethod(mediaPlayer,mid,looping);
}
void MediaPlayer::seekTo(int time)
{
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID mid=env->GetMethodID(jMediaPlayer,"seekTo","(I)V");
	return env->CallVoidMethod(mediaPlayer,mid,time);
}
int MediaPlayer::getCurrentPosition()
{
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID mid=env->GetMethodID(jMediaPlayer,"getCurrentPosition","()I");
	return env->CallIntMethod(mediaPlayer,mid);
}
int MediaPlayer::getDuration()
{
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID mid=env->GetMethodID(jMediaPlayer,"getDuration","()I");
	return env->CallIntMethod(mediaPlayer,mid);
}
int MediaPlayer::getVideoHeight()
{
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID mid=env->GetMethodID(jMediaPlayer,"getVideoHeight","()I");
	return env->CallIntMethod(mediaPlayer,mid);
}
int MediaPlayer::getVideoWidth()
{
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID mid=env->GetMethodID(jMediaPlayer,"getVideoWidth","()I");
	return env->CallIntMethod(mediaPlayer,mid);
}
void MediaPlayer::setVolume(float l,float r)
{
	JNIEnv*env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMediaPlayer=env->FindClass("android/media/MediaPlayer");
	jmethodID mid=env->GetMethodID(jMediaPlayer,"setVolume","(FF)V");
	env->CallVoidMethod(mediaPlayer,mid,l,r);
}
