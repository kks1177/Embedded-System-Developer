
from setuptools import setup, find_packages
# from distutils.core import setup

import os

PACKAGE_NAME = "PyCamera"
PACKAGE_VERSION = "1.8.1"
PACKAGE_AUTHOR = "Cheongho Kim"
PACKAGE_AUTHOR_EMAIL = "mokpo4550@gmail.com"
PACKAGE_DESCRIPTION = "PyCamera Package"
PACKAGE_URL = ""
PACKAGE_LICENSE=""

PLATFORM = ["windows", "linux"]
REQUIRES_PYTHON = '>=3'

current_path = os.path.abspath(os.path.dirname(__file__))
try:
    with open(os.path.join(current_path, "requirements.txt"), encoding="utf-8") as f:
        REQUIRED_PACKAGES = f.read().split("\n")
except:
    REQUIRED_PACKAGES = []

setup(
    name=PACKAGE_NAME,
    version=PACKAGE_VERSION,
    author=PACKAGE_AUTHOR,
    author_email=PACKAGE_AUTHOR_EMAIL,
    description=PACKAGE_DESCRIPTION,
    url=PACKAGE_URL,
    python_requires = REQUIRES_PYTHON,
    license=PACKAGE_LICENSE,
    platforms = PLATFORM,
    packages=find_packages(),
    include_package_data = True,
    zip_safe=False,
    install_requires=REQUIRED_PACKAGES
)
