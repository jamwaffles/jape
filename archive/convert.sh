#!/usr/bin/env bash

# Extract all archives and move folders into `jape-all` before running.

set -e

cd jape-all

rm -rf repo
mkdir repo
pushd repo
git init -q
popd

versions=($(fd jape --type directory --maxdepth 1))

stuff=()

for version in "${versions[@]}"; do
    version_real=$(basename $(realpath $version))

    # %Y is seconds since epoch
    latest_time=$(fd '' $version_real --type f --exclude "GPL.txt" --exclude "Textures" --exec stat -c '%Y' | sort | tail -n1)

    stuff+=("${latest_time} ${version_real}")
done

IFS=$'\n' versions=($(sort <<<"${stuff[*]}")); unset IFS

for time_and_version in "${versions[@]}"; do
echo $time_and_version

    parts=($time_and_version)

    echo "@${parts[0]}"

    # Convert epoch into ISO8601 timestamp
    time=$(date -Is -d "@${parts[0]}")
    version="${parts[1]}"

    echo "Version $version, time $time"

    # Remove any non-git files
    pushd repo
    rm -rf !repo/.git
    popd

    rsync --quiet -avzh "./$version/" repo/

    pushd repo
    git add --all
    GIT_AUTHOR_DATE="$time" GIT_COMMITTER_DATE="$time" git commit --quiet -m "$version" --date "$time"
    popd
done
