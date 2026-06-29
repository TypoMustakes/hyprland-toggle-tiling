{
	description = "hyprland-toggle-tiling";
	
	inputs = {
		nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    		flake-utils.url = "github:numtide/flake-utils";
	};
	
	outputs = { self, nixpkgs, flake-utils }:
		flake-utils.lib.eachDefaultSystem (system:
			let
				pkgs = nixpkgs.legacyPackages.${system};

				hyprland-toggle-tiling = pkgs.stdenv.mkDerivation {
					pname = "hyprland-toggle-tiling";
					version = "latest";
					
					src = self;
					
					nativeBuildInputs = [
						pkgs.cmake
						pkgs.pkg-config
					];
					
					buildInputs = [
						pkgs.nlohmann_json
					];
					
					cmakeFlags = [
						"-DUSE_SYSTEM_JSON=ON"
					];
					
					cmakeBuildType = "Release";
					
					meta = with pkgs.lib; {
						description = "Toggle tiling and floating modes in Hyprland globally.";
						homepage = "https://github.com/TypoMustakes/hyprland-toggle-tiling";
						license = licenses.gpl3Only;
						platforms = platforms.linux;
						mainProgram = "htt";
					};
				};
			in
			{
				packages.default = hyprland-toggle-tiling;
			});
}
