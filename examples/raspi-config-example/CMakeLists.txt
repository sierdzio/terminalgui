add_executable(raspi-config-example
    main.cpp
    mainwindow.h mainwindow.cpp
    menu/item.h menu/item.cpp
    menu/actions.h menu/actions.cpp
)

target_link_libraries(raspi-config-example PUBLIC terminalgui)
