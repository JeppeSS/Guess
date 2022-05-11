cc="clang"
version="-std=c17"
warnings="-Wall -Wextra"

root_dir="-Isrc/"
output_dir="build"

mkdir -p $output_dir
$cc $version $warnings $root_dir src/core/random/hgl_rand.c src/core/string/hgl_str.c src/core/console/hgl_input.c src/game/logic/guess_state.c src/game/guessing.c src/run/main.c -o $output_dir/Guess