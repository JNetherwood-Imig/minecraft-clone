#include "../../include/cglm/struct.h"
#include "../camera.h"
#include "../input.h"
#include "../time.h"

// Initialize empty camera object
Camera camera = {0};

// Initialize camera with basic values
void cameraInit(void) {
	camera.speed =   6.0f; // Blocks per second?
	camera.fov   =  45.0f; // Vertical degrees
	camera.yaw   = -90.0f;
	camera.pitch =   0.0f;
	camera.position = (vec3s){{ 0.0f, 0.0f,  3.0f }};
	camera.front    = (vec3s){{ 0.0f, 0.0f, -1.0f }};
}

// Update camera view and position
void cameraUpdate(void) {

	// Scale factor for camera movements which factors in delta time
	// which varies from frame to frame
	f32 scaledSpeed = camera.speed * time.delta;

	// Set the camera front vector using the camera's yaw and pitch values acquired from mouse movements
	camera.front.x = cosf(glm_rad(camera.yaw)) * cosf(glm_rad(camera.pitch));
	camera.front.y = sinf(glm_rad(camera.pitch));
	camera.front.z = sinf(glm_rad(camera.yaw)) * cosf(glm_rad(camera.pitch));

	// Set camera forward vector using only the camera's yaw value
	// Using a separate vector to store this data
	// allows for camera velocity to be unaffected by view pitch
	camera.forward.x = cosf(glm_rad(camera.yaw));
	camera.forward.z = sinf(glm_rad(camera.yaw));
	camera.forward   = glms_vec3_scale(camera.forward, scaledSpeed);

	// Create camera right vector using normalized cross product of the front and up vectors
	// Then scale it by the scaled speed
	camera.up    = (vec3s){{ 0.0f, 1.0f,  0.0f }};
	camera.right = glms_vec3_scale(glms_normalize(glms_vec3_cross(camera.front, camera.up)), scaledSpeed);

	// Scale camera up vector for correct vertical movement
	camera.up = glms_vec3_scale(camera.up, scaledSpeed);

	// If the forward key (set in config) is pressed,
	// add the camera forward vector to the position
	if (input.key[INPUT_KEY_FORWARD] == KS_PRESSED || input.key[INPUT_KEY_FORWARD] == KS_HELD) {
		camera.position = glms_vec3_add(camera.position, camera.forward);
	}

	// If the backward key (set in config) is pressed,
	// subtract the camera forward vector from the position
	if (input.key[INPUT_KEY_BACKWARD] == KS_PRESSED || input.key[INPUT_KEY_BACKWARD] == KS_HELD) {
		camera.position = glms_vec3_sub(camera.position, camera.forward);
	}

	// If the left key (set in config) is pressed,
	// subtract the camera right vector from the position
	if (input.key[INPUT_KEY_LEFT] == KS_PRESSED || input.key[INPUT_KEY_LEFT] == KS_HELD) {
		camera.position = glms_vec3_sub(camera.position, camera.right);
	}

	// If the right key (set in config) is pressed,
	// add the camera right vector to the position
	if (input.key[INPUT_KEY_RIGHT] == KS_PRESSED || input.key[INPUT_KEY_RIGHT] == KS_HELD) {
		camera.position = glms_vec3_add(camera.position, camera.right);
	}
	
	// If the up key (set in config) is pressed,
	// add the camera up vector to the position
	if (input.key[INPUT_KEY_UP] == KS_PRESSED || input.key[INPUT_KEY_UP] == KS_HELD) {
		camera.position = glms_vec3_add(camera.position, camera.up);
	}

	// If the down key (set in config) is pressed,
	// subtract the camera up vector from the position
	if (input.key[INPUT_KEY_DOWN] == KS_PRESSED || input.key[INPUT_KEY_DOWN] == KS_HELD) {
		camera.position = glms_vec3_sub(camera.position, camera.up);
	}
}

