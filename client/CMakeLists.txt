add_executable(client
        src/main.cpp
        src/CGame.cpp
        src/CGame.h
        src/CCamera.cpp
        src/CCamera.h
        src/CEntity.cpp
        src/CEntity.h
        src/map/CMap.cpp
        src/map/CMap.h
        src/map/CMapCell.cpp
        src/map/CMapCell.h
        src/map/CBlock.cpp
        src/map/CBlock.h
        src/CTexture.cpp
        src/CTexture.h
)

target_link_libraries(client -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network)

add_custom_target(SFMLCopyBin
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/bin/ ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(CopyRes
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources/ ${CMAKE_CURRENT_BINARY_DIR}
)

add_dependencies(client SFMLCopyBin)
add_dependencies(client CopyRes)
