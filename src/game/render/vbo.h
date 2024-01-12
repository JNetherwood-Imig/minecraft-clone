#pragma once

#include <stdbool.h>
#include "../util/types.h"

// Define vbo utility function prototypes
void vboCreate(u32* vbo, void* data, usize size, bool dynamic);
void vboBind(u32* vbo);
void vboUnbind(void);
void vboDelete(u32* vbo);
