with import <nixpkgs> {};
stdenv.mkDerivation {
  pname = "sgx-enable";
  version = "0.0.1";
  src = ./.;
  installFlags = [ "PREFIX=${placeholder "out"}" ];
}
