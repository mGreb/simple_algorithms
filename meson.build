project('simple_algorithms', 'cpp', version: '0.1',
    default_options : ['cpp_std=c++23','warning_level=3'])

add_project_arguments('-Wall', '-Werror', '-Wpedantic', '-Wconversion', language: 'cpp')

    sanitizer_flags = [
  '-fsanitize=signed-integer-overflow',
  '-fsanitize=unsigned-integer-overflow',
  '-fsanitize=integer',
  '-fno-sanitize-recover=all',
  '-fsanitize=undefined',
  '-fno-omit-frame-pointer'
]

add_project_arguments(sanitizer_flags, language: 'cpp')
add_project_link_arguments(sanitizer_flags, language: 'cpp')

executable('01', '01/01.cpp')
executable('02', '02/02.cpp')
executable('03', '03/03.cpp')
executable('04', '04/04.cpp')
executable('05', '05/05.cpp')
executable('06', '06/06.cpp')
executable('07', '07/07.cpp')
executable('08', '08/08.cpp')
executable('09', '09/09.cpp')
executable('10', '10/10.cpp')
executable('11', '11/11.cpp')
executable('12', '12/12.cpp')
executable('13', '13/13.cpp')
executable('14', '14/14.cpp')
