set(
  SRC
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/utils/Fp_model.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/common/data_structures/integer_permutation.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/common/data_structures/set_commitment.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/common/routing_algorithms/benes_routing_algorithm.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/common/routing_algorithms/as_waksman_routing_algorithm.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/common/default_types/r1cs_ppzkpcd_pp.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/common/default_types/tinyram_ppzksnark_pp.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/constraint_satisfaction_problems/r1cs/r1cs.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/constraint_satisfaction_problems/r1cs/r1cs_examples.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/constraint_satisfaction_problems/uscs/uscs.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/constraint_satisfaction_problems/uscs/uscs_examples.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/arithmetic_programs/qap.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/arithmetic_programs/sap.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/arithmetic_programs/ssp.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/reductions/r1cs_to_qap.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/reductions/uscs_to_ssp.cpp"
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