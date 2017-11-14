#ifndef BUZZWIRE_TYPES
#define BUZZWIRE_TYPES

typedef enum State {
  Started,
  Failed,
  Succeeded,
  Notified
};

typedef enum GameType {
   NullGame,
   Free,
   Challenge,
   Tournament
};

typedef enum Button {
   Right,
   Up,
   Down,
   Left,
   Select,
   NullButton
};
#endif
