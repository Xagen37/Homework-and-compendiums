from setuptools import find_packages, setup

setup(
    name = 'xagen37_fast_hist_conflict',
    version = '0.3.0',
    description = 'Dummy module for doing lab.',
    author = 'Alexander Sofrygin',
    author_email = 'xagen37@gmail.com',
    packages = find_packages(),
    install_requires = ['numpy<=1.19'],
    setup_requires = ['numpy<=1.19']
)