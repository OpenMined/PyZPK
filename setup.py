import os
import re
import sys
import platform
import subprocess

from setuptools import find_packages
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
from distutils.version import LooseVersion

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


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def run(self):
        try:
            out = subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError("CMake must be installed to build the following extensions: " +
                               ", ".join(e.name for e in self.extensions))

        if platform.system() == "Windows":
            cmake_version = LooseVersion(re.search(r'version\s*([\d.]+)', out.decode()).group(1))
            if cmake_version < '3.1.0':
                raise RuntimeError("CMake >= 3.1.0 is required on Windows")

        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        # required for auto-detection of auxiliary "native" libs
        if not extdir.endswith(os.path.sep):
            extdir += os.path.sep

        cmake_args = ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + extdir,
                      '-DPYTHON_EXECUTABLE=' + sys.executable]

        cfg = 'Debug' if self.debug else 'Release'
        build_args = ['--config', cfg]

        if platform.system() == "Windows":
            cmake_args += ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{}={}'.format(cfg.upper(), extdir)]
            if sys.maxsize > 2**32:
                cmake_args += ['-A', 'x64']
            build_args += ['--', '/m']
        else:
            cmake_args += ['-DCMAKE_BUILD_TYPE=' + cfg]
            build_args += ['--', '-j2']

        env = os.environ.copy()
        env['CXXFLAGS'] = '{} -DVERSION_INFO=\\"{}\\"'.format(env.get('CXXFLAGS', ''),
                                                              self.distribution.get_version())
        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)
        subprocess.check_call(['cmake', ext.sourcedir] + cmake_args, cwd=self.build_temp, env=env)
        subprocess.check_call(['cmake', '--build', '.'] + build_args, cwd=self.build_temp)

setup(
    name="pyzpk",
    long_description=long_description,
    packages=find_packages(),
    version="0.1",
    author="",
    url="https://github.com/OpenMined/PyZPK",
    download_url="https://github.com/OpenMined/PyZPK/archive/master.zip",
    install_requires=core_reqs,
    dependency_links=core_dependency_links,
    setup_requires=["pbr"],
    ext_modules=[CMakeExtension('PyZPK')],
    cmdclass=dict(build_ext=CMakeBuild),
    zip_safe=False,
)