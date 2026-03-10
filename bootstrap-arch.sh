#!/usr/bin/env bash
set -euo pipefail

USER_NAME="${USER_NAME:-${SUDO_USER:-${USER:-test}}}"
REPO_URL="${REPO_URL:-https://github.com/sokennguyen/chezmoi-kien.git}"

# bail if not Arch (keep it simple)
if [ -f /etc/os-release ]; then . /etc/os-release; fi
if [ "${ID:-}" != "arch" ]; then
  echo "This bootstrap is Arch-only (ID=${ID:-unknown}); aborting."
  exit 1
fi

pacman -Syu --noconfirm
pacman -S --noconfirm sudo git curl chezmoi

if ! id "$USER_NAME" >/dev/null 2>&1; then
  useradd -m -s /bin/bash "$USER_NAME"
  echo "$USER_NAME ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers
fi

su - "$USER_NAME" -c "chezmoi init --apply \"$REPO_URL\""
su - "$USER_NAME" -c "chezmoi status"
