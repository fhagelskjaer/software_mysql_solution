# CMake simple example

## [main]

# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
cmake_minimum_required(VERSION 3.1...3.28)

# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables
project(
  ModernCMakeExample
  VERSION 1.0
  LANGUAGES CXX)

# If you set any CMAKE_ variables, that can go here.
# (But usually don't do this, except maybe for C++ standard)

# Find packages go here.

# You should usually split this into folders, but this is a simple example

# This is a "default" library, and will match the *** variable setting.
# Other common choices are STATIC, SHARED, and MODULE
# Including header files here helps IDEs but is not required.
# Output libname matches target name, with the usual extensions on your system

find_package(Qt5Sql REQUIRED)

# Link each target with other targets or add options, etc.
add_executable(MainTest main.cpp)
target_link_libraries(MainTest  Qt5::Core Qt5::Sql)


add_executable(MainRobot main_robot.cpp)
target_link_libraries(MainRobot  Qt5::Core Qt5::Sql)

# Make sure you link your targets with this command. It can also link libraries and
# even flags, so linking a target that does not exist will not give a configure-time error.



## [main]

# This part is so the Modern CMake book can verify this example builds. For your code,
# you'll probably want tests too


