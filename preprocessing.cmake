function(JOIN VALUES GLUE OUTPUT)
  string (REGEX REPLACE "([^\\]|^);" "\\1${GLUE}" _TMP_STR "${VALUES}")
  string (REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}") #fixes escaping
  set (${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
endfunction()

# Get the file names
file(GLOB FORMULA_ALL_FILES RELATIVE "${PROJECT_SOURCE_DIR}/src" src/formulas/*.h)

# Filter the files
foreach(file ${FORMULA_ALL_FILES})
    if (NOT ${file} MATCHES "(all|Formula|UserDefined)\\.h$")
        list(APPEND FORMULA_FILES ${file})
    endif()
endforeach()

# Get the formula names
foreach(file ${FORMULA_FILES})
    string(REGEX MATCH "([a-zA-Z0-9]+)\\.h$" match ${file})
    list(APPEND FORMULA_NAMES ${CMAKE_MATCH_1})
    list(APPEND QUOTED_FORMULA_NAMES "\"${CMAKE_MATCH_1}\"")
endforeach()

# Create a C++ array
JOIN("${QUOTED_FORMULA_NAMES}" ", " FORMULA_NAMES_ARRAY)

# Create formula creation code
foreach(formula ${FORMULA_NAMES})
    list(APPEND FORMULA_CODE_LINES "if (name == \"${formula}\") return new ${formula}()\;")
    list(APPEND FORMULA_CODE_LINES_WITH_PARAMS "if (name == \"${formula}\") return new ${formula}(params)\;")
endforeach()
JOIN("${FORMULA_CODE_LINES}" "\n" FORMULA_CODE)
JOIN("${FORMULA_CODE_LINES_WITH_PARAMS}" "\n" FORMULA_CODE_WITH_PARAMS)

# Create include FORMULA_CODE_LINES
foreach(file ${FORMULA_FILES})
    list(APPEND FORMULA_INCLUDE_LINES "#include \"${file}\"")
endforeach()
JOIN("${FORMULA_INCLUDE_LINES}" "\n" FORMULA_INCLUDES)