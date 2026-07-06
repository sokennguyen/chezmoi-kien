# chezmoi-kien

Personal dotfiles managed with [chezmoi](https://www.chezmoi.io/).

This repo holds both Linux desktop dotfiles and the Windows tiling-window setup for this machine. It is intended to be applied with `chezmoi`, not copied into `$HOME` by hand.

## What is managed

### Windows

- `komorebi.json` -> `~/komorebi.json`
- `dot_config/whkdrc` -> `~/.config/whkdrc`

These configure Komorebi and whkd hotkeys for workspace focus, moving windows, stacking, resizing, floating, and reloading the window manager.

### Linux / Arch

- Shell startup files: `.bashrc`, `.bash_profile`
- X startup files: `.xinitrc`, `.xprofile`
- `dwm`, `st`, `lf`, `nvim`, and `fcitx5` config under `~/.config`
- Helper scripts under `~/.local/bin`
- Arch/bootstrap scripts for package setup and local builds

## Bootstrap a new machine

Install chezmoi first.

Windows:

```powershell
winget install --id twpayne.chezmoi --exact
```

Linux:

```sh
sh -c "$(curl -fsLS get.chezmoi.io)" -- -b "$HOME/.local/bin"
```

Then initialize from GitHub:

```sh
chezmoi init https://github.com/sokennguyen/chezmoi-kien.git
chezmoi diff
chezmoi apply
```

On Windows, use the same commands from PowerShell after opening a fresh terminal so the installed `chezmoi` command is on `PATH`.

## Daily workflow

Check what chezmoi would change:

```sh
chezmoi diff
```

Apply managed files to the home directory:

```sh
chezmoi apply
```

Pull the latest repo changes and apply them:

```sh
chezmoi update
```

Edit a managed file through chezmoi:

```sh
chezmoi edit ~/.config/whkdrc
chezmoi diff
chezmoi apply
```

Add or refresh a file from the home directory into the repo:

```sh
chezmoi add ~/.config/whkdrc
chezmoi add ~/komorebi.json
```

Commit and push updates:

```sh
chezmoi cd
git status
git add README.md dot_config/whkdrc komorebi.json
git commit -m "Update dotfiles"
git push
```

## Notes

- Review `chezmoi diff` before `chezmoi apply`, especially on a new machine.
- Windows tools such as Komorebi and whkd are installed separately from these dotfiles.
- Some Linux files are desktop-specific and should be applied intentionally on non-Arch systems.
