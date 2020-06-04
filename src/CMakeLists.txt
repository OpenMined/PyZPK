set(
  SRC
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/binding.cpp"
)

include_directories(BEFORE ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

pybind11_add_module(pyzpk ${SRC})
set_target_properties(pyzpk PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED TRUE)
set_target_properties(snark PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(ff PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
target_link_libraries(pyzpk PRIVATE snark)
target_link_libraries(pyzpk PRIVATE ff)


target_include_directories(
  pyzpk

  PRIVATE
  ${DEPENDS_DIR}/libsnark
  ${DEPENDS_DIR}/libsnark/depends/libfqfft
  ${DEPENDS_DIR}/libsnark/depends/libff
  ${DEPENDS_DIR}/pybind11/include
  ${PYTHON_INCLUDE_DIRS}
  ${PYBIND11_INCLUDE_DIRS}
)