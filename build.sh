cc="clang"
version="c17"
warnings="-Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -Wconversion -Werror"

output_dir="build"
output_name="Guess"

root_dir="-Isrc/"
files=$( find src | grep "\.c$")

mkdir -p $output_dir
$cc -std=$version $warnings $root_dir $files -o $output_dir/$output_name