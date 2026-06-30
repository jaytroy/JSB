# JSBSim flight simulator
This is a barebones implementation of a flight simulator using JSBSim and C++. At the moment, it's tested on Ubuntu 24.04 and is unlikely to compile on dissimilar OS's.

Start off by cloning the [JSBSim git repo](https://github.com/JSBSim-Team/jsbsim.git) somewhere.

### Run with Docker compose:
Make sure this line in `docker-compose.yml` points to the directory you cloned above:
```yaml
volumes: 
  - /your/jsb/dir:/app/jsbsim
```

Then run the container with:
```shell
docker compose run --rm -it simulation
```

### Compile from source
You're gonna need to install the required libraries:
```shell
sudo apt install cmake build-essential pkg-config libncurses-dev
```
```shell
sudo apt-get install -y ./libraries/JSBSim_*.deb ./libraries/JSBSim-devel_*.deb
````

Then run it with:
```shell
rm -rf build && cmake -B build && cmake --build build && ./build/JSB
```
You can generally omit the first two commands.

Make sure you have your environment variables set
```dotenv
jsbSimDir="/home/usr/yourjsbdir"
```


### Todo:
| Feature                   | Status | Notes |
|---------------------------|--------|-------|
| Graphics (OpenGL)         | TBD    | Or UEngine/FlightGear instead? Ideally modular. |
| Environment Variables     | Done   | So that users don't have to modify code directly |
| Better FCS strat creation | Almost | Implement factory pattern to declutter FCS strat creation |
| Expand FCS functionality  | TBD    | Implement more than barebones flight controls |
| Dockerize                 | Done   | Make it run anywhere! (that runs Docker) |
| Aircraft selection        | TBD    | Fly something other than a measly 172P |
| Multiple aircraft at once | TBD    | Allow the user to perform mid-air collisions |
| Custom environments       | TBD    | Set up your own worlds and environments be creating bespoke XML Reset files |
| Switch NCurses for something better | TBD    | Curses only allows for keyboard input at a time. Replace with sdl2? |
| Unit tests | TBD | Oh no |
