FROM ubuntu:24.04

RUN apt-get update && apt-get install -y g++ make

WORKDIR src/

COPY . .

RUN g++ -g -std=c++11 MazePathFinder.cpp -o MazePathFinder.exe

CMD ["./MazePathFiner"]