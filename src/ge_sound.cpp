#include "ge_sound.h"

Sound::Sound(void)
{
    engine = createIrrKlangDevice();
}

Sound::~Sound(void)
{
	for(int i=0; i<NUM_SOUNDS; i++) sounds[i]->drop();
    engine->drop();
}

bool Sound::Load()
{
	sounds[SOUND_AMBIENT] =         engine->addSoundSourceFromFile("Sounds/ambient.mp3");
	sounds[SOUND_SWISH] =	        engine->addSoundSourceFromFile("Sounds/swish.wav");
	sounds[SOUND_WARP] =	        engine->addSoundSourceFromFile("Sounds/warp.wav");
	sounds[SOUND_UNLOCK] =	        engine->addSoundSourceFromFile("Sounds/unlock.wav");
	sounds[SOUND_ENERGYFLOW] =	    engine->addSoundSourceFromFile("Sounds/energyflow.wav");
	sounds[SOUND_BOUNCE] =	        engine->addSoundSourceFromFile("Sounds/bounce.wav");
	sounds[SOUND_PICKUP] =	        engine->addSoundSourceFromFile("Sounds/pickup.wav");
	sounds[SOUND_SCREWGRAVITY] =	engine->addSoundSourceFromFile("Sounds/screwgravity.wav");

	return true;
}

void Sound::Play(int sound_id)
{
    if(sound_id >= NUM_SOUNDS || sound_id < 0)
    {
        std::cout << "Invalid sound_id" << std::endl;
        return;
    }

	if (sound_id == SOUND_AMBIENT) 
    {
        sounds[SOUND_AMBIENT]->setDefaultVolume(0.25f);
        engine->play2D(sounds[SOUND_AMBIENT]);
    }
	else 
    {
        engine->play2D(sounds[sound_id], false);
    }
    return;
}

void Sound::PlayBounce(float vol)
{
    sounds[SOUND_BOUNCE]->setDefaultVolume(0.25f);
    engine->play2D(sounds[SOUND_BOUNCE], false);
}

void Sound::StopAll()
{
    // Maybe just stop the ambient sound
	engine->stopAllSounds();
}

void Sound::Update()
{
	//system->update();
    engine->update();
}