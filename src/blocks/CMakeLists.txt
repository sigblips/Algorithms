# Compile each standalone program

set(PROGRAMS sqfft sqpower sqread sqsamples sqsum sqwindow)

foreach(program ${PROGRAMS})
    add_executable(${program} ${program}.c)
    target_link_libraries(${program} ${setikit})
endforeach(program)

