#!/bin/bash

sudo dnf install boost, boost-devel
meson builddir
ninja-build -C builddir install