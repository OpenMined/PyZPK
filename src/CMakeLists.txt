set(
  SRC
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/utils/utils.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/common/data_structures/integer_permutation.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/common/data_structures/set_commitment.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/common/routing_algorithms/benes_routing_algorithm.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/common/routing_algorithms/as_waksman_routing_algorithm.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/common/default_types/r1cs_ppzkpcd_pp.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/common/default_types/tinyram_ppzksnark_pp.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/variable.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/constraint_satisfaction_problems/r1cs/r1cs.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/constraint_satisfaction_problems/r1cs/r1cs_examples.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/constraint_satisfaction_problems/uscs/uscs.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/constraint_satisfaction_problems/uscs/uscs_examples.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/circuit_satisfaction_problems/bacs/bacs.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/circuit_satisfaction_problems/bacs/bacs_examples.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/circuit_satisfaction_problems/tbcs/tbcs.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/circuit_satisfaction_problems/tbcs/tbcs_examples.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/arithmetic_programs/qap.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/arithmetic_programs/sap.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/arithmetic_programs/ssp.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/ram_computations/memory/memory.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/ram_computations/rams/tinyram.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/relations/ram_computations/rams/fooram.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/reductions/uscs_to_ssp.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/reductions/r1cs_to_qap.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/reductions/bacs_to_r1cs.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/constraint_profiling.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/protoboard.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/pb_variable.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/basic_gadgets.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/gadget_from_r1cs.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/cpu_checkers/fooram/fooram_components.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/cpu_checkers/fooram/fooram_cpu_checker.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/cpu_checkers/tinyram/tinyram_protoboard.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/cpu_checkers/tinyram/word_variable_gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/cpu_checkers/tinyram/alu_arithmetic.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/cpu_checkers/tinyram/alu_control_flow.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/cpu_checkers/tinyram/alu_gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/cpu_checkers/tinyram/argument_decoder_gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/cpu_checkers/tinyram/consistency_enforcer_gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/cpu_checkers/tinyram/memory_masking_gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/curves/weierstrass_g1_gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/curves/weierstrass_g2_gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/hashes/hash_io.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/hashes/digest_selector_gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/hashes/knapsack_gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/hashes/sha256_aux.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/hashes/sha256_components.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/hashes/sha256_gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/merkle_tree/merkle_authentication_path_variable.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/merkle_tree/merkle_tree_check_read_gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/merkle_tree/merkle_tree_check_update_gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/pairing/weierstrass_final_exponentiation.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/pairing/weierstrass_miller_loop.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/pairing/weierstrass_precomputation.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/pairing/pairing_checks.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/routing/as_waksman_routing_gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/routing/benes_routing_gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/routing/profile_routing_gadgets.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/set_commitment/set_commitment_gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/set_commitment/set_membership_proof_variable.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib1/gadgets/verifiers/r1cs_ppzksnark_verifier_gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib2/infrastructure.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib2/pp.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib2/variable.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib2/constraint.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib2/protoboard.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib2/integration.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib2/gadget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/PyZPK/gadgetlib2/adapters.cpp"
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