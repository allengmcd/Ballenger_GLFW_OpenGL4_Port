#include "ge_sound.h"

Sound::Sound(void)
{
	FMOD::System_Create(&system);// create an instance of the game engine
	system->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels (cantidad de sonido simultaneo que puede haber)
}

Sound::~Sound(void)
{
	for(int i=0; i<NUM_SOUNDS; i++) sounds[i]->release();
    system->release();
}

bool Sound::Load()
{
	system->createStream("Sounds/ambient.mp3",       FMOD_LOOP_NORMAL, 0, &sounds[SOUND_AMBIENT]);
	system-> createSound("Sounds/swish.wav",         FMOD_DEFAULT, 0, &sounds[SOUND_SWISH]);
	system-> createSound("Sounds/warp.wav",          FMOD_DEFAULT, 0, &sounds[SOUND_WARP]);
	system-> createSound("Sounds/unlock.wav",        FMOD_DEFAULT, 0, &sounds[SOUND_UNLOCK]);
	system-> createSound("Sounds/energyflow.wav",    FMOD_DEFAULT, 0, &sounds[SOUND_ENERGYFLOW]);
	system-> createSound("Sounds/bounce.wav",        FMOD_DEFAULT, 0, &sounds[SOUND_BOUNCE]);
	system-> createSound("Sounds/pickup.wav",        FMOD_DEFAULT, 0, &sounds[SOUND_PICKUP]);
	system-> createSound("Sounds/screwgravity.wav",  FMOD_DEFAULT, 0, &sounds[SOUND_SCREWGRAVITY]);
    //system->createChannelGroup("TestGroup", &TestGroup);
	return true;
}

void Sound::Play(int sound_id)
{
	if (sound_id == SOUND_AMBIENT) 
    {
		system->playSound(sounds[SOUND_AMBIENT], TestGroup, false, &ambient1Channel);
		ambient1Channel->setVolume( 0.25f ); //between 0 and 1
	}
	else 
    {
        system->playSound(sounds[sound_id], TestGroup, false, 0);
    }
}

void Sound::PlayBounce(float vol)
{
	system->playSound(sounds[SOUND_BOUNCE], TestGroup, true, &bounceChannel);
	bounceChannel->setVolume(vol);
	bounceChannel->setPaused(false);
}

void Sound::StopAll()
{
	ambient1Channel->stop();
}

void Sound::Update()
{
	system->update();
}