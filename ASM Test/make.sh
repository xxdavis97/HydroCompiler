open -a Docker
nasm -f elf64 test.asm -o test.o
x86_64-elf-ld test.o -o test
docker build --quiet -t test .
docker run -it --rm test
# shows exit code of last command ran which for this one is important
echo $?