![OpenMined-logo](https://github.com/OpenMined/design-assets/blob/master/logos/OM/horizontal-primary-trans.png)
![](https://github.com/OpenMined/PyZPK/workflows/Tests/badge.svg)
[![License](https://img.shields.io/badge/License-Apache-yellow.svg)](https://github.com/OpenMined/PyZPK/blob/master/LICENSE)
[![Python 3.5,3.6,3.7](https://img.shields.io/badge/python-3.5,3.6,3.7-blue.svg)](https://www.python.org/downloads/release/python-370/)

# PyZPK
PyZPK is a Python wrapper for open-source Zero Proof Knowledge Library, [libsnark](https://github.com/scipr-lab/libsnark). This library provides a set of zkSNARK schemes, a cryptographic method for proving/verifying, in zero-knowledge, the integrity of computations.

## Installation

**Build from Source**

If you want to install PyZPK from the repository, you should make sure to have the requirements for your platform. Currently, it supports Linux.

1. Clone this repository
```bash
$ git clone https://github.com/OpenMined/PyZPK.git
```
2. Get the third party libraries and the requirements (if you did not already) by running the following command from the root directory of the project. This script automates the installation of the prerequisite packages to get you started.
```bash
$ cd PyZPK
$ bash ext_source_setup.sh
```
3. Build the PyZPK library
```bash
$ bash build.sh
```

## Support

PyZPK is part of the OpenMined community, join the rapidly growing community of 8000+ on Slack. The slack community is friendly and great about quickly answering questions and getting your doubts cleared plus; it is a great place to interact with fellow community members with similar interests such as yours. [Click here to join our Slack community!](https://slack.openmined.org)

## Contributing
Pull requests are welcome. For significant changes, please open an issue first to discuss what you would like to change.
Read the OpenMined contributing [guidelines](https://github.com/OpenMined/PyZPK/blob/master/CONTRIBUTING.md) and [styleguide](https://github.com/OpenMined/.github/blob/master/STYLEGUIDE.md) for more information.

## Contributors
See the list of [contributors](https://github.com/OpenMined/PyZPK/graphs/contributors) who participated in this project.

## License
[Apache License 2.0](https://github.com/OpenMined/PyZPK/blob/master/LICENSE)
