#!/usr/bin/env bash
set -euo pipefail

file="$1"
width="${2:-80}"
height="${3:-24}"

if [ -d "$file" ]; then
  ls -lah --group-directories-first --color=always -- "$file" | sed -n '1,200p'
  exit 0
fi

mime="$(file --dereference --brief --mime-type -- "$file")"

case "$mime" in
  image/*)
    chafa --animate=off --size="${width}x${height}" -- "$file" || file -Lb -- "$file"
    ;;
  text/*|application/json|application/xml|application/x-shellscript|inode/x-empty)
    sed -n '1,200p' -- "$file"
    ;;
  *)
    file -Lb -- "$file"
    ;;
esac
