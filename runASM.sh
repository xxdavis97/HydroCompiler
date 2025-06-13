docker build --quiet -t out .
docker run -it --rm out
# shows exit code of last command ran which for this one is important
echo $?