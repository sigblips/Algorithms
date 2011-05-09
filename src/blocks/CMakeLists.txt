# Compile each standalone program

set(CORELIBS ${FFTW_LIBRARIES} ${GSL_LIBRARY} m)
set(PROGRAMS sqfft sqpower sqread sqsamples sqsum sqwindow)

foreach(program ${PROGRAMS})
    add_executable(${program} ${program}.c)
    target_link_libraries(${program} ${CORELIBS})
endforeach(program)

