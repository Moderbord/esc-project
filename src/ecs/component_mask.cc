#include "component_mask.h"

namespace ECS
{
bool ComponentMask::matches(ComponentMask cmp_mask)
{
	return ((mask & cmp_mask.mask) == cmp_mask.mask);
}
} // end namespace
