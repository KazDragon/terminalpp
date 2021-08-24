# A function to parse verson numbers into their parts
function( PARSE_VERSION VERSION PREFIX )

# look for major, minor, and patch numbers in the version string
# this is required if the developer uses CPack for example.
# need to consider two possible formats:
#    Major.Minor.Patch
# or 
#    Major.Minor-PatchStr
# the first format is the standard format used for version numbers,
# but would have to be set by the developer as a tag name.
# however, if the developer just sets a major and minor version with
# a tag, then git will add the number of commits since the tag. for example
#     0.1-10-devel
# indicates that this is the 10th commit on the devel branch after 0.1 patch.
# 
# so, we assume
# version components may be separated by '.' or '-'
# version components must be numerical (this is what cmake supoorts)
#
# we parse by matching a version component and then removing it from the
# version string.

# set full version string to the raw string passed in
set( VERSION_FULL ${VERSION} )

# first number in version string will be the major version number
# version string may be preceeded by a 'v'
set( RE "^v*([0-9]+)[\\.\\-](.*)$" )
if( ${VERSION} MATCHES ${RE} )
  set( VERSION_MAJOR ${CMAKE_MATCH_1} )
  string( REGEX REPLACE ${RE} "\\2" VERSION "${VERSION}" )
else()
  set( VERSION_MAJOR "" )
endif()

# second number in version string will be minor version number
set( RE "^([0-9]+)[\\.\\-](.*)$" )
if( ${VERSION} MATCHES ${RE} )
  set( VERSION_MINOR ${CMAKE_MATCH_1} )
  string( REGEX REPLACE ${RE} "\\2" VERSION "${VERSION}" )
else()
  set( VERSION_MINOR "" )
endif()

# third number in version string will be patch version number
set( RE "^([0-9]+)[\\.\\-](.*)$" )
if( ${VERSION} MATCHES ${RE} )
  set( VERSION_PATCH ${CMAKE_MATCH_1} )
  string( REGEX REPLACE ${RE} "\\2" VERSION "${VERSION}" )
else()
  set( VERSION_PATCH "" )
endif()

# fourth number in version string will be teak version number
# teak number should be the last number
set( RE "^([0-9]+)(.*)$" )
if( ${VERSION} MATCHES ${RE} )
  set( VERSION_TWEAK ${CMAKE_MATCH_1} )
  string( REGEX REPLACE ${RE} "\\2" VERSION "${VERSION}" )
else()
  set( VERSION_TWEAK "" )
endif()


# if the version string passed in coudl be parsed,
# construct a cmake-compatible version string
# to put in ${PREFIX}VERSION. otherwise, just
# set ${PREFIX}VERSION to the string that was passed in.
if( NOT ${VERSION_MAJOR} EQUAL "" )
  set(VERSION ${VERSION_MAJOR})
else()
  set(VERSION ${VERSION_FULL})
endif()
if( NOT ${VERSION_MINOR} EQUAL "" )
  set(VERSION ${VERSION}.${VERSION_MINOR})
endif()
if( NOT ${VERSION_PATCH} EQUAL "" )
  set(VERSION ${VERSION}.${VERSION_PATCH})
endif()
if( NOT ${VERSION_TWEAK} EQUAL "" )
  set(VERSION ${VERSION}.${VERSION_TWEAK})
endif()

# set variables in parent's scope
set( ${PREFIX}VERSION_FULL ${VERSION_FULL} PARENT_SCOPE )
set( ${PREFIX}VERSION ${VERSION} PARENT_SCOPE )
set( ${PREFIX}VERSION_MAJOR ${VERSION_MAJOR} PARENT_SCOPE )
set( ${PREFIX}VERSION_MINOR ${VERSION_MINOR} PARENT_SCOPE )
set( ${PREFIX}VERSION_PATCH ${VERSION_PATCH} PARENT_SCOPE )
set( ${PREFIX}VERSION_TWEAK ${VERSION_TWEAK} PARENT_SCOPE )


endfunction(PARSE_VERSION)

