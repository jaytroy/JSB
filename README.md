# JSBSim flight simulator
This is a barebones implementation of a flight simulator using JSBSim and C++. It is tested on Ubuntu 24.04 and is unlikely to run on dissimilar OS's.

This program currently requires [JSBSim and JSBSim Dev](https://github.com/JSBSim-Team/jsbsim/releases), NCurses, and C++ libraries to be installed. 

Build and (re)run with
>rm -rf build && cmake -B build && cmake --build build && ./build/JSB

### Todo:
| Feature                   | Status      | Notes                                                                      |
|---------------------------|-------------|----------------------------------------------------------------------------|
| Graphics (OpenGL)         | TBD         | Or UEngine/FlightGear instead? Ideally modular.                            |
| Environment Variables     | In progress | So that users don't have to modify code directly                           |
| Better FCS strat creation | In progress | Implement factory pattern to declutter FCS strat creation                  |
| Expand FCS functionality  | TBD         | Implement more than barebones flight controls                              |
| Dockerize                 | TBD         | Make it run anywhere! (that can run docker)                                |
| Aircraft selection        | TBD         | Fly something other than a measly 172P                                     |
| Multiple aircraft at once | TBD         | Allow the user to perform mid-air collisions                               |
| Custom environments       | TBD         | Set up your own worlds and requirement be creating bespoke XML Reset files |
