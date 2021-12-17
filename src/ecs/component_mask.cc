#include "component_mask.h"

bool ComponentMask::matches(ComponentMask cmp_mask)
{
	return ((mask & cmp_mask.mask) == cmp_mask.mask);
}
