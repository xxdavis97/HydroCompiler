# This will be an ubuntu environment
FROM ubuntu:20.04

# Copying the machine language file to the Docker environment. Change "hello" to the name of your output
COPY out /out

# Executing the machine language file. Change "hello" to whatever you copied the file as. 
CMD ["/out"]