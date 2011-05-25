# Compile each standalone program

INCLUDE_DIRECTORIES(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/../) 

set(PROGRAMS sqfft 
             sqpower 
             sqread 
             sqreal 
             sqimag 
             sqsample 
             sqsum 
             sqwindow 
             sqoffset 
             sqconjugate 
             sqscaleandrotate 
             sqmix
             sqzoom
             sqpnm
             sqwola
             sqgensine
   )

foreach(program ${PROGRAMS})
    add_executable(${program} ${program}.c)
    target_link_libraries(${program} setikit)
endforeach(program)

