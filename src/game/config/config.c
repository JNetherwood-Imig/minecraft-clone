#include <GLFW/glfw3.h>
#include <string.h>
#include "../config.h"
#include "../io.h"
#include "../util/utils.h"
#include "../input.h"
#include "../util/types.h"

// Initialize empty config state
ConfigState config = {0};

// Set default config values to be used if a config file cannot be found
static const char* CONFIG_DEFAULT =
	"[controls]\n"
	"forward = W\n"
	"backward = S\n"
	"left = A\n"
	"right = D\n"
	"up = SPACE\n"
	"down = SHIFT\n"
	"escape = ESC\n"
	"\n";

// Temporary buffer to store config value read from config file
static char tmpBuffer[20] = {0};

// Function to search the config file for a specific control and return the associated value
static char* getConfigValue(const char* configBuffer, const char* value) {
	// Search config file for control name
	char* line = strstr(configBuffer, value);
	if (!line)
		ERROR_EXIT("Could not find config value: %s. Try deleting config.ini and restarting.\n", value);
	
	// Variables to store length and end address of the line which defines the requested config value
	usize len = strlen(line);
	char* end = line + len;

	// Incrament through the characters in the line until the '=' is reached,
	// then incrament past it
	char* current = line;
	char* tmpPtr = &tmpBuffer[0];
	while (*current != '=' && current != end) {
		current++;
	}
	current++;

	// Consume whitespace
	while (*current == ' ') {
		current++;
	}

	// Read data until end of line
	while (*current != '\n' && current != end) {
		*tmpPtr++ = *current++;
	}
	*tmpPtr = 0;

	// Return config value
	return tmpBuffer;
}

// Function to load the controls from the config file (using getConfigValue())
static void loadControls(const char *configBuffer) {
	// Search the config file data (configBuffer) for config key names
	// and bind the value to the correct input
	configKeyBind(INPUT_KEY_FORWARD, 	getConfigValue(configBuffer, "forward"	));
	configKeyBind(INPUT_KEY_BACKWARD, 	getConfigValue(configBuffer, "backward"	));
	configKeyBind(INPUT_KEY_LEFT, 		getConfigValue(configBuffer, "left"		));
	configKeyBind(INPUT_KEY_RIGHT, 		getConfigValue(configBuffer, "right"	));
	configKeyBind(INPUT_KEY_UP, 		getConfigValue(configBuffer, "up"		));
	configKeyBind(INPUT_KEY_DOWN, 		getConfigValue(configBuffer, "down"		));
	configKeyBind(INPUT_KEY_ESCAPE, 	getConfigValue(configBuffer, "escape"	));
}

// Function to load config file and assing config values (using loadControls())
// and return an int for either success or faliure
static int loadConfig(void) {
	// Read data from config file and ensure it is valid
	File configFile = ioFileRead("./config.ini");
	if (!configFile.isValid)
		return 1;
	// Load controls from config file
	loadControls(configFile.data);

	free(configFile.data);

	return 0;
}

// Attempts to first load the config file,
// but if that fails, it will attempt to create a new config file useing the default config values
void configInit(void) {
	// Successfully loaded config file
	if (loadConfig() == 0)
		return;
	// Config file was not successfully loaded,
	// creating a new one
	ioFileWrite((void*)CONFIG_DEFAULT, strlen(CONFIG_DEFAULT), "./config.ini");

	// If the config file still cannot be successfully loaded,
	// print an error message and exit
	if (loadConfig() != 0)
		ERROR_EXIT("Could not create or load config file.\n");
}

// Function to bind an input key value to a GLFW_KEY value
// so that it can be read by the key callback
void configKeyBind(InputKey key, const char* keyName) {
	// If the config value is a simple, single character key name,
	// cast the char to a GLFW_KEY and bind it
	if (strlen(keyName) == 1) {
		config.keybinds[key] = (int)keyName[0];
	// Otherwise, use strcmp to match specific config values for binding
	} else {
		if (strcmp(keyName, "ESC") == 0) {
			config.keybinds[key] = GLFW_KEY_ESCAPE;
		}
		if (strcmp(keyName, "SHIFT") == 0) {
			config.keybinds[key] = GLFW_KEY_LEFT_SHIFT;
		}
		if (strcmp(keyName, "SPACE") == 0) {
			config.keybinds[key] = GLFW_KEY_SPACE;
		}
		if (strcmp(keyName, "TAB") == 0) {
			config.keybinds[key] = GLFW_KEY_TAB;
		}
	}
}
