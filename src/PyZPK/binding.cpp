#include <pybind11/pybind11.h>
namespace py = pybind11;

void init_utils(py::module &);
void init_data_structures_integer_permutation(py::module &);
void init_data_structures_set_commitment(py::module &);
void init_algorithms_benes(py::module &);
void init_algorithms_as_waksman(py::module &);
void init_default_types_r1cs_ppzkpcd_pp(py::module &);
void init_default_types_tinyram_ppzksnark_pp(py::module &);
void init_relations_variable(py::module &);
void init_relations_constraint_satisfaction_problems_r1cs(py::module &);
void init_relations_constraint_satisfaction_problems_r1cs_examples(py::module &);
void init_relations_constraint_satisfaction_problems_uscs(py::module &);
void init_relations_constraint_satisfaction_problems_uscs_examples(py::module &);
void init_relations_circuit_satisfaction_problems_bacs(py::module &);
void init_relations_circuit_satisfaction_problems_bacs_examples(py::module &);
void init_relations_circuit_satisfaction_problems_tbcs(py::module &);
void init_relations_circuit_satisfaction_problems_tbcs_examples(py::module &);
void init_relations_arithmetic_programs_qap(py::module &);
void init_relations_arithmetic_programs_sap(py::module &);
void init_relations_arithmetic_programs_ssp(py::module &);
void init_relations_ram_computations_memory(py::module &);
void init_relations_ram_computations_rams_tinyram(py::module &);
void init_relations_ram_computations_rams_fooram(py::module &);
void init_reductions_bacs_to_r1cs(py::module &);
void init_reductions_r1cs_to_qap(py::module &);
void init_reductions_uscs_to_ssp(py::module &);
void init_gadgetlib1_constraint_profiling(py::module &);
void init_gadgetlib1_gadget(py::module &);
void init_gadgetlib1_protoboard(py::module &);
void init_gadgetlib1_pb_variable(py::module &);
void init_gadgetlib1_gadgets_basic_gadgets(py::module &);
void init_gadgetlib1_gadgets_from_r1cs(py::module &);
void init_gadgetlib1_fooram_components(py::module &);
void init_gadgetlib1_fooram_cpu_checker(py::module &);
void init_gadgetlib1_tinyram_components(py::module &);
void init_gadgetlib1_tinyram_word_variable_gadget(py::module &);
void init_gadgetlib1_tinyram_alu_arithmetic(py::module &);
void init_gadgetlib1_tinyram_alu_control_flow(py::module &);
void init_gadgetlib1_tinyram_alu_gadget(py::module &);
void init_gadgetlib1_tinyram_argument_decoder_gadget(py::module &);
void init_gadgetlib1_tinyram_consistency_enforcer_gadget(py::module &);
void init_gadgetlib1_tinyram_memory_masking_gadget(py::module &);
void init_gadgetlib1_curves_weierstrass_g1_gadget(py::module &);
void init_gadgetlib1_curves_weierstrass_g2_gadget(py::module &);
void init_gadgetlib1_hashes_hash_io(py::module &);
void init_gadgetlib1_hashes_digest_selector_gadget(py::module &);
void init_gadgetlib1_hashes_knapsack_gadget(py::module &);
void init_gadgetlib1_hashes_sha256_aux_gadget(py::module &);
void init_gadgetlib1_hashes_sha256_components(py::module &);
void init_gadgetlib1_hashes_sha256_gadget(py::module &);
void init_merkle_authentication_path_variable(py::module &);
void init_merkle_tree_check_read_gadget(py::module &);
void init_merkle_tree_check_update_gadget(py::module &);
void init_gadgetlib1_pairing_weierstrass_final_exponentiation(py::module &);
void init_gadgetlib1_pairing_weierstrass_miller_loop(py::module &);
void init_gadgetlib1_pairing_weierstrass_precomputation(py::module &);
void init_gadgetlib1_pairing_pairing_checks(py::module &);
void init_gadgetlib1_routing_as_waksman_routing_gadget(py::module &);
void init_gadgetlib1_routing_benes_routing_gadget(py::module &);
void init_gadgetlib1_routing_profile_routing_gadgets(py::module &);
void init_set_commitment_gadget(py::module &);
void init_set_membership_proof_variable(py::module &);
void init_gadgetlib1_verifiers_r1cs_ppzksnark_verifier_gadget(py::module &);
void init_gadgetlib2_infrastructure(py::module &);
void init_gadgetlib2_pp(py::module &);
void init_gadgetlib2_variable(py::module &);
void init_gadgetlib2_constraint(py::module &);
void init_gadgetlib2_Protoboard(py::module &);
void init_gadgetlib2_integration(py::module &);
void init_gadgetlib2_gadget(py::module &);
void init_gadgetlib2_adapters(py::module &);
void init_zk_proof_systems_pcd_r1cs_pcd_compliance_predicate(py::module &);
void init_zk_proof_systems_pcd_r1cs_pcd_cp_handler(py::module &);
void init_zk_proof_systems_pcd_r1cs_pcd_r1cs_pcd_params(py::module &);
void init_zk_proof_systems_pcd_r1cs_pcd_tally_cp(py::module &);
void init_zk_proof_systems_ppzksnark_r1cs_ppzksnark_r1cs_ppzksnark(py::module &);

