# Locate PugiXML library
# This script sets the following variables:
# PUGIXML_FOUND - System has PugiXML
# PUGIXML_INCLUDE_DIRS - The PugiXML include directories
# PUGIXML_LIBRARIES - The libraries needed to use PugiXML

# Search for PugiXML library and include directories
find_path(PUGIXML_INCLUDE_DIRS NAMES pugixml.hpp
    HINTS
    /usr/include
    /usr/local/include
    /opt/local/include
    PATH_SUFFIXES pugixml
)

# Search for PugiXML library file
find_library(PUGIXML_LIBRARIES NAMES pugixml
    HINTS
    /usr/lib
    /usr/local/lib
    /opt/local/lib
)

# Check if PugiXML is found
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PugiXML DEFAULT_MSG
    PUGIXML_LIBRARIES PUGIXML_INCLUDE_DIRS
)

# Provide feedback to user if PugiXML is not found
if(NOT PUGIXML_FOUND)
    message(WARNING "PugiXML library not found. Check PUGIXML_INCLUDE_DIRS and PUGIXML_LIBRARIES.")
endif()

mark_as_advanced(PUGIXML_INCLUDE_DIRS PUGIXML_LIBRARIES)
