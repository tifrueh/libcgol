includes = include_directories('../')

e_test_new = executable(
  'test-new',
  'new.c',
  include_directories: includes,
  link_with: libcgol,
)

test(
  'new',
  e_test_new
)
