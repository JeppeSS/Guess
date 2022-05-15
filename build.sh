cc="clang"
version="c17"
warnings="-Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -Wconversion -Werror"
optimization="-O2"

output_dir="build"
output_name="Guess"

root_dir="-Isrc/"
files=$( find src | grep "\.c$")


should_build_release=false
should_build_debug=false
should_clean=false
should_execute=false
while getopts 'rdce' opt; do
    case "$opt" in
        r)
            should_build_release=true;
            ;;
        d)
            should_build_debug=true
            ;;
        c)
            should_clean=true
            ;;
        e)
            should_execute=true
            ;;
        \?)
            should_clean=true
            should_build_debug=true
            should_build_release=true
            ;;
    esac
done


build_application () {
    if [ "$should_clean" = true ] ; then
        rm -rf $output_dir
    fi

    if [ "$should_build_debug" = true ] ; then
        mkdir -p $output_dir/debug
        $cc -std=$version -g $warnings $root_dir $files -o $output_dir/debug/$output_name
    fi

    if [ "$should_build_release" = true ] ; then
        mkdir -p $output_dir/release
        $cc -std=$version $optimization $warnings $root_dir $files -o $output_dir/release/$output_name
    fi

    if [ "$should_execute" = true ] ; then
        if [ "$should_build_debug" = true ] ; then
            ./$output_dir/debug/$output_name
            exit
        fi

        if [ "$should_build_release" = true ] ; then
            ./$output_dir/release/$output_name
            exit
        fi
    fi
}


build_application