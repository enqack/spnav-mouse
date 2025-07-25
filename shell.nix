{ pkgs ? import <nixpkgs> { config.allowUnfree = true; } }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gnumake
    glibc
    xorg.libX11
    libspnav
    libudev-zero
  ];
}
