import distutils
from distutils.core import setup, Extension
import distutils.sysconfig
import numpy


cfg_vars = distutils.sysconfig.get_config_vars()
for key, value in cfg_vars.items():
    if type(value) == str:        
        cfg_vars[key] = value.replace("-O2", "")
        # cfg_vars[key] = value.replace("-O3", "")

for key, value in cfg_vars.items():
    if type(value) == str:        
        cfg_vars[key] = value.replace("-DNDEBUG", "")

cfg_vars = distutils.sysconfig.get_config_vars()
for key, value in cfg_vars.items():
    if type(value) == str:        
        cfg_vars[key] = value.replace("-Wstrict-prototypes", "")


try:
    numpy_include = numpy.get_include()
except AttributeError:
    numpy_include = numpy.get_numpy_include()
print(numpy_include)

setup(
    name = "convex_sampler",
    author = 'Alban Gossard',
    license='MIT License',  
    version = "1.0",
    ext_modules = [
        Extension(
            "_convex_sampler",
            libraries=["gmp","gomp"],
            extra_compile_args = ["-g","-ffast-math","-fopenmp","-std=c++11"],
            sources = ["convex_sampler.i","convex_sampler.cxx"],
            swig_opts=["-c++"],
            include_dirs = [numpy_include]
        )
    ]
)