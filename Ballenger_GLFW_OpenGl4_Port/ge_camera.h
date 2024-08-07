#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <vector>

#define STATE_FPS         0
#define STATE_TPS         1
#define STATE_TPS_FREE	  2

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    SHIFT,
    SHIFT_PRESSED,
    SHIFT_RELEASED
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  25.0f;
const float MAX_SPEED   =  150.0f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;
const float ZNEAR       = 0.1f;
const float ZFAR		= 100.0f;
const float MAX_DISTANCE = 10.0f;
const float SMOOTHING_SPEED = 0.01f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw, LastYaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
	float Lambda;
    float Distance;
	unsigned int SCR_WIDTH = 800;
	unsigned int SCR_HEIGHT = 600;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void MovementSpeed_Handler(Camera_Movement speed, float deltaTime)
    {
        if (speed == SHIFT_PRESSED)
        {
            MovementSpeed = MAX_SPEED;
        }
        else if(speed == SHIFT_RELEASED)
        {
            MovementSpeed = SPEED;
        }
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

	float GetDistance()
	{
		return Distance;
	}

	void SetState(int s)
	{
		state = s;
	}
	int  GetState()
	{
		return state;
	}
    
    void RotateYaw(float angle)
    {
        Yaw += angle;

        Refresh();
    }
    void SetYaw(float angle)
    {
        Yaw = angle;
    }
    float GetYaw()
    {
        return Yaw;
    }

    void SetLastYaw(float angle)
    {
        LastYaw = angle;
    }
    float GetLastYaw()
    {
        return LastYaw;
    }

    void RotatePitch(float angle)
    {
        const float limit = 89.0 * PI / 180.0;

        Pitch += angle;

        if(Pitch < -limit)
            Pitch = -limit;

        if(Pitch > limit)
            Pitch = limit;

        Refresh();
    }
    void SetPitch(float angle)
    {
        Pitch = angle;
    }
    float GetPitch()
    {
        return Pitch;
    }
        

    void Refresh()
    {
        Front = glm::vec3(cos(Yaw) * cos(Pitch), sin(Pitch), sin(Yaw) * cos(Pitch));

        // glMatrixMode(GL_MODELVIEW);
        // glLoadIdentity();
        glm::lookAt(Position, Position + Front, Up);
    }

    float GetLavaLambda(float Py,float Qy,float height)
    {
        float Vy = Qy - Py;
        float D = -height;
        if(Vy == 0.0f) return 1.0f;
        float lambda = -(Py + D) / Vy;
        if(lambda < 0.0f || lambda > 1.0f) return 1.0f;
        return lambda;
    }

    void SetPos(float posx, float posy, float posz)
    {
        Position = glm::vec3(posx, posy, posz);

        Refresh();
    }

	//void Update(Terrain *terrain,Lava *lava,float player_x,float player_y,float player_z);


private:
	int state;

    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};
#endif
