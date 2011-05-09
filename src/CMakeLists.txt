add_library(setikit ${LIB_TYPE}
                    sq_utils.c
                    sq_dsp.c
                    )

set_target_properties(setikit PROPERTIES LINKER_LANGUAGE "C")
set_target_properties(setikit PROPERTIES OUTPUT_NAME "setikit")
set_target_properties(setikit PROPERTIES VERSION ${setikit_VERSION})
set_target_properties(setikit PROPERTIES SOVERSION ${setikit_VERSION_MAJOR})

set(CORELIBS ${FFTW_LIBRARIES} ${GSL_LIBRARY} m)
target_link_libraries(setikit ${CORELIBS})

add_subdirectory(blocks)
