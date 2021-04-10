cmake_minimum_required(VERSION 3.20)

project(CaseByCase)

add_executable(Game
  src/main.cpp
  src/Objects.cpp
  src/Sound.cpp
  src/StageData.cpp
)

target_compile_features(Game
  PRIVATE cxx_std_17
)

find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(/usr/local/include)

target_link_libraries(Game -lftgl -lfreetype -lSDL2 -lSDL2_mixer -lGL)