PYBIND11_MODULE(pyzpk, m)
{
    m.doc() = "Python wrapper for open source Zero Proof Knowledge Library";

    init_utils(m);
    init_data_structures_integer_permutation(m);
    init_data_structures_set_commitment(m);
    init_algorithms_benes(m);
    init_algorithms_as_waksman(m);
    init_default_types_r1cs_ppzkpcd_pp(m);
    init_default_types_tinyram_ppzksnark_pp(m);
    init_relations_variable(m);
    init_relations_constraint_satisfaction_problems_r1cs(m);
    init_relations_constraint_satisfaction_problems_r1cs_examples(m);
    init_relations_constraint_satisfaction_problems_uscs(m);
    init_relations_constraint_satisfaction_problems_uscs_examples(m);
    init_relations_circuit_satisfaction_problems_bacs(m);
    init_relations_circuit_satisfaction_problems_bacs_examples(m);
    init_relations_circuit_satisfaction_problems_tbcs(m);
    init_relations_circuit_satisfaction_problems_tbcs_examples(m);
    init_relations_arithmetic_programs_qap(m);
    init_relations_arithmetic_programs_sap(m);
    init_relations_arithmetic_programs_ssp(m);
    init_relations_ram_computations_memory(m);
    init_relations_ram_computations_rams_tinyram(m);
    init_relations_ram_computations_rams_fooram(m);
    init_reductions_bacs_to_r1cs(m);
    init_reductions_r1cs_to_qap(m);
    init_reductions_uscs_to_ssp(m);
    init_gadgetlib1_constraint_profiling(m);
    init_gadgetlib1_gadget(m);
    init_gadgetlib1_protoboard(m);
    init_gadgetlib1_pb_variable(m);
    init_gadgetlib1_gadgets_basic_gadgets(m);
    init_gadgetlib1_gadgets_from_r1cs(m);
    init_gadgetlib1_fooram_components(m);
    init_gadgetlib1_fooram_cpu_checker(m);
    init_gadgetlib1_tinyram_components(m);
    init_gadgetlib1_tinyram_word_variable_gadget(m);
    init_gadgetlib1_tinyram_alu_arithmetic(m);
    init_gadgetlib1_tinyram_alu_control_flow(m);
    init_gadgetlib1_tinyram_alu_gadget(m);
    init_gadgetlib1_tinyram_argument_decoder_gadget(m);
    init_gadgetlib1_tinyram_consistency_enforcer_gadget(m);
    init_gadgetlib1_tinyram_memory_masking_gadget(m);
    init_gadgetlib1_curves_weierstrass_g1_gadget(m);
    init_gadgetlib1_curves_weierstrass_g2_gadget(m);
    init_gadgetlib1_hashes_hash_io(m);
    init_gadgetlib1_hashes_digest_selector_gadget(m);
    init_gadgetlib1_hashes_knapsack_gadget(m);
    init_gadgetlib1_hashes_sha256_aux_gadget(m);
    init_gadgetlib1_hashes_sha256_components(m);
    init_gadgetlib1_hashes_sha256_gadget(m);
    init_merkle_authentication_path_variable(m);
    init_merkle_tree_check_read_gadget(m);
    init_merkle_tree_check_update_gadget(m);
    init_gadgetlib1_pairing_weierstrass_final_exponentiation(m);
    init_gadgetlib1_pairing_weierstrass_miller_loop(m);
    init_gadgetlib1_pairing_weierstrass_precomputation(m);
    init_gadgetlib1_pairing_pairing_checks(m);
    init_gadgetlib1_routing_as_waksman_routing_gadget(m);
    init_gadgetlib1_routing_benes_routing_gadget(m);
    init_gadgetlib1_routing_profile_routing_gadgets(m);
    init_set_commitment_gadget(m);
    init_set_membership_proof_variable(m);
    init_gadgetlib1_verifiers_r1cs_ppzksnark_verifier_gadget(m);
    init_gadgetlib2_infrastructure(m);
    init_gadgetlib2_pp(m);
    init_gadgetlib2_variable(m);
    init_gadgetlib2_constraint(m);
    init_gadgetlib2_Protoboard(m);
    init_gadgetlib2_integration(m);
    init_gadgetlib2_gadget(m);
    init_gadgetlib2_adapters(m);
    init_zk_proof_systems_pcd_r1cs_pcd_compliance_predicate(m);
    init_zk_proof_systems_pcd_r1cs_pcd_cp_handler(m);
    init_zk_proof_systems_pcd_r1cs_pcd_r1cs_pcd_params(m);
    init_zk_proof_systems_pcd_r1cs_pcd_tally_cp(m);
    init_zk_proof_systems_ppzksnark_r1cs_ppzksnark_r1cs_ppzksnark(m);
}