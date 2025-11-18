# Supercell Coding Test - Panu Kangas

Hello! 🙂

This is my take on the Supercell Code Challenge 2026!  
I had fun creating my version of an Endless runner game, I hope you have fun while playing it too! 🙂


## Instructions

My game is called "Run Dashy, run!"  
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

The game is (surprise surprise) and endless runner, so the player's goal is to get as many points as they can by surviving in the ever moving environment.  

You get points for travelling, but also for defeating enemies!  
Defeat enemies by Dashing at them or using the Meteor attack from above.  

You lose if you touch enemies without dashing, for touching the nasty spike wall or falling off screen.... you'll soon see what I mean 😉

## About the process

All the game code (excluding base code and one random number generator that I commented) is done by me within the two challenge days.  

On preparation day I played around with player movement and platforms, so those were pretty much implemented at the end of Sunday.  
On Monday I first fixed the given code base and then started adding new relevant things to it.  

All of my additions can be found from the **UpdateList.txt** file in the repo.

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

The exact location of the executable may differ depending on your system and compiler. Example locations are `./build/bin/shooter` and `./build/bin/Debug/shooter.exe`.

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


## Submission

Upload your work to Google Drive, Dropbox (or some other service), and complete the provided form with:
- A link to your submission (remember to check permissions)
- Your full name
- Your email address

[**SUBMIT**](https://supr.cl/hive2026submit)
