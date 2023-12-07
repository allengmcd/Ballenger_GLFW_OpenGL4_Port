#include "ge_bicho.h"

Bicho::Bicho(void)
{
	SetVel(0.0,0.0,0.0);
	yaw = 0.0f; pitch = 0.0f;
}
Bicho::~Bicho(void){}

void Bicho::SetPos(float posx, float posy, float posz)
{
	x = posx;
	y = posy;
	z = posz;
}
void Bicho::SetX(float posx)
{
	x = posx;
}
void Bicho::SetY(float posy)
{
	y = posy;
}
void Bicho::SetZ(float posz)
{
	z = posz;
}
float Bicho::GetX()
{
    return x;
}
float Bicho::GetY()
{
    return y;
}
float Bicho::GetZ()
{
    return z;
}

void Bicho::SetVel(float velx, float vely, float velz)
{
	vx = velx;
	vy = vely;
	vz = velz;
}
void Bicho::SetVX(float velx)
{
	vx = velx;
}
void Bicho::SetVY(float vely)
{
	vy = vely;
}
void Bicho::SetVZ(float velz)
{
	vz = velz;
}
float Bicho::GetVX()
{
    return vx;
}
float Bicho::GetVY()
{
    return vy;
}
float Bicho::GetVZ()
{
    return vz;
}

void Bicho::SetYaw(float ang)
{
	yaw = ang;
}
void Bicho::SetPitch(float ang)
{
	pitch = ang;
}
float Bicho::GetYaw()
{
	return yaw;
}
float Bicho::GetPitch()
{
	return pitch;
}

void Bicho::SetState(int s)
{
	state = s;
}
int Bicho::GetState()
{
	return state;
}

void Bicho::SetMaxHealth(int max_h)
{
	max_health = max_h;
}
int Bicho::GetMaxHealth()
{
	return max_health;
}
void Bicho::SetHealth(int h)
{
	health = h;
}
int Bicho::GetHealth()
{
	return health;
}