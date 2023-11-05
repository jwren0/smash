# smash
A random string generator, just like with keyboard smashing,
but with the intent to be more secure.

# Building, installing, and more
```sh
make build       # Build the smash binary
make install     # Install smash (by default in /usr/bin)
make uninstall   # Uninstall smash
make clean       # Remove compiled binaries
make build_debug # Debug build for nerds
```

# Usage
To view the command usage, run the following:
```sh
# If only built
./smash --help

# If installed
smash --help
```

# Examples
Generating a 42 character string with
no punctuation:
```sh
smash -s 42 -p
```

Generating a string (by default 16 characters)
with only numbers:
```sh
smash -l -p -u
```

Overriding previous options to only disable
lower case letters:
```sh
smash -l -p -P
```
