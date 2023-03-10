# Desktop Pet
Authors: Aditi Vinod, Lily Jiang, Luke Witten, and Richard Li

In an effort to combat the crippling loneliness that comes with being a nerd at nerd school, we created a "desktop pet," a little cat that will walk randomly around the screen and interact with inputs you give it. 

# Usage

## Dependencies

Our system uses SDL to generate images.

    sudo apt-get install libsdl2-dev

If there are unmet dependencies, such as `libegl-mesa0` depending on `libgbm1`, visit this [link](https://askubuntu.com/questions/920866/unable-to-install-libsdl2-dev-due-to-unmet-dependencies) to debug

Because we want to make the system accessible to more image types, install the SDL2_image library!

    sudo apt-get install libsdl2-image-dev
    sudo apt-cache search SDL_image
    sudo apt-get install libsdl-image-gst

<!-- sudo apt-get install --reinstall ubuntu-desktop -->

## Compilation

Our system compiles with [CMake](https://cmake.org/), and in order to use it you'll have to build it. Make sure you're in the `desktop_pet` directory, then run:

    mkdir build
    cd build
    cmake ..
    make

Afterwards, running 

    ./scripts/main

From the build directory will bring up your own little friend :).

## Interacting with your new friend

After you see the cat start to wander around the screen, you can do a couple of things

- Press `spacebar` to randomly vary the speed of the cat (it'll also do this on its own sometimes)
- `Click on the cat `to change its color!
- `Esc` to exit



