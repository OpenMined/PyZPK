add_library(pyzpk SHARED PyZPK/main.cpp)

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