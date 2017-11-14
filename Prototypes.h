#ifndef PROTOTYPES_H
#define PROTOTYPES_H
// ino files get concatenated together in no particular order.  I want to ensure that
// my routines get prototyped correctly no matter what the compiler sees first.

#include "BuzzWireTypes.h"

GameType chooseGameType(void);

#endif
