#include <GLFW/glfw3.h>
#include <string.h>
#include "../config.h"
#include "../global.h"
#include "../io.h"
#include "../util/utils.h"
#include "../input.h"
#include "../util/types.h"

ConfigState config = {0};

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

static char tmpBuffer[20] = {0};

static char* getConfigValue(const char* configBuffer, const char* value) {
	char* line = strstr(configBuffer, value);
	if (!line)
		ERROR_EXIT("Could not find config value: %s. Try deleting config.ini and restarting.\n", value);
	
	usize len = strlen(line);
	char* end = line + len;

	char* current = line;
	char* tmpPtr = &tmpBuffer[0];
	while (*current != '=' && current != end) {
		current++;
	}
	current++;

	while (*current == ' ') {
		current++;
	}
	while (*current != '\n' && current != end) {
		*tmpPtr++ = *current++;
	}
	*tmpPtr = 0;

	return tmpBuffer;
}

static void loadControls(const char *configBuffer) {
	configKeyBind(INPUT_KEY_FORWARD, 	getConfigValue(configBuffer, "forward"	));
	configKeyBind(INPUT_KEY_BACKWARD, 	getConfigValue(configBuffer, "backward"	));
	configKeyBind(INPUT_KEY_LEFT, 		getConfigValue(configBuffer, "left"		));
	configKeyBind(INPUT_KEY_RIGHT, 		getConfigValue(configBuffer, "right"	));
	configKeyBind(INPUT_KEY_UP, 		getConfigValue(configBuffer, "up"		));
	configKeyBind(INPUT_KEY_DOWN, 		getConfigValue(configBuffer, "down"		));
	configKeyBind(INPUT_KEY_ESCAPE, 	getConfigValue(configBuffer, "escape"	));
}

static int loadConfig(void) {
	File configFile = ioFileRead("./config.ini");
	if (!configFile.isValid)
		return 1;
	loadControls(configFile.data);

	free(configFile.data);

	return 0;
}

void configInit(void) {
	if (loadConfig() == 0)
		return;
	ioFileWrite((void*)CONFIG_DEFAULT, strlen(CONFIG_DEFAULT), "./config.ini");

	if (loadConfig() != 0)
		ERROR_EXIT("Could not create or load config file.\n");
}

void configKeyBind(InputKey key, const char* keyName) {
	if (strlen(keyName) == 1) {
		config.keybinds[key] = (int)keyName[0];
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
