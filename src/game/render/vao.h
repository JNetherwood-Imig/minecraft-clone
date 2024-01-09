#pragma once

#include "../util/types.h"

void vaoCreate(u32* vao);
void vaoBind(u32 vao);
void vaoUnbind(void);
void vaoDelete(u32* vao);
void vaoAttrib(u32 index, i32 size, u32 stride, u32 offset);
