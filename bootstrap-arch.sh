#!/usr/bin/env bash
set -euo pipefail

USER_NAME="${USER_NAME:-test}"
REPO_URL="${REPO_URL:-https://github.com/sokennguyen/chezmoi-kien.git}"

pacman -Syu --noconfirm
pacman -S --noconfirm sudo git chezmoi

if ! id "$USER_NAME" >/dev/null 2>&1; then
  useradd -m -s /bin/bash "$USER_NAME"
  echo "$USER_NAME ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers
fi

su - "$USER_NAME" -c "chezmoi init --apply \"$REPO_URL\""
su - "$USER_NAME" -c "chezmoi status"
