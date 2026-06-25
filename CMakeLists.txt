# definindo versão do cmake e nome do projeto
cmake_minimum_required(VERSION 3.15)
project(hello-world)

# procura o pacote 
find_package(SDL3 CONFIG REQUIRED)

# adiciona o executavel
add_executable(${PROJECT_NAME} main.cpp)

# define onde o executável final vai ser salvo
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)

# linkando a biblioteca do sdl3
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

# copia o arquivo dll ao lado do executavel automaticamente
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy_if_different
   "$<TARGET_FILE:SDL3::SDL3>"
   "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)

