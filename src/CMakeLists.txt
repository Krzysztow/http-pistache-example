add_executable(http-server main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED) # requirement for pistache - probably, there's a switch to turn it off

target_link_libraries(http-server
	Threads::Threads
	CONAN_PKG::pistache)

