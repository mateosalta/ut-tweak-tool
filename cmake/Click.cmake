if(CLICK_MODE)
  if(NOT DEFINED BZR_SOURCE)
    set(BZR_SOURCE "lp:${LP_PROJECT}")
    message("-- Setting BZR_SOURCE to ${BZR_SOURCE}")
  endif(NOT DEFINED BZR_SOURCE)

  set(QT_IMPORTS_DIR "/lib/${ARCH_TRIPLET}")
  set(CMAKE_INSTALL_PREFIX /)
  set(DATA_DIR /)

  # Path for ut-tweak-tool executable
  set(BIN_DIR ${DATA_DIR}lib/${ARCH_TRIPLET}/bin)
else(CLICK_MODE)
  execute_process(
    COMMAND qmake -query QT_INSTALL_QML
    OUTPUT_VARIABLE QT_IMPORTS_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  set(DATA_DIR ${CMAKE_INSTALL_DATADIR}/${APP_NAME})
endif(CLICK_MODE)

