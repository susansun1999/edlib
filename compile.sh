target_file="cal_ed"

c++ -c edlib/src/edlib.cpp -o edlib.o -I edlib/include
gcc -c ${target_file}.cpp -o ${target_file}.o -I edlib/include
c++ ${target_file}.o edlib.o -o ${target_file}
