project(riot-editor)

add_executable(riot-editor)
target_link_libraries(riot-editor PRIVATE
        riot::lib
		riot::ext
        )
target_include_directories(riot-editor PRIVATE src)

if(CMAKE_CXX_COMPILER_ID STREQUAL Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_compile_options(riot-editor PRIVATE
          -Wall -Wextra -Wpedantic -Wconversion -Werror=return-type
          )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
  target_compile_options(riot-editor PRIVATE
          /W4 /WX
          )
endif()


target_sources(riot-editor PRIVATE
        src/main.cpp
        )

if(GENESIS_PCH)
  target_precompile_headers(genesis-editor PRIVATE
          <vector>
          )
endif()
