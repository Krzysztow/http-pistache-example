add_executable(http-server main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED) # requirement for pistache - probably, there's a switch to turn it off

target_compile_features(http-server PUBLIC cxx_std_17)
target_link_libraries(http-server
	Threads::Threads
	CONAN_PKG::pistache
	CONAN_PKG::argparse)

