# Framebot - 0.1.0 [![Build Status](https://travis-ci.org/giancarlopro/framebot.svg?branch=dev)](https://travis-ci.org/giancarlopro/framebot) [![Open Source Helpers](https://www.codetriage.com/giancarlopro/framebot/badges/users.svg)](https://www.codetriage.com/giancarlopro/framebot) [![Documentation Status](https://readthedocs.org/projects/framebot/badge/?version=latest)](http://framebot.readthedocs.io/pt/latest/?badge=latest)

This is the official repository for Framebot.

## Building from source

### Ubuntu/Debian
First you need to install the dependencies

```
# apt install jansson openssl libcurl4-openssl-dev
```

then you use cmake to create the build files
```
mkdir build
cd build
cmake ..
```

and use make to build and install
```
make
make install
```

### FreeBSD
The required packages can be installed using either ports:

```
make -C /usr/ports/{cmake,jansson,openssl,curl} install clean
```

Or binary packages:

```
pkg install cmake jansson openssl curl
```

After that, cd into the framebot repository continue the same way as above:

```
mkdir build
cd build
cmake ..
make
make install
```

## Usage

See our [Examples](examples/) folder.

## Contributing

If you want to contribute to the project, follow the instructions on [CONTRIBUTING](CONTRIBUTING.md)
