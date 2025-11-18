# Run Dashy, run! 🙂

Run Dashy, run! is an endless runner game that I originally created for a code challenge organized by Supercell.  

They provided me with a very basic (and buggy 😁) base game code, I spent 12 hours debugging and developing it into a working game.  
After the challenge I really wanted to continue developing this game, as I had so many ideas that I wanted to add to the game, but I just didn't have enough time to implement them.  

That's what this repo is about 😎

## Instructions

The game is called "Run Dashy, run!"  
It's a game about a small yellow ball called Dashy, who loves to run far and get a loooot of points in the process.  

The game has in-game instructions too, but here is a quick intro on what's to come:  

### Controls  

A & D - Move sideways  
W - Jump  
W (mid-air) - Double jump  
S (mid air) - Perform Meteor Attack  
S (hold on ground) - Perform Turbo jump  
Space - Dash

### Relevant game info  

It's an endless runner game, so the player's goal is to get as many points as they can by surviving in the ever moving environment.  

You get points for travelling, but also for defeating enemies!  
Defeat enemies by Dashing at them or using the Meteor attack from above.  

You lose if you touch enemies without dashing, for touching the nasty spike wall or falling off screen.... you'll soon see what I mean 😉

## About the process

By the end of the challenge I had implemented:  

- Dashy's movement abilities and their visual effects (jump, double jump, turbo jump, meteor attack & side dash)
- Randomly spawning enemies with continuously faster movement speed and spawn rate
- Platforms that can be jumped on (but were penetrable from under and sided)
- Static spike wall at the end of the screen
- Score system and game states
- Vanishing floor mechanic

My additions after the challenge:  

- Fixed platform collision logic, it was a bit broken before...
- Fixed a bug, where turbo jump was possible to be executed after the floor had vanished in some scenarios
- Made the floor not blink when it returns
- Fixed a bug in player border update logic
- Fixed introduction texts to underline that it is indeed interactive
- Updated dash reset logic - when player successfully hits and enemy with a dash, both the dash and jumping abilities get a reset.
- Fixed a bug where player would stop on the ground level briefly even when the floor has vanished
- Made the platforms solid - added bottom, left and right collisions for them
- Added new obstacle to the game: a wall with a gap. Player needs to move themselves through the gap in order to survive.
  

## Prerequisites

NOTE: Hive computers (should) have these dependencies installed already.

You must have [CMake](https://cmake.org/) version 3.22.1 or later installed to build this project.

If you are on Linux, make sure to install SFML's dependencies. For Debian-based distros:
```
sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libfreetype-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
```

## Building

Simply run `cmake -B build` and `cmake --build build`. This builds the executable in `./build/bin/`.

The exact location of the executable may differ depending on your system and compiler. Example locations are `./build/bin/runner` and `./build/bin/Debug/runner.exe`.

Alternatively, you can specify a generator suited for your toolchain.
- `cmake -B build -G"Unix Makefiles"`
- `cmake -B build -G"Visual Studio 17 2022"`
- `cmake -B build -GXcode`

Run `cmake -G` to list all available generators.

## Troubleshooting

### MacOS
Your game may not be receiving keyboard inputs. If you see "Detected a keyboard without any keys" printed to the terminal. You will need to treat the *launcher* as the app that is "monitoring input"
- Open System Settings -> Privacy & Security -> Input Monitoring
    - If you run from Terminal or iTerm2: enable it for that app.
    - If you run from Xcode or Visual Studio Code: enable it for that app.
- Quit and reopen the launcher, then run your game again.
