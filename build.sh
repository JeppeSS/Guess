cc="clang"
version="-std=c17"
warnings="-Wall -Wextra"

output_dir="build"
output_name="Guess"

root_dir="-Isrc/"
files=$( find src | grep "\.c$")

mkdir -p $output_dir
$cc $version $warnings $root_dir $files -o $output_dir/$output_name