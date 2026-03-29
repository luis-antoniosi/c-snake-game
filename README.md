Simple snake game in C! Runs on Windows and UNIX systems.

---

## How to play

If you have make installed:
```bash
make all
```

If you don't, then just use gcc:
```bash
gcc -std=c11 -Wall -Wpedantic -Wextra -Werror -O3 -march=native main.c game.c utils.c
```
And run the executable.

---

## Controls
- `WASD` -> move up, left, down, right, respectively.
- `Q` -> quit the game