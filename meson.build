project(
  'libcgol',
  'c',
  license: 'MIT',
  license_files: 'LICENSE.md',
  meson_version: '>=1.1.0',
  version: '0.0.0'
)

# Try to get version string from git or use project version if that fails.
git_describe = run_command('git', 'describe', '--always', '--dirty=-d', check: false)
git_describe_out = git_describe.stdout().strip()

version = meson.project_version()

if git_describe_out != ''
  version = git_describe_out.substring(1)
endif

# Initialise the configuration data object.
conf_data = configuration_data()
conf_data.set(
  'version', version
)

# Configure header file.
configure_file(
  input: 'cgol.h',
  output: 'cgol.h',
  configuration: conf_data
)

# Configure library target.
library(
  'cgol',
  'error.c',
  'free.c',
  'getset.c',
  'new.c',
  'renew.c',
  'tick.c',
  version: meson.project_version(),
  install: true
)
