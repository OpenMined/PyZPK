#include <pybind11/pybind11.h>
namespace py = pybind11;

void init_utils_Fp_model(py::module &);
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

PYBIND11_MODULE(pyzpk, m)
{
    m.doc() = "Python wrapper for open source Zero Proof Knowledge Library";

    init_utils_Fp_model(m);
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
}