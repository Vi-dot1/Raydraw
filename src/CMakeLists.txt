
# Each folder is listed indivicually
file(GLOB_RECURSE SOURCE_STATE CONFIGURE_DEPENDS State/*.cpp)
file(GLOB_RECURSE SOURCE_GUI CONFIGURE_DEPENDS Gui/*.cpp)
file(GLOB_RECURSE SOURCE_TOOLS CONFIGURE_DEPENDS Tools/*.cpp)

# Everything else is listed here and bundled into the main 
file(GLOB SOURCE_EXECUTABLE CONFIGURE_DEPENDS *.cpp)

target_sources(${PROJECT_NAME} 
PRIVATE 
    ${SOURCE_STATE} 
    ${SOURCE_GUI} 
    ${SOURCE_TOOLS} 
    
    ${SOURCE_EXECUTABLE}
)


