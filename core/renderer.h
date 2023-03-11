#include "build_type.h"

#ifdef SOFTWARE_BUILD
#include "software_renderer.h"
#endif
#ifdef HARDWARE_BUILD
#include "hardware_renderer.h"
#endif
