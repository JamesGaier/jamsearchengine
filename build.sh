#!/bin/bash

meson builddir
ninja-build -C builddir install