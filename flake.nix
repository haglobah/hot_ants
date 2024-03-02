{
  description = "A project with a devshell.";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    devshell.url = "github:numtide/devshell";
    devshell.inputs.nixpkgs.follows = "nixpkgs";
  };

  outputs = inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      imports = [
        inputs.devshell.flakeModule
        # To import a flake module
        # 1. Add foo to inputs
        # 2. Add foo as a parameter to the outputs function
        # 3. Add here: foo.flakeModule

      ];
      systems = [ "x86_64-linux" "aarch64-linux" "aarch64-darwin" "x86_64-darwin" ];
      perSystem = { config, self', inputs', pkgs, system, ... }: {
        # Per-system attributes can be defined here. The self' and inputs'
        # module parameters provide easy access to attributes of the same
        # system.

        # Equivalent to  inputs'.nixpkgs.legacyPackages.hello;
        packages.default = pkgs.stdenv.mkDerivation {
          name = "water_ants";
          src = ./.;
          buildInputs = [ # available at runtime
            # pkgs.ncurses
          ];

          nativeBuildInputs = [ # available at build time
            pkgs.cmake
            pkgs.gcc
            pkgs.gnumake
          ];

          phases = [
            "unpackPhase"
            "buildPhase"
            "installPhase"
          ];

          buildPhase = ''
            cmake -B build -S .
            cmake --build build
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp ./build/water_ants $out/bin
          '';
        };
        devshells.default = {
          env = [
            # { name = "MY_ENV_VAR"; value = "SOTRUE"; }
          ];
          packages = [
            pkgs.gnumake
            pkgs.cmake
            pkgs.rocmPackages.llvm.clang
            (pkgs.python311.withPackages (python-pkgs: [
              python-pkgs.numpy
              # python-pkgs.cv2
              python-pkgs.glob2
            ]))
          ];
          commands = [
            # { name = "devshell-test"; command = "echo 'Is this working?'"; help = "A command to test devshell";}
          ];
        };
      };
      flake = {
        # The usual flake attributes can be defined here, including system-
        # agnostic ones like nixosModule and system-enumerating ones, although
        # those are more easily expressed in perSystem.

      };
    };
}
