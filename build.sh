cc="clang"
version="c17"
warnings="-Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -Wconversion -Werror"
optimization="-O2"

output_dir="build"
output_name="Guess"

root_dir="-Isrc/"
files=$( find src | grep "\.c$")

while getopts 'rdc' opt; do
    case "$opt" in
        r)
            mkdir -p $output_dir/release
            $cc -std=$version $optimization $warnings $root_dir $files -o $output_dir/release/$output_name
            ;;
        d)
            mkdir -p $output_dir/debug
            $cc -std=$version -g $warnings $root_dir $files -o $output_dir/debug/$output_name
            ;;
        c)
            rm -r $output_dir
            ;;
        \?)
            mkdir -p $output_dir/debug
            $cc -std=$version -g $warnings $root_dir $files -o $output_dir/debug/$output_name
            exit;;
    esac
done