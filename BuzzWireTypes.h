#ifndef BUZZWIRE_TYPES
#define BUZZWIRE_TYPES

typedef enum State {
  Started,
  Failed,
  Succeeded,
  Notified
};

typedef enum GameType {
   Null,
   Free,
   Challenge,
   Tournament
};

#endif
