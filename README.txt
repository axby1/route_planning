(Linux)install all the requirements
sudo apt update
sudo apt install build-essential
sudo apt install cmake
sudo apt install libcairo2-dev
sudo apt install libgraphicsmagick1-dev
sudo apt install libpng-dev
sudo apt install libpugixml-dev
sudo apt install libgtest-dev

this is done to install io2d{ 

git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
cd P0267_RefImpl
mkdir Debug
cd Debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
sudo make install

}
rest is normal cmake tasks

when u run cmake .. if any error like this module not found write seperate .cmake file to help cmake locate it
 
execute: ./OSM_A_star_search
