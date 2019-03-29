#!/bin/bash

if [ "$1" = "" ]; then
    premake5 gmake && make Sandbox
fi

if [ "$1" = "debug" ]; then
    premake5 gmake && make config=debug Sandbox
fi

if [ "$1" = "release" ]; then
    premake5 gmake && make config=release Sandbox
fi
