# temoto\_action\_designer

## Obtain the source files

Clone the repository recursively with the temoto\_action\_engine submodule.

`git clone --recurse-submodules https://github.com/temoto-framework/temoto_action_designer.git`
`pip3 install Jinja2`

## Build instructions

Create a directory for build files and navigate into it.

`mkdir build && cd build`

Generate build files using CMake.

`cmake ..`

Compile the Temoto Action Designer.

`make`

And run it.

`./temoto_action_designer`
