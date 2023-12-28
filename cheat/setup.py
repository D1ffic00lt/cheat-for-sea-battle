from setuptools import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

source_files = ["./gamecalculator/calculator.pyx"]

ext_modules = [
    Extension("gamecalculator", source_files, language="c++", extra_compile_args=["-std=c++17"])
]

setup(
    name="gamecalculator functions",
    cmdclass={"build_ext": build_ext},
    ext_modules=ext_modules
)
print("BUILD FINISHED")
