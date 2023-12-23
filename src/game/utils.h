#pragma once

#include <stdlib.h>
#include <stdio.h>

#define ERROR_EXIT(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define ERROR_RETURN(R, ...) { fprintf(stderr, __VA_ARGS__); return R; }

#define RED 	(vec4){ 1.0, 0.0, 0.0, 1.0 }
#define ORANGE 	(vec4){ 1.0, 0.5, 0.0, 1.0 }
#define YELLOW 	(vec4){ 1.0, 1.0, 0.0, 1.0 }
#define GREEN 	(vec4){ 0.0, 1.0, 0.0, 1.0 }
#define CYAN 	(vec4){ 0.0, 1.0, 1.0, 1.0 }
#define BLUE 	(vec4){ 0.0, 0.0, 1.0, 1.0 }
#define MAGENTA (vec4){ 1.0, 0.0, 1.0, 1.0 }
#define WHITE 	(vec4){ 1.0, 1.0, 1.0, 1.0 }
#define BLACK 	(vec4){ 0.0, 0.0, 0.0, 1.0 }
#define GRAY 	(vec4){ 0.5, 0.5, 0.5, 1.0 }

