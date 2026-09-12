%:%.cpp
	g++ $< -std=c++20 -O2 \
		-Wall -Wextra -Warray-bounds -Wconversion -g \
		-o $@

%-asan:%.cpp
	g++ $< -pedantic -std=c++20 -O1 \
		-pipe -Wall -Wextra -Wshadow -Wconversion \
		-fsanitize=address,undefined -fno-omit-frame-pointer -fsanitize-address-use-after-scope \
		-fstack-protector-strong -g \
		-o $@ -lm
