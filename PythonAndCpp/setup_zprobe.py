from setuptools import setup, Extension

setup(name='zprobe',
      version='1.0',
      description='Zed communication package',
      author='Zed',
      author_email='',
      url='',
      long_description='This is really just a demo package.',
      ext_modules=[
          Extension(
                  'zprobe',
                  ['z_comm.c'],
                  include_dirs=['/usr/include/python3.6'],
                  libraries=['zprobe_impl'],
                  library_dirs=['./src/cpp/.out'],
                  extra_compile_args=["-fPIC"]
          )
      ]
      )
