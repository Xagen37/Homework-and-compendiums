from setuptools import find_packages, setup

setup(
    name = 'xagen37_fast_hist',
    version = '0.6.0',
    description = 'Dummy module for doing lab.',
    author = 'Alexander Sofrygin',
    author_email = 'xagen37@gmail.com',
    packages = find_packages(),
    install_requires = ['numpy>=1.20'],
    setup_requires = ['numpy>=1.20']
)