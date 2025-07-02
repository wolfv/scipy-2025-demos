# Add the source directory submodule
add_subdirectory(src)

# Install the crispy-doom executable as crispy doom itself doesnt provide any 
# install instructions.
install(TARGETS crispy-doom)
