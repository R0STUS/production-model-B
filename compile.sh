#!/usr/bin/env sh

# Move to the app directory
cd "$(dirname "$(readlink -f "$0")")" || exit

# Compile the app
exec g++ -o ai-b src/main.cpp "$@"
