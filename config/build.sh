#!/bin/bash

delete_build_files() {
  if [ -d ../build ]; then
      echo "Cleaning generated build files..."
      rm -rf ../build
  fi
  if [ -d ../logs ]; then
      echo "Cleaning generated log files..."
      rm -rf ../logs
  fi
}

clean() {
  #------Build Files-------
  delete_build_files
}

arg_error() {
  echo -e " Error: no arguments provided.\n "
  echo -e " Usage: $0 [ --run | --debug | --memcheck | --clean ]\n "
}

inv_arg_error() {
  echo -e " Error: Invalid argument '$1'\n "
  echo -e " Usage: $0 [ --run | --debug | --memcheck | --clean ]\n "
  exit 1;
}

setup_directories() {
  # Create directory for database files, build files, & log files
  echo "Setting up log & build directories..."
  mkdir -p ../build
  mkdir -p ../logs

  if [ ! -f ../logs/memcheck.log ]; then
      touch ../logs/memcheck.log
  fi
  if [ ! -f ../logs/errorlogs.log ]; then
      touch ../logs/errorlogs.log
  fi
}

build_project() {
  # change directory to the build directory, and build with Cmake & make
  cd ../build || { echo "Failed to change directory to 'build'"; exit 1; }
  cmake ../config/ || { echo "CMake configuration failed"; exit 1; }
  make main || { echo "Build failed"; exit 1; }
}

run_project() {
  # Run program with ./main or debug with valgrind
  if [[ "$1" == "--memcheck" ]]; then
      echo "Running valgrind to check memory usage of the program..."
      valgrind --tool=memcheck --leak-check=full --track-origins=yes --log-file=../logs/memcheck.log ./main
  elif [[ "$1" == "--debug" ]]; then
      echo "Running GDB to debug the program"
      gdb ./main
  else
      echo "Build successful. running the program..."
      ./main
  fi
}

#? Check if no argument is provided
if [[ $# -eq 0 ]]; then
    arg_error
    exit 1
fi

if [[ "$1" == "--clean" ]]; then
    clean
    exit 0
fi

if [[ "$1" == "--run" ]] || [[ "$1" == "--debug" ]] || [[ "$1" == "--memcheck" ]]; then
    delete_build_files

    setup_directories

    build_project

    run_project "$@"
else
    inv_arg_error "$@"
fi