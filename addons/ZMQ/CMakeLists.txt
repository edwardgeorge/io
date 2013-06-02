# Base Io build system
# Written by Jeremy Tregunna <jeremy.tregunna@me.com>
#
# Builds the Cairo addon

# Find cairo
find_package(ZeroMQ)

# Create the _build bundle hierarchy if needed.
make_build_bundle(_build)

# Did we find cairo? if so, set up the targets and all the support
# variables.
if(ZEROMQ_FOUND)
        # Output our dynamic library to the top-level _build hierarchy
        set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/_build/dll)

        # Additional include directories
        include_directories(${ZEROMQ_INCLUDE_DIR})

        # Additional link directories
        link_directories(${ZEROMQ_LIBRARY_DIR})

        # Generate the IoZMQInit.c file.
        # Argument SHOULD ALWAYS be the exact name of the addon, case is
        # important.
        generate_ioinit(ZMQ)

        # Our library sources.
        set(SRCS
                "${CMAKE_CURRENT_SOURCE_DIR}/source/IoZMQ.c"
                "${CMAKE_CURRENT_SOURCE_DIR}/source/IoZMQContext.c"
                "${CMAKE_CURRENT_SOURCE_DIR}/source/IoZMQSocket.c"
                "${CMAKE_CURRENT_SOURCE_DIR}/source/IoZMQInit.c"
        )

        # Now build the shared library
        add_library(IoZMQ SHARED ${SRCS})
        add_dependencies(IoZMQ iovmall)
        target_link_libraries(IoZMQ iovmall ${ZEROMQ_LIBRARY} ${LIBS})

        # Install the addon to our global addons hierarchy.
        install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION lib/io/addons)
        install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/_build DESTINATION lib/io/addons/ZMQ)
endif(ZEROMQ_FOUND)
