# temoto\_action\_designer

## Obtain the source files

Clone the repository recursively with the temoto\_action\_engine submodule.

`git clone --recurse-submodules https://github.com/temoto-framework/temoto_action_designer.git`
`pip3 install Jinja2`

## Create action package

```bash
python package_generator/scripts/generate_package.py \
--umrf-json <PATH_TO_UMRF_JSON> \
--output <PATH_WHERE_THE_PACKAGE_IS_GENERATED> \
--templates package_generator/templates/ \
--framework <choose either 'CMake' or 'ROS2'>
```
