from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext
import pybind11

# The main interface is through Pybind11Extension.
ext_modules = [
    Pybind11Extension(
        "fireworks_py",
        [
            "python/bindings.cpp",
            "src/fireworks.cpp",
        ],
        include_dirs=[
            # Path to pybind11 headers
            pybind11.get_include(),
            "src",
        ],
        language='c++',
        cxx_std=14,
    ),
]

setup(
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)
