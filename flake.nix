{
  description = "SpaceMouse to mouse control bridge";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        packages = rec {
          default = spnav-mouse;

          spnav-mouse = pkgs.stdenv.mkDerivation {
            pname = "spnav-mouse";
            version = "0.5.1";

            src = ./.;

            nativeBuildInputs = with pkgs; [
              pkg-config
            ];

            buildInputs = with pkgs; [
              xorg.libX11
              libspnav
            ];

            makeFlags = [
              "PREFIX=$(out)"
              "DESTDIR="
            ];

            meta = with pkgs.lib; {
              description = "SpaceMouse to mouse control bridge utility";
              homepage = "https://github.com/enqack/spnav-mouse";
              license = "BSD-3-Clause";
              platforms = platforms.linux;
              maintainers = [ ];
            };
          };
        };

        devShells.default = pkgs.mkShell {
          nativeBuildInputs = with pkgs; [
            pkg-config
            gcc
            gnumake
          ];

          buildInputs = with pkgs; [
            xorg.libX11
            libspnav
          ];

          # Add any environment variables needed for development
          shellHook = ''
            echo "spnav-mouse development shell"
          '';
        };
      }
    );
}
