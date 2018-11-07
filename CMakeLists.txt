cmake_minimum_required(VERSION 3.13)
project(Pong)

###############################################################################
## file globbing ##############################################################
###############################################################################

# these instructions search the directory tree when cmake is
# invoked and put all files that match the pattern in the variables 
# `sources` and `data`
file(GLOB_RECURSE sources      Pong/*.cpp Pong/*.h)

###############################################################################
## target definitions #########################################################
###############################################################################

# add the data to the target, so it becomes visible in some IDE
add_executable(Pong ${sources} ${data})

# this lets me include files relative to the root src dir with a <> pair
target_include_directories(Pong PUBLIC Pong)

###############################################################################
## dependencies ###############################################################
###############################################################################

###############################################################################
## testing ####################################################################
###############################################################################

###############################################################################
## packaging ##################################################################
###############################################################################

# all install commands get the same destination. this allows us to use paths
# relative to the executable.
install(TARGETS Pong DESTINATION bin)

# now comes everything we need, to create a package
# there are a lot more variables you can set, and some
# you need to set for some package types, but we want to
# be minimal here
set(CPACK_PACKAGE_NAME "Pong")
set(CPACK_PACKAGE_VERSION "0.1")

# we don't want to split our program up into several things
set(CPACK_MONOLITHIC_INSTALL 1)

# This must be last
include(CPack)