includes = include_directories('../')

e_test_new = executable(
  'test-new',
  'new.c',
  include_directories: includes,
  link_with: libcgol,
)

e_test_getset = executable(
  'test-getset',
  'getset.c',
  include_directories: includes,
  link_with: libcgol,
)

test(
  'new',
  e_test_new
)

test(
  'getset',
  e_test_getset
)
