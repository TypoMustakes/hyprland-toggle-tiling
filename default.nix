{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation rec {
	pname = "hyprland-toggle-tiling";
	version = "1.4.2";
	
	src = pkgs.fetchFromGitHub {
		owner = "TypoMustakes";
		repo = "hyprland-toggle-tiling";
		rev = "v${version}";
		sha256 = "sha256-NxNT2pZ4zWkF5JPPUcqJl+VFOIHyxq4ZsACg9GsWnwM=";
	};
	
	nativeBuildInputs = [
		pkgs.cmake
		pkgs.pkg-config
	];
	
	buildInputs = [
		pkgs.hyprland
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
}
