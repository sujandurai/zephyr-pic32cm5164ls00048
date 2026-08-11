add_subdirectory(common)
add_subdirectory_given_handle(SOC_SERIES ${SOC_SERIES})

zephyr_include_directories(${SOC_SERIES})
zephyr_include_directories(common)