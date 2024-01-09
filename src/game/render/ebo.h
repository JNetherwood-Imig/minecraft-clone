#pragma once

#include <stdbool.h>
#include "../util/types.h"

void eboCreate(u32* ebo, void* data, usize size, bool dynamic);
void eboBind(u32* ebo);
void eboUnbind(void);
void eboDelete(u32* ebo);
