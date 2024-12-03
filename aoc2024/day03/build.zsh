# build.zsh
#!/bin/sh

BUILD_TYPE=Release  
while getopts "dr" opt; do  
    case $opt in
        d)
            BUILD_TYPE=Debug
            ;;
        r)
            BUILD_TYPE=Release
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            exit 1
            ;;
    esac
done
cd build
echo "Building in $BUILD_TYPE mode..."
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE .. && make
cd ..
