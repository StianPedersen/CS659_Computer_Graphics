# The COMPONENTS part checks that OGRE was built the way we need it
# The CONFIG flag makes sure we get OGRE instead of OGRE-next
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)
 
# add the source files as usual
add_executable(lab src/BaseApplication.cpp src/BaseApplication.h src/TutorialApplication.cpp src/TutorialApplication.h)

# this also sets the includes and pulls third party dependencies
target_link_libraries(lab OgreBites)
