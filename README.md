Solving problems from "Алгоритмы: теория и практика. Структуры данных" which is located  here: https://stepik.org/course/1547

How to compile:
```shell
mkdir -p ./builddir ; cd builddir/ ; env CXX=clang++ meson setup --wipe ; env CXX=clang++ meson compile --verbose ; cd ../
```

How to run tests (task 01 as example):
```shell
sh test_runner.sh ./builddir/01 ./01/tests
```