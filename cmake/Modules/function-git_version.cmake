# A function to parse verson numbers into their parts
include("${CMAKE_CURRENT_LIST_DIR}/function-parse_version.cmake")

# A function to detect a components version number from git tags.
function( GIT_VERSION VAR_PREFIX)

set( GIT_INFO ID AUTHOR DATE BRANCH DESC )

set( GIT_COMMIT_ID_DEFAULT      "UNKNOWN" )
set( GIT_COMMIT_AUTHOR_DEFAULT  "UNKNOWN" )
set( GIT_COMMIT_DATE_DEFAULT    "UNKNOWN" )
set( GIT_COMMIT_BRANCH_DEFAULT  "UNKNOWN" )
set( GIT_COMMIT_DESC_DEFAULT    "None" )

# we need git of course...
find_package( Git )
if( GIT_FOUND )
  # make sure that this is actually a git repo
  execute_process( COMMAND ${GIT_EXECUTABLE} status
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   RESULT_VARIABLE IsGitRepo
                   OUTPUT_VARIABLE OutputTrash
                   ERROR_VARIABLE ErrorTrash)

  if( ${IsGitRepo} EQUAL 0 )
    if( "${GIT_COMMIT_ID}" STREQUAL "" )
      execute_process( COMMAND ${GIT_EXECUTABLE} rev-parse --sq HEAD 
                       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                       OUTPUT_VARIABLE GIT_COMMIT_ID
                       ERROR_VARIABLE Trash)
    endif()
    if( "${GIT_COMMIT_AUTHOR}" STREQUAL "" )
      execute_process( COMMAND ${GIT_EXECUTABLE} log -n1 --pretty="%an" HEAD
                       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                       OUTPUT_VARIABLE GIT_COMMIT_AUTHOR
                       ERROR_VARIABLE Trash)
    endif()
    if( "${GIT_COMMIT_DATE}" STREQUAL "" )
      execute_process( COMMAND ${GIT_EXECUTABLE} log -n1 --pretty="%aD" HEAD
                       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                       OUTPUT_VARIABLE GIT_COMMIT_DATE
                       ERROR_VARIABLE Trash)
    endif()
    if( "${GIT_COMMIT_BRANCH}" STREQUAL "" )
      execute_process( COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
                       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                       OUTPUT_VARIABLE GIT_COMMIT_BRANCH
                       ERROR_VARIABLE Trash)
    endif()
    if( "${GIT_COMMIT_DESC}" STREQUAL "" )
      # check to see if there are any tags
      execute_process( COMMAND ${GIT_EXECUTABLE} tag
                       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                       OUTPUT_VARIABLE Tmp
                       ERROR_VARIABLE Trash)
      if( NOT "${Tmp}" STREQUAL "" )
        # at least one tag (appears to) exist
        execute_process( COMMAND ${GIT_EXECUTABLE} describe --tags HEAD
                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                         OUTPUT_VARIABLE GIT_COMMIT_DESC
                         ERROR_VARIABLE Trash)
      else()
        # no tag found. assume 0.0
        set( GIT_COMMIT_DESC "0.0" )
      endif()
    endif()
  else()
    message( WARNING "Source directory is not a git repo." )
    set( GIT_COMMIT_DESC "0.0.0" )
    set( GIT_COMMIT_BRANCH "none" )
  endif()
else()
  message( WARNING "Could not find git command" )
  set( GIT_COMMIT_DESC "0.0" )
  set( GIT_COMMIT_BRANCH "none" )
endif()

# set defaults for any items that were not found
foreach( item ${GIT_INFO} )
  if( "${GIT_COMMIT_${item}}" STREQUAL "" )
    set( GIT_COMMIT_${item} ${GIT_COMMIT_${item}_DEFAULT} )
  endif()
endforeach( item )

# remove quotes, backslashes, and new lines
# these cause problems when trying to embed version numbers into source files.
foreach( item ${GIT_INFO} )
  string( REPLACE "'"  "" GIT_COMMIT_${item}   ${GIT_COMMIT_${item}} )
  string( REPLACE "\"" "" GIT_COMMIT_${item}   ${GIT_COMMIT_${item}} )
  string( REPLACE "\n" "" GIT_COMMIT_${item}   ${GIT_COMMIT_${item}} )
endforeach( item )

# set full version string
set(VERSION_FULL "${GIT_COMMIT_DESC}-${GIT_COMMIT_BRANCH}" )

parse_version( ${VERSION_FULL} "" )

# now set version information in the parent scope
set( ${VAR_PREFIX}_VERSION_FULL   ${VERSION_FULL}  PARENT_SCOPE )
set( ${VAR_PREFIX}_VERSION        ${VERSION}       PARENT_SCOPE )
set( ${VAR_PREFIX}_VERSION_MAJOR  ${VERSION_MAJOR} PARENT_SCOPE )
set( ${VAR_PREFIX}_VERSION_MINOR  ${VERSION_MINOR} PARENT_SCOPE )
set( ${VAR_PREFIX}_VERSION_PATCH  ${VERSION_PATCH} PARENT_SCOPE )

endfunction(GIT_VERSION)

