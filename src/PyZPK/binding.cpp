#include <pybind11/pybind11.h>
namespace py = pybind11;

void init_data_structures_integer_permutation(py::module &);
void init_data_structures_set_commitment(py::module &);
void init_algorithms_benes(py::module &);
void init_algorithms_as_waksman(py::module &);
void init_default_types_r1cs_ppzkpcd_pp(py::module &);
void init_default_types_tinyram_ppzksnark_pp(py::module &);
void init_relations_constraint_satisfaction_problems_r1cs_examples(py::module &);
void init_relations_arithmetic_programs_qap(py::module &);
void init_relations_arithmetic_programs_sap(py::module &);

PYBIND11_MODULE(pyzpk, m)
{
    m.doc() = "Python wrapper for open source Zero Proof Knowledge Library";
    
    init_data_structures_integer_permutation(m);
    init_data_structures_set_commitment(m);
    init_algorithms_benes(m);
    init_algorithms_as_waksman(m);
    init_default_types_r1cs_ppzkpcd_pp(m);
    init_default_types_tinyram_ppzksnark_pp(m);
    init_relations_constraint_satisfaction_problems_r1cs_examples(m);
    init_relations_arithmetic_programs_qap(m);
    init_relations_arithmetic_programs_sap(m);
}