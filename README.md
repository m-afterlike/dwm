# DWM Configuration

Personal fork of [dwm](https://dwm.suckless.org/). Includes custom patches and configurations.

## Installation

### 1. Clone the repository:
```bash
git clone https://github.com/m-afterlike/dwm.git
cd dwm
```

### 2. Install DWM:
```bash
cd dwm
sudo make clean install
```

### 3. Install DWMBlocks:
```bash
cd ../dwmblocks
sudo make clean install
```

### 4. Install and Configure Picom
```bash
yay -S picom-git
cp -r ../picom ~/.config/
```