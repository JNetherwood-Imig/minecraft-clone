#pragma once

#include <stdbool.h>
#include "../util/types.h"

void vboNew(u32* vbo);
void vboCreate(u32* vbo, void* data, usize size, bool dynamic);
void vboBind(u32* vbo);
void vboUnbind(void);
void vboDelete(u32* vbo);
