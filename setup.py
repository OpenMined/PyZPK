import os
from setuptools import find_packages
from setuptools import setup

# reads a file
def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()


# get the requirements from text file "requirements.txt"
def get_requirements(req_file):
    """Read requirements file and return packages and git repos separately"""
    requirements = []
    dependency_links = []
    lines = read(req_file).split("\n")
    for line in lines:
        if line.startswith("git+"):
            dependency_links.append(line)
        else:
            requirements.append(line)
    return requirements, dependency_links


REQ_DIR = os.path.dirname(os.path.abspath(__file__))
core_reqs, core_dependency_links = get_requirements(
    os.path.join(REQ_DIR, "requirements.txt")
)
long_description = read("README.md")


setup(
    name="pyzpk",
    long_description=long_description,
    packages=find_packages(),
    version="0.1",
    author="",
    url="https://github.com/Benardi/PyZPK",
    download_url="https://github.com/Benardi/PyZPK/archive/master.zip",
    install_requires=core_reqs,
    dependency_links=core_dependency_links,
    setup_requires=["pbr"],
)
