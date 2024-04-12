#include "ge_playerCamera.h"


PlayerCamera::PlayerCamera(){}
PlayerCamera::~PlayerCamera(){}

void PlayerCamera::Update(Camera *camera, Terrain *terrain, Lava *lava, float player_x,float player_y,float player_z)
{
    camera->Front = glm::vec3(cos(camera->Yaw) * cos(camera->Pitch), sin(camera->Pitch), sin(camera->Yaw) * cos(camera->Pitch));

    // //camera sigue a player
    // if(camera->GetState() == STATE_FPS) camera->SetPos(player_x, player_y + 0.5, player_z);
    // else
    // {
        float newLambda = terrain->GetSegmentIntersectionLambda(player_x,player_y,player_z, camera->Front.x,camera->Front.y,camera->Front.z, MAX_DISTANCE);
        newLambda = std::min( newLambda , camera->GetLavaLambda(player_y,player_y - MAX_DISTANCE*camera->Front.y,lava->GetHeight()) );

        if(camera->Lambda < newLambda)
        {
            camera->Lambda += SMOOTHING_SPEED;
            if(camera->Lambda > newLambda) camera->Lambda = newLambda;
        }
        else camera->Lambda = newLambda;


        camera->Distance = MAX_DISTANCE*camera->Lambda*0.85;

        camera->SetPos(player_x - camera->Distance*camera->Front.x,player_y - camera->Distance*camera->Front.y,player_z - camera->Distance*camera->Front.z);
    //}

    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    //gluLookAt(x, y, z,     x + vx, y + vy, z + vz,    0,1,0);
}