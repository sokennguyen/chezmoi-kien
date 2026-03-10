#!/usr/bin/env bash
set -euo pipefail

build() {
  local dir="$1"
  local path="$HOME/.config/$dir"
  [ -d "$path" ] || return 0
  if command -v make >/dev/null 2>&1; then
    make -C "$path" clean >/dev/null 2>&1 || true
    make -C "$path"
    if command -v sudo >/dev/null 2>&1; then
      sudo make -C "$path" install
    else
      make -C "$path" install
    fi
  else
    echo "make not found; skipping $dir build" >&2
  fi
}

build dwm
build st
